#ifndef UDP_H
#define UDP_H

#include <QObject>
#include <QtNetwork>
#include <QString>
#include "qslog/QsLog.h"
#include "QsLog.h"
#include "datasource.h"

class UDP : public QObject
{
    Q_OBJECT

public:
    explicit UDP(QString recip, QObject *parent = nullptr);

private:
    DataSource *ds = nullptr;
    QUdpSocket *udpSocket = nullptr;
    QHostAddress receiverIp;

signals:
    void canSend();

private slots:
    void sendData(QString rdata);

};

#endif // UDP_H
