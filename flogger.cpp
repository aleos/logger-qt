/*! \file    logger.cpp
    \author  aleos <aleos@flightstudio.ru>
*/

#include "flogger.h"
#include "loggerdumper.h"

Message::Message(std::string message, std::string logname, bool writeToTerminal, bool writeToFile):
    message(message), logname(logname), writeToTerminal(writeToTerminal), writeToFile(writeToFile)
{
}

FLogger* FLogger::logger = NULL;

FLogger::FLogger()
{
    dumper = new LoggerDumper(&isWriteRun, &commonLogFileName, &files, &messages);
    isWriteRun = true;
    dumper->start();
}

FLogger::~FLogger()
{
    FilesMap::iterator iterator;
    for (iterator = files.begin(); iterator != files.end(); ++iterator) {
        delete iterator->second;
        files.erase(iterator);
    }
    delete dumper;
}

void FLogger::logText(const std::string &logFileName, const std::string &logMessage, bool writeToTerminal, bool writeToFile)
{
    addLogMessageLocker.lock();
    messages.push_back(Message(logMessage, logFileName, writeToTerminal, writeToFile));
    addLogMessageLocker.unlock();
}

void FLogger::logText(const QString &logMessage, bool writeToTerminal, bool writeToFile)
{
    logText(commonLogFileName, logMessage.toAscii().data(), writeToTerminal, writeToFile);
}

void FLogger::logText(const QString &logFileName, const QString &logMessage, bool writeToTerminal)
{
    logText(std::string(logFileName.toAscii().data()), std::string(logMessage.toAscii().data()), writeToTerminal, true);
}

// End of file
