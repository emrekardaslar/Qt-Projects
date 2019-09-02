#include "mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QtGui>
#include <QtCore>
#include <QLabel>
#include <QLineEdit>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget *window = new QWidget;
    window->setWindowTitle("My App");

    QGridLayout *layout = new QGridLayout;
    QLabel *label1 = new QLabel("Name:");
    QLineEdit *txtName = new QLineEdit;

    layout->addWidget(label1,0,0);
    layout->addWidget(txtName,0,1);

    QPushButton *pbutton = new QPushButton("Ok");

    layout->addWidget(pbutton,2,0,1,2);

    window->setLayout(layout);
    window->show();
    return app.exec();
}
