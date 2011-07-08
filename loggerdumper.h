#ifndef LOGGERDUMPER_H
#define LOGGERDUMPER_H

#include <QThread>
#include "flogger.h"

class LoggerDumper : public QThread
{
    Q_OBJECT
public:
//    explicit LoggerDumper(QObject *parent = 0);
    LoggerDumper(bool *isRun, std::string *commonLogFileName, FilesMap *files, std::list<Message> *messages);
    ~LoggerDumper(void);

    void run(void);

private:
    bool *isRun;
    std::string *commonLogFileName;
    FilesMap *files;
    std::list<Message> *messages;

    QMutex writeLocker;

    void write(void);
};

#endif // LOGGERDUMPER_H
