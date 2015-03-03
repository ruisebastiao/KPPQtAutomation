

INCLUDEPATH += . .. $$PWD
INCLUDEPATH += $$PWD/../../ExternalLibs/IDS/include

SOURCES +=\
    Hardware\camerainfo.cpp \
    Hardware\idscamera.cpp \
    Hardware\idscamerainfo.cpp \
    Hardware\idseventsthandler.cpp \
    Hardware\kpphardware.cpp

HEADERS +=\
   Hardware\camerainfo.h \
   Hardware\idscamera.h \
   Hardware\idscamerainfo.h \
   Hardware\idseventsthandler.h \
   Hardware\kpphardware.h

win32: LIBS += -L$$PWD/../../ExternalLibs/IDS/Lib/ -luEye_tools
win32: LIBS += -L$$PWD/../../ExternalLibs/IDS/Lib/ -luEye_api
