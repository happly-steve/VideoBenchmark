#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QtCharts>
#include <qslog/QsLog.h>
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString protocol, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Client *client = nullptr;
    QLineSeries *series1 = nullptr;
    QLineSeries *series2 = nullptr;
    int n = 0;
//    QChart *chart1 = nullptr;
//    QChart *chart2 = nullptr;
    QChartView *chartView1 = nullptr;
    QChartView *chartView2 = nullptr;

signals:
    void needToConnectTcp(QString ip);
    void needToDisconnectTcp();
    void needToConnectUdp(QString ip);
    void needToDisconnectUdp();
    void needStream();
    void canShow(QChart *chart1, QChart *chart2);

public slots:
    void printResponse(QString response);
    void printError(QString errstr);
    void disconnectedFromHost();
    void connectedToHost();
    void printState(QAbstractSocket::SocketState currState);
    void unableToConnect();
    void drawCharts(QString data);
    void showCharts(QChart *chart1, QChart *chart2);

private slots:
    void on_connectButton_clicked();
    void on_disconnectButton_clicked();
    void on_clearButton_clicked();
    void on_videoButton_clicked();
};
#endif // MAINWINDOW_H
