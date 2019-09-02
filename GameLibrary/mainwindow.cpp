#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "dialog.h"
#include <QTextStream>
#include <QFile>
#include <QMessageBox>

void MainWindow::readText()
{
    QFile file ("C:\\Users\\user\\Documents\\Qt Projects\\GameLibrary\\games.txt");

    if(file.open(QFile::ReadOnly)) {
        QTextStream stream (&file);
        QStringList gamesList;
        while(true) {
            QString line = stream.readLine();
            if (line.isNull())
                break;
            else
                gamesList.append(line);
        }
        ui->listWidget->addItems(gamesList);
    }
    else {
        QMessageBox::information(0, "error", file.errorString());
    }

    file.close();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    readText();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_Games_triggered()
{
    Dialog addGameWindow;
    addGameWindow.setModal(true);
    addGameWindow.exec();
}

void MainWindow::on_actionRefresh_triggered()
{
    ui->listWidget->clear();
    readText();
}

void MainWindow::on_deleteButton_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
    }
}
