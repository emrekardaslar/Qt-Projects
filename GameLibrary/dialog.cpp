#include "dialog.h"
#include "ui_dialog.h"
#include <QTextStream>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    for (int i=1;i<=10;i++) {
        ui->comboBox->addItem(QString::number(i) + "");
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_saveButton_clicked()
{
    QFile file ("C:\\Users\\user\\Documents\\Qt Projects\\GameLibrary\\games.txt");
    if(file.open(QFile::ReadWrite | QIODevice::Append | QIODevice::Text)) {
        QTextStream out (&file);
        out << ui->plainTextEdit->toPlainText() << endl;
    }
    ui->plainTextEdit->clear();
    file.close();
}

void Dialog::on_cancelButton_clicked()
{
    close();
}
