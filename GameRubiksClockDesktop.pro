include(../RibiLibraries/DesktopApplication.pri)

include(../RibiClasses/CppAbout/CppAbout.pri)
include(../RibiClasses/CppFileIo/CppFileIo.pri)
include(../RibiClasses/CppHelp/CppHelp.pri)
include(../RibiClasses/CppMenuDialog/CppMenuDialog.pri)
include(../RibiClasses/CppQtAboutDialog/CppQtAboutDialog.pri)
include(../RibiClasses/CppQtHideAndShowDialog/CppQtHideAndShowDialog.pri)

#Specific, console
include(../RibiClasses/CppCanvas/CppCanvas.pri)
include(../RibiClasses/CppContainer/CppContainer.pri)
include(../RibiClasses/CppDial/CppDial.pri)
include(../RibiClasses/CppDialWidget/CppDialWidget.pri)
include(../DotMatrix/DotMatrix.pri)
include(../RibiClasses/CppDrawCanvas/CppDrawCanvas.pri)
include(../RibiClasses/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../RibiClasses/CppGeometry/CppGeometry.pri)
include(../plane/plane.pri)
include(../RibiClasses/CppRibiRegex/CppRibiRegex.pri)
include(../RibiClasses/CppRubiksClock/CppRubiksClock.pri)
include(../RibiClasses/CppRubiksClockWidget/CppRubiksClockWidget.pri)
include(../RibiClasses/CppTextCanvas/CppTextCanvas.pri)
include(../RibiClasses/CppToggleButton/CppToggleButton.pri)
include(../RibiClasses/CppToggleButtonWidget/CppToggleButtonWidget.pri)
include(../RibiClasses/CppWidget/CppWidget.pri)
include(../RibiClasses/CppXml/CppXml.pri)

#Specific, desktop
include(../RibiClasses/CppQtDialWidget/CppQtDialWidget.pri)
include(../RibiClasses/CppQtRubiksClockWidget/CppQtRubiksClockWidget.pri)
include(../RibiClasses/CppQtToggleButtonWidget/CppQtToggleButtonWidget.pri)

include(GameRubiksClockDesktop.pri)

SOURCES += qtmain.cpp
