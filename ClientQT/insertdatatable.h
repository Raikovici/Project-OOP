#ifndef INSERTDATATABLE_H
#define INSERTDATATABLE_H

#include <QDialog>
#include <QStringList>
#include "ctable.h"
namespace Ui {
class insertDataTable;
}

class insertDataTable : public QDialog
{
    Q_OBJECT

public:
    explicit insertDataTable(QWidget *parent = nullptr);
    ~insertDataTable();
    CTable* getTabel();
    void setTabel(CTable* t);
    void setHeaderTable();
    QString getResult();

private slots:
    void on_Accept_clicked();

    void on_Cancel_clicked();
private:
    Ui::insertDataTable *ui;
    QAction* addRow;
    QAction* deleteRow;
    QString result;
    CTable* tabel;
};

#endif // INSERTDATATABLE_H
