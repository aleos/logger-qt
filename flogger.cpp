/*! \file    logger.cpp
    \author  aleos <aleos@flightstudio.ru>
*/

#include <sstream>
#include "flogger.h"
#include "loggerdumper.h"

#include <QTime>

//OnlyOne* OnlyOne::theSingleInstance=NULL;

FLogger::Message::Message(std::string message, std::string logname, bool writeToTerminal, bool writeToFile):
    message(message), logname(logname), writeToTerminal(writeToTerminal), writeToFile(writeToFile)
{
//    this->message = new char[strlen(message) + 1];
//    strcpy(this->message, message);
//    this->logname = new char[strlen(logname) + 1];
//    strcpy(this->logname, logname);
}

FLogger* FLogger::logger = NULL;

FLogger::FLogger()
{
    connect(&dumper, SIGNAL(dump()), SLOT(write()));
    dumper.start();
    workTime.start();
    startTime = time(NULL);
}

FLogger::~FLogger()
{
    filesMap::iterator iterator;
    for (iterator = files.begin(); iterator != files.end(); ++iterator) {
        delete iterator->second;
        files.erase(iterator);
    }
}

void FLogger::write(void)
{
    if (messages.size() > 0) {
        filesMap::iterator filesIterator;
        std::ofstream *logFileStream = NULL;

        std::list<Message>::iterator messagesIterator = messages.begin();
        std::list<Message>::iterator messagesEndIterator = messages.end();
        while (messagesIterator != messagesEndIterator) {
            time_t currentTime = time(NULL);
            double timeDiff = (double)clock() / CLOCKS_PER_SEC; //difftime(currentTime, startTime);
            clock_t t;
            if (messagesIterator->writeToTerminal) { // Write to a terminal (standart output)
                std::cout << messagesIterator->message << ' ' << timeDiff << "sec" << std::endl;
            }
            if (messagesIterator->writeToFile) { // Write to a file if not to write on console only
                filesIterator = files.find(messagesIterator->logname);
                if (filesIterator != files.end()) {  // Good. Get pointer to file stream
                    logFileStream = filesIterator->second;
                } else {    // No file present in map of files. Create one.
                    logFileStream = new std::ofstream(messagesIterator->logname.data());
                    files.insert(filesMapPair(messagesIterator->logname, logFileStream));
                }
                *logFileStream << messagesIterator->message << ' ' << timeDiff << "sec" << "\n";
                ++messagesIterator;
            }
            logFileStream->flush();
        }

//        messagesIterator = messages.begin();    // return messages iterator to begin
        // Lock for erasing messages from list of messages
        mutex.lock();
        messages.erase(messages.begin(), messagesEndIterator);
        mutex.unlock();
    }
}

void FLogger::logText(const std::string &logFileName, const std::string &logMessage, bool consoleOnly)
{
    messages.push_back(Message(logMessage, logFileName, true, true));
//    write();
}

void FLogger::logText(const QString &logMessage, bool consoleOnly)
{
    std::ostringstream strstream;
    strstream << workTime.elapsed();
    std::string message = strstream.str();

    logText(commonLogFileName, message + "msec " + logMessage.toAscii().data(), consoleOnly);
}

void FLogger::logText(const QString &logFileName, const QString &logMessage, bool consoleOnly)
{
//    int id;
//    std::ostringstream strstream;
//    strstream << id;
//    std::string str = strstream.str();
    logText(std::string(logFileName.toAscii().data()), std::string(logMessage.toAscii().data()), consoleOnly);
}

void FLogger::logTextToFileOnly(const QString& text)
{
    QString logtext = QString("%1: %2").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss:zzz")).arg(text);
    
}

// End of file
