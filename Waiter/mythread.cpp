#include "mythread.h"

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

void MyThread::run() {
    for(int i=0;i<10;i++) {
        qDebug() << i;
        msleep(100);
    }
}
