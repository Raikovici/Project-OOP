QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Client.cpp \
    ITCPClient.cpp \
    appwindow.cpp \
    cdatabase.cpp \
    ctable.cpp \
    finddialog.cpp \
    findform.cpp \
    findreplacedialog.cpp \
    findreplaceform.cpp \
    insertdatatable.cpp \
    main.cpp \
    mainwindow.cpp \
    newdatabase.cpp \
    newtabledialog.cpp \
    preferencesdialog.cpp \
    settings.cpp \
    treewidget.cpp

HEADERS += \
    Client.h \
    ITCPClient.h \
    appwindow.h \
    cdatabase.h \
    ctable.h \
    defines.h \
    finddialog.h \
    findform.h \
    findreplacedialog.h \
    findreplaceform.h \
    insertdatatable.h \
    mainwindow.h \
    newdatabase.h \
    newtabledialog.h \
    preferencesdialog.h \
    settings.h \
    treewidget.h

FORMS += \
    appwindow.ui \
    findreplacedialog.ui \
    findreplaceform.ui \
    insertdatatable.ui \
    mainwindow.ui \
    newdatabase.ui \
    newtabledialog.ui \
    preferencesdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
