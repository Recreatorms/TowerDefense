#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>


class Signal : public QObject
{
    Q_OBJECT
signals:
    void sig();
};


#endif // MYTHREAD_H
