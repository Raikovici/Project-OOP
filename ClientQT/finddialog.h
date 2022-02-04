/*
 * Copyright (C) 2009  Lorenzo Bettini <http://www.lorenzobettini.it>
 * See COPYING file that comes with this distribution
 */

#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QSettings>
#include "findreplacedialog.h"

class FindDialog : public FindReplaceDialog {
    Q_OBJECT
public:
    FindDialog(QWidget *parent = 0);
    ~FindDialog();

    virtual void writeSettings(QSettings &settings, const QString &prefix = "FindDialog");

    virtual void readSettings(QSettings &settings, const QString &prefix = "FindDialog");
};

#endif // FINDDIALOG_H
