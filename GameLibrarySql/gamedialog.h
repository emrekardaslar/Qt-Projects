#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <QDialog>
#include <QSqlRelationalTableModel>

namespace Ui {
class GameDialog;
}

class GameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameDialog(QWidget *parent = 0, QSqlRelationalTableModel* model=0, QModelIndex idx = QModelIndex(), bool editMode = true);
    ~GameDialog();

private:
    Ui::GameDialog *ui;
    QSqlRelationalTableModel *m_model;
    QModelIndex m_idx;
    bool m_editMode;
};

#endif // GAMEDIALOG_H
