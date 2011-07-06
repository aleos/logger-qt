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
    file.flush();
//    delete file;
//    file = 0;
}

//void Logger::addLogFile(const int id, const QString& logfilename)
//{
//    Logger *log = getLogger();
//    std::ostringstream strstream;
//    strstream << id;
//    std::string filename = strstream.str();
//    log->files.insert(std::pair<int, std::ofstream*>(id, new std::ofstream(filename.data())));
////    getLogger()->file.open(logfilename.toAscii().data());
//}

void Logger::logText(char* logFileName, char* logtext, bool consoleOnly)
{
    // Write to a terminal (standart output)
    std::cout << logtext << std::endl;

    // Write to a file if !consoleOnly
    if (!consoleOnly) {
        filesMap::iterator iterator = files.begin();
        iterator = files.find(logFileName);
        std::ofstream *logFileStream = NULL;
        if (iterator != files.end()) {
            logFileStream = iterator->second;
        } else {
            std::ofstream *fileStream = new std::ofstream(logFileName);
            files.insert(filesMapPair(logFileName, fileStream));
        }
        *logFileStream << logtext << "\n";
        logFileStream->flush();
    }
}

void Logger::logText(const QString &logtext, bool consoleOnly)
{
    logText(commonLogFileName, logtext.toAscii().data(), consoleOnly);
}

void Logger::logText(const QString &logFileName, const QString &logText, bool consoleOnly)
{
//    Logger *log = getLogger();
//    std::ostringstream strstream;
//    strstream << id;

}

void Logger::logTextToFileOnly(const QString& text)
{
    QString logtext = QString("%1: %2").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss:zzz")).arg(text);
    
    // write the text to the logfile
//    if (filestream != 0) filestream << logtext << endl;
}

// End of file
