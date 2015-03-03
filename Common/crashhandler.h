#ifndef CRASHHANDLER_H
#define CRASHHANDLER_H

#ifdef _WIN32
#include <Windows.h>
#include <imagehlp.h>
#endif

#include <iostream>
#include "qdebug.h"
#include "qmessagebox.h"


namespace CrashReport {

    #ifdef _WIN32
     void windows_print_stacktrace(CONTEXT* context);
     LONG WINAPI windows_exception_handler(EXCEPTION_POINTERS * ExceptionInfo);
    #endif
}
#endif // CRASHHANDLER_H
