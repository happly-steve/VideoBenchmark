#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QFile>
#include "qslog/QsLog.h"

// объявляет формат и способ формирования пакетов данных
class DataSource : public QObject
{
    Q_OBJECT

public:
    explicit DataSource(QObject *parent = nullptr);
    struct Packet {
        QString cmd;
        QString length;
        QString data;
    };
    QTimer *timer = nullptr;

private:
    QString dataPacket;
    int prevframes = 0;
    long int prevbytes = 0;
    int frames = 0;
    long int bytes = 0;
    int frres = 0;
    long int byres = 0;
    void procData(QString d);

signals:
    void dataReceived(QString rdata);

public slots:
    void getData();
    void setData();

};

#endif // DATASOURCE_H
