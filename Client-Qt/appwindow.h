#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "cdatabase.h"
#include "ctable.h"
#include "ui_appwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class AppWindow; }
QT_END_NAMESPACE

class QSqlQueryModel;

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppWindow(QWidget *parent = nullptr);

    ~AppWindow();
protected:
    void dragEnterEvent(QDragEnterEvent* e);
    void dragLeaveEvent(QDragLeaveEvent* e);
    void dragMoveEvent(QDragMoveEvent* e);
    void dropEvent(QDropEvent* e);
private slots:
    void on_actionOpen_Database_triggered();

    void on_actionSave_Database_triggered();

    void on_actionOpen_Query_triggered();

    void on_actionSave_Query_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionFind_and_Replace_triggered();

    void on_actionRun_triggered();

    void on_actionPreferences_triggered();

    void on_actionManual_triggered();

    void on_actionAbout_triggered();

    void on_treeWidget_clicked(const QModelIndex &index);

private:
    Ui::AppWindow *ui;
    CDataBase usedBase;
    CTable tableForUse;
    std::string pathUsed;
};
#endif // APPWINDOW_H
