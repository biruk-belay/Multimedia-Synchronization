#-------------------------------------------------
#
# Project created by QtCreator 2015-05-20T00:32:18
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Play_sound
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    assemble_all.cpp \
    func_engine.cpp \
    kiss_fft.c

HEADERS  += mainwindow.h \
    assemble_all.h \
    func_engine.h \
    kiss_fft.h \
    kissfft.hh \
    _kiss_fft_guts.h

FORMS    += mainwindow.ui
