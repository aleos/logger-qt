#include <QtCore/QCoreApplication>
#include <QTextCodec>
#include "logger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    Logger logger;
    logger.setLogFile("Logger.log");
    logger.logText("12345");

    QFile file("filetest.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream fstream(&file);
    QString str("qstr");
    fstream << str << endl;

    return a.exec();
}
