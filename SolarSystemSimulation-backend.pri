INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/src

# Reliable recursive enumeration (works everywhere)
SOURCES += $$files($$PWD/src/*.cpp)
for(subdir, $$list($$files($$PWD/src/*))) {
    exists($$subdir/*.cpp): SOURCES += $$files($$subdir/*.cpp)
    exists($$subdir/*.c):   SOURCES += $$files($$subdir/*.c)
}

HEADERS += $$files($$PWD/src/*.h) \
           $$files($$PWD/src/*.hpp)
for(subdir, $$list($$files($$PWD/src/*))) {
    exists($$subdir/*.h):   HEADERS += $$files($$subdir/*.h)
    exists($$subdir/*.hpp): HEADERS += $$files($$subdir/*.hpp)
}

CONFIG += c++23
