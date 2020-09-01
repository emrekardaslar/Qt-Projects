#include "course.h"

Course::Course(QObject *parent, QString code, QString letter, int credit) : QObject(parent)
{
    this->code=code;
    this->letter=letter;
    this->credit=credit;
}

Course::~Course()
{

}

QString Course::info()
{
    QString str = "Code: " + this->code + "\nLetter: " + this->letter + "\nCredit: " + QString::number(this->credit);
    qDebug() << str;
    return str;
}

double Course::findCorrespondingScore(QString letter)
{
    QMap<QString,double> map;
    map["A"] = 4.0;
    map["A-"] = 3.7;
    map["B+"] = 3.3;
    map["B"] = 3.0;
    map["B-"] = 2.7;
    map["C+"] = 2.3;
    map["C"] = 2.0;
    map["C-"] = 1.7;
    map["D+"] = 1.3;
    map["D"] = 1.0;
    map["F1"] = 0.0;
    map["F2"] = 0.0;

    return map.value(letter);
}
