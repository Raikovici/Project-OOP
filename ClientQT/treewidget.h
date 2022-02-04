#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QTreeWidget>
#include <QWidget>
class QAction;
class TreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    TreeWidget(QWidget* parent = nullptr);
signals:
    void newDatabase();
    void dropDatabase();
    void newTable();
    void dropTable();
    void insertData();
    void selectFrom();
public:
    virtual ~TreeWidget(){}
private:
    QAction* actionNewDatabase;
    QAction* actionDropDatabase;
    QAction* actionNewTable;
    QAction* actionDropTable;
    QAction* actionSelectFrom;
    QAction* actionInsertData;
};

#endif // TREEWIDGET_H
