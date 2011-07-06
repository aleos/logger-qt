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

void Logger::logText(const char* logFileName, const char* logtext, bool consoleOnly)
{
    std::cout << logtext << std::endl;

    if (!consoleOnly && file != 0) {
        *files[0] << logtext << std::endl;
        *files[0] << "logtext" << std::endl;
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
