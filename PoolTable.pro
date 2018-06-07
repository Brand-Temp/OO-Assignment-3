#-------------------------------------------------
#
# Project created by QtCreator 2018-04-23T23:26:07
#
#-------------------------------------------------

QT       += core gui
CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = PoolTable
TEMPLATE = app


SOURCES += main.cpp \
    dialog.cpp \
    poolgame.cpp \
    gamebuilder.cpp \
    initializer.cpp \
    stage2ball.cpp \
    stage2factory.cpp \
    stage1factory.cpp \
    stage1table.cpp \
    stage1ball.cpp \
    stage2table.cpp \
    pocket.cpp \
    util.cpp \
    changeinpoolgame.cpp \
    cueballdecorator.cpp \
    duplicationballdecorator.cpp \
    caretaker.cpp \
    momento.cpp \
    facade.cpp \
    soundobjectpool.cpp

HEADERS  += dialog.h \
    poolgame.h \
    table.h \
    ball.h \
    abstractfactory.h \
    gamebuilder.h \
    initializer.h \
    stage2ball.h \
    stage2factory.h \
    stage1factory.h \
    stage1ball.h \
    stage1table.h \
    changeinpoolgame.h \
    util.h \
    stage2table.h \
    pocket.h \
    balldecorator.h \
    cueballdecorator.h \
    duplicationballdecorator.h \
    momento.h \
    caretaker.h \
    facade.h \
    soundobjectpool.h

DISTFILES += \
    config.json

