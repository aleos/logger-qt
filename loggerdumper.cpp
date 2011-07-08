#include <iostream>
#include <cmath>
#include <ctime>
#include <QMutex>
#include "loggerdumper.h"

LoggerDumper::LoggerDumper(bool *isRun, std::string *commonLogFileName, FilesMap *files, std::list<Message> *messages):
    isRun(isRun), commonLogFileName(commonLogFileName), files(files), messages(messages)
{ }

LoggerDumper::~LoggerDumper(void) { }

void LoggerDumper::run()
{
    while (isRun) {
        writeLocker.lock();
        write();
        writeLocker.unlock();
        msleep(50);
    }
//    exec();
}

void LoggerDumper::write(void)
{
    if (messages->size() > 0) {
        FilesMap::iterator filesIterator;
        std::ofstream *logFileStream = NULL;

        std::list<Message>::iterator messagesIterator = messages->begin();
        std::list<Message>::iterator messagesEndIterator = messages->end();
        while (messagesIterator != messagesEndIterator) {
            double time = (double)clock() / CLOCKS_PER_SEC; // time from application start (in sec)
            double sec;
            int msec = (int)(modf(time, &sec) * 1000);
            if (messagesIterator->writeToTerminal) { // Write to a terminal (standart output)
                std::cout << sec << ":" << msec << " " << messagesIterator->message << '\n';
            }
            if (messagesIterator->writeToFile) { // Write to a file if not to write on console only
                filesIterator = files->find(messagesIterator->logname);
                if (filesIterator != files->end()) {  // Good. Get pointer to file stream
                    logFileStream = filesIterator->second;
                } else {    // No file present in map of files. Create one.
                    logFileStream = new std::ofstream(messagesIterator->logname.data());
                    files->insert(FilesMapPair(messagesIterator->logname, logFileStream));
                }
                *logFileStream << messagesIterator->message << "\n";
                ++messagesIterator;
            }
            std::cout << std::flush;
            *logFileStream << std::flush;
        }
        messagesIterator = messages->begin();    // return messages iterator to begin
        // Lock for erasing messages from list of messages
        messages->erase(messages->begin(), messagesEndIterator);
    }
}
