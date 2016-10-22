#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T16:58:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = team3
TEMPLATE = app


SOURCES += main.cpp\
    object.cpp \
    highscore.cpp \
    world.cpp \
    loadsave.cpp \
    collisiondetails.cpp \
    player.cpp \
    platform.cpp \
    collectible.cpp \
    movingplatform.cpp \
    item.cpp \
    coin.cpp  \
    enemy.cpp \
    mainwidget.cpp

HEADERS  += mainwidget.h \
    object.h \
    highscore.h \
    world.h \
    loadsave.h \
    collisiondetails.h \
    player.h \
    platform.h \
    collectible.h \
    movingplatform.h \
    item.h \
    coin.h \
    enemy.h

FORMS    += mainwidget.ui

QMAKE_CXXFLAGS += -std=c++11

DISTFILES += \
    GameFileFormat.txt

RESOURCES += \
    resources.qrc
