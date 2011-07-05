/*! \file    logger.h
    \author  aleos <aleos@flightstudio.ru>
*/

#ifndef __LOGGER_H
#define __LOGGER_H

#include <QDebug>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QObject>
#include <QDateTime>
//#include <windows.h>

//#include "assert.h"

//#if (defined _MSC_VER )
////#define _CRT_SECURE_NO_WARNINGS
//#define _CRT_SECURE_NO_DEPRECATE
//#endif

//! Logger
class Logger  : public QObject
{
    Q_OBJECT

protected:

    static Logger* logger;

    QFile* file;
    QTextStream* filestream;

public:

    static Logger* getLogger()
    {
        if (logger == 0)
            logger = new Logger;

        return logger;
    }

    static void finish()
    {
        delete getLogger();
        logger = 0;
    }

    //! logs to console and file
    static void log(const QString& text, bool isConsoleOnly = false)
    {
        getLogger()->logText(text, isConsoleOnly);
    }

//    static int printf(const char* fmt,...)
//    {
//        char* args;
//        va_start(args,fmt);
//        char _buf[0x1000];
//        unsigned long dwWritten;
//        dwWritten=vsprintf_s(_buf, 0x1000, fmt, args);
//        WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),_buf,dwWritten,&dwWritten,NULL);
//        return (int)dwWritten;
//    }

    //! logs to file only
    static void logToFileOnly(const QString& text)
    {
        getLogger()->logTextToFileOnly(text);
    }

    //-----

    Logger();
    virtual ~Logger();

    void setLogFile(const QString& logfilename);
    void logText(const QString& text, bool console_only = false);
    void logTextToFileOnly(const QString& text);

signals:

    void signalLogging(const QString& text);

private:
    //! Hidden copy-constructor
    Logger(const Logger&);
    //! Hidden assignment operator
    const Logger& operator = (const Logger&);
};

#endif /* __LOGGER_H */

