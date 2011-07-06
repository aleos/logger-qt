/*! \file    logger.h
    \author  aleos <aleos@flightstudio.ru>
*/

#ifndef __LOGGER_H
#define __LOGGER_H

#include <iostream>
#include <fstream>

#include <QDebug>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QObject>
#include <QDateTime>
#include <map>

class OnlyOne
{
public:
        static OnlyOne* Instance()
        {
                if(theSingleInstance==NULL)
                        theSingleInstance=new OnlyOne;
                return theSingleInstance;
        }
private:
        static OnlyOne* theSingleInstance;
        OnlyOne(){}
};

//! Logger
class Logger  : public QObject
{
    Q_OBJECT

protected:

    static Logger* logger;

    static std::ofstream stdLogFile;
    std::map<int, std::ofstream*> files;

    std::ofstream file;

public:

    Logger(const Logger&);

    static Logger* getLogger()
    {
        if (logger == 0) {
            logger = new Logger;
            logger->files.insert(std::pair<int, std::ofstream*>(0, new std::ofstream("logger.txt")));
        }

        return logger;
    }

//    static void addLogFile(const int id, const QString& logfilename);

    static void finish()
    {
        delete getLogger();
        logger = 0;
    }

    //! logs to console and file
    static void log(const QString &logFileName, const QString& text, bool isConsoleOnly = false)
    {
        getLogger()->logText(logFileName, text, isConsoleOnly);
    }

    static void log(const QString& text, bool isConsoleOnly = false)
    {
        getLogger()->logText(text, isConsoleOnly);
    }


    //! logs to file only
    static void logToFileOnly(const QString& text)
    {
        getLogger()->logTextToFileOnly(text);
    }

private:

    Logger();
    virtual ~Logger();

    void logText(const QString &logFileName, const QString& text, bool isConsoleOnly = false);
    void logText(const QString& text, bool isConsoleOnly = false);
    void logText(const char* logFileName, const char* logText, bool consoleOnly = false);
    void logTextToFileOnly(const QString& text);
};

#endif /* __LOGGER_H */

