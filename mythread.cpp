#include "mythread.h"
#include <QDebug>
MyThread::MyThread(QThread *parent) :
  QThread(parent)
{
//  this->start();
//  this->moveToThread(nullptr);
//  qDebug() << "Thread:\t" << this->thread();
//  this->moveToThread(this);
//  this->moveToThread(this->thread());
 // this->moveToThread(nullptr);
  qDebug() << "Thread:\t" << this->thread();
// this->start();

}

void MyThread::run() {
   threadTimer = new QTimer(this);
   qDebug() << "Timer:\t" << threadTimer->thread();

//  threadTimer->moveToThread(this);
//   qDebug() << "Timer:\t" << threadTimer->thread();


//  connect(this, &MyThread::signalStartTimer, this, &MyThread::slotStartTimer);
  connect(threadTimer, &QTimer::timeout, this, &MyThread::doIt);
//  emit (signalStartTimer());
//  this->moveToThread(this);
  threadTimer->start(1);
  exec();
}

void MyThread::doIt() {
  emit (signalStartTimer());
  qDebug() << "It just works";
}

//void MyThread::slotStartTimer() {
//  threadTimer->start(1);
//}
int p;
//std::thread([&p](){std::this_thread::sleep_for(std::chrono::milliseconds(10); /*doSOMEJOB*/}).detach();
