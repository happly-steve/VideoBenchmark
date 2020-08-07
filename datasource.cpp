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
      int prevframes = 0;
      int prevbytes = 0;
      int frames = 0;
      int bytes = 0;
        while (!file.atEnd()) {
            QByteArray tmp = file.readLine();
            QString line = QString(tmp);
            if (line.contains("Frames:")) {
                line.remove(0, line.indexOf(":")+1);
                line.remove(line.length()-2, line.length());
                prevframes = frames;
                frames = line.toInt() - prevframes;
            }
            if (line.contains("Bytes decoded:")) {
                line.remove(0, line.indexOf(":")+1);
                line.remove(line.length()-2, line.length());
                prevbytes = bytes;
                bytes = line.toInt() - prevbytes;
            }
            procData("Frames:" + QString::number(frames) + ", Bytes decoded:" + QString::number(bytes));
        }
        file.close();
    }
}
void DataSource::procData(QString d) {
    dataPacket = "";
    dataPacket = d;
}

