#include <QCoreApplication>
#include <QDebug>
#include <QLinkedList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QLinkedList<int> list;
    list << 1 << 3 << 5;
    list.append(6);
    foreach(int i, list) {
        qDebug() << i;
    }

    return a.exec();
}
