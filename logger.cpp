/*! \file    logger.cpp
    \author  aleos <aleos@flightstudio.ru>
*/

#include "logger.h"

Logger* Logger::logger = 0;

Logger::Logger()
{
    file = 0;
    filestream = 0;
}

Logger::~Logger() 
{
    delete filestream;
    filestream = 0;
    file->flush();
    delete file;
    file = 0;
}

void Logger::setLogFile(const QString& logfilename)
{
    if (file != 0) delete file;
    if (filestream != 0) delete filestream;
    
    file = new QFile(logfilename);
    streamFile.open(logfilename.toLatin1().data());
    if (!file->open(QIODevice::WriteOnly))
    {
//        qDebug() << "File not opened!";
    }

    file->resize(0);
    filestream = new QTextStream(file);
}

void Logger::logText(const QString& text, bool console_only)
{/*
    QString logtext = QString("%1: %2").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss:zzz")).arg(text);

    QTextStream terminal(stdout);
    terminal << logtext << endl;
//    terminal.flush();
//    fflush(stdout);
    
    // write the text to the logfile
    if (!console_only && filestream != 0) *filestream << logtext << endl;
//    filestream->flush();
    
    emit signalLogging(logtext);
*/
    std::string logtext(text.toLatin1().data());
    std::cout << logtext;
    if (!console_only && streamFile != 0) streamFile << logtext;
    streamFile.flush();
}

void Logger::logTextToFileOnly(const QString& text)
{
    QString logtext = QString("%1: %2").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss:zzz")).arg(text);
    
    // write the text to the logfile
    if (filestream != 0) *filestream << logtext << endl;
}

// End of file
