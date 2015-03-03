
SOURCES += \
    vision/kppvision.cpp \
    vision/inspection.cpp \
    vision/configurationswidget.cpp \
    vision/sidewidget.cpp \
    vision/SizeGripItem.cpp \
    vision/settings.cpp \
    vision/visiontreewidget.cpp \
    vision/kppstyleditemdelegate.cpp \
    vision/kppvisionlist.cpp \
    vision/request.cpp \
    vision/ilistviewitem.cpp \
    vision/inspectiontreewidget.cpp \
    vision/capturesource.cpp \
    vision/imagefilecapture.cpp \
    vision/requestmenu.cpp \
    vision/inspectionmenu.cpp \
    vision/kpproi.cpp \
    vision/resizableitem.cpp \
    vision/kppgraphicsview.cpp \
    vision/kppgraphicsscene.cpp \
    vision/imageholder.cpp \
    vision/kppvisionauxfunctions.cpp \
    vision/visionwindow.cpp

HEADERS += \
   vision/kppvision.h\
   vision/inspection.h \
   vision/configurationswidget.h \
   vision/sidewidget.h \
   vision/SizeGripItem.h \
   vision/settings.h \
   vision/visiontreewidget.h \
   vision/kppstyleditemdelegate.h \
   vision/kppvisionlist.h \
   vision/request.h \
   vision/ilistviewitem.h \
   vision/inspectiontreewidget.h \
   vision/capturesource.h \
   vision/imagefilecapture.h \
   vision/BoostDef.h \
   vision/requestmenu.h \
   vision/inspectionmenu.h \
   vision/kpproi.h \
   vision/resizableitem.h \
   vision/kppgraphicsview.h \
   vision/kppgraphicsscene.h \
   vision/imageholder.h \
   vision/kppvisionauxfunctions.h \
   vision/visionwindow.h




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
