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
#include "qtrubiksclockmenudialog.h"

#include <QMessageBox>

#include "qtrubiksclockmaindialog.h"
#include "rubiksclock.h"
#include "ui_qtrubiksclockmenudialog.h"

ribi::ruco::QtRubiksClockMenuDialog::QtRubiksClockMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtRubiksClockMenuDialog)
{
  ui->setupUi(this);
#ifdef Q_OS_WASM
  // A web page cannot be quit
  ui->button_quit->hide();
#endif
}

ribi::ruco::QtRubiksClockMenuDialog::~QtRubiksClockMenuDialog() noexcept
{
  delete ui;
}

void ribi::ruco::QtRubiksClockMenuDialog::on_button_about_clicked()
{
  QMessageBox * const box{new QMessageBox(this)};
  box->setAttribute(Qt::WA_DeleteOnClose);
  box->setWindowTitle("About Rubik's Clock");
  box->setTextFormat(Qt::RichText);
  box->setText(
    "<b>Rubik's Clock</b> version " + QString::fromStdString(GetVersion()) + "<br>"
    "A Rubik's Clock simulator<br>"
    "Copyright 2007-2026 Richel Bilderbeek<br>"
    "<a href=\"https://github.com/richelbilderbeek/RubiksClock\">"
    "https://github.com/richelbilderbeek/RubiksClock</a><br>"
    "Licensed under the GPL-3.0"
  );
  box->setDetailedText(QString::fromStdString(
    [](){
      std::string s;
      for (const auto& line: GetVersionHistory()) s += line + "\n";
      return s;
    }()
  ));
  box->open();
}

void ribi::ruco::QtRubiksClockMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::ruco::QtRubiksClockMenuDialog::on_button_start_clicked()
{
  QtRubiksClockMainDialog * const d{new QtRubiksClockMainDialog(this)};
  d->setAttribute(Qt::WA_DeleteOnClose);
  ShowChild(d);
}
