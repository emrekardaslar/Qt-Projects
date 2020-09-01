#ifndef TRANSCRIPT_H
#define TRANSCRIPT_H

#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class Transcript;
}

class Transcript : public QDialog
{
    Q_OBJECT

public:
    explicit Transcript(QWidget *parent = 0);
    ~Transcript();

    QList<QString> prepareSemesters();
    QString calcSuccess(double gpa);
    
private:
    Ui::Transcript *ui;
};

#endif // TRANSCRIPT_H
