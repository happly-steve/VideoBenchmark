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
    series1 = new QLineSeries();
    series2 = new QLineSeries();
    chartView1 = new QChartView();
    chartView2 = new QChartView();
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

    connect(client, SIGNAL(response(QString)),
            this, SLOT(drawCharts(QString)));

    connect(this, SIGNAL(canShow(QChart*, QChart*)),
            this, SLOT(showCharts(QChart*, QChart*)));

    connect(this, SIGNAL(needStream()),
            client, SLOT(getStream()));
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

void MainWindow::drawCharts(QString data)
{

    QChart *chart1 = new QChart();
    QChart *chart2 = new QChart();
    //TODO: get ints of frames and bytes and draw charts for them continously
    int frames = data.remove(data.indexOf("Frames:"), 7).toInt();
    int bytes = data.remove(data.indexOf("Bytes decoded:"), 14).toInt();
    QLOG_DEBUG() << frames;
    QLOG_DEBUG() << bytes;
    *series1 << QPointF(n, frames);
    *series2 << QPointF(n, bytes);
    n++;
    chart1->legend()->hide();
    chart1->addSeries(series1);
    chart1->createDefaultAxes();
    chart2->legend()->hide();
    chart2->addSeries(series2);
    chart2->createDefaultAxes();
    emit canShow(chart1, chart2);

}
void MainWindow::showCharts(QChart *chart1, QChart *chart2){
    chartView1->setChart(chart1);
    chartView2->setChart(chart2);
    chartView1->setParent(ui->chartWidget);
    chartView2->setParent(ui->chartWidget2);
    chartView1->setRenderHint(QPainter::Antialiasing);
    chartView2->setRenderHint(QPainter::Antialiasing);
    chartView1->show();
    chartView2->show();
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

void MainWindow::on_videoButton_clicked()
{
    emit needStream();
}
