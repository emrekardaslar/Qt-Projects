#include "calculator.h"
#include "ui_calculator.h"
#include <QDataWidgetMapper>
#include <QSqlError>


Calculator::Calculator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    fillCourseBox();
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::fillCourseBox()
{
    QSqlQuery query;

    query.prepare("SELECT code FROM courses");
    query.exec();

    while (query.next()) {
        ui->courseBox->addItem(query.value(0).toString());
        query.prepare("INSERT INTO details SET quiz1 = 100, midterm = 100 WHERE code = ENG199;");
        query.exec();
    }

    ui->finPer->setText("40");
    ui->mtPer->setText("35");
    ui->qzPer->setText("15");
    ui->lhPer->setText("10");
}


void Calculator::setDetails()
{
    QString code;
    QSqlQuery query;
   // int credit;
    int quiz1,midterm,final,hw;
    int qzPer, mtPer, finPer, hwPer;
    bool ok;
    double totalPoint;

    code = ui->courseBox->currentText().toInt(&ok);
    quiz1 = ui->qzLine->text().toInt(&ok);
    midterm = ui->mtLine->text().toInt(&ok);
    final = ui->finalLine->text().toInt(&ok);
    hw = ui->lhLine->text().toInt(&ok);

    finPer = ui->finPer->text().toInt(&ok);
    hwPer = ui->lhPer->text().toInt(&ok);
    qzPer = ui->qzPer->text().toInt(&ok);
    mtPer = ui->mtPer->text().toInt(&ok);

    if (!ok) {
        qDebug() << "Failed to convert!!";
    }
    else {
        qDebug() << "Quiz: " << quiz1 << endl;
        qDebug() << "Midterm: " << midterm << endl;
        qDebug() << "Final: " << final << endl;
        qDebug() << "Hw: " << hw << endl;

        qDebug() << "Final Per.: " << finPer << endl;
        qDebug() << "Midterm Per.: " << mtPer << endl;
        qDebug() << "Hw Per.: " << hwPer << endl;
        qDebug() << "Quiz Per.: " << qzPer << endl;
        totalPoint = quiz1*qzPer/100 + midterm*mtPer/100 + final*finPer/100 + hw*hwPer/100;
        qDebug() << "Total Points: " << totalPoint << endl;
        //QMessageBox::information(this,"Info", "Semester: " + semester + "\n" + str);

        //query.exec("UPDATE details SET quiz1 = " + quiz1 + " , midterm = " + midterm + "; ");
        query.prepare("UPDATE details SET quiz1 = :quiz1, midterm = :midterm WHERE code = :code;");
        query.bindValue(":quiz1",quiz1);
        query.bindValue(":midterm",midterm);
        query.bindValue(":code",code);
        query.exec();
    }
}



void Calculator::on_saveBtn_clicked()
{
    setDetails();
}
