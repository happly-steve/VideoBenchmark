#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tcpSocket = new QTcpSocket(this);
    //tcpSocket->connectToHost("127.0.0.1", 5000);

    connect(tcpSocket, SIGNAL(connected()),
            this, SLOT(connectedToHost()));
    connect(tcpSocket, SIGNAL(readyRead()),
            this, SLOT(onReadyRead()));
    connect(tcpSocket, SIGNAL(readyRead()),
            this, SLOT(getResponse()));
    connect(tcpSocket, SIGNAL(errorOccurred()),
            this, SLOT(printErrr()));
    connect(tcpSocket, SIGNAL(disconnectedFromHost()),
            this, SLOT(disconnect()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onReadyRead() {
    tmp = QString::fromLatin1(tcpSocket->readAll());
    qDebug() << tmp;
}
void MainWindow::getResponse(){
    ui->label->setText(tmp);
    //ui->label->show();
}
void MainWindow::printError() {
    qDebug() << tcpSocket->errorString();
}

void MainWindow::disconnectedFromHost()
{
    qDebug() << "disconnected";
    ui->label->setText("disconnected");
}

void MainWindow::connectedToHost()
{
    qDebug() << "connected";
}

void MainWindow::on_connectButton_clicked()
{
    tcpSocket->connectToHost("127.0.0.1", 5000);
}
// TODO:
void MainWindow::on_pushButton2_clicked()
{
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}
