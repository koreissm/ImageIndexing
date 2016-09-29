#-------------------------------------------------
#
# Project created by QtCreator 2016-09-28T14:14:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#LIBS += -L/usr/local/libjpeg/lib/ -ljpeg
#INCLUDEPATH += /usr/local/libjpeg/include/

TARGET = ImageIndexing
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    clickablelabel.cpp \
    ../../ImageIndexing/libs/ImageProcessingTools.C \
    ../../ImageIndexing/libs/Distance.C

HEADERS  += mainwindow.h \
    clickablelabel.h

FORMS    += mainwindow.ui
