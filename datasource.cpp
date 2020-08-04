#include "datasource.h"
#include "packet.h"

DataSource::DataSource(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    timer->start(1000);
//  Собирает данные и дает сигнал на отправку по таймауту
    connect(timer, SIGNAL(timeout()),
            this, SLOT(setData()));

}
void DataSource::setData()
{
    dataPacket = cmdname + cmd + lengthname + dataname + data;
    length = dataPacket.length();
    int index = dataPacket.indexOf(lengthname);
    dataPacket.insert(index+8, QString::number(length));
    dataPacket += ";";
    emit dataReceived(dataPacket);
}
//void DataSource::getData()
//{
//    Packet pack;
//    if (dataPacket.contains(";")
//        && dataPacket.indexOf(";") == dataPacket.length()-1) {
//        QStringList list = dataPacket.split(":");
//        pack.cmd = list[cmdid];
//        pack.length = list[lengthid];
//        pack.data = list[dataid].remove(5,1);
//    }
//    qDebug() << pack.cmd;
//    qDebug() << pack.length;
//    qDebug() << pack.data;
//}

