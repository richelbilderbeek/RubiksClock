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
#include "qtrubiksclockmaindialog.h"

#include <random>

#include <QRandomGenerator>

#include "ui_qtrubiksclockmaindialog.h"

ribi::ruco::QtRubiksClockMainDialog::QtRubiksClockMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtRubiksClockMainDialog)
{
  ui->setupUi(this);
  QObject::connect(
    ui->clock,
    &QtRubiksClockWidget::clock_changed,
    this,
    &QtRubiksClockMainDialog::UpdateStatus
  );
  on_button_scramble_clicked();
}

ribi::ruco::QtRubiksClockMainDialog::~QtRubiksClockMainDialog() noexcept
{
  delete ui;
}

void ribi::ruco::QtRubiksClockMainDialog::on_button_flip_clicked()
{
  ui->clock->Flip();
  UpdateStatus();
}

void ribi::ruco::QtRubiksClockMainDialog::on_button_scramble_clicked()
{
  std::mt19937 rng(QRandomGenerator::global()->generate());
  ui->clock->Scramble(rng);
  UpdateStatus();
}

void ribi::ruco::QtRubiksClockMainDialog::UpdateStatus()
{
  const QString side{ui->clock->GetDisplayFront() ? "Front" : "Back"};
  if (ui->clock->GetClock().IsSolved())
  {
    ui->label_status->setText(side + ": solved!");
  }
  else
  {
    ui->label_status->setText(side + ": make all dials point up");
  }
}
