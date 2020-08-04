#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QDebug>
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Client *client;

signals:
    void needToConnect(QString ip);
    void needToDisconnect();
    void changeProtocol(int i);
    void needToConnectUdp();
    void needToDisconnectUdp();

public slots:
    void printResponse(QString response);
    void printError(QString errstr);
    void disconnectedFromHost();
    void connectedToHost();
    void printState(QAbstractSocket::SocketState currState);
    void unableToConnect();

private slots:
    void on_connectButton_clicked();
    void on_disconnectButton_clicked();
    void on_clearButton_clicked();
    void on_checkTcp_stateChanged(int arg1);
    void on_checkUdp_stateChanged(int arg1);
};
#endif // MAINWINDOW_H
