QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = conway
TEMPLATE = app


SOURCES += src/gamewidget.cpp \
    src/game/clear.cpp \
    src/game/dump.cpp \
    src/game/generation.cpp \
    src/game/mouse.cpp \
    src/game/neighbourhood.cpp \
    src/game/paint.cpp \
    src/game/progress.cpp \
    src/game/universe.cpp \
    src/game/util.cpp \
    src/gui/color.cpp \
    src/gui/load.cpp \
    src/gui/loadData.cpp \
    src/gui/progressBar.cpp \
    src/gui/save.cpp \
    src/gui/surviveGui.cpp \
    src/gui/universeGui.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/game/survive.cpp

HEADERS  += include/mainwindow.h \
    include/gamewidget.h

FORMS    += ui/mainwindow.ui

OTHER_FILES += \
    README
