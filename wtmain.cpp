//---------------------------------------------------------------------------
/*
RubiksClock. Rubik's Clock game.
Copyright (C) 2007-2011  Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/GameRubiksClock.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push



#include <Wt/WApplication>
#include <Wt/WEnvironment>

#include "trace.h"
#include "wtautoconfig.h"
#include "wtrubiksclockmenudialog.h"

#include <QFile>
#pragma GCC diagnostic pop

struct WtApplication : public Wt::WApplication
{
  WtApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
  {
    this->setTitle("RubiksClock");
    this->useStyleSheet("wt.css");
    root()->addWidget(new ribi::ruco::WtRubiksClockMenuDialog);
  }
};

Wt::WApplication *createApplication(
  const Wt::WEnvironment& env)
{
  return new WtApplication(env);
}

int main(int argc, char **argv)
{
  START_TRACE();
  ribi::WtAutoConfig a(argc,argv,createApplication);
  ribi::WtAutoConfig::SaveDefaultStylesheet();
  return a.Run();
}
