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
#ifndef QTRUBIKSCLOCKMAINDIALOG_H
#define QTRUBIKSCLOCKMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtRubiksClockMainDialog;
}

namespace ribi {
namespace ruco {

///The dialog in which the Rubik's Clock is played
class QtRubiksClockMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT //!OCLINT

public:
  explicit QtRubiksClockMainDialog(QWidget *parent = nullptr);
  QtRubiksClockMainDialog(const QtRubiksClockMainDialog&) = delete;
  QtRubiksClockMainDialog& operator=(const QtRubiksClockMainDialog&) = delete;
  ~QtRubiksClockMainDialog() noexcept;

private slots:
  void on_button_flip_clicked();
  void on_button_scramble_clicked();
  void UpdateStatus();

private:
  Ui::QtRubiksClockMainDialog *ui;
};

} //~namespace ruco
} //~namespace ribi

#endif // QTRUBIKSCLOCKMAINDIALOG_H
