/*! \file    logger.h
    \author  aleos <aleos@flightstudio.ru>
*/

#ifndef __LOGGER_H
#define __LOGGER_H

#include <fstream>
#include <map>
#include <QMutex>
#include <QObject>

typedef std::map<std::string, std::ofstream*> FilesMap;
typedef std::pair<std::string, std::ofstream*> FilesMapPair;

class LoggerDumper;

struct Message
{
    Message(std::string message, std::string logname, bool writeToTerminal, bool writeToFile);
    std::string message;
    std::string logname;
    bool writeToTerminal;
    bool writeToFile;
};

//! Logger
class FLogger  : public QObject
{
    Q_OBJECT

protected:

    bool isWriteRun;
    static FLogger *logger;
    LoggerDumper *dumper;

    QMutex addLogMessageLocker;

    FilesMap files;
    std::string commonLogFileName;

    std::list<Message> messages;

public:

    FLogger(const FLogger&);

    static void finish()
    {
        delete getLogger();
        logger = NULL;
    }

    //! logs to console and file
    static void log(const QString &logFileName, const QString &text, bool writeToTerminal = true)
    {
        getLogger()->logText(logFileName, text, writeToTerminal);
    }

    static void log(const QString& text, bool writeToTerminal = true, bool writeToFile = true)
    {
        getLogger()->logText(text, writeToTerminal, writeToFile);
    }

private:

    FLogger();
    virtual ~FLogger();

    static FLogger* getLogger()
    {
        if (logger == NULL) {
            logger = new FLogger;
            logger->commonLogFileName = "log.txt";
            logger->files.insert(FilesMapPair(logger->commonLogFileName, new std::ofstream(logger->commonLogFileName.data())));
        }

        return logger;
    }

    void logText(const QString &logFileName, const QString& logMessage, bool writeToTerminal = true);
    void logText(const QString &logMessage, bool writeToTerminal = true, bool writeToFile = true);
    void logText(const std::string &logFileName, const std::string &logMessage, bool writeToTerminal = true, bool writeToFile = true);
    void logTextToFileOnly(const QString& text);
};

#endif /* __LOGGER_H */

