/*! \file    logger.h
    \author  aleos <aleos@flightstudio.ru>
*/

#ifndef __LOGGER_H
#define __LOGGER_H

#include <fstream>
#include <map>
#include <QMutex>
#include <QObject>

//! Short name for a files map type
typedef std::map<std::string, std::ofstream*> FilesMap;
//! Short name for a element in FilesMap
typedef std::pair<std::string, std::ofstream*> FilesMapPair;

// Pre define for logger dumper
class LoggerDumper;

//! Struct of message with full information about message (point which log output will be used).
struct Message
{
    //! Only constructor with full parameters list.
    Message(std::string message, std::string logname, bool writeToTerminal, bool writeToFile);
    //! String of a message.
    std::string message;
    //! Name of a log file. Must be filled even when default log filename.
    std::string logname;
    //! Sets to true if need to write to a terminal.
    bool writeToTerminal;
    //! Sets to true if need to write to a log file.
    bool writeToFile;
};

/*! Thread safe class of a logger.
  Singleton with static overloaded methods for logging.
  */
class FLogger
{
protected:

    //! Flag of activity of logger dumper.
    bool isWriteRun;
    //! Only one object of FLogger (singleton).
    static FLogger *logger;
    //! Logger dumper is in separate thread.
    LoggerDumper *dumper;

    //! Mutex for lock adding messages in a message list
    QMutex addLogMessageLocker;

    //! Map with all used log file names.
    FilesMap files;
    //! If no log filename provided, used this.
    std::string commonLogFileName;

    //! List of last log messages. Part of old messages already in logfile or terminal and no present in this list.
    std::list<Message> messages;

public:

    //! Interface method for logging to a file with logFileName and optionally to a terminal (write to a terminal by default)
    /*!
      /param logFileName Name of a file where you need to write log messages.
      /param logMessage Text of a log message.
      /param writeToTerminal Set this flag to false if you don't need to write to a terminal.
      */
    static void log(const QString &logFileName, const QString &logMessage, bool writeToTerminal = true)
    {
        getLogger()->logText(logFileName, logMessage, writeToTerminal);
    }

    //! Interface method for logging to a default log file and to a terminal with control where to write and where there is no.
    /*!
      /param logMessage Text of a log message.
      /param writeToTerminal Set this flag to false if you don't need to write to a terminal.
      /param writeToFile Set this flag to false if you don't need to write to a default log file.
      */
    static void log(const QString& logMessage, bool writeToTerminal = true, bool writeToFile = true)
    {
        getLogger()->logText(logMessage, writeToTerminal, writeToFile);
    }

    //! May be called when no longer logger need. You really don't need to call this method as general.
    static void finish()
    {
        delete getLogger();
        logger = NULL;
    }

private:

    //! Private constructor. Uses for create only one instance of a logger.
    FLogger();
    //! Private destructor for delete only instance of a logger.
    virtual ~FLogger();

    //! Create new or get exists logger object. Uses in public methods (singleton)
    static FLogger* getLogger()
    {
        if (logger == NULL) {
            logger = new FLogger;
            //! Name of default log file. Uses when no logger file name provided.
            logger->commonLogFileName = "log.txt";
            logger->files.insert(FilesMapPair(logger->commonLogFileName, new std::ofstream(logger->commonLogFileName.data())));
        }

        return logger;
    }

    //! Method for logging to a file and optionally to a terminal (write to a terminal by default)
    /*!
      /param logFileName Name of a file where you need to write log messages.
      /param logMessage Text of a log message.
      /param writeToTerminal Set this flag to false if you don't need to write to a terminal.
      */
    void logText(const QString &logFileName, const QString& logMessage, bool writeToTerminal = true);
    //! Method for logging to a default log file and to a terminal with control where to write and where there is no.
    /*!
      /param logMessage Text of a log message.
      /param writeToTerminal Set this flag to false if you don't need to write to a terminal.
      /param writeToFile Set this flag to false if you don't need to write to a default log file.
      */
    void logText(const QString &logMessage, bool writeToTerminal = true, bool writeToFile = true);
    //! Main method for logging. No more methods really write to a log messages list.
    /*!
      /param logFileName Name of a file where you need to write log messages.
      /param logMessage Text of a log message.
      /param writeToTerminal Set this flag to false if you don't need to write to a terminal.
      /param writeToFile Set this flag to false if you don't need to write to a default log file.
      */
    void logText(const std::string &logFileName, const std::string &logMessage, bool writeToTerminal = true, bool writeToFile = true);
};

#endif /* __LOGGER_H */

