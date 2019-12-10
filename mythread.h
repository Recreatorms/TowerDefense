#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QTimer>

class Signal : public QObject
{
    Q_OBJECT
signals:
    void sig();
};

//class MyThread : public QThread
//{
//  Q_OBJECT
//public:
//  MyThread(QThread *parent);
//  QTimer *threadTimer;
//signals:
//  void signalStartTimer();
//public slots:
//  void doIt();
//  //void slotStartTimer();
//protected:
//  void run() override;
//};

#endif // MYTHREAD_H
