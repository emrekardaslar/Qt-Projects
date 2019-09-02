#include <QCoreApplication>
#include <QDebug>
#include <QStringList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList list;
    QString line = "a,b,c,d,e,f,g";

    list=line.split(",");
    list.replaceInStrings("b","batman");

    QString after = list.join(",");
    qDebug() << after;

    foreach (QString item, list) {
        qDebug() << item;
    }

    return a.exec();
}
