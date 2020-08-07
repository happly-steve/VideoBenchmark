#include "mainwindow.h"
#include "videoplayer.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QtCore/QDir>
#include <QApplication>
//#include "qslog/QsLog.h"
//#include "qslog/QsLogDest.h"
//#include "qslog/QsLogMessage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString str = argv[1];

    QCommandLineParser parser;
    parser.setApplicationDescription("Qt Video Widget Example");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("url", "The URL to open.");
    parser.process(a);

    VideoPlayer player;
//    commandline options
//    if (!parser.positionalArguments().isEmpty()) {
//        const QUrl url =
//    QUrl::fromUserInput(parser.positionalArguments().constFirst(),
//                        QDir::currentPath(), QUrl::AssumeLocalFile);
//        player.setUrl(url);
//    }
    const QRect availableGeometry = QApplication::desktop()->availableGeometry(&player);
    player.resize(availableGeometry.width() / 6, availableGeometry.height() / 4);
    const QUrl url =
    QUrl::fromUserInput("rtsp://admin:q1w2e3r4@91.226.107.146:554/Streaming/Channels/1302");
    player.setUrl(url);
    player.play();
    player.show();

    MainWindow w(str);

    w.show();

//    using namespace QsLogging;

//    Logger& logger = Logger::instance();
//    logger.setLoggingLevel(QsLogging::TraceLevel);
//    const QString sLogPath(QDir(a.applicationDirPath()).filePath("log.txt"));
//    DestinationPtrU fileDestination(DestinationFactory::MakeFileDestination(
//                                    sLogPath,
//                                    LogRotationOption::EnableLogRotation,
//                                    MaxSizeBytes(512),
//                                    MaxOldLogCount(2)));
//    DestinationPtrU debugDestination(DestinationFactory::MakeDebugOutputDestination());
//    logger.addDestination(std::move(debugDestination));
//    logger.addDestination(std::move(fileDestination));

//    QLOG_INFO() << "testmain";

    return a.exec();
}
