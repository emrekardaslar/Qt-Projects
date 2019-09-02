#include <QSqlDatabase>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "initdb.h"
#include <QDialog>

#include "gamedialog.h"

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

    m_model = new QSqlRelationalTableModel(ui->gameTableView);
    //m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_model->setTable("game");

    // Set the localized header captions
    //m_model->setHeaderData(model->fieldIndex("id"), Qt::Horizontal, tr("Id"));
    m_model->setHeaderData(m_model->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    m_model->setHeaderData(m_model->fieldIndex("price"), Qt::Horizontal, tr("Price"));
    m_model->setHeaderData(m_model->fieldIndex("quantity"), Qt::Horizontal, tr("Quantity"));

    // Populate the model
    if (!m_model->select()) {
        qWarning() << "Unable to select from game model" << m_model->lastError();
        return;
    }

    // Set the model and hide the ID column
    ui->gameTableView->setModel(m_model);
    ui->gameTableView->setColumnHidden(m_model->fieldIndex("id"), true);
    ui->gameTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->gameTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->gameTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->gameTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onGameTableViewDoubleClicked(QModelIndex)));

}

void MainWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Unable to initialize Database",
                          "Error initializing database: " + err.text());
}

void MainWindow::addOrEditItem(bool editMode, QModelIndex idx)
{
    if (editMode) {
        if (!idx.isValid())
            return;
    }

    GameDialog editDialog(this, m_model, idx, editMode);
    editDialog.setModal(true);
    if (editDialog.exec() == QDialog::Accepted) {
        m_model->submitAll();
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
        //ui->gameTableView->selectionModel()->setCurrentIndex(newIdx, QItemSelectionModel::Select);
        ui->gameTableView->selectRow(row);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onGameTableViewDoubleClicked(QModelIndex idx)
{
    addOrEditItem(true, idx);
}

void MainWindow::on_actionEdit_triggered()
{
    addOrEditItem(true, ui->gameTableView->selectionModel()->currentIndex());
}

void MainWindow::on_actionAdd_triggered()
{
    addOrEditItem(false);
}

void MainWindow::on_actionDelete_triggered()
{
    //m_model->removeRows(ui->gameTableView->selectionModel()->currentIndex().row(), 1);
    deleteItem(ui->gameTableView->selectionModel()->currentIndex());
}
