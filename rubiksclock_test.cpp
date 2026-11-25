// Tests for Rubik's Clock
// Run with: ./rubiksclock_test
#include <QtTest>

#include <random>

#include "qtrubiksclockmaindialog.h"
#include "qtrubiksclockmenudialog.h"
#include "rubiksclock.h"

using namespace ribi::ruco;

class rubiksclock_test : public QObject
{
  Q_OBJECT

private slots:

  void new_clock_is_solved()
  {
    const Clock c;
    QVERIFY(c.IsSolved());
    for (int x = 0; x != 3; ++x)
    {
      for (int y = 0; y != 3; ++y)
      {
        QCOMPARE(c.GetTime(true, x, y), 0);
        QCOMPARE(c.GetTime(false, x, y), 0);
      }
    }
  }

  void sides_convert_to_coordinates_and_back()
  {
    for (const auto side: { Side::topLeft, Side::topRight, Side::bottomLeft, Side::bottomRight })
    {
      QCOMPARE(ToSide(GetX(side), GetY(side)), side);
    }
  }

  void toggling_a_peg_twice_gives_the_original()
  {
    Clock c;
    const bool before{c.IsPegPressed(true, 0, 0)};
    c.TogglePeg(Side::topLeft);
    QCOMPARE(c.IsPegPressed(true, 0, 0), !before);
    c.TogglePeg(Side::topLeft);
    QCOMPARE(c.IsPegPressed(true, 0, 0), before);
  }

  void a_pressed_peg_is_up_at_the_back()
  {
    Clock c;
    c.TogglePeg(Side::topLeft);
    QCOMPARE(c.IsPegPressed(false, 1, 0), !c.IsPegPressed(true, 0, 0));
  }

  void turning_a_wheel_unsolves_and_turning_back_solves()
  {
    for (const auto side: { Side::topLeft, Side::topRight, Side::bottomLeft, Side::bottomRight })
    {
      Clock c;
      c.TurnWheel(side, 1);
      QVERIFY(!c.IsSolved());
      c.TurnWheel(side, -1);
      QVERIFY(c.IsSolved());
    }
  }

  void turning_a_wheel_twelve_steps_does_nothing()
  {
    Clock c;
    c.TogglePeg(Side::bottomRight);
    c.TurnWheel(Side::bottomRight, 12);
    QVERIFY(c.IsSolved());
  }

  void scramble_unsolves()
  {
    std::mt19937 rng(42);
    Clock c;
    c.Scramble(rng);
    QVERIFY(!c.IsSolved());
  }

  void version_is_known()
  {
    QVERIFY(!GetVersion().empty());
    QVERIFY(!GetVersionHistory().empty());
  }

  void menu_dialog_can_be_shown()
  {
    QtRubiksClockMenuDialog d;
    d.show();
    QVERIFY(QTest::qWaitForWindowExposed(&d));
  }

  void main_dialog_responds_to_clicks()
  {
    QtRubiksClockMainDialog d;
    d.show();
    QVERIFY(QTest::qWaitForWindowExposed(&d));
    const int n{10};
    for (int x = 0; x != n; ++x)
    {
      for (int y = 0; y != n; ++y)
      {
        const QPoint p(
          (x * d.width()) / n + d.width() / (2 * n),
          (y * d.height()) / n + d.height() / (2 * n)
        );
        QTest::mouseClick(&d, Qt::LeftButton, Qt::NoModifier, p);
        QTest::mouseClick(&d, Qt::RightButton, Qt::NoModifier, p);
      }
    }
    QVERIFY(d.isVisible());
  }
};

QTEST_MAIN(rubiksclock_test)
#include "rubiksclock_test.moc"
