#include "tcp.h"
// Объявляет и запускает TCP-сервер
TCP::TCP(QObject *parent) : QObject(parent)
{
    QTcpServer *tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any, 5000);

    connect(tcpServer, &QTcpServer::newConnection, [tcpServer] {
    QTcpSocket *tcpSocket = tcpServer->nextPendingConnection();
    QByteArray response = QString("Hello").toLatin1();
    tcpSocket->write(response);
    qDebug() << "Send response";
    });
    connect(tcpServer, &QTcpServer::acceptError, [tcpServer]{
    qDebug() << tcpServer->errorString();
    });
}
void TCP::onTimeoutCMD() {
    dataReceived();
}
