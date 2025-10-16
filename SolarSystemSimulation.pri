INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/src

SOURCES += $$files($$PWD/src/**/*.cpp, true)
HEADERS += $$files($$PWD/src/**/*.h, true)
HEADERS += $$files($$PWD/src/**/*.hpp, true)

CONFIG += c++23
