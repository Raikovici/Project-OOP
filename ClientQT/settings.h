#ifndef SETTINGS_H
#define SETTINGS_H
#include <QString>
#include <QVariant>

#define GFONT "GFONT"
#define KFONTTYPE "KFONTTYPE"
#define KFONTSIZE "KFONTSIZE"

QVariant load(const QString&g, const QString& k, const QVariant& v = QVariant());
void save(const QString& g, const QString& k, const QVariant& v);
#endif // SETTINGS_H
