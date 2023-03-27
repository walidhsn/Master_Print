#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "comptes.h"
#include "employe.h"
#include "accueil.h"
#include <QMessageBox>
#include <QCryptographicHash>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_users->setModel(cmpt.afficher_compte());
    QRegularExpression rx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",
    QRegularExpression::CaseInsensitiveOption);
    ui->emailU_compte->setValidator(new QRegularExpressionValidator(rx, this));
    ui->affichage_emailU->setValidator(new QRegularExpressionValidator(rx, this));

    windowTitle();
    setWindowTitle("Authentification");

    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_CreerCompte_clicked()
{
    QString type=ui->comboBox_type->currentText();
    QString nomUtilisateur=ui->nomU_compte->text();
    QString email=ui->emailU_compte->text();
    QByteArray mdp=ui->mdpU_compte->text().toLatin1();
    QByteArray mdp_conf=ui->mdpConf_compte->text().toLatin1();
    QString rfid=ui->rfid_compte->text();

    if(!ui->emailU_compte->hasAcceptableInput())
    {
        QMessageBox::critical(nullptr,QObject::tr("OK"),
                QObject::tr("Email invalide \n"
                            "Click cancel to exit."),QMessageBox::Cancel);
        return;
    }

    if(mdp==mdp_conf){
        QCryptographicHash cryptoHashSHA256(QCryptographicHash::Sha256);
        cryptoHashSHA256.addData(mdp);
        QString mdp_hash=cryptoHashSHA256.result().toHex().data();
        comptes c(type,nomUtilisateur,email,mdp_hash,rfid);
        bool test=c.ajouter_compte();
        if(test)
        {
            QMessageBox::information(nullptr,QObject::tr("OK"),
                    QObject::tr("Création de compte effectuée \n"
                                "Click cancel to exit."),QMessageBox::Cancel);

            ui->comboBox_type->setCurrentText("Admin");
            ui->nomU_compte->clear();
            ui->emailU_compte->clear();
            ui->mdpU_compte->clear();
            ui->mdpConf_compte->clear();
            ui->rfid_compte->clear();

        }
        else{
            QMessageBox::critical(nullptr,QObject::tr("OK"),
                    QObject::tr("Création de compte non effectuée \n"
                                "Click cancel to exit."),QMessageBox::Cancel);
        }
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("OK"),
                QObject::tr("Mots de passes diférents \n"
                            "Click cancel to exit."),QMessageBox::Cancel);
    }

}

void MainWindow::on_refresh_users_clicked()
{
    ui->tab_users->setModel(cmpt.afficher_compte());
    ui->affichage_type->clear();
    ui->affichage_nomU->clear();
    ui->affichage_emailU->clear();
    ui->affichage_mdpU->clear();
    ui->affichage_rfid->clear();
}

void MainWindow::on_tab_users_activated(const QModelIndex &index)
{
    QString nomU=ui->tab_users->model()->data(index).toString();

    QSqlQuery query;
    query.prepare("select * from comptes where nomutilisateur=:nomutilisateur");
    query.bindValue(":nomutilisateur",nomU);
    if(query.exec())
    {
        while(query.next())
        {
            ui->affichage_type->setText(query.value(0).toString());
            ui->affichage_nomU->setText(query.value(1).toString());
            ui->affichage_emailU->setText(query.value(2).toString());
            ui->affichage_mdpU->setText(query.value(3).toString());
            ui->affichage_rfid->setText(query.value(4).toString());
        }
    }
}

void MainWindow::on_modifierU_clicked()
{
    QString nomU=ui->affichage_nomU->text();
    QString emailU=ui->affichage_emailU->text();
    QByteArray mdpU=ui->affichage_mdpU->text().toLatin1();
    QString rfid=ui->affichage_rfid->text();
    QCryptographicHash cryptoHashSHA256(QCryptographicHash::Sha256);
    cryptoHashSHA256.addData(mdpU);
    QString mdp_hash=cryptoHashSHA256.result().toHex().data();

    if(!ui->affichage_emailU->hasAcceptableInput())
    {
        QMessageBox::critical(nullptr,QObject::tr("OK"),
                QObject::tr("Email invalide \n"
                            "Click cancel to exit."),QMessageBox::Cancel);
        return;
    }

    comptes c;
    bool test=c.modifier_compte(nomU,emailU,mdp_hash,rfid);
    if(test)
    {
        ui->tab_users->setModel(cmpt.afficher_compte());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("Modification du compte effectuée \n"
                            "Click cancel to exit."),QMessageBox::Cancel);

    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("OK"),
                QObject::tr("Modification du compte non effectuée \n"
                            "Click cancel to exit."),QMessageBox::Cancel);
    }

}


void MainWindow::on_supprimerU_clicked()
{
    QString nomU=ui->affichage_nomU->text();
    comptes c;
    bool test=c.supprimer_compte(nomU);
    if(test)
    {
        ui->tab_users->setModel(cmpt.afficher_compte());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("Suppression du compte effectuée \n"
                            "Click cancel to exit."),QMessageBox::Cancel);

        ui->affichage_type->clear();
        ui->affichage_nomU->clear();
        ui->affichage_emailU->clear();
        ui->affichage_mdpU->clear();

    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("OK"),
                QObject::tr("Suppression du compte non effectuée \n"
                            "Click cancel to exit."),QMessageBox::Cancel);
    }

}


void MainWindow::on_connexion_clicked()
{
    accueil a;
    employe e;
    QString nomU=ui->nomU_connexion->text();
    QByteArray mdpU=ui->mdpU_connexion->text().toLatin1();
    QCryptographicHash cryptoHashSHA256(QCryptographicHash::Sha256);
    cryptoHashSHA256.addData(mdpU);
    QString mdp_hash=cryptoHashSHA256.result().toHex().data();
    comptes c;
    QString type=c.afficher_type(nomU);
    int test=c.SeConnecter(nomU,mdp_hash);
    if(test==1)
    {
        QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("Connexion effectuée \n"
                            "Click cancel to exit."),QMessageBox::Cancel);
        ui->nomU_connexion->clear();
        ui->mdpU_connexion->clear();

        hide();
        a.setData(nomU,type);
        a.setModal(true);
        a.exec();
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("OK"),
                QObject::tr("Nom d'utilisateur ou mot de passe incorrect \n"
                            "Click cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_confirmer_reset_clicked()
{
    comptes c;
    int verif_mdp;
    bool modif_mdp;
    QString nomU=ui->nomU_reset->text();

    QByteArray mdp_old=ui->mdpU_old->text().toLatin1();

    QByteArray mdpU_1=ui->mdpU_new1->text().toLatin1();
    QByteArray mdpU_2=ui->mdpU_new2->text().toLatin1();

    QCryptographicHash cryptoHashSHA256(QCryptographicHash::Sha256);
    cryptoHashSHA256.addData(mdp_old);
    QString mdp_hash=cryptoHashSHA256.result().toHex().data();

    verif_mdp=c.verif_mdp(nomU,mdp_hash);

    if(verif_mdp==1){
        if(mdpU_1==mdpU_2){
            QCryptographicHash cryptoHashSHA256(QCryptographicHash::Sha256);
            cryptoHashSHA256.addData(mdpU_1);
            QString mdp_hash_new=cryptoHashSHA256.result().toHex().data();
            modif_mdp=c.reset_mdp(nomU,mdp_hash_new);
            if(modif_mdp){
                QMessageBox::information(nullptr,QObject::tr("OK"),
                        QObject::tr("Mot de passe réinitialisé \n"
                                    "Click cancel to exit."),QMessageBox::Cancel);

                ui->nomU_reset->clear();
                ui->mdpU_old->clear();
                ui->mdpU_new1->clear();
                ui->mdpU_new2->clear();
            }
        }
        else{
            QMessageBox::critical(nullptr,QObject::tr("OK"),
                    QObject::tr("Mots de passes différents \n"
                                "Click cancel to exit."),QMessageBox::Cancel);
        }
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("OK"),
                QObject::tr("Nom d'utilisateur ou mot de passe incorrect \n"
                            "Click cancel to exit."),QMessageBox::Cancel);

    }
}

void MainWindow::on_sauvegarder_mdp_clicked()
{   comptes c;
    QString nomU=ui->nomU_connexion->text();
    QString rfid=c.afficher_RFID(nomU);
    if(A.write_to_arduino(rfid.toLatin1()))
    {
        if( A.write_to_arduino("b"))
        {
           if(A.write_to_arduino(ui->mdpU_connexion->text().toLatin1()))
           {
               QMessageBox::information(nullptr,QObject::tr("OK"),
                       QObject::tr("Sauvegarde avec succés \n"
                                   "Click cancel to exit."),QMessageBox::Cancel);
           }
        }

    }
}

void MainWindow::on_afficher_mdp_clicked()
{
    comptes c;
    QString nomU=ui->nomU_connexion->text();
    QString rfid=c.afficher_RFID(nomU);
    qDebug()<<"rfid : "<<rfid;
    if(A.write_to_arduino(rfid.toLatin1()))
    {
        if( A.write_to_arduino("a"))
        {
            data=A.read_from_arduino();
            qDebug()<<"data : "<<data;
            ui->mdpU_connexion->setText(data);
        }
    }
}
