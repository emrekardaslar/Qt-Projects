#include "dialog.h"
#include "ui_dialog.h"
#include <QtCore>
#include <QtWidgets>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(2);
    ui->treeWidget->setHeaderLabels(QStringList() << "one"<<"two");
    AddRoot("hello","world");
    AddRoot("hello","world");
    AddRoot("hello","world");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::AddRoot(QString name,QString Description) {
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0,name);
    item->setText(1,Description);
    ui->treeWidget->addTopLevelItem(item);

    AddChild(item,"one","hello");
    AddChild(item,"two","hello");
}

void Dialog::AddChild(QTreeWidgetItem *parent, QString name,QString Description) {
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0,name);
    item->setText(1,Description);
    parent->addChild(item);
}

void Dialog::on_pushButton_clicked()
{
    ui->treeWidget->currentItem()->setBackgroundColor(0,Qt::red);
    ui->treeWidget->currentItem()->setBackgroundColor(1,Qt::blue);

}
