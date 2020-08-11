#include <QCoreApplication>
#include <QThreadPool>
#include <QFile>
#include "tcp.h"
#include "udp.h"
#include "mydata.h"
#include "qslog/QsLog.h"
#include "qslog/QsLogDest.h"
#include "qslog/QsLogMessage.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString arg1 = argv[1];
    QString arg2;
    if (argv[2] != NULL) {
        arg2 = argv[2];
    }
    TCP *tcp = nullptr;
    UDP *udp = nullptr;
    if (arg1 == "tcp") {
        tcp = new TCP();
    }
    if (arg1 == "udp") {
        udp = new UDP(arg2);
    }

    MyData *video;
    video = new MyData();
    QThreadPool::globalInstance()->start(video);


    using namespace QsLogging;

    Logger& logger = Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);
    const QString sLogPath(QDir(a.applicationDirPath()).filePath("log.txt"));
    DestinationPtrU fileDestination(DestinationFactory::MakeFileDestination(                                    sLogPath,
                                  LogRotationOption::DisableLogRotation,
                                    MaxSizeBytes(512),
                                    MaxOldLogCount(1)));
    DestinationPtrU debugDestination(DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(std::move(debugDestination));
    logger.addDestination(std::move(fileDestination));

    QLOG_INFO() << "testmain";


    return a.exec();
}
