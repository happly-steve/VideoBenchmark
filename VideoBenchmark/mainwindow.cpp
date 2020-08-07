#include "mainwindow.h"


#include "ui_mainwindow.h"

MainWindow::MainWindow(QString protocol, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scrollArea->setWidget(ui->logLabel);




    if (protocol == "tcp") {
        ui->checkTcp->setChecked(true);
        ui->checkUdp->setChecked(false);
    }
    if (protocol == "udp") {
        ui->checkTcp->setChecked(false);
        ui->checkUdp->setChecked(true);
    }
    client = new Client(protocol);
//  Вызывает запрос на подключение к хосту по tcp
    connect(this, SIGNAL(needToConnectTcp(QString)),
            client, SLOT(connectTcp(QString)));
//  Вызывает запрос на подключение к хосту по udp
    connect(this, SIGNAL(needToConnectUdp(QString)),
            client, SLOT(connectUdp(QString)));
//  Вызывает запрос на отключение от tcp хоста
    connect(this, SIGNAL(needToDisconnectTcp()),
            client, SLOT(disconnectFromTcp()));
//  Вызывает запрос на отключение от udp хоста
    connect(this, SIGNAL(needToDisconnectUdp()),
            client, SLOT(disconnectFromUdp()));
//  Вызывается при обнаружении отсутствия подключения по таймауту 3 сек
    connect(client, SIGNAL(noConnection()),
            this, SLOT(unableToConnect()));
//  Вызывается при удачном подключении
    connect(client, SIGNAL(connected()),
            this, SLOT(connectedToHost()));
//  Вызывается при отключении
    connect(client, SIGNAL(disconnected()),
            this, SLOT(disconnectedFromHost()));
//  Вызывается при получении ошибки
    connect(client, SIGNAL(error(QString)),
            this, SLOT(printError(QString)));
//  Вызывается при получении ответа от хоста
    connect(client, SIGNAL(response(QString)),
            this, SLOT(printResponse(QString)));

//  Выводит состояние подключения
//    connect(client, SIGNAL(state(QAbstractSocket::SocketState)),
//            this, SLOT(printState(QAbstractSocket::SocketState)));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::printResponse(QString response)
{
    QString str = ui->logLabel->text();
    str.append(response);
    ui->logLabel->setText(str + "\n");
    ui->scrollArea->ensureVisible(0,
                                  ui->logLabel->size().rheight(),
                                  ui->logLabel->width()/6,
                                  ui->logLabel->height()/4);
}
void MainWindow::printState(QAbstractSocket::SocketState currState) {
    QString str = ui->logLabel->text();
    QString state = "";
    switch (currState) {
        case QAbstractSocket::UnconnectedState:
            state = "UnconnectedState";
        break;
        case QAbstractSocket::HostLookupState:
            state = "HostLookupState";
        break;
        case QAbstractSocket::ConnectingState:
            state = "ConnectingState";
        break;
        case QAbstractSocket::ConnectedState:
            state = "ConnectedState";
        break;
        case QAbstractSocket::BoundState:
            state = "BoundState";
        break;
        case QAbstractSocket::ClosingState:
            state = "ClosingState";
        break;
        case QAbstractSocket::ListeningState:
            state = "ListeningState";
        break;
    }
    str.append(state);
    ui->logLabel->setText(str + "\n");
}
void MainWindow::printError(QString errstr)
{
    QString str = ui->logLabel->text();
    str.append("ERR: " + errstr);
    ui->logLabel->setText(str + "\n");
    ui->scrollArea->ensureVisible(0,
                                  ui->logLabel->size().rheight(),
                                  ui->logLabel->width()/6,
                                  ui->logLabel->height()/4);
}
void MainWindow::unableToConnect()
{
    ui->status->setText("Not connected");
    QString str = ui->logLabel->text();
    str.append("Couldn't connect!");
    ui->logLabel->setText(str + "\n");
    ui->scrollArea->ensureVisible(0,
                                  ui->logLabel->size().rheight(),
                                  ui->logLabel->width()/6,
                                  ui->logLabel->height()/4);
}
void MainWindow::connectedToHost()
{
    ui->status->setText("Connected");
}
void MainWindow::disconnectedFromHost()
{
    ui->status->setText("Disconnected");
}
void MainWindow::on_connectButton_clicked()
{
    if (ui->checkTcp->isChecked()) {
        emit needToConnectTcp(ui->ipToConnect->text());
    }
    if (ui->checkUdp->isChecked()) {
        emit needToConnectUdp(ui->ipToConnect->text());
    }
}
void MainWindow::on_disconnectButton_clicked()
{
    if (ui->checkTcp->isChecked()) {
        emit needToDisconnectTcp();
    }
    if (ui->checkUdp->isChecked()) {
        emit needToDisconnectUdp();
    }
}
void MainWindow::on_clearButton_clicked()
{
    ui->logLabel->setText("");
}
