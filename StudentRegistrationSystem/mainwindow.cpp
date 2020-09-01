#include <QSqlDatabase>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "initdb.h"
#include "transcript.h"
#include "calendar.h"
#include "calculator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (!QSqlDatabase::drivers().contains("QSQLITE"))
            QMessageBox::critical(this, "Unable to load database", "This demo needs the SQLITE driver");

        // initialize the database
    if (!initDb()) {
        showError(tr("Database error"));
        return;
    }

    m_model = new QSqlRelationalTableModel(ui->courseTable);
    m_model->setTable("courses");

    m_model->setHeaderData(m_model->fieldIndex("semester"),Qt::Horizontal,tr("Semester"));
    m_model->setHeaderData(m_model->fieldIndex("code"), Qt::Horizontal, tr("Code"));
    m_model->setHeaderData(m_model->fieldIndex("letter"), Qt::Horizontal, tr("Letter"));
    m_model->setHeaderData(m_model->fieldIndex("credit"), Qt::Horizontal, tr("Credit"));

    if (!m_model->select()) {
            qWarning() << "Unable to select from course model" << m_model->lastError();
            return;
    }

    // Set the model and hide the ID column
   ui->courseTable->setModel(m_model);
   ui->courseTable->setColumnHidden(m_model->fieldIndex("id"), true);
   ui->courseTable->setSelectionMode(QAbstractItemView::SingleSelection);
   ui->courseTable->setSelectionBehavior(QAbstractItemView::SelectRows);
   ui->courseTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
   ui->courseTable->sortByColumn(1,Qt::DescendingOrder);

   connect(ui->courseTable, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_courseTable_doubleClicked(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_Course_triggered()
{
    addOrEditItem(false);

}

void MainWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Unable to initialize Database",
                          "Error initializing database: " + err.text());
}

void MainWindow::on_courseTable_doubleClicked(const QModelIndex &index)
{
    addOrEditItem(true,index);
}

void MainWindow::addOrEditItem(bool editMode, QModelIndex idx)
{
    if (editMode) {
        if (!idx.isValid())
            return;
    }

    NewCourse editDialog(this, m_model, idx, editMode);
    editDialog.setModal(true);
    if (editDialog.exec() == QDialog::Accepted) {
        m_model->submitAll();
        ui->courseTable->sortByColumn(1,Qt::DescendingOrder);
    }
    else {
        m_model->revertAll();
    }
}

void MainWindow::deleteItem(QModelIndex idx)
{
    if (!idx.isValid())
        return;

    int row = idx.row();
    int rowCount = m_model->rowCount();

    m_model->removeRows(row, 1);
    m_model->select();

    if (row == rowCount-1) {
        row = rowCount-2;
    }

    QModelIndex newIdx = m_model->index(row, 0);

    if (newIdx.isValid()) {
        ui->courseTable->selectRow(row);
    }
}

void MainWindow::on_actionDelete_triggered()
{
    deleteItem(ui->courseTable->selectionModel()->currentIndex());
}

void MainWindow::on_actionTranscript_triggered()
{
    Transcript *tscript = new Transcript(this);
    tscript->exec();
}

void MainWindow::on_actionCalendar_triggered()
{
    Calendar *calendar = new Calendar(this);
    calendar->exec();
}

void MainWindow::on_actionCalculator_triggered()
{
    Calculator *calc = new Calculator(this);
    calc->exec();
}
/*
void MainWindow::on_courseTable_activated(const QModelIndex &index)
{

}
*/
