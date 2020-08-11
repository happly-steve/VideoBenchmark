#include "client.h"

Client::Client(QString protocol, QObject *parent) : QObject(parent)
{
    if (protocol == "tcp") {
        proto = 1;
    }
    if (protocol == "udp") {
        proto = 2;
    }
    switch (proto) {
        case 1:
            tcpSocket = new QTcpSocket(this);
//          Получает данные по протоколу tcp после подключения
            connect(tcpSocket, SIGNAL(readyRead()),
                    this, SLOT(getTcpResponse()));
            break;

        case 2:
            udpSocket = new QUdpSocket(this);
            udpSocket->open(QIODevice::ReadOnly);
//          Получает данные по протоколу udp после подключения
            connect(udpSocket, SIGNAL(readyRead()),
                    this, SLOT(getUdpResponse()));
            break;

        default:
            emit error("Wrong protocol");
            QLOG_DEBUG() << "Wrong protocol";
        break;
    }
    statetimer = new QTimer();
//  Проверяет состояние подключения каждые 3 сек
    connect(statetimer, SIGNAL(timeout()),
            this, SLOT(getState()));

}
void Client::connectTcp(QString mip)
{
    tcpSocket->connectToHost(mip, 5000);
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
void Client::connectUdp(QString hip) {
    hostIp = QHostAddress(hip);
    udpSocket->bind(9877);
    emit connected();
    statetimer->start(3000);
}
void Client::disconnectFromTcp()
{
    tcpSocket->disconnectFromHost();
    emit disconnected();
    statetimer->stop();
}
void Client::disconnectFromUdp()
{
    udpSocket->abort();
    emit disconnected();
    statetimer->stop();
}
void Client::getState()
{
    if (proto == 1) {
        currState = tcpSocket->state();
    }
    if (proto == 2) {
        currState = udpSocket->state();
    }
//  emit state(currState);
   QLOG_DEBUG() << currState;
    emit noConnection();
    if (proto == 1) {
        connectTcp(hostIp.toString());
    }
    if (proto == 2) {
        connectUdp(hostIp.toString());
    }
}
void Client::getTcpResponse()
{
    tmp = QString::fromLatin1(tcpSocket->readAll());
    if (statetimer->isActive()){
        statetimer->stop();
        statetimer->start(2000);
    }
    emit response(tmp);
}
void Client::getUdpResponse()
{
    if (udpSocket->hasPendingDatagrams()) {
        QByteArray dg;
        dg.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(dg.data(), dg.size());
        tmp = QString::fromLatin1(dg);
        if (statetimer->isActive()){
            statetimer->stop();
            statetimer->start(3000);
        }
        emit response(tmp);
    }
}

void Client::getStream()
{
    //char stream[] = "rtsp://admin:q1w2e3r4@91.226.107.146:554/Streaming/Channels/1302";
    Player *pl;
    pl = new Player();
    QThreadPool::globalInstance()->start(pl);
}
