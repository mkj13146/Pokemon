#-------------------------------------------------
#
# Project created by QtCreator 2017-05-19T18:01:30
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        tcpclient.cpp \
    fightmanager.cpp \
    pokemon.cpp

HEADERS  += tcpclient.h \
    fightmanager.h \
    pokemon.h

FORMS    += tcpclient.ui \
    fightmanager.ui

RESOURCES += \
    resource.qrc
