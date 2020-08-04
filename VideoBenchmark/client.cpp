#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    statetimer = new QTimer();
//  Проверяет состояние подключения каждые 2 сек
    connect(statetimer, SIGNAL(timeout()),
            this, SLOT(getState()));

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
    statetimer->start(2000);
}
void Client::disconnectFromHost()
{
    tcpSocket->disconnectFromHost();
    emit disconnected();
    statetimer->stop();
}

void Client::disconnectFromUdp()
{
    udpSocket->disconnectFromHost();
    emit disconnected();
}
void Client::getState()
{
    currState = tcpSocket->state();
//    emit state(currState);
    qDebug() << currState;
    emit noConnection();

}
void Client::getResponse()
{
    tmp = QString::fromLatin1(tcpSocket->readAll());
    if (statetimer->isActive()){
        statetimer->stop();
        statetimer->start(2000);
    }
    emit response(tmp);
}
void Client::getUdpData()
{
    if (udpSocket->hasPendingDatagrams()) {
        QByteArray dg;
        dg.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(dg.data(), dg.size());
        tmp = QString::fromLatin1(dg);
        emit response(tmp);
    }
}
void Client::newProtocol(int protocol) {
    switch (protocol) {
        case 1:
            tcpSocket = new QTcpSocket(this);
        //  Получает данные по протоколу tcp после подключения
            connect(tcpSocket, SIGNAL(readyRead()),
                    this, SLOT(getResponse()));
            break;

        case 2:
            udpSocket = new QUdpSocket(this);
            udpSocket->bind(QHostAddress::Any, 9877);
        //  Получает данные по протоколу udp после подключения
            connect(udpSocket, SIGNAL(readyRead()),
                    this, SLOT(getUdpData()));
            break;

        default:
            emit error("Wrong protocol");
            qDebug() << "Wrong protocol";
            break;
    }
}
