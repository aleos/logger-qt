/*! \file    logger.h
    \author  aleos <aleos@flightstudio.ru>
*/

#ifndef __LOGGER_H
#define __LOGGER_H

#include <iostream>
#include <fstream>

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

typedef std::map<const char*, std::ofstream*> filesMap;
typedef std::pair<const char*, std::ofstream*> filesMapPair;

//! Logger
class Logger  : public QObject
{
    Q_OBJECT

protected:

    static Logger* logger;

    std::ofstream stdLogFile;
    filesMap files;
    const char *commonLogFileName;

    std::ofstream file;

public:

    Logger(const Logger&);

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

    static Logger* getLogger()
    {
        if (logger == NULL) {
            logger = new Logger;
            logger->commonLogFileName = "logger.log";
            logger->files.insert(filesMapPair(logger->commonLogFileName, new std::ofstream(logger->commonLogFileName)));
        }

        return logger;
    }

    void logText(const QString &logFileName, const QString& logMessage, bool isConsoleOnly = false);
    void logText(const QString& logMessage, bool isConsoleOnly = false);
    void logText(char* logFileName, char* logMessage, bool consoleOnly = false);
    void logTextToFileOnly(const QString& text);
};

#endif /* __LOGGER_H */

