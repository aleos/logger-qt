/*! \file    logger.h
    \author  aleos <aleos@flightstudio.ru>
*/

#ifndef __LOGGER_H
#define __LOGGER_H

#include <iostream>
#include <fstream>
#include <map>
#include <QDateTime>

//class OnlyOne
//{
//public:
//        static OnlyOne* Instance()
//        {
//                if(theSingleInstance==NULL)
//                        theSingleInstance=new OnlyOne;
//                return theSingleInstance;
//        }
//private:
//        static OnlyOne* theSingleInstance;
//        OnlyOne(){}
//};

typedef std::map<const char*, std::ofstream*> filesMap;
typedef std::pair<const char*, std::ofstream*> filesMapPair;

//! Logger
class FLogger  : public QObject
{
    Q_OBJECT

protected:

    static FLogger* logger;

    filesMap files;
    const char *commonLogFileName;


public:

    FLogger(const FLogger&);

//    static void addLogFile(const int id, const QString& logfilename);

    static void finish()
    {
        delete getLogger();
        logger = NULL;
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

    FLogger();
    virtual ~FLogger();

    static FLogger* getLogger()
    {
        if (logger == NULL) {
            logger = new FLogger;
            logger->commonLogFileName = "logger.log";
            logger->files.insert(filesMapPair(logger->commonLogFileName, new std::ofstream(logger->commonLogFileName)));
        }

        return logger;
    }

    void logText(const QString &logFileName, const QString& logMessage, bool isConsoleOnly = false);
    void logText(const QString& logMessage, bool isConsoleOnly = false);
    void logText(const char* logFileName, const char* logMessage, bool consoleOnly = false);
    void logTextToFileOnly(const QString& text);
};

#endif /* __LOGGER_H */

