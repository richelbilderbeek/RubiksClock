

#include <QApplication>
#include "qtrubiksclockmenudialog.h"



int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::ruco::QtRubiksClockMenuDialog d;
  d.show();
  return a.exec();
}
