#-------------------------------------------------
#
# Project created by QtCreator 2012-11-25T23:51:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = musicman
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canvas.cpp \
    ../note.cpp \
    note.cpp \
    button.cpp

HEADERS  += mainwindow.h \
    canvas.h \
    ../note.h \
    note.h \
    button.h

FORMS    += mainwindow.ui
