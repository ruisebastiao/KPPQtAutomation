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

INCLUDEPATH +=$$PWD/../ExternalLibs/QsLog

DEFINES += QSLOG_IS_SHARED_LIBRARY_IMPORT

LIBS += -L$$PWD/../ExternalLibs/QsLog/build-QsLogShared
win32 {
    LIBS += -lQsLog2
} else {
    LIBS += -lQsLog
}


SOURCES += main.cpp\
        mainwindow.cpp \
    actionbar.cpp \
    menustyle.cpp \
    loginwindow.cpp \
    applicationsettingswindow.cpp \
    applicationsettings.cpp

HEADERS  += mainwindow.h \
    actionbar.h \
    menustyle.h \
    loginwindow.h \
    applicationsettingswindow.h \
    applicationsettings.h


FORMS    += mainwindow.ui \
    applicationsettings.ui \
    loginwindow.ui



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

#DISTFILES +=
