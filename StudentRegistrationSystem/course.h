#ifndef COURSE_H
#define COURSE_H

#include <QObject>
#include <QMessageBox>
#include <QDebug>

class Course : public QObject
{
    Q_OBJECT
public:
    //Constructor
    explicit Course(QObject *parent = nullptr, QString code="", QString letter="", int credit=0);
    QString code;
    QString letter;
    int credit;
    //Deconstructor
    ~Course();
    QString info();
    double findCorrespondingScore(QString letter);
signals:

public slots:
};

#endif // COURSE_H
