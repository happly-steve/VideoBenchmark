#include "tcp.h"

// Объявляет и запускает TCP-сервер
TCP::TCP(QObject *parent) : QObject(parent)
{
    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any, 5000);

    connect(tcpServer, SIGNAL(newConnection()),
            this, SLOT(onNewConnection()));
    connect(tcpServer, SIGNAL(acceptError(QAbstractSocket::SocketError)),
            this, SLOT(onError(QAbstractSocket::SocketError)));
}
void TCP::onTimeoutCMD() {
    dataReceived();
}
void TCP::onNewConnection() {
    qDebug() << "New connection appeared";
    tcpSocket = tcpServer->nextPendingConnection();
        timer = new QTimer();
        timer->start(500);
        connect(timer, SIGNAL(timeout()),
                this, SLOT(sendResponse()));
}

void TCP::onError(QAbstractSocket::SocketError err)
{
    qDebug() << tcpServer->errorString();
}

void TCP::sendResponse()
{
    if (tcpSocket->state() != 0) {
        QByteArray response = QString("Hello").toLatin1();
        tcpSocket->write(response);
        qDebug() << "Send response";
    }
    else {
        timer->stop();
    }
}
