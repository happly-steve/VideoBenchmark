#include "tcp.h"


TCP::TCP(QObject *parent) : QObject(parent)
{
    ds = new DataSource();
    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any, 5000);
    tcpSocket = new QTcpSocket();
//  Принимает данные по сигналу источника данных и передает их клиенту
    connect(ds, SIGNAL(dataReceived(QString)),
            this, SLOT(sendData(QString)));
//  Инициализирует новое tcp подключение на сокете
    connect(tcpServer, SIGNAL(newConnection()),
            this, SLOT(onNewConnection()));
//  Обработчик ошибок на стороне сервера
    connect(tcpServer, SIGNAL(acceptError(QAbstractSocket::SocketError)),
            this, SLOT(onError(QAbstractSocket::SocketError)));

}
void TCP::onNewConnection()
{
    qDebug() << "New connection appeared";
    tcpSocket = tcpServer->nextPendingConnection();
    sendResponse();
}
void TCP::onError(QAbstractSocket::SocketError err)
{
//    QLOG_DEBUG() << tcpServer->errorString();
}
void TCP::sendResponse()
{
    QByteArray response = QString("Hello").toLatin1();
    tcpSocket->write(response);
    qDebug() << "Send response";
}
void TCP::sendData(QString rdata)
{
    if (tcpSocket->state() != 0) {
        QByteArray sData = rdata.toLatin1();
        tcpSocket->write(sData);
        qDebug() << "Send data";
    }
}
