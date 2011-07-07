/*! \file    logger.cpp
    \author  aleos <aleos@flightstudio.ru>
*/

#include <sstream>
#include <QMutex>
#include "flogger.h"

//OnlyOne* OnlyOne::theSingleInstance=NULL;

FLogger::Message::Message(const char *message, const char *logname, bool writeToTerminal, bool writeToFile):
    message(message), logname(logname), writeToTerminal(writeToTerminal), writeToFile(writeToFile)
{
}

FLogger* FLogger::logger = NULL;

FLogger::FLogger()
{
}

FLogger::~FLogger()
{
    filesMap::iterator iterator;
    for (iterator = files.begin(); iterator != files.end(); ++iterator) {
        delete iterator->second;
        files.erase(iterator);
    }
}

void FLogger::write()
{
    Message *message = &messages.front();
    const char *logMessage = messages.front().message;
    // Write to a terminal (standart output)
    std::cout << logMessage << std::endl;

    // Write to a file if not to write on console only
    if (message->writeToFile) {
        filesMap::iterator iterator;
        iterator = files.find(message->logname);
        std::ofstream *logFileStream = NULL;
        if (iterator != files.end()) {  // Good. Get pointer to file stream
            logFileStream = iterator->second;
        } else {    // No file present in map of files. Create one.
            std::ofstream *logFileStream = new std::ofstream(message->logname);
            files.insert(filesMapPair(message->logname, logFileStream));
        }
        *logFileStream << logMessage << "\n";
        logFileStream->flush();
    }
    // Lock for erasing messages from list of messages
    QMutex mutex;
    mutex.lock();
    messages.pop_front();
    mutex.unlock();
}

void FLogger::logText(const char* logFileName, const char* logMessage, bool consoleOnly)
{
    messages.push_back(Message(logMessage, logFileName, true, true));
    write();
}

void FLogger::logText(const QString &logMessage, bool consoleOnly)
{
    logText(commonLogFileName, logMessage.toAscii().data(), consoleOnly);
}

void FLogger::logText(const QString &logFileName, const QString &logMessage, bool consoleOnly)
{
//    int id;
//    std::ostringstream strstream;
//    strstream << id;
//    std::string str = strstream.str();
    logText(logFileName.toAscii().data(), logMessage.toAscii().data(), consoleOnly);
}

void FLogger::logTextToFileOnly(const QString& text)
{
    QString logtext = QString("%1: %2").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss:zzz")).arg(text);
    
}

// End of file
