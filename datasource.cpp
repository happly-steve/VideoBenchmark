#include "datasource.h"
#include "tcp.h"
#include "packet.h"

DataSource::DataSource(QObject *parent) : QObject(parent)
{
    TCP *socket1;
    socket1 = new TCP();
    connect(socket1, SIGNAL(dataReceived()),
            this, SLOT(setData()));
    connect(socket1, SIGNAL(dataReceived()),
            this, SLOT(getData()));
}
void DataSource::onTimeoutCMD() {
    dataReceived();
}
void DataSource::setData() {
    dataPacket = cmdname + cmd + lengthname + dataname + data;
    length = dataPacket.length();
    int index = dataPacket.indexOf(lengthname);
    dataPacket.insert(index+8, QString::number(length));
    dataPacket += ";";
}
void DataSource::getData() {
    Packet pack;
    if (dataPacket.contains(";")
        && dataPacket.indexOf(";") == dataPacket.length()-1) {
        QStringList list = dataPacket.split(":");
        pack.cmd = list[cmdid];
        pack.length = list[lengthid];
        pack.data = list[dataid].remove(5,1);
    }
    qDebug() << pack.cmd;
    qDebug() << pack.length;
    qDebug() << pack.data;
}

