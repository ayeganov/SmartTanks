#-------------------------------------------------
#
# Project created by QtCreator 2015-06-17T15:33:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartTanks
TEMPLATE = app


SOURCES += main.cpp\
    gameview.cpp \
    controller.cpp \
    utils.cpp \
    tank.cpp \
    ammo.cpp

HEADERS  += \
    gameview.h \
    controller.h \
    utils.h \
    tank.h \
    globals.h \
    ammo.h
CONFIG += c++11

FORMS    +=

RESOURCES += \
    images.qrc
