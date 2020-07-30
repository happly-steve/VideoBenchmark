#include <QCoreApplication>
#include "datasource.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DataSource ds;

    return a.exec();
}
