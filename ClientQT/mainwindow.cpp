#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "appwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->username->setPlaceholderText("Enter your username");
    ui->password->setPlaceholderText("Enter your password");
    ui->username2->setPlaceholderText("Please enter username");
    ui->password2->setPlaceholderText("Please enter password");
    ui->email->setPlaceholderText("Enter your email");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_registerButon_clicked()
{
    // Connecting to mySql Database

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setHostName("127.0.0.1");
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("C:\\Users\\Andrei\\Desktop\\RegisterSystem\\RegisterSystem\\myDB.sqlite");

    if(database.open())
    {
        QString username = ui->username->text();
        QString password = ui->password->text();
        QString email = ui->email->text();

        // Run our insert Query

        QSqlQuery query;
        query.prepare("INSERT INTO users (username, password, email)"
                       "VALUES (:username, :password, :email)");
        query.bindValue(":username", username);
        query.bindValue(":password",password);
        query.bindValue(":email",email);

        if(query.exec())
        {

            QMessageBox::information(this,"Inserted","Data Inserted Successfully");
        }
        else
        {
            QMessageBox::information(this,"Not Inserted", "Data is not inserted");
        }

    }
    else
    {
        QMessageBox::information(this,"Not Connected","Database is not connected");
    }
}

void MainWindow::on_loginButon_clicked()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", "MyConnect");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("C:\\Users\\Andrei\\Desktop\\RegisterSystem\\RegisterSystem\\myDB.sqlite");

    QString username = ui->username2->text();
    QString password = ui->password2->text();

    if (db.open())
    {
        //QMessageBox::information(this, "Database Succes", "Database connection success!");
        QSqlQuery query(QSqlDatabase::database("MyConnect"));

        query.prepare((QString("SELECT * FROM users WHERE username = :username AND password = :password")));
        query.bindValue(":username", username);
        query.bindValue(":password", password);

        if(!query.exec())
        {
            QMessageBox::information(this,"Failed", "Query failed to execute");

        }
        else
        {
            while(query.next())
            {
                QString usernameFromDB = query.value(0).toString();
                QString passwordFromDB = query.value(1).toString();

                if(usernameFromDB == username && passwordFromDB == password)
                {
                    QMessageBox::information(this,"Succes", "Login Success");
                    hide();
                    W = new AppWindow(this);
                    W->show();
                }
                else
                {
                    QMessageBox::information(this,"Failed","Login Failed");
                }
            }
        }
    }
    else
        QMessageBox::information(this, "Database Failed", "Database connection failed!");
}

