#include <QTimer>
#include "loggerdumper.h"

LoggerDumper::LoggerDumper(QObject *parent) :
    QThread(parent)
{
}

void LoggerDumper::run()
{
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), SLOT(slotDump())) ;
    timer.start(1000);

    exec();
}
