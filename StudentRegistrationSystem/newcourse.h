#ifndef NEWCOURSE_H
#define NEWCOURSE_H

#include <QDialog>
#include <QDebug>
#include <QSqlRelationalTableModel>
#include "course.h"

namespace Ui {
class NewCourse;
}

class NewCourse : public QDialog
{
    Q_OBJECT

public:
    explicit NewCourse(QWidget *parent = 0, QSqlRelationalTableModel* model=0, QModelIndex idx = QModelIndex(), bool editMode = true);
    ~NewCourse();
    void setCourse();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::NewCourse *ui;
    QSqlRelationalTableModel *m_model;
    QModelIndex m_idx;
    bool m_editMode;
};

#endif // NEWCOURSE_H
