#ifndef LOGGERDUMPER_H
#define LOGGERDUMPER_H

#include <QThread>

class LoggerDumper : public QThread
{
    Q_OBJECT
public:
    explicit LoggerDumper(QObject *parent = 0);

    void run(void);

signals:
    void dump(void);

public slots:
    void slotDump()
    {
        emit dump();
    }
};

#endif // LOGGERDUMPER_H
