#ifndef UDP_H
#define UDP_H

#include <QObject>
#include <QtNetwork>
#include <QString>
#include "datasource.h"

class UDP : public QObject
{
    Q_OBJECT

public:
    explicit UDP(QObject *parent = nullptr);

private:
    DataSource *ds = nullptr;
    QUdpSocket *udpSocket = nullptr;

private slots:
    void sendData(QString rdata);

};

#endif // UDP_H
