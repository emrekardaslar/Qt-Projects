#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->okButton, SIGNAL(clicked(bool)), this, SLOT(okButtonClicked(bool)));
    connect(ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(cancelButtonClicked(bool)));
    connect(this, SIGNAL(emreAdded()), this, SLOT(onEmreAdded()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::okButtonClicked(bool)
{
    QString key = ui->lineEdit1->text();
    QString value = ui->lineEdit2->text();

    ui->listWidget->addItem(key);
    m_hash[key] = value;

    if (key == "emre") {
        emit emreAdded();
    }
}

void MainWindow::cancelButtonClicked(bool)
{
    ui->listWidget->clear();

    if (m_hash.contains("emre")) {
        ui->listWidget->addItem(m_hash["emre"]);
    }
}

void MainWindow::onEmreAdded()
{
    ui->listWidget->addItem("EMRE ADDED!!!");
}
