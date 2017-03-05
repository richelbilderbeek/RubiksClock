#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtrubiksclockmenudialog.h"

#include <QKeyEvent>

#include "qtaboutdialog.h"
#include "qtdialwidget.h"
#include "qthideandshowdialog.h"
#include "qtrubiksclockmaindialog.h"
#include "qtrubiksclockwidget.h"
#include "qttogglebuttonwidget.h"
#include "rubiksclockmenudialog.h"
#include "ui_qtrubiksclockmenudialog.h"
#pragma GCC diagnostic pop

ribi::ruco::QtRubiksClockMenuDialog::QtRubiksClockMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtRubiksClockMenuDialog)
{
  ui->setupUi(this);
}

ribi::ruco::QtRubiksClockMenuDialog::~QtRubiksClockMenuDialog() noexcept
{
  delete ui;
}

void ribi::ruco::QtRubiksClockMenuDialog::keyPressEvent(QKeyEvent * e)
{
  if (e->key()  == Qt::Key_Escape) close();
}

void ribi::ruco::QtRubiksClockMenuDialog::on_button_about_clicked()
{
  About a = MenuDialog().GetAbout();
  a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  a.AddLibrary("QtRubiksClockWidget version: " + QtRubiksClockWidget::GetVersion());
  a.AddLibrary("QtToggleButtonWidget version: " + QtToggleButtonWidget::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::ruco::QtRubiksClockMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::ruco::QtRubiksClockMenuDialog::on_button_start_clicked()
{
  QtRubiksClockMainDialog d;
  ShowChild(&d);
}
