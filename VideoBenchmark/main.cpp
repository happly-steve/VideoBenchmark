#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString str = argv[1];

    MainWindow w(str);
    w.show();
    return a.exec();
}
