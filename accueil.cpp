#include "accueil.h"
#include "ui_accueil.h"
#include "employe.h"
#include "gerer_commande.h"
#include "materiaux.h"
#include "livraison.h"
#include "client.h"
#include "produitmain.h"

accueil::accueil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accueil)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
}

accueil::~accueil()
{
    delete ui;
}
void accueil::setData(QString nomU,QString typeU)
{
    role=typeU;
    nom_u=nomU;
    if(typeU=="Employe")
    {
        ui->pushButton_employes->hide();
        ui->label_2->setText("Welcome "+nomU);
    }
    else{
        ui->label_2->setText("Welcome "+nomU);
    }
}

void accueil::on_pushButton_employes_clicked()
{
    employe e;
    e.role=role;
    e.nom_u=nom_u;
    hide();
    e.setModal(true);
    e.exec();

}

void accueil::on_pushButton_commandes_clicked()
{
    gerer_commande g_c;
    g_c.role=role;
    g_c.nom_u=nom_u;
    hide();
    g_c.setModal(true);
    g_c.exec();
}

void accueil::on_pushButton_materiaux_clicked()
{
    materiaux mat;
    mat.role=role;
    mat.nom_u=nom_u;
    hide();
    mat.setModal(true);
    mat.exec();
}


void accueil::on_pushButton_livraisons_clicked()
{
    livraison l;
    l.role=role;
    l.nom_u=nom_u;
    hide();
    l.setModal(true);
    l.exec();
}

void accueil::on_pushButton_clients_clicked()
{
    client cl;
    cl.role=role;
    cl.nom_u=nom_u;
    hide();
    cl.setModal(true);
    cl.exec();
}

void accueil::on_pushButton_produits_clicked()
{
    produitmain pr;
    pr.role=role;
    pr.nom_u=nom_u;
    hide();
    pr.setModal(true);
    pr.exec();
}
