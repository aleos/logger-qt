/*! \file    logger.cpp
    \author  aleos <aleos@flightstudio.ru>
*/

#include "logger.h"
#include <sstream>

OnlyOne* OnlyOne::theSingleInstance=NULL;

Logger* Logger::logger = NULL;

Logger::Logger()
{
//    streamFile = NULL;
//    filestream = 0;
}

Logger::~Logger() 
{
//    delete filestream;
//    filestream = 0;
}

void Logger::logText(char* logFileName, char* logMessage, bool consoleOnly)
{
    // Write to a terminal (standart output)
    std::cout << logMessage << std::endl;

    // Write to a file if not to write on console only
    if (!consoleOnly) {
        filesMap::iterator iterator = files.begin();
        iterator = files.find(logFileName);
        std::ofstream *logFileStream = NULL;
        if (iterator != files.end()) {  // Good. Get pointer to file stream
            logFileStream = iterator->second;
        } else {    // No file present in map of files. Create one.
            std::ofstream *fileStream = new std::ofstream(logFileName);
            files.insert(filesMapPair(logFileName, fileStream));
        }
        *logFileStream << logMessage << "\n";
        logFileStream->flush();
    }
}

void Logger::logText(const QString &logMessage, bool consoleOnly)
{
    logText(commonLogFileName, logMessage.toAscii().data(), consoleOnly);
}

void Logger::logText(const QString &logFileName, const QString &logMessage, bool consoleOnly)
{
//    int id;
//    std::ostringstream strstream;
//    strstream << id;
//    std::string str = strstream.str();
    logText(logFileName.toAscii().data(), logMessage.toAscii().data(), consoleOnly);
}

void Logger::logTextToFileOnly(const QString& text)
{
    QString logtext = QString("%1: %2").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss:zzz")).arg(text);
    
    // write the text to the logfile
//    if (filestream != 0) filestream << logtext << endl;
}

// End of file
