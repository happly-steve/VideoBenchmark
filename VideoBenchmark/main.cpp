#include "mainwindow.h"
#include <QApplication>
#include "qslog/QsLog.h"
#include "qslog/QsLogDest.h"
#include "qslog/QsLogMessage.h"

extern "C"
{
#include "SDL2/SDL.h"
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString str = argv[1];

    MainWindow w(str);

    w.show();

    using namespace QsLogging;

    Logger& logger = Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);
    const QString sLogPath(QDir(a.applicationDirPath()).filePath("log.txt"));
    DestinationPtrU fileDestination(DestinationFactory::MakeFileDestination(
                                    sLogPath,
                                    LogRotationOption::EnableLogRotation,
                                    MaxSizeBytes(512),
                                    MaxOldLogCount(2)));
    DestinationPtrU debugDestination(DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(std::move(debugDestination));
    logger.addDestination(std::move(fileDestination));

    QLOG_INFO() << "testmain";

    return a.exec();
}
