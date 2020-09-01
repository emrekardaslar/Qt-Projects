#include <QDataWidgetMapper>
#include "newcourse.h"
#include "ui_newcourse.h"
#include <QSqlError>

NewCourse::NewCourse(QWidget *parent, QSqlRelationalTableModel *model, QModelIndex idx, bool editMode) :
    QDialog(parent),
    ui(new Ui::NewCourse)
{
    ui->setupUi(this);

    m_model = model;
    m_idx = idx;
    m_editMode = editMode;

    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(ui->semesterBox,model->fieldIndex("semester"));
    mapper->addMapping(ui->codeBox, model->fieldIndex("code"));
    mapper->addMapping(ui->creditBox, model->fieldIndex("credit"));
    mapper->addMapping(ui->comboBox, model->fieldIndex("letter"));

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
            model->setData(model->index(rowCount, model->fieldIndex("letter")), 1);
        }
    }
}


NewCourse::~NewCourse()
{
    delete ui;
}

void NewCourse::setCourse()
{
    QString code,letter,str,semester;
    int credit;
    bool ok;
    semester = ui->semesterBox->currentText();
    code = ui->codeBox->currentText();
    letter = ui->comboBox->currentText();
    credit = (ui->creditBox->currentText()).toInt(&ok);
    if (!ok) {
        qDebug() << "Failed to convert!!";
    }
    else {
        Course *course = new Course(0,code,letter,credit);
        str = course->info();
        //QMessageBox::information(this,"Info", "Semester: " + semester + "\n" + str);
    }
}

void NewCourse::on_buttonBox_accepted()
{
    setCourse();
    accept();
}

void NewCourse::on_buttonBox_rejected()
{
    reject();
}
