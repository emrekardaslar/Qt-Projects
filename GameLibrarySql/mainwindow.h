#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlError>
#include <QSqlRelationalTableModel>

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
    void onGameTableViewDoubleClicked(QModelIndex);

    void on_actionEdit_triggered();

    void on_actionAdd_triggered();

    void on_actionDelete_triggered();

private:
    Ui::MainWindow *ui;
    QSqlRelationalTableModel *m_model;

    void showError(const QSqlError &err);
    void addOrEditItem(bool editMode=true, QModelIndex idx=QModelIndex());
    void deleteItem(QModelIndex idx);
};

#endif // MAINWINDOW_H
