#include <QCoreApplication>
#include <QDebug>
#include <QVector>
#include <QStringList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    QList<int> list;
//    list << 2 << 3 << 1 << 0;
//    qSort(list);
//    //qSort(list.begin() +1,list.end()-1);

//    foreach (int i, list) {
//        qDebug() << i ;
//    }
    QStringList slist;
    slist << "a" << "b" <<"c";

    QVector<QString> Vect(3);

    qCopy(slist.begin() +1,slist.end(),Vect.begin());

    foreach (QString item, Vect) {
        qDebug() << item;
    }

    QVector<QString> fillVect(5);
    qFill(fillVect.begin(),fillVect.end() -1 ,"Hello");

    foreach(QString item, fillVect) {
        qDebug() << item;
    }

    QList<int> toFindList;
    toFindList << 1 << 5 << 15 << 23;
    QList<int>::const_iterator iter = qFind(toFindList.begin(),toFindList.end(),15);
    if (iter != toFindList.end()) {
        qDebug() << "Found:" << *iter;
    }
    else {
        qDebug() << "Not Found!";
    }


    return a.exec();
}
