
SOURCES += \
    $$PWD/kppvision.cpp \
    $$PWD/inspection.cpp \
    $$PWD/configurationswidget.cpp \
    $$PWD/sidewidget.cpp \
    $$PWD/SizeGripItem.cpp \
    $$PWD/visiontreewidget.cpp \
    $$PWD/kppstyleditemdelegate.cpp \
    $$PWD/request.cpp \
    $$PWD/ilistviewitem.cpp \
    $$PWD/inspectiontreewidget.cpp \
    $$PWD/capturesource.cpp \
    $$PWD/imagefilecapture.cpp \
    $$PWD/requestmenu.cpp \
    $$PWD/inspectionmenu.cpp \
    $$PWD/kpproi.cpp \
    $$PWD/resizableitem.cpp \
    $$PWD/kppgraphicsview.cpp \
    $$PWD/kppgraphicsscene.cpp \
    $$PWD/imageholder.cpp \
    $$PWD/kppvisionauxfunctions.cpp \
    $$PWD/visionwindow.cpp \
    $$PWD/visionsettings.cpp \
    $$PWD/visionmodule.cpp \
    $$PWD/visionmoduletreewidget.cpp

HEADERS += \
    $$PWD/kppvision.h\
    $$PWD/inspection.h \
    $$PWD/configurationswidget.h \
    $$PWD/sidewidget.h \
    $$PWD/SizeGripItem.h \
    $$PWD/visiontreewidget.h \
    $$PWD/kppstyleditemdelegate.h \
    $$PWD/request.h \
    $$PWD/ilistviewitem.h \
    $$PWD/inspectiontreewidget.h \
    $$PWD/capturesource.h \
    $$PWD/imagefilecapture.h \
    $$PWD/BoostDef.h \
    $$PWD/requestmenu.h \
    $$PWD/inspectionmenu.h \
    $$PWD/kpproi.h \
    $$PWD/resizableitem.h \
    $$PWD/kppgraphicsview.h \
    $$PWD/kppgraphicsscene.h \
    $$PWD/imageholder.h \
    $$PWD/kppvisionauxfunctions.h \
    $$PWD/visionwindow.h \
    $$PWD/visionsettings.h \
    $$PWD/visionmodule.h \
    $$PWD/visionmoduletreewidget.h




FORMS += \
    vision/configurationswidget.ui \
    vision/requestmenu.ui \
    vision/inspectionmenu.ui \
    vision/visionwindow.ui


INCLUDEPATH += . .. $$PWD

INCLUDEPATH +=$$PWD/../../ExternalLibs/OpenCV/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../ExternalLibs/OpenCV/lib/ -lopencv_core300 -lopencv_imgproc300 -lopencv_highgui300 -lopencv_imgcodecs300
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../ExternalLibs/OpenCV/lib/ -lopencv_core300d -lopencv_imgproc300d -lopencv_highgui300d -lopencv_imgcodecs300d


RESOURCES += \
    vision/resources/visionres.qrc
