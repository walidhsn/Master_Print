#include "mainwindow.h"
#include <QApplication>
#include "employe.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "connection.h"
#include "employes.h"
#include <QFile>
#include <QInputDialog>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Set Style Sheet :
        QFile styleSheetFile(":/resources/sheet/darkorange.qss");
        styleSheetFile.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(styleSheetFile.readAll());
        a.setStyleSheet(styleSheet);
        //-----------------|

    QTranslator t;
    QStringList language;
    language << "French" <<"English"<<"Arabic";
    QString lang;
    do{
    lang = QInputDialog::getItem(NULL,"Language","Select a language :",language);
    }while(lang!="French" && lang != "English" && lang!="Arabic");
    if(lang=="English")
    {
        t.load(":/english.qm");
    }else if(lang=="Arabic")
    {
        t.load(":/arabic.qm");
    }
    if(lang!="French")
    {
        a.installTranslator(&t);
    }
    Connection c;
    bool test=c.createconnection();
    MainWindow w;

    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("La base de données est ouverte"),
                    QObject::tr("connecté avec succès.\n"
                                "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
         w.show();

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("La base de données n'est pas ouverte"),
                    QObject::tr("la connexion a échoué.\n"
                                "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
//------------------------------------------------------------------------------------|



    return a.exec();
}
