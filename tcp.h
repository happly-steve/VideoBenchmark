#ifndef TCP_H
#define TCP_H

#include <QObject>
#include <QtNetwork>
#include <QString>
#include "qslog/QsLog.h"
#include "datasource.h"

class TCP : public QObject
{
    Q_OBJECT

public:
    explicit TCP(QObject *parent = nullptr);

private:
    QTcpServer *tcpServer = nullptr;
    QTcpSocket *tcpSocket = nullptr;
    DataSource *ds = nullptr;

private slots:
    void onNewConnection();
    void onError(QAbstractSocket::SocketError err);
    void sendResponse();
    void sendData(QString rdata);

};

#endif // TCP_H
