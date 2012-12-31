#-------------------------------------------------
#
# Project created by QtCreator 2012-11-25T23:51:38
#
#-------------------------------------------------

QT       += core gui\
    phonon\
    opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = musicman
TEMPLATE = app


SOURCES += main.cpp\
    canvas.cpp \
    note.cpp \
    midi.cpp \
    mainwindow.cpp

HEADERS  += \
    canvas.h \
    note.h \
    midi.h \
    mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
