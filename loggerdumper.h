#ifndef LOGGERDUMPER_H
#define LOGGERDUMPER_H

#include <QThread>
#include "flogger.h"


//! Class for dump accumulated messages in messages list to log output.
class LoggerDumper : public QThread
{
    Q_OBJECT
public:
    //! Constructor for init members.
    /*!
      /param isRun Flag of thread's life.
      /param commonLogFileName Name of general log file.
      /param files Collection of file names and streams.
      /param messages Collection of a messages.
      */
    LoggerDumper(bool *isRun, std::string *commonLogFileName, FilesMap *files, std::list<Message> *messages);
    //! Destructor
    ~LoggerDumper(void);

    //! Entry point for thread. Call write() method.
    void run(void);

private:
    //! Flag of a thread's life.
    bool *isRun;
    //! Pointer to a common log file name string.
    std::string *commonLogFileName;
    //! Pointer to a files collection.
    FilesMap *files;
    //! Pointer to a messages collection.
    std::list<Message> *messages;

    //! Mutex for locking write to a file and/or to a terminal.
    QMutex writeLocker;

    //! Write messages from messages list to a log output.
    void write(void);
};

#endif // LOGGERDUMPER_H
