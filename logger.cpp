/*! \file    logger.h
    \author  aleos <aleos@flightstudio.ru>
*/

#include "logger.h"
#include <iostream>

Logger* Logger::m_logger = 0;

/////////////////////////////////////////////////////////////////////////////

Logger::Logger()
{
    m_logfile = 0;
    m_logfilestream = 0;
}

/////////////////////////////////////////////////////////////////////////////

Logger::~Logger() 
{
    delete m_logfilestream;
    m_logfilestream = 0;
    m_logfile->flush();
    delete m_logfile;
    m_logfile = 0;
}

/////////////////////////////////////////////////////////////////////////////

void Logger::setLogFile(const QString& logfilename)
{
//    MYASSERT(!logfilename.isEmpty());
    if (m_logfile != 0) delete m_logfile;
    if (m_logfilestream != 0) delete m_logfilestream;
    
    m_logfile = new QFile(logfilename);
//    MYASSERT(m_logfile != 0);
    if (!m_logfile->open(QIODevice::WriteOnly))
    {
#if! VASFMC_GAUGE
//        QMessageBox::critical(0, "LOGFILE", QString("Could not open logfile (%1)").arg(logfilename));
//        MYASSERT(false);
#endif
    }
//    MYASSERT(m_logfile->isWritable());
//    MYASSERT(m_logfile->resize(0));
    
    m_logfilestream = new QTextStream(m_logfile);
//    MYASSERT(m_logfilestream != 0);
}

/////////////////////////////////////////////////////////////////////////////

void Logger::logText(const QString& text,bool console_only)
{
    QString logtext = QString("%1: %2").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss:zzz")).arg(text);
    
    // write out the text
//    printf("%s\n", logtext.toLatin1().data());
    QTextStream logToConsole(stdout);
    logToConsole << logtext << "\n";

    fflush(stdout);
    
    // write the text to the logfile
    if (!console_only && m_logfilestream != 0) *m_logfilestream << logtext << endl;
    
    emit signalLogging(logtext);
}

/////////////////////////////////////////////////////////////////////////////

void Logger::logTextToFileOnly(const QString& text)
{
    QString logtext = QString("%1: %2").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss:zzz")).arg(text);
    
    // write the text to the logfile
    if (m_logfilestream != 0) *m_logfilestream << logtext << endl;
}

// End of file
