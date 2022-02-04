#include "treewidget.h"
#include <QAction>
#include <QMouseEvent>
TreeWidget::TreeWidget(QWidget* parent) : QTreeWidget(parent)
{
    actionNewDatabase = new QAction(QIcon(":/images/new-db.png"), "New Database", this);
    actionNewTable = new QAction(QIcon(":/images/addtable.png"), "New Table", this);
    actionDropTable = new QAction(QIcon(":/images/table_delete.png"), "Drop Table", this);
    actionDropDatabase = new QAction(QIcon(":/images/delete-db.png"), "Drop Database", this);
    actionInsertData = new QAction(QIcon(":/images/text-table.png"), "Insert Data", this);
    actionSelectFrom = new QAction(QIcon(":/images/select-icon.png"), "SELECT * FROM", this);
    addActions({actionNewDatabase, actionNewTable ,actionDropTable, actionDropDatabase, actionInsertData, actionSelectFrom});

    connect(actionNewDatabase, &QAction::triggered, [&](){
           emit newDatabase();
    });
    connect(actionDropDatabase, &QAction::triggered, [&](){
           emit dropDatabase();
    });
    connect(actionNewTable, &QAction::triggered, [&](){
           emit newTable();
    });
    connect(actionDropTable, &QAction::triggered, [&](){
           emit dropTable();
    });
    connect(actionInsertData, &QAction::triggered, [&](){
           emit insertData();
    });
    connect(actionSelectFrom, &QAction::triggered, [&](){
           emit selectFrom();
    });
}


