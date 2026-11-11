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
#ifndef RUBIKSCLOCK_H
#define RUBIKSCLOCK_H

#include <random>
#include <string>
#include <vector>

namespace ribi {
namespace ruco {

///A corner of the clock, as seen from the front
enum class Side
{
  topLeft, topRight, bottomLeft, bottomRight
};

///A Rubik's Clock: two sides with 3x3 dials each,
///four pegs and four wheels.
///
///Coordinates are (x, y), with (0, 0) at the top-left.
///The back side is stored as seen from the back,
///so it is mirrored horizontally compared to the front.
class Clock
{
public:
  ///Creates a solved clock: all dials at 12 o'clock, all pegs up
  Clock() noexcept;

  ///The time a dial shows, from 0 (12 o'clock) to 11.
  ///Use 'front' to select the side, x and y are as seen from that side
  int GetTime(const bool front, const int x, const int y) const noexcept;

  ///Is the peg pressed, as seen from a side?
  ///A peg that is pressed at the front is up at the back.
  ///x and y are as seen from that side
  bool IsPegPressed(const bool front, const int x, const int y) const noexcept;

  ///Are all dials at 12 o'clock?
  bool IsSolved() const noexcept;

  ///Do random moves
  void Scramble(std::mt19937& rng, const int n_moves = 1000) noexcept;

  ///Toggle a peg, as seen from the front
  void TogglePeg(const Side side) noexcept;

  ///Turn a wheel clockwise, as seen from the front.
  ///A negative number of steps turns counter-clockwise
  void TurnWheel(const Side side, const int n_steps) noexcept;

private:
  ///Times shown by the front dials, [x][y] as seen from the front
  int m_front[3][3];

  ///Times shown by the back dials, [x][y] as seen from the back
  int m_back[3][3];

  ///Is the peg pressed? [x][y] as seen from the front
  bool m_pegs[2][2];

  ///Turn the dials that are true by n_steps, front clockwise
  ///and back counter-clockwise
  void Turn(
    const bool turn_front[3][3],
    const bool turn_back[3][3],
    const int n_steps
  ) noexcept;
  void TurnWheelTopLeft(const int n_steps) noexcept;
  void TurnWheelTopRight(const int n_steps) noexcept;
  void TurnWheelBottomLeft(const int n_steps) noexcept;
  void TurnWheelBottomRight(const int n_steps) noexcept;
};

///Converts a corner as seen from the front to its x and y in the
///2x2 grid of pegs: 0 is left or top, 1 is right or bottom
int GetX(const Side side) noexcept;
int GetY(const Side side) noexcept;

///Converts x and y in the 2x2 grid of pegs, as seen from the front,
///to a corner
Side ToSide(const int x, const int y) noexcept;

std::string GetVersion() noexcept;
std::vector<std::string> GetVersionHistory() noexcept;

} //~namespace ruco
} //~namespace ribi

#endif // RUBIKSCLOCK_H
