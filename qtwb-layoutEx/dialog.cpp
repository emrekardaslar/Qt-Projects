#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_okBtn_clicked()
{
    QString toppings = getToppings(ui->Toppings);
    QString sauces = getSauce(ui->Sauce);
    QString order;
    order += "Order:\r\n";
    order += "Toppings: " + toppings + "\r\nSauces: " + sauces + "\r\n";
    QMessageBox::information(this,"Order",order);
    accept();
}

void Dialog::on_cancelBtn_clicked()
{
    QMessageBox::warning(this,"Cancel","You want to cancel the order?");

    reject();
}

QString Dialog::getToppings(QObject *obj)
{
    QString value = "None";
    QList<QRadioButton*> list =obj->findChildren<QRadioButton*>(QString(),Qt::FindDirectChildrenOnly);

    foreach (QRadioButton* radio, list) {
        if (radio->isChecked()) {
            value = radio->text();
            break;
        }
    }
    return value;
}

QString Dialog::getSauce(QObject *obj)
{
    QString value = "None";
    QList<QCheckBox*> list = obj->findChildren<QCheckBox*>(QString(),Qt::FindDirectChildrenOnly);
    foreach (QCheckBox* box, list) {
        if (box->isChecked()) {
            value = box->text();
            break;
        }
    }
    return value;
}
