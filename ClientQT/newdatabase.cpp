#include "newdatabase.h"
#include "ui_newdatabase.h"
#include <QDir>
newDatabase::newDatabase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newDatabase)
{
    ui->setupUi(this);
}

newDatabase::~newDatabase()
{
    delete ui;
}

void newDatabase::on_accept_clicked()
{
    accept();
}

void newDatabase::on_cancel_clicked()
{
    reject();
}

QString newDatabase::location()
{

    auto s = ui->location->text();
    return s;
}

QString newDatabase::name()
{
    return ui->name->text();
}

void newDatabase::on_Browse_clicked()
{
    auto loc = QFileDialog::getExistingDirectory(this, "Browse", QDir::currentPath());
    if(loc.isEmpty())
    {
        return;
    }
    ui->location->setText(QString(loc));
}
