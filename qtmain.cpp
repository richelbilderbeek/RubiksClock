#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <cassert>
#include <iostream>
#include <QApplication>
#include "qtrubiksclockmenudialog.h"

#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  #ifndef NDEBUG
  std::clog << "DEBUG mode" << std::endl;
  #else
  std::clog << "RELEASE mode" << std::endl;
  assert(1==2 && "Assume debugging is really disabled");
  #endif

  ribi::ruco::QtRubiksClockMenuDialog d;
  d.show();
  return a.exec();
}
