#include <QCoreApplication>
#include <QList>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<int> list;
    for(int i=0;i<10;i++) {
        list.append(i);
    }
    list.removeOne(5); //remove 5

    foreach (int number, list) {
        qDebug() << number;
    }


    return a.exec();
}
