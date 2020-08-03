#ifndef TCP_H
#define TCP_H

#include <QObject>
#include <QtNetwork>
#include <QString>

class TCP : public QObject
{
    Q_OBJECT

public:
    explicit TCP(QObject *parent = nullptr);

private:
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    QTimer *timer;

signals:
    void dataReceived();

private slots:
    void onTimeoutCMD();
    void onNewConnection();
    void onError(QAbstractSocket::SocketError err);
    void sendResponse();

};

#endif // TCP_H
