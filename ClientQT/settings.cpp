#include "settings.h"
#include <QSettings>
void save(const QString &g, const QString &k, const QVariant &v)
{
    QSettings S;
    S.beginGroup(g);
    S.setValue(k, v);
    S.endGroup();
}

QVariant load(const QString &g, const QString &k, const QVariant &v)
{
    QSettings S;
    S.beginGroup(g);
    auto val = S.value(k, v);
    S.endGroup();
    return val;
}
