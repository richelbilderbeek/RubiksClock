#include "rubiksclockmenudialog.h"

#include <cassert>
#include <iostream>

#include "about.h"
#include "canvas.h"
#include "dial.h"
#include "dialwidget.h"
#include "drawcanvas.h"
#include "rubiksclock.h"
#include "rubiksclockdial.h"
#include "rubiksclockdialwidget.h"
#include "rubiksclockside.h"
#include "rubiksclockwidget.h"
#include "textcanvas.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"

int ribi::ruco::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc != 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }

  const boost::shared_ptr<ClockWidget> widget(
    new ClockWidget
  );

  for (int i=0; i!=100; ++i)
  {
    std::cout << (*widget->ToTextCanvas()) << std::endl;
    Side side = Side::bottomLeft;
    switch ((std::rand() >> 4) % 4)
    {
      case 0: side = Side::bottomLeft; break;
      case 1: side = Side::bottomRight; break;
      case 2: side = Side::topLeft; break;
      case 3: side = Side::topRight; break;
      default: assert(!"Should not get here");
    }
    widget->GetRubiksClock()->TurnWheel(side,std::rand() % 12);

    switch ((std::rand() >> 4) % 4)
    {
      case 0: side = Side::bottomLeft; break;
      case 1: side = Side::bottomRight; break;
      case 2: side = Side::topLeft; break;
      case 3: side = Side::topRight; break;
      default: assert(!"Should not get here");
    }

    widget->GetRubiksClock()->TogglePeg(side);
  }
  return 0;
}

ribi::About ribi::ruco::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "RubiksClock",
    "simulates a Rubik's Clock",
    "the 23rd of January 2014",
    "2007-2015",
    "http://www.richelbilderbeek.nl/GameRubiksClock.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("Dial version: " + Dial::GetVersion());
  a.AddLibrary("DialWidget version: " + ::ribi::DialWidget::GetVersion());
  a.AddLibrary("DrawCanvas version: " + DrawCanvas::GetVersion());
  a.AddLibrary("RubiksClock version: " + ruco::Clock::GetVersion());
  a.AddLibrary("RubiksClockDial version: " + ruco::ClockDial::GetVersion());
  a.AddLibrary("RubiksClockDialWidget version: " + ruco::ClockDialWidget::GetVersion());
  a.AddLibrary("RubiksClockWidget version: " + ruco::ClockWidget::GetVersion());
  a.AddLibrary("TextCanvas version: " + TextCanvas::GetVersion());
  a.AddLibrary("ToggleButton version: " + ToggleButton::GetVersion());
  a.AddLibrary("ToggleButtonWidget version: " + ToggleButtonWidget::GetVersion());
  a.AddLibrary("Widget version: " + Widget::GetVersion());
  return a;
}

ribi::Help ribi::ruco::MenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

std::string ribi::ruco::MenuDialog::GetVersion() const noexcept
{
  return "2.3";
}

std::vector<std::string> ribi::ruco::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2007-12-19: Version 1.0: initial Windows-only version using C++ Builder",
    "2011-09-08: Version 2.0: initial port to Qt using Qt Creator, but not complete yet",
    "2011-09-15: Version 2.1: created web application version, RubiksClock has all functionality",
    "2012-12-23: Version 2.2: created desktop version",
    "2014-01-23: Version 2.3: console version gives a demo"
  };
}

#ifndef NDEBUG
void ribi::ruco::MenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  ruco::MenuDialog d;
  d.Execute( { "rubiksclockconsole" } );
}
#endif
