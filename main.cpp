#include <QtCore/QCoreApplication>

#include "flogger.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FLogger::log("hi");
    FLogger::log("hello.log", QString("hello"));
    FLogger::log("end");


    for (int i = 0; i < 10000000; i++) {
        FLogger::log(QString("%1").arg(i));
    }


//    std::map<int, std::ofstream*> m;
//    m.insert(std::pair<int, std::ofstream*>(0, new std::ofstream("0")));
//    m.insert(std::pair<int, std::ofstream*>(1, new std::ofstream("1")));

//    std::map<int, std::ofstream*>::iterator iter = m.begin();
//    iter = m.find(1);
//    *iter->second << "lskjdf";
//    iter->second->close();

//    std::ofstream f("qwe.txt");
//    f << "hi" << "\n";
//    f.flush();
//    f << "hello" << "\n";
//    f.flush();


    return a.exec();
}
