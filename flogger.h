/*! \file    logger.h
    \author  aleos <aleos@flightstudio.ru>
*/

#ifndef __LOGGER_H
#define __LOGGER_H

#include <iostream>
#include <fstream>
#include <map>
#include <QDateTime>
#include <QObject>
#include <QMutex>
#include <ctime>

#include "loggerdumper.h"

typedef std::map<std::string, std::ofstream*> filesMap;
typedef std::pair<std::string, std::ofstream*> filesMapPair;

//! Logger
class FLogger  : public QObject
{
    Q_OBJECT

protected:

    static FLogger *logger;
    LoggerDumper dumper;
    QTime workTime;
    time_t startTime;

    QMutex mutex;

    filesMap files;
    std::string commonLogFileName;

    struct Message
    {
        Message(std::string message, std::string logname, bool writeToTerminal, bool writeToFile);
        std::string message;
        std::string logname;
        bool writeToTerminal;
        bool writeToFile;
    };

    std::list<Message> messages;

public:

    FLogger(const FLogger&);

//    static void addLogFile(const int id, const QString& logfilename);

    static void finish()
    {
        delete getLogger();
        logger = NULL;
    }

    //! logs to console and file
    static void log(const QString &logFileName, const QString &text, bool isConsoleOnly = false)
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
            logger->commonLogFileName = "log.txt";
            logger->files.insert(filesMapPair(logger->commonLogFileName, new std::ofstream(logger->commonLogFileName.data())));
        }

        return logger;
    }

    void logText(const QString &logFileName, const QString& logMessage, bool isConsoleOnly = false);
    void logText(const QString &logMessage, bool isConsoleOnly = false);
    void logText(const std::string &logFileName, const std::string &logMessage, bool consoleOnly = false);
    void logTextToFileOnly(const QString& text);

public slots:
    void write(void);
};

#endif /* __LOGGER_H */

