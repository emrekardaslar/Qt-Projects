#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_okBtn_clicked();
    void on_cancelBtn_clicked();

private:
    Ui::Dialog *ui;

    QString getToppings(QObject *obj);
    QString getSauce(QObject *obj);
};

#endif // DIALOG_H
