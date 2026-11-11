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
#include "rubiksclock.h"

#include <cassert>

ribi::ruco::Clock::Clock() noexcept
  : m_front{},
    m_back{},
    m_pegs{}
{
}

int ribi::ruco::GetX(const Side side) noexcept
{
  return side == Side::topLeft || side == Side::bottomLeft ? 0 : 1;
}

int ribi::ruco::GetY(const Side side) noexcept
{
  return side == Side::topLeft || side == Side::topRight ? 0 : 1;
}

int ribi::ruco::Clock::GetTime(const bool front, const int x, const int y) const noexcept
{
  assert(x >= 0 && x < 3);
  assert(y >= 0 && y < 3);
  return front ? m_front[x][y] : m_back[x][y];
}

std::string ribi::ruco::GetVersion() noexcept
{
  return "3.0";
}

std::vector<std::string> ribi::ruco::GetVersionHistory() noexcept
{
  return {
    "2007-12-19: Version 1.0: initial Windows-only version using C++ Builder",
    "2011-09-08: Version 2.0: initial port to Qt using Qt Creator, but not complete yet",
    "2011-09-15: Version 2.1: created web application version, RubiksClock has all functionality",
    "2012-12-23: Version 2.2: created desktop version",
    "2014-01-23: Version 2.3: console version gives a demo",
    "2026-11-11: Version 3.0: use Qt 6, play in the browser using WebAssembly"
  };
}

bool ribi::ruco::Clock::IsPegPressed(const bool front, const int x, const int y) const noexcept
{
  assert(x >= 0 && x < 2);
  assert(y >= 0 && y < 2);
  //The back is mirrored horizontally, and a peg that is pressed
  //at one side sticks out at the other side
  return front ? m_pegs[x][y] : !m_pegs[1 - x][y];
}

bool ribi::ruco::Clock::IsSolved() const noexcept
{
  for (int x=0; x!=3; ++x)
  {
    for (int y=0; y!=3; ++y)
    {
      if (m_front[x][y] != 0 || m_back[x][y] != 0) return false;
    }
  }
  return true;
}

void ribi::ruco::Clock::Scramble(std::mt19937& rng, const int n_moves) noexcept
{
  std::uniform_int_distribution<int> side_dist(0, 3);
  std::uniform_int_distribution<int> steps_dist(1, 11);
  std::bernoulli_distribution toggle_dist(0.5);
  for (int i=0; i!=n_moves; ++i)
  {
    const Side side{static_cast<Side>(side_dist(rng))};
    if (toggle_dist(rng))
    {
      TogglePeg(side);
    }
    else
    {
      TurnWheel(side, steps_dist(rng));
    }
  }
}

void ribi::ruco::Clock::TogglePeg(const Side side) noexcept
{
  bool& peg = m_pegs[GetX(side)][GetY(side)];
  peg = !peg;
}

ribi::ruco::Side ribi::ruco::ToSide(const int x, const int y) noexcept
{
  assert(x == 0 || x == 1);
  assert(y == 0 || y == 1);
  if (x == 0) return y == 0 ? Side::topLeft : Side::bottomLeft;
  return y == 0 ? Side::topRight : Side::bottomRight;
}

void ribi::ruco::Clock::Turn(
  const bool turn_front[3][3],
  const bool turn_back[3][3],
  const int n_steps
) noexcept
{
  for (int x=0; x!=3; ++x)
  {
    for (int y=0; y!=3; ++y)
    {
      if (turn_front[x][y])
      {
        m_front[x][y] = (((m_front[x][y] + n_steps) % 12) + 12) % 12;
      }
      if (turn_back[x][y])
      {
        m_back[x][y] = (((m_back[x][y] - n_steps) % 12) + 12) % 12;
      }
    }
  }
}

void ribi::ruco::Clock::TurnWheel(const Side side, const int n_steps) noexcept
{
  switch (side)
  {
    case Side::topLeft    : TurnWheelTopLeft(n_steps);     break;
    case Side::topRight   : TurnWheelTopRight(n_steps);    break;
    case Side::bottomLeft : TurnWheelBottomLeft(n_steps);  break;
    case Side::bottomRight: TurnWheelBottomRight(n_steps); break;
  }
}

void ribi::ruco::Clock::TurnWheelTopLeft(const int n_steps) noexcept
{
  const auto p = [this](const int x, const int y) { return m_pegs[x][y]; };
  bool f[3][3];
  bool b[3][3];
  f[0][0] = true;
  f[1][0] = !p(0,0);
  f[2][0] = p(0,0) == p(1,0);
  f[0][1] = !p(0,0);
  f[1][1] = !p(0,0);
  f[2][1] = !p(0,0) && (!p(1,0) || !p(1,1));
  f[0][2] = p(0,0) == p(0,1);
  f[1][2] = !p(0,0) && (!p(0,1) || !p(1,1));
  f[2][2] = p(0,0) == p(1,1);

  b[0][0] = p(0,0) == p(1,0);
  b[1][0] = p(0,0);
  b[2][0] = true;
  b[0][1] = p(0,0) && (p(1,0) || p(1,1));
  b[1][1] = p(0,0);
  b[2][1] = p(0,0);
  b[0][2] = p(0,0) == p(1,1);
  b[1][2] = p(0,0) && (p(0,1) || p(1,1));
  b[2][2] = p(0,0) == p(0,1);
  Turn(f, b, n_steps);
}

void ribi::ruco::Clock::TurnWheelTopRight(const int n_steps) noexcept
{
  const auto p = [this](const int x, const int y) { return m_pegs[x][y]; };
  bool f[3][3];
  bool b[3][3];
  f[2][0] = true;
  f[1][0] = !p(1,0);
  f[0][0] = p(0,0) == p(1,0);
  f[2][1] = !p(1,0);
  f[1][1] = !p(1,0);
  f[0][1] = !p(1,0) && (!p(0,0) || !p(0,1));
  f[2][2] = p(1,0) == p(1,1);
  f[1][2] = !p(1,0) && (!p(1,1) || !p(0,1));
  f[0][2] = p(1,0) == p(0,1);

  b[2][0] = p(1,0) == p(0,0);
  b[1][0] = p(1,0);
  b[0][0] = true;
  b[2][1] = p(1,0) && (p(0,0) || p(0,1));
  b[1][1] = p(1,0);
  b[0][1] = p(1,0);
  b[2][2] = p(1,0) == p(0,1);
  b[1][2] = p(1,0) && (p(1,1) || p(0,1));
  b[0][2] = p(1,0) == p(1,1);
  Turn(f, b, n_steps);
}

void ribi::ruco::Clock::TurnWheelBottomLeft(const int n_steps) noexcept
{
  const auto p = [this](const int x, const int y) { return m_pegs[x][y]; };
  bool f[3][3];
  bool b[3][3];
  f[0][2] = true;
  f[1][2] = !p(0,1);
  f[2][2] = p(0,1) == p(1,1);
  f[0][1] = !p(0,1);
  f[1][1] = !p(0,1);
  f[2][1] = !p(0,1) && (!p(1,1) || !p(1,0));
  f[0][0] = p(0,1) == p(0,0);
  f[1][0] = !p(0,1) && (!p(0,0) || !p(1,0));
  f[2][0] = p(0,1) == p(1,0);

  b[0][2] = p(0,1) == p(1,1);
  b[1][2] = p(0,1);
  b[2][2] = true;
  b[0][1] = p(0,1) && (p(1,1) || p(1,0));
  b[1][1] = p(0,1);
  b[2][1] = p(0,1);
  b[0][0] = p(0,1) == p(1,0);
  b[1][0] = p(0,1) && (p(0,0) || p(1,0));
  b[2][0] = p(0,1) == p(0,0);
  Turn(f, b, n_steps);
}

void ribi::ruco::Clock::TurnWheelBottomRight(const int n_steps) noexcept
{
  const auto p = [this](const int x, const int y) { return m_pegs[x][y]; };
  bool f[3][3];
  bool b[3][3];
  f[2][2] = true;
  f[1][2] = !p(1,1);
  f[0][2] = p(0,1) == p(1,1);
  f[2][1] = !p(1,1);
  f[1][1] = !p(1,1);
  f[0][1] = !p(1,1) && (!p(0,1) || !p(0,0));
  f[2][0] = p(1,1) == p(1,0);
  f[1][0] = !p(1,1) && (!p(1,0) || !p(0,0));
  f[0][0] = p(1,1) == p(0,0);

  b[2][2] = p(1,1) == p(0,1);
  b[1][2] = p(1,1);
  b[0][2] = true;
  b[2][1] = p(1,1) && (p(0,1) || p(0,0));
  b[1][1] = p(1,1);
  b[0][1] = p(1,1);
  b[2][0] = p(1,1) == p(0,0);
  b[1][0] = p(1,1) && (p(1,0) || p(0,0));
  b[0][0] = p(1,1) == p(1,0);
  Turn(f, b, n_steps);
}
