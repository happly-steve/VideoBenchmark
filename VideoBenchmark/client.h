#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork>
#include <QDebug>
#include "player.h"
#include <qslog/QsLog.h>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QString protocol, QObject *parent = nullptr);

private:
    QString tmp;
    QTcpSocket *tcpSocket = nullptr;
    QUdpSocket *udpSocket = nullptr;
    QHostAddress hostIp;
    QTimer *statetimer;
    QAbstractSocket::SocketState currState;
    int proto = 1;
    //char streamname[];

signals:
    void noConnection();
    void connected();
    void disconnected();
    void response(QString response);
    void error(QString errstr);
    void state(QAbstractSocket::SocketState currState);

public slots:
    void connectTcp(QString mip);
    void connectUdp(QString ip);
    void disconnectFromTcp();
    void disconnectFromUdp();
    void getState();
    void getTcpResponse();
    void getUdpResponse();
    void getStream();
};

#endif // CLIENT_H
