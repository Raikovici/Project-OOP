#ifndef NEWDATABASE_H
#define NEWDATABASE_H

#include <QDialog>
#include <QString>
#include <QFileDialog>
#include <QDir>
namespace Ui {
class newDatabase;
}

class newDatabase : public QDialog
{
    Q_OBJECT

public:
    explicit newDatabase(QWidget *parent = nullptr);
    ~newDatabase();
    QString name();
    QString location();
private slots:
    void on_accept_clicked();

    void on_cancel_clicked();

    void on_Browse_clicked();

private:
    Ui::newDatabase *ui;
};

#endif // NEWDATABASE_H
