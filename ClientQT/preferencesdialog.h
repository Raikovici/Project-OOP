#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include <QFont>
#include <QSpinBox>
namespace Ui {
class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesDialog(QWidget *parent = nullptr);
    ~PreferencesDialog();
signals:
    void applyFont(QFont);
private slots:
    void on_apply_clicked();

    void on_accept_clicked();

private:
    Ui::PreferencesDialog *ui;
};

#endif // PREFERENCESDIALOG_H
