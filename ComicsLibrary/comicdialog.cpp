#include "comicdialog.h"
#include "ui_comicdialog.h"
#include <QDataWidgetMapper>
#include <QDebug>
#include <QSqlError>

ComicDialog::ComicDialog(QWidget *parent, QSqlRelationalTableModel* model, QModelIndex idx, bool editMode) :
    QDialog(parent),
    ui(new Ui::ComicDialog)
{
    ui->setupUi(this);

    m_model = model;
    m_idx = idx;
    m_editMode = editMode;

    for (int i=1;i<=10;i++) {
        ui->qtycomboBox->addItem(QString::number(i) + "");
    }

    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(ui->nameEdit, model->fieldIndex("name"));
    mapper->addMapping(ui->priceEdit, model->fieldIndex("price"));
    mapper->addMapping(ui->qtycomboBox, model->fieldIndex("quantity"));
    if (editMode) {
        mapper->setCurrentModelIndex(idx);
    }
    else {
        int rowCount = model->rowCount();
        if(!model->insertRow(rowCount)) {
            qWarning() << "insertRow" << model->lastError().text();
        }
        else {
            mapper->setCurrentModelIndex(m_model->index(rowCount, 0));
            model->setData(model->index(rowCount, model->fieldIndex("quantity")), 1);
        }
    }
}

ComicDialog::~ComicDialog()
{
    delete ui;
}
