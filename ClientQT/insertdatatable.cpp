#include "insertdatatable.h"
#include "ui_insertdatatable.h"
#include <QAction>
#include <QTextBlock>
#include <QLabel>
#include <QTableWidgetItem>
#include <QLineEdit>
insertDataTable::insertDataTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::insertDataTable)
{
    ui->setupUi(this);

    addRow = new QAction(QIcon(":/images/plus.png"),"Add Row", this);
    deleteRow = new QAction(QIcon(":/images/minus.png"),"Delete Row", this);
    ui->tableWidget->addActions({addRow, deleteRow});

    connect(addRow, &QAction::triggered, [&]()
    {
        int nfiles = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(nfiles);
    });
    connect(deleteRow, &QAction::triggered, [&]()
    {
        ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    });
}

void insertDataTable::setHeaderTable()
{
    tabel = this->getTabel();
    std::string fields = tabel->getFields();
    std::string delim = " ", token = "";
    auto start = 0;
    auto end = fields.find(delim);
    int c = 0;
    ui->tableWidget->setRowCount(1);
    int cc = 0;
    while (end != std::string::npos)
    {
           token = fields.substr(start, end - start);
           if(token != "" && token != "->")
           {
               cc++;
           }
           start = end + delim.length();
           end = fields.find(delim, start);
    }
    token = fields.substr(start, end);
    if(token != "" && token != "->")
    {
        cc++;
    }
    ui->tableWidget->setColumnCount(cc);
    start = 0;
    end = fields.find(delim);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(128);
    ui->tableWidget->horizontalHeader()->setEnabled(true);
    while (end != std::string::npos)
    {
           token = fields.substr(start, end - start);
           if(token != "" && token != "->")
           {
               QString n = QString::fromStdString(token);
               ui->tableWidget->setHorizontalHeaderItem(c, new QTableWidgetItem(n));
               c++;
           }
           start = end + delim.length();
           end = fields.find(delim, start);
    }
    token = fields.substr(start, end);
    if(token != "" && token != "->")
    {
        QString n = QString::fromStdString(token);
        ui->tableWidget->setHorizontalHeaderItem(c, new QTableWidgetItem(n));
        c++;
    }
    ui->tableName->setText(QString::fromStdString(tabel->getNume()));
}
void insertDataTable::setTabel(CTable *t)
{
    this->tabel = t;
}

CTable* insertDataTable::getTabel()
{
    return this->tabel;
}
insertDataTable::~insertDataTable()
{
    delete ui;
}

void insertDataTable::on_Accept_clicked()
{
    accept();
}

void insertDataTable::on_Cancel_clicked()
{
    reject();
}

QString insertDataTable::getResult()
{
    QString res = QString("INSERT INTO %1 (").arg(ui->tableName->text());
    int cols = ui->tableWidget->columnCount();
    for(int i = 0; i < cols; i++)
    {
        res += ui->tableWidget->horizontalHeaderItem(i)->text();
        res += ", ";
    }
    res[res.size() - 2] = ')';
    res += "VALUES (";
    int rows = ui->tableWidget->rowCount();
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            auto name = ui->tableWidget->item(i, j)->text();
            res += name + ", ";
        }

    }

    res[res.size() - 2] = ')';
    return res;
}

