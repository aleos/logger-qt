///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005-2007 Alexander Wemmer
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
///////////////////////////////////////////////////////////////////////////////

/*! \file    logger.h
    \author  Alexander Wemmer, alex@wemmer.at
*/

#ifndef LOGGER_H
#define LOGGER_H

#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QObject>
#include <QDateTime>
#include <windows.h>

#include "assert.h"

/////////////////////////////////////////////////////////////////////////////
#if (defined _MSC_VER )
//#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#endif

//! Logger
class Logger  : public QObject
{
    Q_OBJECT

public:

    static Logger* getLogger()
    {
        if (m_logger == 0)
        {
            m_logger = new Logger;
//            MYASSERT(m_logger != 0);
        }

        return m_logger;
    }

    static void finish()
    {
        delete getLogger();
        m_logger = 0;
    }

    //! logs to console and file
    static void log(const QString& text,bool console_only = false) { getLogger()->logText(text,console_only); }

    static int printf(const char* fmt,...)
    {
    	va_list args;
   	    va_start(args,fmt);
   	    char _buf[0x1000];
   	    DWORD dwWritten;
		dwWritten=vsprintf_s(_buf, 0x1000, fmt, args);
   	    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),_buf,dwWritten,&dwWritten,NULL);
   	    return (int)dwWritten;

    }

    //! logs to file only
    static void logToFileOnly(const QString& text) { getLogger()->logTextToFileOnly(text); }

    //-----

    Logger();
    virtual ~Logger();

    void setLogFile(const QString& logfilename);
    void logText(const QString& text,bool console_only = false);
    void logTextToFileOnly(const QString& text);

signals:

    void signalLogging(const QString& text);

protected:

    static Logger* m_logger;

    QFile* m_logfile;
    QTextStream* m_logfilestream;

private:
    //! Hidden copy-constructor
    Logger(const Logger&);
    //! Hidden assignment operator
    const Logger& operator = (const Logger&);
};

#endif /* LOGGER_H */

// End of file

