#pragma GCC diagnostic push

#include <QApplication>
#include "qtrubiksclockmenudialog.h"

#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::ruco::QtRubiksClockMenuDialog d;
  d.show();
  return a.exec();
}
