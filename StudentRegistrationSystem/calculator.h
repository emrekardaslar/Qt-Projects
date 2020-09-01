#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>
#include <QDebug>
#include <QSqlRelationalTableModel>
#include <QSqlQuery>

namespace Ui {
class Calculator;
}

class Calculator : public QDialog
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();
    void setDetails();
    void fillCourseBox();

private slots:


    void on_saveBtn_clicked();

private:
    Ui::Calculator *ui;
    QSqlRelationalTableModel *m_model;
    QModelIndex m_idx;
    bool m_editMode;
};

#endif // CALCULATOR_H
