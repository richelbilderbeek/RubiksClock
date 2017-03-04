include(../RibiLibraries/BoostAll.pri)
#include(../RibiLibraries/Apfloat.pri)
include(../RibiLibraries/Wt.pri)

include(../RibiLibraries/GeneralConsole.pri)
include(../RibiLibraries/GeneralWeb.pri)

#Specific, console
include(../RibiClasses/CppCanvas/CppCanvas.pri)
include(../RibiClasses/CppContainer/CppContainer.pri)
include(../RibiClasses/CppDial/CppDial.pri)
include(../RibiClasses/CppDialWidget/CppDialWidget.pri)
include(../DotMatrix/DotMatrix.pri)
include(../RibiClasses/CppDrawCanvas/CppDrawCanvas.pri)
include(../RibiClasses/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../RibiClasses/CppGeometry/CppGeometry.pri)
include(../RibiClasses/CppImageCanvas/CppImageCanvas.pri)
include(../plane/plane.pri)
include(../RibiClasses/CppRibiRegex/CppRibiRegex.pri)
include(../RibiClasses/CppRubiksClock/CppRubiksClock.pri)
include(../RibiClasses/CppRubiksClockWidget/CppRubiksClockWidget.pri)
include(../RibiClasses/CppTextCanvas/CppTextCanvas.pri)
include(../RibiClasses/CppToggleButton/CppToggleButton.pri)
include(../RibiClasses/CppToggleButtonWidget/CppToggleButtonWidget.pri)
include(../RibiClasses/CppTribool/CppTribool.pri)
include(../RibiClasses/CppWidget/CppWidget.pri)
include(../RibiClasses/CppXml/CppXml.pri)

#Specific, web
include(../RibiClasses/CppWtDialWidget/CppWtDialWidget.pri)
include(../RibiClasses/CppWtRubiksClockWidget/CppWtRubiksClockWidget.pri)
include(../RibiClasses/CppWtToggleButtonWidget/CppWtToggleButtonWidget.pri)

include(GameRubiksClockWebsite.pri)

SOURCES += wtmain.cpp

# C++14
CONFIG += c++14
QMAKE_CXX = g++-5
QMAKE_LINK = g++-5
QMAKE_CC = gcc-5
QMAKE_CXXFLAGS += -Wall -Wextra -std=c++14


# Debug and release mode
CONFIG += debug_and_release

CONFIG(debug, debug|release) {
  message(Debug mode)
}

CONFIG(release, debug|release) {
  message(Release mode)
  DEFINES += NDEBUG
}

# Qt
QT += core

# Wt
LIBS += -lwt -lwthttp

# Prevents this error:
#/usr/include/boost/math/constants/constants.hpp:277: error: unable to find numeric literal operator 'operator""Q'
#   BOOST_DEFINE_MATH_CONSTANT(half, 5.000000000000000000000000000000000000e-01, "5.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-01")
#   ^
QMAKE_CXXFLAGS += -fext-numeric-literals
