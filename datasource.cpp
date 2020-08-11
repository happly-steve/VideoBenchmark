#include "datasource.h"
#include "packet.h"


DataSource::DataSource(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    timer->start(1000);
    connect(timer, SIGNAL(timeout()),
            this, SLOT(getData()));
    //  Собирает данные и отправляет по таймеру
    connect(timer, SIGNAL(timeout()),
            this, SLOT(setData()));

}
void DataSource::setData()
{
    emit dataReceived(dataPacket);
}
void DataSource::getData()
{
    QFile file("Framecount.txt");
    if (file.exists()) {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        while (!file.atEnd()) {
            QByteArray tmp = file.readLine();
            QString line = QString(tmp);
            if (line.contains("Frames:")) {
                prevframes = frames;
                line.remove(0, line.indexOf(":")+1);
                line.remove(line.length()-2, line.length());
                frames = line.toInt();
                frres = frames - prevframes;
            }
            if (line.contains("Bytes decoded:")) {
                prevbytes = bytes;
                line.remove(0, line.indexOf(":")+1);
                line.remove(line.length()-2, line.length());
                bytes = line.toInt();
                byres = bytes - prevbytes;
            }
        }
        file.close();
        QLOG_DEBUG() << frres;
        QLOG_DEBUG() << byres;
        procData("Frames:" +
                 QString::number(frres) +
                 ", Bytes decoded:" +
                 QString::number(byres));
    }
}
void DataSource::procData(QString d) {
    dataPacket = "";
    dataPacket = d;
}

