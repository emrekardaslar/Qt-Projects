#include <QCoreApplication>
#include <QList>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<int> list;
    for (int i=0; i<10; i++) {
        list.append(i);
    }
    QListIterator<int> Iter(list);
    Iter.toBack();
    while(Iter.hasPrevious()) {
        qDebug() << Iter.previous();
        if (Iter.hasPrevious()) {
            qDebug() <<" next..." << Iter.peekPrevious();
        }
    }

    return a.exec();
}
