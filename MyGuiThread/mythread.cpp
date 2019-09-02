#include "mythread.h"
#include <QThread>
#include <QtCore>

MyThread::MyThread(QObject *parent):QThread(parent)
{

}

void MyThread::run() {
    for (int i=0;i<100;i++) {
        QMutex mutex;
        mutex.lock();
        if(this->Stop) break;
        mutex.unlock();

        emit NumberChanged(i);
        this->msleep(100);
    }
}
