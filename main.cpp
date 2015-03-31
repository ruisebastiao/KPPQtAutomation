#include "mainwindow.h"
#include <QApplication>
#include "qmessagebox.h"
//#include "settings.h"
#include "qstandardpaths.h"
#include "qdebug.h"
#include "crashhandler.h"
#include "kppcommon.h"

//#include <QxtCore/QxtBasicFileLoggerEngine>
//#include <QxtCore/QxtLogger>
//#include <QxtCore/QxtXmlFileLoggerEngine>

#include "QsLog.h"
#include "QsLogDest.h"

#include "qobject.h"

using namespace CrashReport;

//using namespace std;

/*
void setupLogger(QString path="")
{
    QString loc="";
    if(path==""){
         loc=qApp->applicationDirPath().append("/");//QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    }
    else
        loc=path;



    QxtXmlFileLoggerEngine *dbg  = new QxtXmlFileLoggerEngine(QString().append(loc).append("debug.log"));
    QxtXmlFileLoggerEngine *info = new QxtXmlFileLoggerEngine(QString().append(loc).append("info.log"));



    // qxtLog takes ownership of dbg - no need to manage its memory
    qxtLog->addLoggerEngine("dbg", dbg);
    qxtLog->addLoggerEngine("app", info);

    qxtLog->disableAllLogLevels();

    qxtLog->enableLogLevels("dbg", QxtLogger::AllLevels);
    qxtLog->enableLogLevels("app",  QxtLogger::InfoLevel | QxtLogger::WarningLevel | QxtLogger::ErrorLevel | QxtLogger::CriticalLevel | QxtLogger::FatalLevel | QxtLogger::WriteLevel );
}
*/


void logFunction(const QString &message, QsLogging::Level level)
{
    std::cout << "From log function: " << qPrintable(message) << " " << static_cast<int>(level)
              << std::endl;
}


int main(int argc, char *argv[])
{


    // Adiciona callback para erros indefinidos
    SetUnhandledExceptionFilter(windows_exception_handler);    

    QApplication a(argc, argv);


    a.setAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents,true);
    a.setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents,true);
   // setupLogger();

    using namespace QsLogging;

    // 1. init the logging mechanism
    Logger& logger = Logger::instance();

    logger.setLoggingLevel(QsLogging::TraceLevel);
    const QString sLogPath(QDir(a.applicationDirPath()).filePath("log.txt"));

    // 2. add two destinations
    DestinationPtr fileDestination(DestinationFactory::MakeFileDestination(
      sLogPath, EnableLogRotation, MaxSizeBytes(512), MaxOldLogCount(2)));
    DestinationPtr debugDestination(DestinationFactory::MakeDebugOutputDestination());
    DestinationPtr functorDestination(DestinationFactory::MakeFunctorDestination(&logFunction));
    logger.addDestination(debugDestination);
    logger.addDestination(fileDestination);
    logger.addDestination(functorDestination);

    QLOG_INFO() << "|_______________________________";
    QLOG_INFO() << "|Program started";


    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    qApp->installTranslator(&qtTranslator);


    QTranslator *translator= new QTranslator;

    translator->load(":/language/entr_pt_qm");
    qApp->installTranslator(translator);


    //qxtLog->debug()<<translator->tr("Initializing application...");


    MainWindow w;


    qApp->setStyleSheet(ApplicationSettings::loadStyleSheet(":/glossy"));

    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint) ;

    w.showMaximized();



    QObject::connect(&a, SIGNAL(focusChanged(QWidget*,QWidget*)), &w, SLOT(focusChanged(QWidget*,QWidget*)));



    const int r=a.exec();

    QsLogging::Logger::destroyInstance();

    return r;




}
