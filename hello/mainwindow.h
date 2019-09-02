#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QHash<QString, QString> m_hash;

private slots:
    void okButtonClicked(bool);
    void cancelButtonClicked(bool);
    void onEmreAdded();

signals:
    void emreAdded();
};

#endif // MAINWINDOW_H
