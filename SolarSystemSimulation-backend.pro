TEMPLATE = lib
CONFIG += staticlib c++23
TARGET = SolarSystemSimulation-backend

INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src

SOURCES += $$files($$PWD/src/**/*.cpp, true)
HEADERS += $$files($$PWD/src/**/*.h, true)
HEADERS += $$files($$PWD/src/**/*.hpp, true)
