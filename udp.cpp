#include "udp.h"

UDP::UDP(QObject *parent) : QObject(parent)
{
    ds = new DataSource();
    udpSocket = new QUdpSocket(this);

    connect(ds, SIGNAL(dataReceived(QString)),
            this, SLOT(sendData(QString)));

}
void UDP::sendData(QString rdata)
{
        QByteArray sData = rdata.toLatin1();
        udpSocket->writeDatagram(sData, QHostAddress::Broadcast, 9877);
        qDebug() << "Send UDP data";
}
