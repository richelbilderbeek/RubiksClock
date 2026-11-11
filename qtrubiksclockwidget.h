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
#ifndef QTRUBIKSCLOCKWIDGET_H
#define QTRUBIKSCLOCKWIDGET_H

#include <QRectF>
#include <QWidget>

#include "rubiksclock.h"

namespace ribi {
namespace ruco {

///Displays a Rubik's Clock and lets the user play with it:
///  - click on a corner dial to turn its wheel clockwise
///  - right-click or Shift-click on a corner dial to turn it counter-clockwise
///  - click on a peg to toggle it
class QtRubiksClockWidget : public QWidget
{
  Q_OBJECT //!OCLINT

public:
  explicit QtRubiksClockWidget(QWidget * parent = nullptr);

  ///Show the other side of the clock
  void Flip();

  const Clock& GetClock() const noexcept { return m_clock; }
  bool GetDisplayFront() const noexcept { return m_display_front; }

  ///Do random moves
  void Scramble(std::mt19937& rng);

signals:
  ///Emitted when the clock is changed by the user
  void clock_changed();

protected:
  void mousePressEvent(QMouseEvent * e) override;
  void paintEvent(QPaintEvent * e) override;

private:
  Clock m_clock;
  bool m_display_front;

  ///The square the clock is drawn in
  QRectF GetClockRect() const noexcept;

  ///The rectangle of a dial, x and y as seen from the side shown
  QRectF GetDialRect(const int x, const int y) const noexcept;

  ///The rectangle of a peg, x and y as seen from the side shown
  QRectF GetPegRect(const int x, const int y) const noexcept;
};

} //~namespace ruco
} //~namespace ribi

#endif // QTRUBIKSCLOCKWIDGET_H
