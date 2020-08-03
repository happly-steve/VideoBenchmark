#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scrollArea->setWidget(ui->logLabel);
    client = new Client();

    connect(this, SIGNAL(needToConnect(QString)),
            client, SLOT(connectToHost(QString)));

    connect(this, SIGNAL(needToDisconnect()),
            client, SLOT(disconnectFromHost()));

    connect(client, SIGNAL(noConnection()),
            this, SLOT(unableToConnect()));

    connect(client, SIGNAL(connected()),
            this, SLOT(connectedToHost()));

    connect(client, SIGNAL(disconnected()),
            this, SLOT(disconnectedFromHost()));

    connect(client, SIGNAL(error(QString)),
            this, SLOT(printError(QString)));

//    connect(client, SIGNAL(state(QAbstractSocket::SocketState)),
//            this, SLOT(printState(QAbstractSocket::SocketState)));

    connect(client, SIGNAL(response(QString)),
            this, SLOT(printResponse(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::printResponse(QString response){
    QString str = ui->logLabel->text();
    str.append(response);
    ui->logLabel->setText(str + "\n");
    ui->scrollArea->ensureVisible(530, ui->logLabel->size().rheight(),
                                  530, ui->logLabel->height()/4);
}
//void MainWindow::printState(QAbstractSocket::SocketState currState) {
//    QString str = ui->logLabel->text();
//    QString state = "";
//    switch (currState) {
//        case QAbstractSocket::UnconnectedState:
//            state = "UnconnectedState";
//        break;
//        case QAbstractSocket::HostLookupState:
//            state = "HostLookupState";
//        break;
//        case QAbstractSocket::ConnectingState:
//            state = "ConnectingState";
//        break;
//        case QAbstractSocket::ConnectedState:
//            state = "ConnectedState";
//        break;
//        case QAbstractSocket::BoundState:
//            state = "BoundState";
//        break;
//        case QAbstractSocket::ClosingState:
//            state = "ClosingState";
//        break;
//        case QAbstractSocket::ListeningState:
//            state = "ListeningState";
//        break;
//    }
//    str.append(state);
//    ui->logLabel->setText(str + "\n");
//}
void MainWindow::printError(QString errstr) {
    QString str = ui->logLabel->text();
    str.append(errstr);
    ui->logLabel->setText("ERR: "+ str + "\n");
    ui->scrollArea->ensureVisible(530, ui->logLabel->size().rheight(),
                                  530, ui->logLabel->height()/4);
}
void MainWindow::unableToConnect() {
    QString str = ui->logLabel->text();
    str.append("Couldn't connect!");
    ui->logLabel->setText(str + "\n");
    ui->scrollArea->ensureVisible(530, ui->logLabel->size().rheight(),
                                  530, ui->logLabel->height()/4);
}
void MainWindow::connectedToHost() {
    QString str = ui->logLabel->text();
    str.append("Connected!");
    ui->logLabel->setText(str + "\n");
    ui->scrollArea->ensureVisible(530, ui->logLabel->size().rheight(),
                                  530, ui->logLabel->height()/4);
}
void MainWindow::disconnectedFromHost() {
    QString str = ui->logLabel->text();
    str.append("Disconnected!");
    ui->logLabel->setText(str + "\n");
    ui->scrollArea->ensureVisible(530, ui->logLabel->size().rheight(),
                                  530, ui->logLabel->height()/4);
}
void MainWindow::on_connectButton_clicked()
{
    emit needToConnect(ui->ipToConnect->text());
}
void MainWindow::on_disconnectButton_clicked()
{
    emit needToDisconnect();
}

