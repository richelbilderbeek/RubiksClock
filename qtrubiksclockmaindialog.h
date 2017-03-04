#ifndef QTRUBIKSCLOCKMAINDIALOG_H
#define QTRUBIKSCLOCKMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtRubiksClockMainDialog;
}

namespace ribi {
namespace ruco {

class QtRubiksClockMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT //!OCLINT
  
public:
  explicit QtRubiksClockMainDialog(QWidget *parent = 0);
  QtRubiksClockMainDialog(const QtRubiksClockMainDialog&) = delete;
  QtRubiksClockMainDialog& operator=(const QtRubiksClockMainDialog&) = delete;
  ~QtRubiksClockMainDialog() noexcept;
  
private slots:
  void keyPressEvent(QKeyEvent *);
  void on_button_flip_clicked();
  void resizeEvent(QResizeEvent *);

private:
  Ui::QtRubiksClockMainDialog *ui;
};

} //~namespace ruco
} //~namespace ribi

#endif // QTRUBIKSCLOCKMAINDIALOG_H
