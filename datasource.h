#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QFile>
//#include<QsLog.h>

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
    void procData(QString d);
private:
    QString dataPacket;

signals:
    void dataReceived(QString rdata);

public slots:
    void getData();
    void setData();

};

#endif // DATASOURCE_H
