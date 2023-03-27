QT += core gui
QT += sql
QT += network
QT += serialport
QT += printsupport
QT += multimedia multimediawidgets charts
include(QZXing/QZXing.pri)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accueil.cpp \
    arduino.cpp \
    chatclient.cpp \
    chatserver.cpp \
    chatwindow.cpp \
    comptes.cpp \
    connection.cpp \
    employe.cpp \
    employes.cpp \
    main.cpp \
    mainwindow.cpp \
    serverwindow.cpp \
    serverworker.cpp \
    commande.cpp \
    gerer_commande.cpp \
    scenario_02.cpp \
    materiaux.cpp \
    materiel.cpp \
    smtp.cpp \
    glivraison.cpp \
    livraison.cpp \
    client.cpp \
    clients.cpp \
    popup.cpp \
    produit.cpp \
    produitmain.cpp \
    seriallink.cpp


HEADERS += \
    accueil.h \
    arduino.h \
    chatclient.h \
    chatserver.h \
    chatwindow.h \
    comptes.h \
    connection.h \
    employe.h \
    employes.h \
    mainwindow.h \
    serverwindow.h \
    serverworker.h \
    commande.h \
    gerer_commande.h \
    scenario_02.h \
    materiaux.h \
    materiel.h \
    smtp.h \
    glivraison.h \
    livraison.h \
    client.h \
    clients.h \
    popup.h \
    produit.h \
    produitmain.h \
    seriallink.h

FORMS += \
    accueil.ui \
    chatwindow.ui \
    employe.ui \
    mainwindow.ui \
    serverwindow.ui \
    gerer_commande.ui \
    scenario_02.ui \
    materiaux.ui \
    livraison.ui \
    client.ui \
    produitmain.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    map.qrc \
    resources.qrc
RC_ICONS = picture/App_LOGO.ico
