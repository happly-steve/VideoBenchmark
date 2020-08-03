#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    tcpSocket = new QTcpSocket(this);
    statetimer = new QTimer();

    connect(statetimer, SIGNAL(timeout()),
            this, SLOT(getState()));

    connect(tcpSocket, SIGNAL(readyRead()),
            this, SLOT(getResponse()));

}
void Client::connectToHost(QString mip)
{
    ip = mip;
    tcpSocket->connectToHost(ip, 5000);
    if (!tcpSocket->waitForConnected(3000)) {
        emit noConnection();
        QString errstr = tcpSocket->errorString();
        emit error(errstr);
    }
    else {
        emit connected();
    }
    statetimer->start(1500);
}
void Client::disconnectFromHost()
{
    tcpSocket->disconnectFromHost();
    emit disconnected();
    statetimer->stop();
}
void Client::getState() {
    currState = tcpSocket->state();
//    emit state(currState);
    qDebug() << currState;
    if (!tcpSocket->waitForConnected(3000)) {
        emit noConnection();
        tcpSocket->connectToHost(ip, 5000);
    }
}
void Client::getResponse() {
    tmp = QString::fromLatin1(tcpSocket->readAll());
    emit response(tmp);
}


