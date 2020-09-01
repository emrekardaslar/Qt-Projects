#include "transcript.h"
#include "ui_transcript.h"
#include "course.h"
#include <QDebug>

QList<QString> Transcript::prepareSemesters()
{
    QList<QString> semesters;

    semesters.append("2017 Fall");
    semesters.append("2018 Spring");
    semesters.append("2018 Fall");
    semesters.append("2019 Spring");
    semesters.append("2019 Fall");
    semesters.append("2020 Spring");
    semesters.append("2020 Fall");
    semesters.append("2021 Spring");
    semesters.append("2021 Fall");

    return semesters;
}

QString Transcript::calcSuccess(double gpa)
{
    if (gpa >=3.5)
        return "High Honor";
    else if (gpa >=3.0 && gpa <3.5)
        return "Honor";
    else if (gpa >=2.0 and gpa<3.0)
        return "Successfull";
    else
        return "Failed";
}

Transcript::Transcript(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Transcript)
{
    ui->setupUi(this);
    QSqlQuery query;
    QList<QString> semesters = prepareSemesters();
    double totalScore=0;
    double totalCredit=0;
    QString success;
    double gpa;
    for (int i=0;i<semesters.size();i++) {
        double semesterCredit=0;
        double semesterScore=0;

        query.prepare(""
                      "SELECT DISTINCT * FROM courses WHERE semester = '" + semesters.at(i) + "'"
                      );
        query.exec();
        ui->listWidget->addItem(semesters.at(i));
        ui->listWidget->addItem("Code:\tLetter:\t Credit:\t Score: ");
        while (query.next()) {
            QString code = query.value(2).toString();
            QString letter = query.value(3).toString();
            QString credit = query.value(4).toString();
            int creditValue = credit.toInt();
            Course *course = new Course(0,code,letter,creditValue);
            double corresp = course->findCorrespondingScore(letter);
            double score = corresp * creditValue;
            ui->listWidget->addItem(code + " \t"  + letter + " \t"  + credit + "\t" + QString::number(score));
            semesterCredit += creditValue;
            semesterScore += score;
        }
        double average = semesterScore / semesterCredit;
        totalScore += semesterScore;
        totalCredit += semesterCredit;
        gpa = totalScore/totalCredit;
        success = calcSuccess(gpa);
        ui->listWidget->addItem("\nSemester Score: " + QString::number(semesterScore,'f',2) + "\tSemester Credit: " + QString::number(semesterCredit,'f',2) + "\tSemester Average: " + QString::number(average,'f',2));
        ui->listWidget->addItem("Previous Socre: " + QString::number(totalScore - semesterScore,'f',2) + "\tPrevious Credit: " + QString::number(totalCredit-semesterCredit,'f',2) + "\tGPA: " + QString::number(gpa,'f',2));
        ui->listWidget->addItem("Total Score: " + QString::number(totalScore,'f',2)+ "\tTotal Credit: " + QString::number(totalCredit,'f',2) + "\tSuccess: " + success + "\n--------------------------");
    }
}

Transcript::~Transcript()
{
    delete ui;
}

