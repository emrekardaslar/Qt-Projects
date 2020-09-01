#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlError>
#include <QSqlRelationalTableModel>
#include "newcourse.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAdd_Course_triggered();

    void on_courseTable_doubleClicked(const QModelIndex &index);


    void on_actionDelete_triggered();

    void on_actionTranscript_triggered();

    void on_actionCalendar_triggered();

    void on_actionCalculator_triggered();



private:
    Ui::MainWindow *ui;
    QSqlRelationalTableModel *m_model;

    void showError(const QSqlError &err);
    void addOrEditItem(bool editMode=true, QModelIndex idx=QModelIndex());
    void deleteItem(QModelIndex idx);
};

#endif // MAINWINDOW_H
