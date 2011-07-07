#ifndef LOGGERDUMPER_H
#define LOGGERDUMPER_H

#include <QThread>
#include "flogger.h"

class LoggerDumper : public QThread
{
    Q_OBJECT
public:
    explicit LoggerDumper(QObject *parent = 0);

signals:

public slots:

};

#endif // LOGGERDUMPER_H
