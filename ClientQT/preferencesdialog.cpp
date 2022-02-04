#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"
#include "settings.h"
PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);
    auto vfont = load(GFONT, KFONTTYPE);
    ui->fontComboBox->setCurrentFont(vfont.value<QFont>());
    ui->spinBox->setValue(vfont.value<QFont>().pointSize());

}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

void PreferencesDialog::on_apply_clicked()
{
    auto f = ui->fontComboBox->currentFont();

    f.setPointSize(ui->spinBox->value());
    emit applyFont(f);
}

void PreferencesDialog::on_accept_clicked()
{
    on_apply_clicked();
    accept();
}
