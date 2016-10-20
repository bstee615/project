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
        mainwidget.cpp \
    object.cpp \
    highscore.cpp \
    world.cpp \
    enemy.cpp

HEADERS  += mainwidget.h \
    object.h \
    highscore.h \
    world.h \
    enemy.h

FORMS    += mainwidget.ui
