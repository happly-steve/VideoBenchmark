#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork>
#include <QDebug>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QString protocol, QObject *parent = nullptr);

private:
    QString tmp;
    QTcpSocket *tcpSocket = nullptr;
    QUdpSocket *udpSocket = nullptr;
    QString ip;
    QTimer *statetimer;
    QAbstractSocket::SocketState currState;

signals:
    void noConnection();
    void connected();
    void disconnected();
    void response(QString response);
    void error(QString errstr);
    void state(QAbstractSocket::SocketState currState);

public slots:
    void connectToHost(QString mip);
    void disconnectFromHost();
    void disconnectFromUdp();
    void getState();
    void getResponse();
    void getUdpData();

};

#endif // CLIENT_H
