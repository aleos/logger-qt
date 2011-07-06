#include <QtCore/QCoreApplication>
#include <QTextCodec>

#include "logger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    Logger::addLogFile(1, "vasya.txt");
    Logger::log("hi");
    Logger::log("hello");
    Logger::log("end");



//    std::map<int, std::ofstream*> m;
//    m.insert(std::pair<int, std::ofstream*>(0, new std::ofstream("0")));
//    m.insert(std::pair<int, std::ofstream*>(1, new std::ofstream("1")));

//    std::map<int, std::ofstream*>::iterator iter = m.begin();
//    iter = m.find(1);
//    *iter->second << "lskjdf";
//    iter->second->close();

    std::ofstream f("qwe.txt");
    f << "hi" << "\n";
    f.flush();
    f << "hello" << "\n";
    f.flush();


    return a.exec();
}
