
SOURCES +=\
    $$PWD\kppcommon.cpp \
    $$PWD/kppeditbox.cpp \
    $$PWD/kppframe.cpp \
    $$PWD/kppgestureframe.cpp \
    $$PWD/kpppushbutton.cpp \
    $$PWD/slidewidget.cpp \
    $$PWD/SlidingStackedWidget.cpp \
    $$PWD/kppadjustablelistview.cpp \
    $$PWD/kpptreewidgetitem.cpp \
    $$PWD/kpplineedit.cpp \
    $$PWD/kpptreepushbutton.cpp \
    $$PWD/kppanimatedframe.cpp \
    $$PWD/swipegesturerecognizer.cpp \
    $$PWD/kppadjustablelistview.cpp \
    $$PWD/crashhandler.cpp \
    $$PWD/crashdialog.cpp \
    $$PWD/serializablelist.cpp \
    $$PWD/applicationmodule.cpp \
    $$PWD/kppactionpushbutton.cpp


HEADERS += \
    $$PWD/kppcommon.h\
    $$PWD/kppcommon_global.h \
    $$PWD/kppeditbox.h \
    $$PWD/kppframe.h \
    $$PWD/kppgestureframe.h \
    $$PWD/kpppushbutton.h \
    $$PWD/slidewidget.h \
    $$PWD/SlidingStackedWidget.h \
    $$PWD/kppadjustablelistview.h \
    $$PWD/kpptreewidgetitem.h \
    $$PWD/kpplineedit.h \
    $$PWD/kpptreepushbutton.h \
    $$PWD/kppanimatedframe.h \
    $$PWD/swipegesturerecognizer.h \
    $$PWD/kppadjustablelistview.h \
    $$PWD/crashhandler.h \
    $$PWD/crashdialog.h \
    $$PWD/serializablelist.h \
    $$PWD/applicationmodule.h \
    $$PWD/kppactionpushbutton.h



INCLUDEPATH += . .. $$PWD
INCLUDEPATH +=$$PWD/../../ExternalLibs/Qxt/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../ExternalLibs/Qxt/lib/ -lQxtCore -lQxtWidgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../ExternalLibs/Qxt/lib/ -lQxtCored -lQxtWidgetsd

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../ExternalLibs/dbghelp/lib/ -ldbghelp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../ExternalLibs/dbghelp/lib/ -ldbghelp

INCLUDEPATH += $$PWD/../../ExternalLibs/boost
LIBS += -L$$PWD/../../ExternalLibs/boost/lib


