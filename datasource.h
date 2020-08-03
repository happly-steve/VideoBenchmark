#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include <QDebug>
#include <QTimer>

// объявляет формат и способ формирования пакетов данных
class DataSource : public QObject
{
    Q_OBJECT

public:
    explicit DataSource(QObject *parent = nullptr);
    QString cmd = "lol";
    int length = 0;
    QString data = "nolol";
    QString dataPacket;

private:
    struct Packet {
        QString cmd;
        QString length;
        QString data;
    };

signals:
    void dataReceived();

public slots:
    void getData();
    void setData();
    void onTimeoutCMD();

};

#endif // DATASOURCE_H
