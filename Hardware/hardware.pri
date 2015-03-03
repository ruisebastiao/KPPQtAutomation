

INCLUDEPATH += . .. $$PWD
INCLUDEPATH += $$PWD/../../ExternalLibs/IDS/include

SOURCES +=\
    Hardware\cameras\camerainfo.cpp \
    Hardware\cameras\ids\idscamera.cpp \
    Hardware\kpphardware.cpp

HEADERS +=\
   Hardware\cameras\camerainfo.h \
   Hardware\cameras\ids\idscamera.h \
   Hardware\kpphardware.h

win32: LIBS += -L$$PWD/../../ExternalLibs/IDS/Lib/ -luEye_tools
win32: LIBS += -L$$PWD/../../ExternalLibs/IDS/Lib/ -luEye_api
