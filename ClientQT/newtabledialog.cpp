#include "newtabledialog.h"
#include "ui_newtabledialog.h"
#include <QAction>
#include <QComboBox>
#include <QRadioButton>
#include <QCheckBox>
newTableDialog::newTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newTableDialog)
{
    ui->setupUi(this);
    auto add = new QAction(QIcon(":/images/plus.png"), "Add", this);
    auto deleteA = new QAction(QIcon(":/images/minus.png"), "Delete", this);
    ui->tableWidget->addActions({add, deleteA});
    fields = "";
    auto newQComboBox = [&](QWidget* parrent)
    {
       auto combo = new QComboBox(parrent);
       combo->addItems({"INTEGER", "DOUBLE", "VARCHAR", "DATE"});
       return combo;
    };
    connect(add, &QAction::triggered, [&]()
    {
        int nfiles = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(nfiles);
        ui->tableWidget->setCellWidget(nfiles, 1, newQComboBox(this));
        ui->tableWidget->setCellWidget(nfiles, 2, new QRadioButton(this));
        ui->tableWidget->setCellWidget(nfiles, 3, new QCheckBox(this));
        ui->tableWidget->setCellWidget(nfiles, 4, new QCheckBox(this));
    });
    connect(deleteA, &QAction::triggered, [&]()
    {
        ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    });
}

newTableDialog::~newTableDialog()
{
    delete ui;
}

void newTableDialog::on_Accept_clicked()
{
    accept();
}

void newTableDialog::on_Cancel_clicked()
{
    reject();
}
std::string newTableDialog::getName()
{
    return ui->name->text().toStdString();
}
QString newTableDialog::result()
{
    QString res = QString("CREATE TABLE IF NOT EXISTS %1 (").arg(ui->name->text());
    int nfiles = ui->tableWidget->rowCount();
    for(int i = 0; i < nfiles; i++)
    {
        auto name = ui->tableWidget->item(i, 0)->text();

        fields.append(QString(name)+ " ");
        auto type = static_cast<QComboBox*>(ui->tableWidget->cellWidget(i,1))->currentText();
        bool primaryKey = static_cast<QRadioButton*>(ui->tableWidget->cellWidget(i, 2))->isChecked();
        bool notNull = static_cast<QRadioButton*>(ui->tableWidget->cellWidget(i, 3))->isChecked();
        bool autoInc = static_cast<QRadioButton*>(ui->tableWidget->cellWidget(i, 4))->isChecked();
        res += name + " " + type + " ";
        if(primaryKey)
            res += " PRIMARY KEY";
        if(autoInc)
            res += " AUTOINCREMENT";
        if(notNull)
            res += " NOT NULL";

        res += ", ";
    }

    res[res.size() - 2] = ')';
    return res;
}

QString newTableDialog::getFields()
{
    return this->fields;
}
