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
    note.cpp \
    button.cpp \
    jdksmidi/jdksmidi_advancedsequencer.cpp \
    jdksmidi/jdksmidi_driver.cpp \
    jdksmidi/jdksmidi_driverdump.cpp \
    jdksmidi/jdksmidi_edittrack.cpp \
    jdksmidi/jdksmidi_file.cpp \
    jdksmidi/jdksmidi_fileread.cpp \
    jdksmidi/jdksmidi_filereadmultitrack.cpp \
    jdksmidi/jdksmidi_fileshow.cpp \
    jdksmidi/jdksmidi_filewrite.cpp \
    jdksmidi/jdksmidi_filewritemultitrack.cpp \
    jdksmidi/jdksmidi_keysig.cpp \
    jdksmidi/jdksmidi_manager.cpp \
    jdksmidi/jdksmidi_matrix.cpp \
    jdksmidi/jdksmidi_midi.cpp \
    jdksmidi/jdksmidi_msg.cpp \
    jdksmidi/jdksmidi_multitrack.cpp \
    jdksmidi/jdksmidi_parser.cpp \
    jdksmidi/jdksmidi_process.cpp \
    jdksmidi/jdksmidi_queue.cpp \
    jdksmidi/jdksmidi_sequencer.cpp \
    jdksmidi/jdksmidi_showcontrol.cpp \
    jdksmidi/jdksmidi_showcontrolhandler.cpp \
    jdksmidi/jdksmidi_smpte.cpp \
    jdksmidi/jdksmidi_sysex.cpp \
    jdksmidi/jdksmidi_tempo.cpp \
    jdksmidi/jdksmidi_tick.cpp \
    jdksmidi/jdksmidi_track.cpp \
    jdksmidi/jdksmidi_utils.cpp

HEADERS  += mainwindow.h \
    canvas.h \
    note.h \
    button.h \
    jdksmidi/jdksmidi/advancedsequencer.h \
    jdksmidi/jdksmidi/driver.h \
    jdksmidi/jdksmidi/driverdump.h \
    jdksmidi/jdksmidi/driverwin32.h \
    jdksmidi/jdksmidi/edittrack.h \
    jdksmidi/jdksmidi/file.h \
    jdksmidi/jdksmidi/fileread.h \
    jdksmidi/jdksmidi/filereadmultitrack.h \
    jdksmidi/jdksmidi/fileshow.h \
    jdksmidi/jdksmidi/filewrite.h \
    jdksmidi/jdksmidi/filewritemultitrack.h \
    jdksmidi/jdksmidi/keysig.h \
    jdksmidi/jdksmidi/manager.h \
    jdksmidi/jdksmidi/matrix.h \
    jdksmidi/jdksmidi/midi.h \
    jdksmidi/jdksmidi/msg.h \
    jdksmidi/jdksmidi/multitrack.h \
    jdksmidi/jdksmidi/parser.h \
    jdksmidi/jdksmidi/process.h \
    jdksmidi/jdksmidi/queue.h \
    jdksmidi/jdksmidi/sequencer.h \
    jdksmidi/jdksmidi/showcontrol.h \
    jdksmidi/jdksmidi/showcontrolhandler.h \
    jdksmidi/jdksmidi/smpte.h \
    jdksmidi/jdksmidi/song.h \
    jdksmidi/jdksmidi/sysex.h \
    jdksmidi/jdksmidi/tempo.h \
    jdksmidi/jdksmidi/tick.h \
    jdksmidi/jdksmidi/track.h \
    jdksmidi/jdksmidi/utils.h \
    jdksmidi/jdksmidi/world.h

FORMS    += mainwindow.ui
