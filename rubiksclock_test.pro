# Tests for the game, with code coverage measured in CI
# Run with: ./rubiksclock_test

lessThan(QT_MAJOR_VERSION, 6): error("RubiksClock needs Qt 6")

QT       += core gui widgets

TARGET = rubiksclock_test
TEMPLATE = app
CONFIG += c++17

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

!wasm:!msvc {
  QMAKE_CXXFLAGS += -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
}

SOURCES += \
    qthideandshowdialog.cpp \
    rubiksclock_test.cpp \
    qtrubiksclockmaindialog.cpp \
    qtrubiksclockmenudialog.cpp \
    qtrubiksclockwidget.cpp \
    rubiksclock.cpp

HEADERS += \
    qthideandshowdialog.h \
    qtrubiksclockmaindialog.h \
    qtrubiksclockmenudialog.h \
    qtrubiksclockwidget.h \
    rubiksclock.h

FORMS += \
    qtrubiksclockmaindialog.ui \
    qtrubiksclockmenudialog.ui

RESOURCES += \
    RubiksClock.qrc

QT += testlib
CONFIG += console
CONFIG -= app_bundle
