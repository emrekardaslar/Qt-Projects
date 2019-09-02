#include <QCoreApplication>
#include <QMap>
#include <QHash>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
   // QMap<int,QString> Employees;
    QHash<int,QString> Employees;

    Employees.insert(2,"Bob");
    Employees.insert(1,"Chad");
    Employees.insert(3,"Mary");
    Employees.insertMulti(1,"Amy");
    qDebug() << "3 = " << Employees.value(3);

//    foreach (int i, Employees.keys()) {
//        qDebug() << Employees[i];
//    }
//    //QMapIterator<int,QString> iter(Employees);
//    QHashIterator<int,QString> iter(Employees);
//    while(iter.hasNext()) {
//        iter.next();
//        qDebug() << iter.key() << " = " <<iter.value();
//    }
    return a.exec();
}
