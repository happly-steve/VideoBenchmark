#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork>
#include <QDebug>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

private:
    QString tmp;
    QTcpSocket *tcpSocket;
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
    void getState();
    void getResponse();

};

#endif // CLIENT_H
