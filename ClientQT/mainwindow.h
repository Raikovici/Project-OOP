#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include "appwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; class AppWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_registerButon_clicked();

    void on_loginButon_clicked();

private:
    Ui::MainWindow *ui;
    AppWindow* W;
    QSqlDatabase database;
};
#endif // MAINWINDOW_H
