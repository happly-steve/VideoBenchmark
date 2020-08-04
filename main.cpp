#include <QCoreApplication>
#include "tcp.h"
#include "udp.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString str = argv[1];
    TCP *tcp = nullptr;
    UDP *udp = nullptr;
    if (str == "tcp") {
        tcp = new TCP();
    }
    if (str == "udp") {
        udp = new UDP();
    }
    return a.exec();
}
