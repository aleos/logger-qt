#include <QtCore/QCoreApplication>

#include "flogger.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FLogger::log("hi");
    FLogger::log("hello.log", QString("hello"));
    FLogger::log("end");

    for (int i = 0; i < 100000; i++) {
        FLogger::log(QString("%1").arg(i));
    }
    return a.exec();
}
