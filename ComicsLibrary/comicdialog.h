#ifndef COMICDIALOG_H
#define COMICDIALOG_H

#include <QDialog>
#include <QSqlRelationalTableModel>

namespace Ui {
class ComicDialog;
}

class ComicDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ComicDialog(QWidget *parent = 0, QSqlRelationalTableModel* model=0, QModelIndex idx = QModelIndex(), bool editMode = true);
    ~ComicDialog();

private:
    Ui::ComicDialog *ui;
    QSqlRelationalTableModel *m_model;
    QModelIndex m_idx;
    bool m_editMode;
};

#endif // COMICDIALOG_H
