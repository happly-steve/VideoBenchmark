#include "udp.h"

UDP::UDP(QString recIp, QObject *parent) : QObject(parent)
{
    ds = new DataSource();
    udpSocket = new QUdpSocket(this);
    receiverIp = QHostAddress(recIp);
    udpSocket->open(QIODevice::WriteOnly);
    connect(ds, SIGNAL(dataReceived(QString)),
            this, SLOT(sendData(QString)));


}
void UDP::sendData(QString rdata)
{
    QByteArray sData = rdata.toLatin1();
    udpSocket->writeDatagram(sData, receiverIp, 9877);
    qDebug() << "Send UDP data" << sData;
}
