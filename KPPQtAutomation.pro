#-------------------------------------------------
#
# Project created by QtCreator 2015-03-02T14:31:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KPPQtAutomation
TEMPLATE = app

UI_DIR = uics
MOC_DIR = mocs
OBJECTS_DIR = objs



SOURCES += main.cpp\
        mainwindow.cpp \
    actionbar.cpp \
    menustyle.cpp

HEADERS  += mainwindow.h \
    actionbar.h \
    menustyle.h

FORMS    += mainwindow.ui


RESOURCES += \
    resources/res.qrc


! include( Common/common.pri ) {
    error( "Couldn't find the common.pri file!" )
}


! include( Hardware/hardware.pri ) {
    error( "Couldn't find the hardware.pri file!" )
}


! include( Vision/vision.pri ) {
    error( "Couldn't find the vision.pri file!" )
}

DISTFILES +=
