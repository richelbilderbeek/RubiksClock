//---------------------------------------------------------------------------
/*
RubiksClock. Rubik's Clock game.
Copyright (C) 2007-2026 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
#include "qtrubiksclockwidget.h"

#include <algorithm>
#include <cmath>

#include <QMouseEvent>
#include <QPainter>

ribi::ruco::QtRubiksClockWidget::QtRubiksClockWidget(QWidget * parent)
  : QWidget(parent),
    m_clock{},
    m_display_front{true}
{
  setMinimumSize(300, 300);
}

void ribi::ruco::QtRubiksClockWidget::Flip()
{
  m_display_front = !m_display_front;
  update();
}

QRectF ribi::ruco::QtRubiksClockWidget::GetClockRect() const noexcept
{
  const double size{static_cast<double>(std::min(width(), height()))};
  return QRectF(
    (width() - size) / 2.0,
    (height() - size) / 2.0,
    size,
    size
  );
}

QRectF ribi::ruco::QtRubiksClockWidget::GetDialRect(const int x, const int y) const noexcept
{
  //The dials are on a 3x3 grid inside the clock, with a margin
  const QRectF r{GetClockRect()};
  const double margin{r.width() * 0.1};
  const double cell{(r.width() - (2.0 * margin)) / 3.0};
  const double dial{cell * 0.8};
  return QRectF(
    r.left() + margin + (x * cell) + ((cell - dial) / 2.0),
    r.top() + margin + (y * cell) + ((cell - dial) / 2.0),
    dial,
    dial
  );
}

QRectF ribi::ruco::QtRubiksClockWidget::GetPegRect(const int x, const int y) const noexcept
{
  //The pegs are between the dials
  const QRectF r{GetClockRect()};
  const double margin{r.width() * 0.1};
  const double cell{(r.width() - (2.0 * margin)) / 3.0};
  const double peg{cell * 0.3};
  return QRectF(
    r.left() + margin + ((x + 1) * cell) - (peg / 2.0),
    r.top() + margin + ((y + 1) * cell) - (peg / 2.0),
    peg,
    peg
  );
}

void ribi::ruco::QtRubiksClockWidget::mousePressEvent(QMouseEvent * e)
{
  const QPointF pos{e->position()};
  const bool counter_clockwise{
       e->button() == Qt::RightButton
    || (e->modifiers() & Qt::ShiftModifier)
  };
  for (int x=0; x!=2; ++x)
  {
    for (int y=0; y!=2; ++y)
    {
      //x as seen from the front
      const int front_x{m_display_front ? x : 1 - x};
      const Side side{ToSide(front_x, y)};
      const QRectF peg{GetPegRect(x, y)};
      if (peg.contains(pos))
      {
        m_clock.TogglePeg(side);
        update();
        emit clock_changed();
        return;
      }
      const QRectF dial{GetDialRect(x * 2, y * 2)};
      const QPointF d{pos - dial.center()};
      if (std::hypot(d.x(), d.y()) <= dial.width() / 2.0)
      {
        //Clockwise as seen from the side shown
        const int steps_seen{counter_clockwise ? -1 : 1};
        m_clock.TurnWheel(side, m_display_front ? steps_seen : -steps_seen);
        update();
        emit clock_changed();
        return;
      }
    }
  }
}

void ribi::ruco::QtRubiksClockWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  const bool front{m_display_front};

  //The body
  painter.setPen(QPen(Qt::black, 2));
  painter.setBrush(front ? QColor(127, 127, 196) : QColor(96, 96, 196));
  painter.drawEllipse(GetClockRect().adjusted(1, 1, -1, -1));

  //The dials
  const QColor dial_color{front ? QColor(196, 196, 255) : QColor(128, 128, 255)};
  for (int x=0; x!=3; ++x)
  {
    for (int y=0; y!=3; ++y)
    {
      const QRectF r{GetDialRect(x, y)};
      const double radius{r.width() / 2.0};
      painter.setPen(QPen(Qt::black, 1));
      painter.setBrush(dial_color);
      painter.drawEllipse(r);

      //The 12 o'clock marker
      painter.setBrush(Qt::red);
      painter.setPen(Qt::NoPen);
      const double marker{radius * 0.15};
      painter.drawEllipse(
        QPointF(r.center().x(), r.top() + (marker * 1.5)),
        marker / 2.0,
        marker / 2.0
      );

      //The hand
      const double pi{std::acos(-1.0)};
      const double angle{m_clock.GetTime(front, x, y) * 2.0 * pi / 12.0};
      const QPointF tip{
        r.center().x() + (std::sin(angle) * radius * 0.75),
        r.center().y() - (std::cos(angle) * radius * 0.75)
      };
      painter.setPen(QPen(Qt::black, std::max(2.0, radius * 0.12), Qt::SolidLine, Qt::RoundCap));
      painter.drawLine(r.center(), tip);
    }
  }

  //The pegs: a pressed peg is drawn small and dark
  for (int x=0; x!=2; ++x)
  {
    for (int y=0; y!=2; ++y)
    {
      const QRectF r{GetPegRect(x, y)};
      const bool pressed{m_clock.IsPegPressed(front, x, y)};
      painter.setPen(QPen(Qt::black, 1));
      if (pressed)
      {
        painter.setBrush(QColor(128, 128, 0));
        const double d{r.width() * 0.2};
        painter.drawEllipse(r.adjusted(d, d, -d, -d));
      }
      else
      {
        painter.setBrush(QColor(255, 255, 0));
        painter.drawEllipse(r);
      }
    }
  }
}

void ribi::ruco::QtRubiksClockWidget::Scramble(std::mt19937& rng)
{
  m_clock.Scramble(rng);
  update();
}
