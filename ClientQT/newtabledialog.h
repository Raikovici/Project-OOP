#ifndef NEWTABLEDIALOG_H
#define NEWTABLEDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class newTableDialog;
}

class newTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit newTableDialog(QWidget *parent = nullptr);
    ~newTableDialog();
    QString result();
    QString getFields();
    std::string getName();
private slots:
    void on_Accept_clicked();

    void on_Cancel_clicked();

private:
    Ui::newTableDialog *ui;
    QString fields;
};

#endif // NEWTABLEDIALOG_H
