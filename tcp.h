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

signals:
    void dataReceived();

private slots:
    void onTimeoutCMD();

};

#endif // TCP_H
