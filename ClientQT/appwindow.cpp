#define _CRT_SECURE_NO_WARNINGS
#include "appwindow.h"
#include "ui_appwindow.h"
#include "findreplacedialog.h"
#include "preferencesdialog.h"
#include "newtabledialog.h"
#include "settings.h"
#include "newdatabase.h"
#include "Client.h"
#include "insertdatatable.h"
#include "defines.h"
#include <QFile>
#include <QTextStream>
#include <QClipboard>
#include <QMessageBox>
#include <QFileDialog>
#include <QTreeWidgetItem>
#include <QPrintDialog>
#include <QPrinter>
#include <QSqlDatabase>
#include <QList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDropEvent>
#include <QMoveEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QMimeData>
#include <QUrl>
#include <QVariant>
#include <QModelIndex>
#include <QWidgetItem>
#include <QDesktopServices>
using TreeItem = QTreeWidgetItem;
using ListItem = QListWidgetItem;

Client& C = Client::getInstance();

AppWindow::AppWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::AppWindow)
{

    C.startClient();
    ui->setupUi(this);
    centralWidget()->layout()->setContentsMargins(3,15,3,2);
    auto nameApp = "Client SQL";
    TreeItem* root = new TreeItem();
    root->setText(0, nameApp);
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    ui->treeWidget->setItemWidget(root, 0, ui->treeWidget);
    ui->treeWidget->addTopLevelItem(root);

    auto vfont = load(GFONT, KFONTTYPE, ui->textEdit->font());
    ui->textEdit->setFont(vfont.value<QFont>());
    setAcceptDrops(true);

    connect(ui->treeWidget, &TreeWidget::newDatabase, [&]()
    {
        auto item = ui->treeWidget->currentItem();
        if(item == 0)
        {
            QMessageBox::warning(this, "Warning!"," This function can be used "
                                "when you select a database!");
            return;
        }
        newDatabase D(this);
        if(D.exec() == QDialog::Rejected)
        {
            return;
        }
        auto name = D.name();
        auto loc = D.location();

        usedBase.setName(name.toStdString());
        usedBase.setLoc(loc.toStdString());
        usedBase.setPath(name.toStdString() + "/" +loc.toStdString());
        ui->textEdit->setPlainText(QString("CREATE DATABASE %1").arg(D.name()));

    });
    connect(ui->treeWidget, &TreeWidget::newTable, [&]()
    {
        auto item = ui->treeWidget->currentItem();
        if(item == nullptr)
        {
            QMessageBox::warning(this, "Warning!"," This function can be used "
                                "when you select a database!");
            return;
        }
        auto parent = item->parent();
        if(parent != nullptr)
        {
            QMessageBox::warning(this, "Warning!"," This function can be used "
                                "when you select a database!");
            return;
        }
        newTableDialog D(this);
        if(D.exec() == QDialog::Rejected)
        {
            return;
        }
        tableForUse.setRes(D.result().toStdString());
        tableForUse.setNume(D.getName());
        tableForUse.setFields(D.getFields().toStdString());
        ui->textEdit->setPlainText(D.result());
    });
    connect(ui->treeWidget, &TreeWidget::dropTable, [&]()
    {
        auto item = ui->treeWidget->currentItem();
        if(item == nullptr)
        {
            QMessageBox::warning(this, "Warning!"," This function can be used "
                                "when you select a table!");
            return;
        }
        auto parent = item->parent();
        if(parent == nullptr)
        {
            QMessageBox::warning(this, "Warning!"," This function can be used "
                                "when you select a table!");
            return;
        }
        string s = item->text(0).toStdString();
        int pos = s.find("->");
        string ss = s.substr(0, pos - 1);
        ui->textEdit->setPlainText(QString("DROP TABLE %1").arg(QString::fromStdString(ss)));
    });
    connect(ui->treeWidget, &TreeWidget::dropDatabase, [&]()
    {
        auto item = ui->treeWidget->currentItem();
        if(item == nullptr)
        {
            QMessageBox::warning(this, "Warning!"," This function can be used "
                                "when you select a database!");
            return;
        }
        auto parent = item->parent();
        if(parent != nullptr)
        {
            QMessageBox::warning(this, "Warning!"," This function can be used "
                                "when you select a database!");
            return;
        }
        ui->textEdit->setPlainText(QString("DROP DATABASE %1").arg(item->text(0)));
    });
    connect(ui->treeWidget, &TreeWidget::insertData, [&]()
    {
        auto item = ui->treeWidget->currentItem();
        if(item == nullptr)
        {
            QMessageBox::warning(this, "Warning!"," This function can be used "
                                "when you select a table!");
            return;
        }
        auto parent = item->parent();
        if(parent == nullptr)
        {
            QMessageBox::warning(this, "Warning!"," This function can be used "
                                "when you select a table!");
            return;
        }
        auto tab = ui->treeWidget->currentItem();
        auto txt = tab->text(0);
        std::string t = txt.toStdString();
        std::string delim = " ", token = "", campuri = "";
        auto start = 0;
        auto end = t.find(delim);
        int i = 0;
        while (end != std::string::npos)
        {
               token = t.substr(start, end - start);
               if(token != "" && token != "->" && token != " ")
               {
                   if(i == 0)
                       tableForUse.setNume(token);
                   else
                       campuri += token + " ";
               }
               start = end + delim.length();
               end = t.find(delim, start);
            i++;
        }
        token = t.substr(start, end);
        if(token != "" && token != "->" && token != " ")
            campuri += token + " ";

        tableForUse.setFields(campuri);
        insertDataTable D(this);
        D.setTabel(&tableForUse);
        D.setHeaderTable();
        if(D.exec() == QDialog::Rejected)
        {
            return;
        }
        ui->textEdit->setPlainText(D.getResult());
    });
    connect(ui->treeWidget, &TreeWidget::selectFrom, [&]()
    {
        auto item = ui->treeWidget->currentItem();
        if(item == nullptr)
        {
            QMessageBox::warning(this, "Warning!"," This function can be used "
                                "when you select a table!");
            return;
        }
        auto parent = item->parent();
        if(parent == nullptr)
        {
            QMessageBox::warning(this, "Warning!"," This function can be used "
                                "when you select a table!");
            return;
        }
        string s = item->text(0).toStdString();
        int pos = s.find("->");
        string ss = s.substr(0, pos - 1);
        ui->textEdit->setPlainText(QString("SELECT * FROM %1").arg(QString::fromStdString(ss)));
    });
}

AppWindow::~AppWindow()
{
    delete ui;
}

void AppWindow::dragEnterEvent(QDragEnterEvent *e)
{
    e->accept();
}

void AppWindow::dragLeaveEvent(QDragLeaveEvent *e)
{
    e->accept();
}

void AppWindow::dragMoveEvent(QDragMoveEvent *e)
{
    e->accept();
}

string getDBName(string name)
{
    int poz = 0;
    for(int i = 0; i < name.size(); i++)
    {
        if(name[i] == '/')
        {
            poz = i;
        }
    }
    string n = name.substr(poz + 1);
    int p = n.find('.');
    string nn = n.substr(0, p);
    return nn;
}

void AppWindow::dropEvent(QDropEvent *e)
{
    auto data = e->mimeData();
    auto url = data->urls();
    for(auto u : url)
    {
        auto name = u.toLocalFile();
        auto dbItem = new TreeItem();
        dbItem->setIcon(0, QIcon(":/images/db_flat.png"));
        string n = name.toStdString();
        string nname = getDBName(n);
        dbItem->setText(0, QString::fromStdString(nname));
        QList<TreeItem*> tabels;
        QFile file(name);
        if(!file.open(QIODevice::ReadWrite))
        {
            QMessageBox::critical(this, "Error", QString("Can't open file %1\n").arg(QString::fromStdString(nname)));
        }
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            auto tableItem = new TreeItem;
            tableItem->setIcon(0, QIcon(":/images/table-icon.png"));
            tableItem->setText(0, line);
            tabels.append(tableItem);
            dbItem->addChild(tableItem);
        }
        ui->treeWidget->addTopLevelItem(dbItem);
    }
}

void AppWindow::on_actionOpen_Database_triggered()
{
    auto name = QFileDialog::getOpenFileName(this, "Open DataBase",
                                             QDir::currentPath(),
                                             "Any type (*.*)");
    if(name.isEmpty())
    {
        return;
    }
    pathUsed = name.toStdString();
    auto dbItem = new TreeItem();
    dbItem->setIcon(0, QIcon(":/images/db_flat.png"));
    string n = name.toStdString();
    string nname = getDBName(n);
    dbItem->setText(0, QString::fromStdString(nname));

    QList<TreeItem*> tabels;
    QFile file(name);
    if(!file.open(QIODevice::ReadWrite))
    {
        QMessageBox::critical(this, "Error", QString("Can't open file %1\n").arg(QString::fromStdString(nname)));
    }
    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        auto tableItem = new TreeItem;
        tableItem->setIcon(0, QIcon(":/images/table-icon.png"));
        tableItem->setText(0, line);
        tabels.append(tableItem);
        dbItem->addChild(tableItem);
    }
    ui->treeWidget->addTopLevelItem(dbItem);
}

void AppWindow::on_actionSave_Database_triggered()
{
    auto name = QFileDialog::getSaveFileName(this, "Save DataBase",
                                             QDir::currentPath(),
                                             "Database(*.db);;"\
                                             "Any type (*.*)");
    if(name.isEmpty())
    {
        return;
    }
    auto dbItem = new TreeItem();
    dbItem->setIcon(0, QIcon(":/images/db_flat.png"));
    dbItem->setText(0, name);
    ui->treeWidget->addTopLevelItem(dbItem);
    QSqlDatabase base;
    base.setDatabaseName(name);
    if(base.open())
    {
        QMessageBox::critical(this, "Error", QString("Can't create database %1\n").arg(name));
    }
}

void AppWindow::on_actionOpen_Query_triggered()
{
    auto name = QFileDialog::getOpenFileName(this, "Open SQL", QDir::currentPath(),
                                               "File SQL (*.sql);;"\
                                                "Any type (*.*)");
    if(name.isEmpty())
    {
        return;
    }
    QFile F(name);
    if(!F.open(QIODevice::Text | QIODevice::ReadWrite))
    {
        QMessageBox::critical(this, "Error", QString("Error: %1").arg(F.errorString()));
        return;
    }
    QTextStream S(&F);
    ui->textEdit->setText(S.readAll());
    F.close();
}

void AppWindow::on_actionSave_Query_triggered()
{
    auto name = QFileDialog::getSaveFileName(this, "Open SQL", QDir::currentPath(),
                                               "File SQL (*.sql);;"\
                                                "Any type (*.*)");
    if(name.isEmpty())
    {
        return;
    }
    QFile F(name);
    if(!F.open(QIODevice::Text | QIODevice::WriteOnly))
    {
        QMessageBox::critical(this, "Error", QString("Error: %1").arg(F.errorString()));
        return;
    }
    QTextStream S(&F);
    S << ui->textEdit->toPlainText();
    F.flush();
    F.close();
}

void AppWindow::on_actionPrint_triggered()
{
    QPrintDialog P(this);
    if(P.exec() == QDialog::Rejected)
        return;
    ui->textEdit->print(P.printer());

}

void AppWindow::on_actionExit_triggered()
{
    close();
}

void AppWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void AppWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void AppWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void AppWindow::on_actionFind_and_Replace_triggered()
{
    FindReplaceDialog F(this);
    F.setTextEdit(ui->textEdit);
    F.exec();
}

void AppWindow::on_actionRun_triggered()
{
    auto sql = ui->textEdit->toPlainText();

    string str = sql.toStdString();
    C.sendToServer(str);
    C.receiveFromServer();
    if(sql.startsWith("select", Qt::CaseInsensitive))
    {
        string result = "";
        ui->tableWidget->setRowCount(0);
        result = C.getResponse();
        vector<vector<string>> vectorRes;
        int lines = 0;
        for (int i = 0; i < result.length(); i++)
        {
                if (result[i] == '\n')
                    lines++;
        }

        vectorRes.resize(lines);
        string record = "";
        int j = 0;
        for (int i = 0; i < result.length(); i++)
        {
            if (result[i] == ' ')
                {
                    vectorRes[j].push_back(record);
                    record = "";
                }
                else if (result[i] == '\n')
                {
                    vectorRes[j].push_back(record);
                    record = "";
                    j++;
                }
                else
                {
                    record += result[i];
                }
         }
         int cols = 0;
         for(auto it = vectorRes[0].begin(); it < vectorRes[0].end(); it++)
         {
             if(*it != " " && *it != "\n" && *it != "")
                cols++;
         }
         ui->tableWidget->setColumnCount(cols);
         for(auto i = 0; i < vectorRes[0].size(); i++)
         {
             if(vectorRes[0][i] != " " && vectorRes[0][i] != "\n" && vectorRes[0][i] != "")
             {
                QString n = QString::fromStdString(vectorRes[0][i]);
                ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(n));
             }
         }
         int q = 0, p = 0, a = j;
         for (int i = 1; i < a; i++)
         {
             q = 0;
             ui->tableWidget->insertRow(p);
             for (int k = 0; k < vectorRes[i].size(); k++)
             {
                 if(vectorRes[i][k] != " " && vectorRes[i][k] != "\n" && vectorRes[i][k] != "")
                 {
                     QString cell = QString::fromStdString(vectorRes[i][k]);
                     ui->tableWidget->setItem(p, q, new QTableWidgetItem(cell));
                     ++q;
                 }
             }
             ++p;
         }
    }

    else if(sql.startsWith("create database", Qt::CaseInsensitive))
    {
        ListItem* newListItem = new ListItem(QIcon(":/images/correct.png"), sql);
        ui->listWidget->addItem(newListItem);

        CDataBase* c = new CDataBase();
        c->setName(usedBase.getName());
        c->setLoc(usedBase.getLoc());
        auto name = c->getLoc() + "\\";
        QDir d;
        std::replace(name.begin(), name.end(), '/', '\\');
        d.mkpath(QString::fromStdString(name));
        QFile file(QString::fromStdString(name) + QString::fromStdString("\\" + c->getName() + ".txt"));
        file.open(QIODevice::ReadWrite);
    }

    else if(sql.startsWith("create table", Qt::CaseInsensitive))
    {
        ListItem* newListItem = new ListItem(QIcon(":/images/correct.png"), sql);
        ui->listWidget->addItem(newListItem);
        auto createTable = QString("CREATE TABLE IF NOT EXISTS ");

        int pos1 = createTable.size();
        int pos2 = sql.indexOf("(", pos1);
        auto table = sql.mid(pos1, pos2 - pos1);
        table = table.mid(0, table.indexOf(" "));
        auto name = usedBase.getLoc() + "\\";
        std::replace(name.begin(), name.end(), '/', '\\');
        QFile file(QString::fromStdString(name) + QString::fromStdString("\\" + usedBase.getName() + ".txt"));
        QTextStream out(&file);
        if(file.open(QIODevice::Append))
        {
            out << table << " -> " << QString::fromStdString(tableForUse.getFields()) << "\n";
        }
        int i = 0, nr = ui->treeWidget->topLevelItemCount(), poz = 0;
        for(i = 0; i < nr; i++)
        {
            if(ui->treeWidget->topLevelItem(i)->text(0) == QString::fromStdString(usedBase.getName()))
            {
                break;
            }
        }
        std::string line;
        poz= i;
        auto dbItem = ui->treeWidget->topLevelItem(poz);
        auto tableItem = new TreeItem;
        tableItem->setIcon(0, QIcon(":/images/table-icon.png"));
        tableItem->setText(0, table + " -> " + QString::fromStdString(tableForUse.getFields()));
        dbItem->addChild(tableItem);
    }

    else if(sql.startsWith("drop table", Qt::CaseInsensitive))
    {
        ListItem* newListItem = new ListItem(QIcon(":/images/correct.png"), sql);
        ui->listWidget->addItem(newListItem);


        auto base = usedBase.getName();
        int i = 0, nr = ui->treeWidget->topLevelItemCount(), poz = 0;
        for(i = 0; i < nr; i++)
        {
            if(ui->treeWidget->topLevelItem(i)->text(0) == QString::fromStdString(base))
            {
                break;
            }
        }
        poz = i;
        auto dropTable = QString("drop table");
        auto table = sql.mid(dropTable.size());
        auto dbItem = ui->treeWidget->topLevelItem(poz);
        int j = 0, nrT = dbItem->childCount();
        table = table.mid(1);

        for(j = 0; j < nrT; j++)
        {
            if(dbItem->child(j)->text(0).contains(table))
                break;
        }
        dbItem->removeChild(dbItem->child(j));
        auto name = pathUsed;
        std::replace(name.begin(), name.end(), '/', '\\');
        QFile file(QString::fromStdString(name));
        QString newLine;
        if(file.open(QIODevice::ReadWrite))
        {
            QTextStream in(&file);

            while(!in.atEnd())
            {
                QString line = in.readLine();
                if(line.toStdString().find(table.toStdString()) == std::string::npos)
                {
                    newLine.append(line + "\n");
                }
            }
            file.resize(0);
            in << newLine;
        }
        file.close();
    }

    else if(sql.startsWith("drop database", Qt::CaseInsensitive))
    {
        ListItem* newListItem = new ListItem(QIcon(":/images/correct.png"), sql);
        ui->listWidget->addItem(newListItem);

        auto dropbase = QString("drop database");
        auto basse = sql.mid(dropbase.size());
        basse = basse.mid(1);

        int i = 0, nr = ui->treeWidget->topLevelItemCount(), poz = 0;
        for(i = 0; i < nr; i++)
        {
            if(ui->treeWidget->topLevelItem(i)->text(0) == basse)
            {
                break;
            }
        }
        poz = i;
        auto root = ui->treeWidget->takeTopLevelItem(poz);
        ui->treeWidget->removeItemWidget(root, 0);
    }

    else if(sql.startsWith("insert into ", Qt::CaseInsensitive))
    {
        ListItem* newListItem = new ListItem(QIcon(":/images/correct.png"), sql);
        ui->listWidget->addItem(newListItem);
    }

    else if(sql.startsWith("use ", Qt::CaseInsensitive))
    {
        ListItem* newListItem = new ListItem(QIcon(":/images/correct.png"), sql);
        ui->listWidget->addItem(newListItem);
        string s = sql.toStdString();
        int pos = s.find(' ');
        string base = s.substr(pos + 1);
        usedBase.setName(base);

        int poz = pathUsed.find(base);
        string pathtrue = pathUsed.substr(0, poz);
        usedBase.setLoc(pathtrue);
    }

    else if(sql.startsWith("update ", Qt::CaseInsensitive) || sql.startsWith("delete ", Qt::CaseInsensitive)
            || sql.startsWith("alter ", Qt::CaseInsensitive))
    {
        ListItem* newListItem = new ListItem(QIcon(":/images/correct.png"), sql);
        ui->listWidget->addItem(newListItem);
    }
    else
    {
        QString ress = QString::fromStdString(C.getResponse());
        if(ress.contains("send a valid query"))
        {
            ListItem* newListItem = new ListItem(QIcon(":/images/fail.png"), sql);
            ui->listWidget->addItem(newListItem);
            return;
        }
    }

}

void AppWindow::on_actionPreferences_triggered()
{
    PreferencesDialog p(this);
    connect(&p, &PreferencesDialog::applyFont, [&](const QFont& f)
    {
        ui->textEdit->setFont(f);
        save(GFONT, KFONTTYPE, f);
    });
    if(p.exec() == QDialog::Rejected)
        return;
}

void AppWindow::on_actionManual_triggered()
{
    QDesktopServices::openUrl(QUrl("https://wiki.qt.io/Main"));
}

void AppWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "ClientSQL",
                       QString("Autors: Raicu Andrei + Nicolita Andrei\nApp: Database Engine\nVersion: %1\nOrganization Name: "
                                                "%2\nProject Coordinator: Lt. col. prof. univ. dr. ing. TOGAN Mihai ").arg(APPVER, ORGNAME));
}

void AppWindow::on_treeWidget_clicked(const QModelIndex &index)
{
    if(index.parent().isValid())
        return;

    auto name = index.data().toString();
}
