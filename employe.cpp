#include "employe.h"
#include "ui_employe.h"
#include <QMessageBox>
#include "employes.h"
#include "mainwindow.h"
#include <QDebug>

#include <QPdfWriter>
#include <QPainter>

#include <QDesktopServices>
#include <QUrl>

#include "chatwindow.h"
#include "serverwindow.h"

#include "accueil.h"
#include "client.h"


employe::employe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::employe)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);
    ui->tab_emp->setModel(etmp.afficher());
    ui->lineEdit_salaire->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_nom->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]*"),this));
    ui->lineEdit_prenom->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]*"),this));
    ui->lineEdit_fonction->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]*"),this));

    ui->affichage_salaire->setValidator(new QIntValidator(0,999999,this));
    ui->affichage_nom->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]*"),this));
    ui->affichage_prenom->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]*"),this));
    ui->affichage_fonction->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]*"),this));

    windowTitle();
    setWindowTitle("Gestion des employés");
}
employe::~employe()
{
    delete ui;
}

void employe::on_ajouter_clicked()
{
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString matricule=ui->lineEdit_matricule->text();

    QString fonction=ui->lineEdit_fonction->text();
    float salaire=ui->lineEdit_salaire->text().toFloat();

    employes e(matricule,nom,prenom,fonction,salaire);

    bool test=e.ajouter();

    if(test)
    {
        ui->tab_emp->setModel(etmp.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("Ajout effectué \n"
                            "Click cancel to exit."),QMessageBox::Cancel);

    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("OK"),
                QObject::tr("Ajout non effectué \n"
                            "Click cancel to exit."),QMessageBox::Cancel);
    }
    ui->lineEdit_nom->clear();
    ui->lineEdit_prenom->clear();
    ui->lineEdit_matricule->clear();
    ui->lineEdit_fonction->clear();
    ui->lineEdit_salaire->clear();

}

void employe::on_supprimer_clicked()
{
    QString matricule=ui->affichage_matricule->text();

    bool test=etmp.supprimer(matricule);
    if(test)
    {
        ui->tab_emp->setModel(etmp.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("Suppression effectuée \n"
                            "Click cancel to exit."),QMessageBox::Cancel);

        ui->affichage_nom->clear();
        ui->affichage_prenom->clear();
        ui->affichage_salaire->clear();
        ui->affichage_matricule->clear();
        ui->affichage_fonction->clear();
        QDateTime dateTime=QDateTimeEdit().dateTime();
        ui->affichage_date->setDateTime(dateTime);

    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("OK"),
                QObject::tr("Suppression non effectuée \n"
                            "Click cancel to exit."),QMessageBox::Cancel);
    }


}

void employe::on_modifier_clicked()
{
    employes e;
    QString matricule=ui->affichage_matricule->text();
    QString nom=ui->affichage_nom->text();
    QString prenom=ui->affichage_prenom->text();
    float salaire=ui->affichage_salaire->text().toFloat();
    QString fonction=ui->affichage_fonction->text();

        bool test=e.modifier(matricule,nom,prenom,fonction,salaire);
        if(test)
        {
            ui->tab_emp->setModel(etmp.afficher());

            QMessageBox::information(nullptr,QObject::tr("OK"),
                    QObject::tr("Modification effectuée \n"
                                "Click cancel to exit."),QMessageBox::Cancel);

        }
        else{
            QMessageBox::critical(nullptr,QObject::tr("OK"),
                    QObject::tr("Modification non effectuée \n"
                                "Click cancel to exit."),QMessageBox::Cancel);
        }
}

void employe::on_annuler_clicked()
{
    ui->lineEdit_nom->clear();
    ui->lineEdit_prenom->clear();
    ui->lineEdit_matricule->clear();
    ui->lineEdit_fonction->clear();
    ui->lineEdit_salaire->clear();
}

void employe::on_refresh_clicked()
{
    ui->tab_emp->setModel(etmp.afficher());
    ui->affichage_nom->clear();
    ui->affichage_prenom->clear();
    ui->affichage_salaire->clear();
    ui->affichage_matricule->clear();
    ui->affichage_fonction->clear();
    QDateTime dateTime=QDateTimeEdit().dateTime();
    ui->affichage_date->setDateTime(dateTime);

}

void employe::on_tab_emp_activated(const QModelIndex &index)
{
    QString matricule=ui->tab_emp->model()->data(index).toString();

    QSqlQuery query;
    query.prepare("select * from employes where matricule=:matricule");
    query.bindValue(":matricule",matricule);
    if(query.exec())
    {
        while(query.next())
        {
            ui->affichage_matricule->setText(query.value(0).toString());
            ui->affichage_nom->setText(query.value(1).toString());
            ui->affichage_prenom->setText(query.value(2).toString());
            ui->affichage_date->setDate(query.value(3).toDate());
            ui->affichage_salaire->setText(query.value(4).toString());
            ui->affichage_fonction->setText(query.value(5).toString());
        }
    }
}

void employe::on_radioButton_tri_nom_clicked()
{
    ui->tab_emp->setModel(etmp.tri_croissant_nom());
}


void employe::on_radioButton_tri_prenom_clicked()
{
     ui->tab_emp->setModel(etmp.tri_croissant_prenom());
}


void employe::on_radioButton_tri_salaire_clicked()
{
     ui->tab_emp->setModel(etmp.tri_croissant_salaire());
}


void employe::on_radioButton_tri_fonction_clicked()
{
    ui->tab_emp->setModel(etmp.tri_croissant_fonction());
}

void employe::on_PDF_clicked()
{
    QPdfWriter fichier_pdf("G:\\ListeEmployes.pdf");
    QString date=QDateTime::currentDateTime().toString();

   QPainter painter(&fichier_pdf);
   int i = 4000;
          QImage img("G:\\2A\\2A_S2\\Gestion-employes\\App_LOGO.png");
          QPoint imageCoordinates(10,200);
          painter.drawImage(imageCoordinates,img);
          painter.setPen(Qt::black);
          painter.setFont(QFont("Time New Roman", 25));
          painter.drawText(3000,1400,"Liste Des Employes");
          painter.setPen(Qt::black);
          painter.setFont(QFont("Time New Roman", 10));
          painter.drawText(7300,0,date);
          painter.drawRect(100,100,9400,2500);
          painter.drawRect(100,3000,9400,500);
          painter.setFont(QFont("Time New Roman", 9));
          painter.drawText(400,3300,"Matricule");
          painter.drawText(1350,3300,"Nom");
          painter.drawText(2200,3300,"Prenom");
          painter.drawText(3400,3300,"Date d'Embauche");
          painter.drawText(5400,3300,"Salaire");
          painter.drawText(7200,3300,"Fonction");
          painter.drawRect(100,3000,9400,9000);

          QSqlQuery query;
          query.prepare("select * from employes");
          query.exec();
          while (query.next())
          {
              painter.drawText(400,i,query.value(0).toString());
              painter.drawText(1350,i,query.value(1).toString());
              painter.drawText(2200,i,query.value(2).toString());
              painter.drawText(3400,i,query.value(3).toString());
              painter.drawText(5400,i,query.value(4).toString());
              painter.drawText(7200,i,query.value(5).toString());

             i = i + 350;
          }
          QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
          QObject::tr("PDF Enregistré.\n" "Click Cancel to exit."), QMessageBox::Cancel);
          QDesktopServices::openUrl(QUrl("G://ListeEmployes.pdf", QUrl::TolerantMode));

}
void employe::setData(QString data)
{
    if(data=="Admin"){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("Welcome admin \n"
                            "Click cancel to exit."),QMessageBox::Cancel);
    }
}

void employe::on_lineEdit_rec_textChanged(const QString &arg1)
{
           ui->tab_emp->setModel(etmp.rechercher(arg1));
}

void employe::on_lancerChat_clicked()
{
    ServerWindow serverWin;
    serverWin.hide();

    ChatWindow chatWin;
    chatWin.setModal(true);
    chatWin.show();
    chatWin.exec();
}

void employe::on_pushButton_clicked()
{
    accueil a;
    hide();
    a.setData(nom_u,role);
    a.setModal(true);
    a.exec();
}
