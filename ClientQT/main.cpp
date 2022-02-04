#include "mainwindow.h"
#include "defines.h"
#include <QApplication>
#include <QMetaObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    a.setApplicationName(APPNAME);
    a.setApplicationVersion(APPVER);
    a.setOrganizationDomain(ORGDOM);
    a.setOrganizationName(ORGNAME);

    MainWindow w;
    w.show();

    return a.exec();
}
