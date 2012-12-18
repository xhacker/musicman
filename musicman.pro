#-------------------------------------------------
#
# Project created by QtCreator 2012-11-25T23:51:38
#
#-------------------------------------------------

QT       += core gui\
    phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = musicman
TEMPLATE = app


SOURCES += main.cpp\
    canvas.cpp \
    note.cpp \
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
    jdksmidi/jdksmidi_utils.cpp \
    midi.cpp \
    mainwindow.cpp

HEADERS  += \
    canvas.h \
    note.h \
    jdksmidi/advancedsequencer.h \
    jdksmidi/driver.h \
    jdksmidi/driverdump.h \
    jdksmidi/driverwin32.h \
    jdksmidi/edittrack.h \
    jdksmidi/file.h \
    jdksmidi/fileread.h \
    jdksmidi/filereadmultitrack.h \
    jdksmidi/fileshow.h \
    jdksmidi/filewrite.h \
    jdksmidi/filewritemultitrack.h \
    jdksmidi/keysig.h \
    jdksmidi/manager.h \
    jdksmidi/matrix.h \
    jdksmidi/midi.h \
    jdksmidi/msg.h \
    jdksmidi/multitrack.h \
    jdksmidi/parser.h \
    jdksmidi/process.h \
    jdksmidi/queue.h \
    jdksmidi/sequencer.h \
    jdksmidi/showcontrol.h \
    jdksmidi/showcontrolhandler.h \
    jdksmidi/smpte.h \
    jdksmidi/song.h \
    jdksmidi/sysex.h \
    jdksmidi/tempo.h \
    jdksmidi/tick.h \
    jdksmidi/track.h \
    jdksmidi/utils.h \
    jdksmidi/world.h \
    midi.h \
    mainwindow.h

FORMS    += mainwindow.ui
