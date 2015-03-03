
SOURCES +=Common\kppcommon.cpp \
        Common/kppeditbox.cpp \
        Common/kppframe.cpp \
        Common/kppgestureframe.cpp \
        Common/kpppushbutton.cpp \
        Common/slidewidget.cpp \
        Common/SlidingStackedWidget.cpp \
        Common/kppadjustablelistview.cpp \
        Common/kpptreewidgetitem.cpp \
        Common/kpplineedit.cpp \
        Common/kpptreepushbutton.cpp \
        Common/kppanimatedframe.cpp \
        Common/swipegesturerecognizer.cpp \
        Common/kppadjustablelistview.cpp \
        Common/crashhandler.cpp \
        Common/crashdialog.cpp

HEADERS += Common/kppcommon.h\
        Common/kppcommon_global.h \
        Common/kppeditbox.h \
        Common/kppframe.h \
        Common/kppgestureframe.h \
        Common/kpppushbutton.h \
        Common/slidewidget.h \
        Common/SlidingStackedWidget.h \
        Common/kppadjustablelistview.h \
        Common/kpptreewidgetitem.h \
        Common/kpplineedit.h \
        Common/kpptreepushbutton.h \
        Common/kppanimatedframe.h \
        Common/swipegesturerecognizer.h \
        Common/kppadjustablelistview.h \
        Common/crashhandler.h \
        Common/crashdialog.h



INCLUDEPATH += . .. $$PWD
INCLUDEPATH +=$$PWD/../../ExternalLibs/Qxt/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../ExternalLibs/Qxt/lib/ -lQxtCore -lQxtWidgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../ExternalLibs/Qxt/lib/ -lQxtCored -lQxtWidgetsd

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../ExternalLibs/dbghelp/lib/ -ldbghelp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../ExternalLibs/dbghelp/lib/ -ldbghelp

INCLUDEPATH += $$PWD/../../ExternalLibs/boost
LIBS += -L$$PWD/../../ExternalLibs/boost/lib


