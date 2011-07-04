#include <QtCore/QCoreApplication>
#include "logger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Logger::log("test");

    return a.exec();
}
