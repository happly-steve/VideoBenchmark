#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QDebug>

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
    QString tmp;
    QTcpSocket *tcpSocket;

public slots:
    void onReadyRead();
    void getResponse();
    void printError();
    void disconnectedFromHost();
    void connectedToHost();


private slots:
    void on_connectButton_clicked();
    //void on_disconnectButton_clicked();
    void on_pushButton2_clicked();
};
#endif // MAINWINDOW_H
