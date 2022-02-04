/*
 * Copyright (C) 2009  Lorenzo Bettini <http://www.lorenzobettini.it>
 * See COPYING file that comes with this distribution
 */

#ifndef FINDFORM_H
#define FINDFORM_H

#include <QWidget>
#include <QTextCursor>

#include "findreplaceform.h"

class FindForm : public FindReplaceForm {
    Q_OBJECT
public:
    FindForm(QWidget *parent = 0);
    ~FindForm();

    virtual void writeSettings(QSettings &settings, const QString &prefix = "FindDialog");

    virtual void readSettings(QSettings &settings, const QString &prefix = "FindDialog");

protected:
    void changeEvent(QEvent *e);

};

#endif // FINDFORM_H
