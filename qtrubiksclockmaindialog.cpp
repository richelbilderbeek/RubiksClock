#pragma GCC diagnostic push

#include "qtrubiksclockmaindialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "ui_qtrubiksclockmaindialog.h"
#pragma GCC diagnostic pop

ribi::ruco::QtRubiksClockMainDialog::QtRubiksClockMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtRubiksClockMainDialog)
{
  ui->setupUi(this);

  for (int i=0; i!=10000; ++i)
  {
    const int x = (std::rand() >> 4);
    switch (x % 8)
    {
      case 0: ui->clock->GetWidget()->GetRubiksClock()->TogglePeg(Side::topLeft); break;
      case 1: ui->clock->GetWidget()->GetRubiksClock()->TogglePeg(Side::topRight); break;
      case 2: ui->clock->GetWidget()->GetRubiksClock()->TogglePeg(Side::bottomLeft); break;
      case 3: ui->clock->GetWidget()->GetRubiksClock()->TogglePeg(Side::bottomRight); break;
      case 4: ui->clock->GetWidget()->GetRubiksClock()->TurnWheel(Side::topLeft,(x >> 4) % 11); break;
      case 5: ui->clock->GetWidget()->GetRubiksClock()->TurnWheel(Side::topRight,(x >> 4) % 11); break;
      case 6: ui->clock->GetWidget()->GetRubiksClock()->TurnWheel(Side::bottomLeft,(x >> 4) % 11); break;
      case 7: ui->clock->GetWidget()->GetRubiksClock()->TurnWheel(Side::bottomRight,(x >> 4) % 11); break;
    }
  }
}

ribi::ruco::QtRubiksClockMainDialog::~QtRubiksClockMainDialog() noexcept
{
  delete ui;
}

void ribi::ruco::QtRubiksClockMainDialog::keyPressEvent(QKeyEvent * e)
{
  if (e->key()  == Qt::Key_Escape) close();
}

void ribi::ruco::QtRubiksClockMainDialog::on_button_flip_clicked()
{
  ui->clock->GetWidget()->Flip();
}

void ribi::ruco::QtRubiksClockMainDialog::resizeEvent(QResizeEvent *)
{
  //const QRectF r(ui->widget_hold_clock->geometry().adjusted(0.0,0.0,-16.0,-16.0));
  const QRectF r(ui->clock->geometry());
  ui->clock->GetWidget()->SetGeometry(r.x(),r.y(),r.width(),r.height());
}
