#include "gerer_commande.h"
#include "ui_gerer_commande.h"
#include "commande.h"
#include "scenario_02.h"
#include "accueil.h"
gerer_commande::gerer_commande(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gerer_commande)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);
    com.auto_delete_validated();
    ui->tableView->setModel(com.afficher());
    ui->tableView_h_Ajouter->setModel(com.afficher("ajouter"));
    ui->tableView_h_modifier->setModel(com.afficher("modifier"));
    ui->tableView_h_supprimer->setModel(com.afficher("supprimer"));
    selected="";

}

gerer_commande::~gerer_commande()
{
    delete ui;
}

void gerer_commande::on_pushButton_historique_clicked()
{
    ui->tabWidget_commande->setCurrentWidget(ui->tab_historique);
    ui->tableView_h_Ajouter->setModel(com.afficher("ajouter"));
    ui->tableView_h_modifier->setModel(com.afficher("modifier"));
    ui->tableView_h_supprimer->setModel(com.afficher("supprimer"));
}

void gerer_commande::on_pushButton_Ajouter_clicked()
{
    bool verif=false;
    int cin = ui->lineEdit_idClient->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString type = ui->lineEdit_type->text();
    QDateTime date = QDateTime::currentDateTime();
    int nb = ui->spinBox_nbPage->text().toInt();
    int etat = ui->lineEdit_etat->text().toInt();
    float prix = ui->doubleSpinBox_prix->text().toFloat();
    if(cin>=0 && cin<=99999999) verif=true;
    std::string length = std::to_string(cin);
    int l = length.length();
    qDebug() << l;
    if((etat!=0 && etat!=1))
    {
        QMessageBox::information(nullptr, QObject::tr("Manquer des informations"),
                    QObject::tr("Veuillez saisir (0 ou 1) dans Etat.\n"
                                "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
    }
    else if (l<8 || !verif)
    {
        QMessageBox::information(nullptr, QObject::tr("Manquer des informations"),
                    QObject::tr("Veuillez Insérez 8 chiffres dans ID CLient.\n"
                                "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
    }
    else if(nom=="")
    {
        QMessageBox::information(nullptr, QObject::tr("Manquer des informations"),
                    QObject::tr("Veuillez Insérez Le nom de Commande.\n"
                                "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
    }
    else if(type=="")
    {
        QMessageBox::information(nullptr, QObject::tr("Manquer des informations"),
                    QObject::tr("Veuillez Insérez Le Type de Commande.\n"
                                "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
    }
    else if(!nb)
    {
        QMessageBox::information(nullptr, QObject::tr("Manquer des informations"),
                    QObject::tr("Veuillez Insérez Le Nombre des Pages de Commande.\n"
                                "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
    }
    else if(prix<=0.00f)
    {
        QMessageBox::information(nullptr, QObject::tr("Manquer des informations"),
                    QObject::tr("Veuillez Insérez Le Prix de Commande.\n"
                                "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
    }
    else
    {
        Commande c(cin,nom,type,date,nb,etat,prix);
        bool test = c.ajouter();
        if(test)
        {
            //Ajout de l'historique 'Recently added':
            QString act="ajouter";
            QDateTime d=c.getDate_commande();
            QString id_c=QString::number(c.getid_client());
            QSqlQuery *m = c.search_data(d,id_c);
            if(m->isSelect())
            {
                if(m->next())
                {
                   Commande h(m->value(0).toInt(),cin,nom,type,date,nb,etat,prix,act);
                    bool test_h= h.ajouter_historique();
                    if(test_h)
                    {
                        qDebug() << "True : Historique added.";
                    }
                    else
                        qDebug() << "False : Historique not added.";
                }
            }
            //--------------------------------------|
            QMessageBox::information(nullptr, QObject::tr("Succès"),
                        QObject::tr("inséré avec succès.\n"
                                    "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
            ui->tableView->setModel(com.afficher());
            ui->tabWidget_commande->setCurrentWidget(ui->tab_liste);
            selected="";
            ui->lineEdit_idClient->clear();
            ui->lineEdit_nom->clear();
            ui->lineEdit_type->clear();
            ui->spinBox_nbPage->clear();
            ui->lineEdit_etat->clear();
            ui->doubleSpinBox_prix->clear();

        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Échoué"),
                        QObject::tr("ERREUR : Échec de l'insertion.\n"
                                    "Cliquez sur Annuler pour Quitter."), QMessageBox::Cancel);
        }
    }
}

void gerer_commande::on_pushButton_refresh_clicked()
{
    ui->tableView->setModel(com.afficher());
    ui->radioButton_id->setChecked(false);
    ui->radioButton_date->setChecked(false);
    ui->radioButton_croissant->setChecked(false);
    ui->radioButton_decroissant->setChecked(false);
    ui->radioButton_5->setChecked(false);
}

void gerer_commande::on_tableView_activated(const QModelIndex &index)
{
   selected=ui->tableView->model()->data(index).toString();
   int i = ui->tableView->selectionModel()->currentIndex().row();
   qDebug()<< selected;
   qDebug()<< i;

}

void gerer_commande::on_pushButton_supprimer_clicked()
{
    if(selected!="")
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::critical(nullptr, QObject::tr("Supprimer"),
                    QObject::tr("Voulez-vous vraiment supprimer ?\n"
                                "Cliquez sur 'Yes' pour Supprimer."), QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {
            //Ajout de l'historique 'Recently Deleted':
             QSqlQuery * m = com.search_data(selected);
             if(m->isSelect())
             {
                 while(m->next())
                 {
                     QString act ="supprimer";
                     int id = m->value(0).toInt();
                     int cin = m->value(1).toInt();
                     QString nom = m->value(2).toString();
                     QString type = m->value(3).toString();
                     QDateTime date = m->value(4).toDateTime();
                     int nb = m->value(5).toInt();
                     int etat = m->value(6).toInt();
                     float prix = m->value(7).toFloat();
                     Commande h(id,cin,nom,type,date,nb,etat,prix,act);
                     bool test = h.ajouter_historique();
                     if(test)
                     {
                         qDebug()<< "True : Deleted History stored";
                     }
                     else
                        qDebug()<< "False : Deleted History not stored";
                 }
             }
            //----------------------------------------|
            bool test=com.supprimer(selected);
            if(test)
            {
                ui->tableView->setModel(com.afficher());
                QMessageBox::information(nullptr, QObject::tr("Succès"),
                            QObject::tr("Supprimé avec succès.\n"
                                        "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
                selected="";
            }
            else {
                QMessageBox::critical(nullptr, QObject::tr("Échoué"),
                            QObject::tr("ERREUR : La suppression a échoué. sélectionnez l'identifiant ou Cin Or (aucune colonne n'est sélectionnée ou la ligne n'existe pas)\n"
                                        "Cliquez sur Annuler pour Quitter."), QMessageBox::Cancel);
                selected="";
            }
        }
    }
    else
    {
        QMessageBox::information(nullptr, QObject::tr("Sélectionner"),
                    QObject::tr("Veuillez sélectionner l'Id ou le Cin du client (Double clic).\n"
                                "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
    }
}

void gerer_commande::on_pushButton_modifier_clicked()
{
    if(selected!="")
    {
        QSqlQuery * m = com.search_data(selected);
        if(m->isSelect())
        {
            ui->tabWidget_commande->setCurrentWidget(ui->tab_modifier);
            if(m->next())
            {
                selected=m->value(0).toString();
                ui->lineEdit_idClient_2->setText(m->value(1).toString());
                ui->lineEdit_nom_2->setText(m->value(2).toString());
                ui->lineEdit_type_2->setText(m->value(3).toString());
                ui->spinBox_nbPage_2->setValue(m->value(5).toInt());
                ui->lineEdit_etat_2->setText(m->value(6).toString());
                ui->doubleSpinBox_prix_2->setValue(m->value(7).toDouble());
            }
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Échoué"),
                        QObject::tr("ERREUR : lors de la sélection des données\n"
                                    "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        }
    }
    else
    {
        QMessageBox::information(nullptr, QObject::tr("Sélectionner"),
                    QObject::tr("Veuillez sélectionner l'Id ou le Cin du client (Double clic).\n"
                                "Cliquez sur OK pour quitter."), QMessageBox::Ok);
    }
}

void gerer_commande::on_pushButton_modifier_2_clicked()
{
    if(selected!="")
    {
        bool verif=false;
        int cin = ui->lineEdit_idClient_2->text().toInt();
        QString nom = ui->lineEdit_nom_2->text();
        QString type = ui->lineEdit_type_2->text();
        QDateTime date = QDateTime::currentDateTime();
        int nb = ui->spinBox_nbPage_2->text().toInt();
        int etat = ui->lineEdit_etat_2->text().toInt();
        float prix = ui->doubleSpinBox_prix_2->text().toFloat();
        if(cin>=0 && cin<=99999999) verif=true;
        std::string length = std::to_string(cin);
        int l = length.length();
        if((etat!=0 && etat!=1))
        {
            QMessageBox::information(nullptr, QObject::tr("Manquer des informations"),
                        QObject::tr("Veuillez saisir (0 ou 1) dans Etat.\n"
                                    "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
        }
        else if (l<8 || !verif)
        {
            QMessageBox::information(nullptr, QObject::tr("Manquer des informations"),
                        QObject::tr("Veuillez Insérez 8 chiffres dans ID CLient.\n"
                                    "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
        }
        else if(nom=="")
        {
            QMessageBox::information(nullptr, QObject::tr("Manquer des informations"),
                        QObject::tr("Veuillez Insérez Le nom de Commande.\n"
                                    "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
        }
        else if(type=="")
        {
            QMessageBox::information(nullptr, QObject::tr("Manquer des informations"),
                        QObject::tr("Veuillez Insérez Le Type de Commande.\n"
                                    "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
        }
        else if(!nb)
        {
            QMessageBox::information(nullptr, QObject::tr("Manquer des informations"),
                        QObject::tr("Veuillez Insérez Le Nombre des Pages de Commande.\n"
                                    "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
        }
        else if(prix<=0.00f)
        {
            QMessageBox::information(nullptr, QObject::tr("Manquer des informations"),
                        QObject::tr("Veuillez Insérez Le Prix de Commande.\n"
                                    "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
        }
        else
        {
            Commande c(cin,nom,type,date,nb,etat,prix);
            bool test = c.modifier(selected);
            if(test)
            {
                //Ajout de l'historique 'Recently Modified':
                         QString act ="modifier";
                         int id_c = selected.toInt();
                         Commande h(id_c,cin,nom,type,date,nb,etat,prix,act);
                         bool test_h = h.ajouter_historique();
                         if(test_h)
                         {
                             qDebug()<< "True : Modified History stored";
                         }
                         else
                            qDebug()<< "False : Modified History not stored";
                //----------------------------------------|
                QMessageBox::information(nullptr, QObject::tr("Succès"),
                            QObject::tr("Mise à jour réussie .\n"
                                        "Cliquez sur OK pour quitter."), QMessageBox::Ok);
                ui->tableView->setModel(com.afficher());
                ui->tabWidget_commande->setCurrentWidget(ui->tab_liste);
                selected="";
                ui->lineEdit_idClient_2->clear();
                ui->lineEdit_nom_2->clear();
                ui->lineEdit_type_2->clear();
                ui->spinBox_nbPage_2->clear();
                ui->lineEdit_etat_2->clear();
                ui->doubleSpinBox_prix_2->clear();
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Échoué"),
                            QObject::tr("ERREUR : Échec de la mise à jour.\n"
                                        "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
            }
        }
    }
    else
    {
        QMessageBox::information(nullptr, QObject::tr("Sélectionner"),
                    QObject::tr("Veuillez sélectionner l'ID ou le Cin du client (double clic) dans la liste.\n"
                                "Cliquez sur OK pour quitter."), QMessageBox::Ok);
         ui->tabWidget_commande->setCurrentWidget(ui->tab_liste);
         selected="";
    }
}

void gerer_commande::on_pushButton_annuler_clicked()
{
    ui->tableView->setModel(com.afficher());
    ui->tabWidget_commande->setCurrentWidget(ui->tab_liste);
    selected="";
    ui->lineEdit_idClient_2->clear();
    ui->lineEdit_nom_2->clear();
    ui->lineEdit_type_2->clear();
    ui->spinBox_nbPage_2->clear();
    ui->lineEdit_etat_2->clear();
    ui->doubleSpinBox_prix_2->clear();
}



void gerer_commande::on_radioButton_id_clicked()
{
    ui->tableView->setModel(com.tri_id());
    selected="";
}

void gerer_commande::on_radioButton_date_clicked()
{
    ui->tableView->setModel(com.tri_date());
    selected="";
}

void gerer_commande::on_radioButton_croissant_clicked()
{
    ui->tableView->setModel(com.tri_AZ());
    selected="";
}

void gerer_commande::on_radioButton_decroissant_clicked()
{
    ui->tableView->setModel(com.tri_ZA());
    selected="";
}

void gerer_commande::on_radioButton_5_clicked()
{
    ui->tableView->setModel(com.afficher());
    selected="";
}

void gerer_commande::on_lineEdit_rechercher_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM Commande WHERE id_commande LIKE '"+arg1+"%' or cin_client LIKE '"+arg1+"%' or nom_commande LIKE '"+arg1+"%' or type_commande LIKE '"+arg1+"%' or date_commande LIKE '"+arg1+"%' or nb_page LIKE '"+arg1+"%' or prix_commande LIKE '"+arg1+"%'");
     query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->tableView->setModel(model);
     }
     else {
         QMessageBox::information(nullptr, QObject::tr("Rechercher"),
                         QObject::tr("Aucun résultat trouvé !.\n"
                                     "Cliquez sur OK pour quitter."), QMessageBox::Ok);
         ui->lineEdit_rechercher->clear();
         delete(model);
         delete(query);
        }
}
//--------------------------------------------------------------- Trier Historique :
//Default radio Button Historique ajouter :
void gerer_commande::on_radioButton_6_clicked()
{
    ui->tableView_h_Ajouter->setModel(com.afficher("ajouter"));
}
//Default radio Button Historique modifier :
void gerer_commande::on_radioButton_7_clicked()
{
    ui->tableView_h_modifier->setModel(com.afficher("modifier"));
}
//Default radio Button Historique Supprimer :
void gerer_commande::on_radioButton_8_clicked()
{
     ui->tableView_h_supprimer->setModel(com.afficher("supprimer"));
}
//-------------------------------------------------------------
// Id radio Button Historique ajouter :
void gerer_commande::on_radioButton_clicked()
{
     ui->tableView_h_Ajouter->setModel(com.tri_id("ajouter"));
}
// Id radio Button Historique modifier :
void gerer_commande::on_radioButton_9_clicked()
{
    ui->tableView_h_modifier->setModel(com.tri_id("modifier"));
}
// Id radio Button Historique Supprimer :
void gerer_commande::on_radioButton_13_clicked()
{
    ui->tableView_h_supprimer->setModel(com.tri_id("supprimer"));
}
//-------------------------------------------------------------
// date radio Button Historique ajouter :
void gerer_commande::on_radioButton_2_clicked()
{
    ui->tableView_h_Ajouter->setModel(com.tri_date("ajouter"));
}
// date radio Button Historique modifier :
void gerer_commande::on_radioButton_10_clicked()
{
    ui->tableView_h_modifier->setModel(com.tri_date("modifier"));
}
// date radio Button Historique Supprimer:
void gerer_commande::on_radioButton_14_clicked()
{
   ui->tableView_h_supprimer->setModel(com.tri_date("supprimer"));
}
//---------------------------------------------------------------
// AZ radio Button Historique ajouter :
void gerer_commande::on_radioButton_3_clicked()
{
    ui->tableView_h_Ajouter->setModel(com.tri_AZ("ajouter"));
}
// AZ radio Button Historique modifier :
void gerer_commande::on_radioButton_11_clicked()
{
    ui->tableView_h_modifier->setModel(com.tri_AZ("modifier"));
}
// AZ radio Button Historique supprimer :
void gerer_commande::on_radioButton_15_clicked()
{
    ui->tableView_h_supprimer->setModel(com.tri_AZ("supprimer"));
}
//----------------------------------------------------------------
// ZA radio Button Historique ajouter :
void gerer_commande::on_radioButton_4_clicked()
{
    ui->tableView_h_Ajouter->setModel(com.tri_ZA("ajouter"));
}
// ZA radio Button Historique modifier :
void gerer_commande::on_radioButton_12_clicked()
{
    ui->tableView_h_modifier->setModel(com.tri_ZA("modifier"));
}
// ZA radio Button Historique Supprimer :
void gerer_commande::on_radioButton_16_clicked()
{
    ui->tableView_h_supprimer->setModel(com.tri_ZA("supprimer"));
}
//------------------------------------------------------------------------------ Fin de tri Historique
//---------------------------------------------RECHERCHE bar Historique :
// Rechercher Dans Historique Ajouter :
void gerer_commande::on_lineEdit_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM historique_commande WHERE (id_commande LIKE '"+arg1+"%' or cin_client LIKE '"+arg1+"%' or nom_commande LIKE '"+arg1+"%' or type_commande LIKE '"+arg1+"%' or date_commande LIKE '"+arg1+"%' or nb_page LIKE '"+arg1+"%' or prix_commande LIKE '"+arg1+"%') AND activity=:activity");
    query->bindValue(":activity","ajouter");
    query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->tableView_h_Ajouter->setModel(model);
     }
     else {
         QMessageBox::information(nullptr, QObject::tr("Rechercher"),
                         QObject::tr("Aucun résultat trouvé !.\n"
                                     "Cliquez sur OK pour quitter."), QMessageBox::Ok);
         ui->lineEdit->clear();
         delete(model);
         delete(query);
        }
}
// Rechercher Dans Historique Modifier :
void gerer_commande::on_lineEdit_3_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM historique_commande WHERE (id_commande LIKE '"+arg1+"%' or cin_client LIKE '"+arg1+"%' or nom_commande LIKE '"+arg1+"%' or type_commande LIKE '"+arg1+"%' or date_commande LIKE '"+arg1+"%' or nb_page LIKE '"+arg1+"%' or prix_commande LIKE '"+arg1+"%') AND activity=:activity");
    query->bindValue(":activity","modifier");
    query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->tableView_h_modifier->setModel(model);
     }
     else {
         QMessageBox::information(nullptr, QObject::tr("Rechercher"),
                         QObject::tr("Aucun résultat trouvé !.\n"
                                     "Cliquez sur OK pour quitter."), QMessageBox::Ok);
         ui->lineEdit_3->clear();
         delete(model);
         delete(query);
        }
}
// Rechercher Dans Historique Supprimer :
void gerer_commande::on_lineEdit_4_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM historique_commande WHERE (id_commande LIKE '"+arg1+"%' or cin_client LIKE '"+arg1+"%' or nom_commande LIKE '"+arg1+"%' or type_commande LIKE '"+arg1+"%' or date_commande LIKE '"+arg1+"%' or nb_page LIKE '"+arg1+"%' or prix_commande LIKE '"+arg1+"%') AND activity=:activity");
    query->bindValue(":activity","supprimer");
    query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->tableView_h_supprimer->setModel(model);
     }
     else {
         QMessageBox::information(nullptr, QObject::tr("Rechercher"),
                         QObject::tr("Aucun résultat trouvé !.\n"
                                     "Cliquez sur OK pour quitter."), QMessageBox::Ok);
         ui->lineEdit_4->clear();
         delete(model);
         delete(query);
        }
}
//--------------------------------------------------------------------------------
//Refresh les Tableaux d'Historique :
void gerer_commande::on_tabWidget_commande_tabBarClicked(int index)
{
    if(index == 3)
    {
        ui->tableView_h_Ajouter->setModel(com.afficher("ajouter"));
        ui->tableView_h_modifier->setModel(com.afficher("modifier"));
        ui->tableView_h_supprimer->setModel(com.afficher("supprimer"));
    }
}
//-------------------------------------------------------------------------
//Button Supprimer_Tout Historique Ajouter:
void gerer_commande::on_pushButton_supprimerH_a_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::critical(nullptr, QObject::tr("Supprimer Tout"),
                QObject::tr(" Voulez-vous vraiment supprimer l'historique.\n"
                            "Cliquez sur 'Yes' pour Supprimer."), QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        bool test=com.supprimer_h("ajouter");
        if(test)
        {
            ui->tableView_h_Ajouter->setModel(com.afficher("ajouter"));
            QMessageBox::information(nullptr, QObject::tr("Succès"),
                        QObject::tr("Supprimé avec succès.\n"
                                    "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("Échoué"),
                        QObject::tr("ERREUR : La suppression a échoué.\n"
                                    "Cliquez sur Annuler pour Quitter."), QMessageBox::Cancel);
        }
    }
}
//Button Supprimer_Tout Historique Modifier:
void gerer_commande::on_pushButton_supprimer_H_m_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::critical(nullptr, QObject::tr("Supprimer Tout"),
                QObject::tr(" Voulez-vous vraiment supprimer l'historique.\n"
                            "Cliquez sur 'Yes' pour Supprimer."), QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        bool test=com.supprimer_h("modifier");
        if(test)
        {
            ui->tableView_h_modifier->setModel(com.afficher("modifier"));
            QMessageBox::information(nullptr, QObject::tr("Succès"),
                        QObject::tr("Supprimé avec succès.\n"
                                    "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("Échoué"),
                        QObject::tr("ERREUR : La suppression a échoué.\n"
                                    "Cliquez sur Annuler pour Quitter."), QMessageBox::Cancel);
        }
    }
}
//Button Supprimer_Tout Historique Supprimer:
void gerer_commande::on_pushButton_supprimer_H_s_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::critical(nullptr, QObject::tr("Supprimer Tout"),
                QObject::tr(" Voulez-vous vraiment supprimer l'historique.\n"
                            "Cliquez sur 'Yes' pour Supprimer."), QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        bool test=com.supprimer_h("supprimer");
        if(test)
        {
            ui->tableView_h_supprimer->setModel(com.afficher("supprimer"));
            QMessageBox::information(nullptr, QObject::tr("Succès"),
                        QObject::tr("Supprimé avec succès.\n"
                                    "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("Échoué"),
                        QObject::tr("ERREUR : La suppression a échoué.\n"
                                    "Cliquez sur Annuler pour Quitter."), QMessageBox::Cancel);
        }
    }
}
// les Buttons Refresh des Tableaux Historique:
void gerer_commande::on_pushButton_refresh_h_A_clicked()
{
     ui->tableView_h_supprimer->setModel(com.afficher("ajouter"));
}

void gerer_commande::on_pushButton_refresh_h_M_clicked()
{
     ui->tableView_h_supprimer->setModel(com.afficher("modifier"));
}

void gerer_commande::on_pushButton_refresh_h_S_clicked()
{
     ui->tableView_h_supprimer->setModel(com.afficher("supprimer"));
}

void gerer_commande::on_pushButton_exportPdf_clicked()
{
    QDateTime d= QDateTime::currentDateTime();
    QString date=d.toString("dd-MM-yyyy hh:mm:ss");
    QString strStream;
    QTextStream out(&strStream);
    if(selected !="")
    {
        QSqlQuery * m = com.search_data(selected);
        if(m->isSelect())
        {
            if(m->next())
            {
                out <<  "<html>\n"
                    "<head>\n"
                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    <<  QString("<title>%1</title>\n").arg("strTitle")
                    <<  "</head>\n"
                    "<body bgcolor=#ffffff link=#5000A0>\n"

                    "<img src="":/picture/App_LOGO.ico"" alt=""logo"" height=""90"" width=""90"" align=""right"">"
                    "<h2 style=""color:orange"" align=""left""><b>-Facture De Commande : </b></h2><br></br>\n";
                out << "<br></br><br></br><hr><br></br><br></br>";
                out << "<table>";
                       out <<"<tr>"
                          " <td>ID de Commande :</td>"
                         << QString("<td>%1</td>").arg(m->value(0).toString()) <<"</tr>";
                       out <<"<tr>"
                          " <td>Cin de Client :</td>"
                         << QString("<td>%1</td>").arg(m->value(1).toString()) <<"</tr>";
                       out <<"<tr>"
                          " <td>Nom de Commande :</td>"
                         << QString("<td>%1</td>").arg(m->value(2).toString()) <<"</tr>";
                       out <<"<tr>"
                          " <td>Type de Commande :</td>"
                         << QString("<td>%1</td>").arg(m->value(3).toString()) <<"</tr>";
                       out <<"<tr>"
                          " <td>Date de Commande :</td>"
                         << QString("<td>%1</td>").arg(m->value(4).toString()) <<"</tr>";
                       out <<"<tr>"
                          " <td>Nombre des Pages :</td>"
                         << QString("<td>%1</td>").arg(m->value(5).toString()) <<"</tr>";
                       out <<"<tr>"
                          " <td>Prix de Commande :</td>"
                         << QString("<td bgcolor=""orange"">%1 .Dt</td>").arg(m->value(7).toString()) <<"</tr>";
                   out << "</table>";
                out << "<br></br><br></br><br></br><hr><br></br>";
                out << QString("<br></br><h4 align=""left"">%1</h4>").arg(date);
                out <<   "</body>\n"
                         "</html>\n";
            }
        }
    }
    else
    {
        const int rowCount = ui->tableView->model()->rowCount();
        const int columnCount = ui->tableView->model()->columnCount();

        out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg("strTitle")
            <<  "</head>\n"
            "<body bgcolor=#ffffff link=#5000A0>\n"

            "<img src="":/picture/App_LOGO.ico"" alt=""logo"" height=""90"" width=""90"">"
            "<center> <h2 style=""color:orange"">-Table Des Commandes-</h2><br></br><br></br><br></br><table border=0.5 cellspacing=1 cellpadding=3>\n";

        // headers
        out << "<thead><tr bgcolor=""#333""><th><font color=""orange"">Ligne</font></th>";
        for (int column = 0; column < columnCount; column++)
            if (!ui->tableView->isColumnHidden(column))
                out << QString("<th><font color=""orange"">%1</font></th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
        out << "</tr></thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++)
        {
            out << "<tr><td bgcolor=""lightgray"">" << row + 1 << "</td>";
            for (int column = 0; column < columnCount; column++)
            {
                if (!ui->tableView->isColumnHidden(column))
                {
                    QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                    out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                }
            }
            out << "</tr>\n";
        }
        out <<  "</table> </center>\n";
                out << QString("<br></br><h4 align=""left"">%1</h4>").arg(date);
           out<< "</body>\n"
            "</html>\n";
    }
    QString fileName = QFileDialog::getSaveFileName((QWidget * )0, "Sauvegarder en PDF", QString(), "*.pdf");
    if(fileName!="")
    {
        if (QFileInfo(fileName).suffix().isEmpty())
        {
            fileName.append(".pdf");
        }

        QPrinter printer (QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QTextDocument doc;
        doc.setHtml(strStream);
        doc.setPageSize(printer.pageRect().size()); //This is necessary if you want to hide the page number
        doc.print(&printer);
    }
}

void gerer_commande::on_pushButton_imprimer_clicked()
{
    QDateTime d= QDateTime::currentDateTime();
    QString date=d.toString("dd-MM-yyyy hh:mm:ss");
    QString strStream;
    QTextStream out(&strStream);
    if(selected !="")
    {
        QSqlQuery * m = com.search_data(selected);
        if(m->isSelect())
        {
            if(m->next())
            {
                out <<  "<html>\n"
                    "<head>\n"
                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    <<  QString("<title>%1</title>\n").arg("strTitle")
                    <<  "</head>\n"
                    "<body bgcolor=#ffffff link=#5000A0>\n"

                    "<img src="":/picture/App_LOGO.ico"" alt=""logo"" height=""90"" width=""90"" align=""right"">"
                    "<h2 style=""color:orange"" align=""left""><b>-Facture De Commande : </b></h2><br></br>\n";
                out << "<br></br><br></br><hr><br></br><br></br>";
                out << "<table>";
                       out <<"<tr>"
                          " <td>ID de Commande :</td>"
                         << QString("<td>%1</td>").arg(m->value(0).toString()) <<"</tr>";
                       out <<"<tr>"
                          " <td>Cin de Client :</td>"
                         << QString("<td>%1</td>").arg(m->value(1).toString()) <<"</tr>";
                       out <<"<tr>"
                          " <td>Nom de Commande :</td>"
                         << QString("<td>%1</td>").arg(m->value(2).toString()) <<"</tr>";
                       out <<"<tr>"
                          " <td>Type de Commande :</td>"
                         << QString("<td>%1</td>").arg(m->value(3).toString()) <<"</tr>";
                       out <<"<tr>"
                          " <td>Date de Commande :</td>"
                         << QString("<td>%1</td>").arg(m->value(4).toString()) <<"</tr>";
                       out <<"<tr>"
                          " <td>Nombre des Pages :</td>"
                         << QString("<td>%1</td>").arg(m->value(5).toString()) <<"</tr>";
                       out <<"<tr>"
                          " <td>Prix de Commande :</td>"
                         << QString("<td bgcolor=""orange"">%1 .Dt</td>").arg(m->value(7).toString()) <<"</tr>";
                   out << "</table>";
                out << "<br></br><br></br><br></br><hr><br></br>";
                out << QString("<br></br><h4 align=""left"">%1</h4>").arg(date);
                out <<   "</body>\n"
                         "</html>\n";
            }
        }
    }
    else
    {
        const int rowCount = ui->tableView->model()->rowCount();
        const int columnCount = ui->tableView->model()->columnCount();

        out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg("strTitle")
            <<  "</head>\n"
            "<body bgcolor=#ffffff link=#5000A0>\n"

            "<img src="":/picture/App_LOGO.ico"" alt=""logo"" height=""90"" width=""90"">"
            "<center> <h2 style=""color:orange"">-Table Des Commandes-</h2><br></br><br></br><br></br><table border=0.5 cellspacing=1 cellpadding=3>\n";

        // headers
        out << "<thead><tr bgcolor=""#333""><th><font color=""orange"">Ligne</font></th>";
        for (int column = 0; column < columnCount; column++)
            if (!ui->tableView->isColumnHidden(column))
                out << QString("<th><font color=""orange"">%1</font></th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
        out << "</tr></thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++)
        {
            out << "<tr><td bgcolor=""lightgray"">" << row + 1 << "</td>";
            for (int column = 0; column < columnCount; column++)
            {
                if (!ui->tableView->isColumnHidden(column))
                {
                    QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                    out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                }
            }
            out << "</tr>\n";
        }
        out <<  "</table> </center>\n";
        out << QString("<br></br><h4 align=""left"">%1</h4>").arg(date);
            out<<"</body>\n"
            "</html>\n";
    }
    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }
    delete(document);
}
//Export PDF : Historique :
void gerer_commande::on_pushButton_pdf_h_A_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_h_Ajouter->model()->rowCount();
    const int columnCount = ui->tableView_h_Ajouter->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("strTitle")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"

        "<img src="":/picture/App_LOGO.ico"" alt=""logo"" height=""90"" width=""90"">"
        "<center> <h2 style=""color:orange"">-Historique Des Commandes Recemment Ajoute-</h2><br></br><br></br><br></br><table border=0.5 cellspacing=1 cellpadding=3>\n";

    // headers
    out << "<thead><tr bgcolor=""#333""><th><font color=""orange"">Ligne</font></th>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView_h_Ajouter->isColumnHidden(column))
            out << QString("<th><font color=""orange"">%1</font></th>").arg(ui->tableView_h_Ajouter->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr><td bgcolor=""lightgray"">" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableView_h_Ajouter->isColumnHidden(column))
            {
                QString data = ui->tableView_h_Ajouter->model()->data(ui->tableView_h_Ajouter->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table> </center>\n"
        "</body>\n"
        "</html>\n";

    QString fileName = QFileDialog::getSaveFileName((QWidget * )0, "Sauvegarder en PDF", QString(), "*.pdf");
    if(fileName!="")
    {
        if (QFileInfo(fileName).suffix().isEmpty())
        {
            fileName.append(".pdf");
        }

        QPrinter printer (QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QTextDocument doc;
        doc.setHtml(strStream);
        doc.setPageSize(printer.pageRect().size()); //This is necessary if you want to hide the page number
        doc.print(&printer);
    }
}

void gerer_commande::on_pushButton_pdf_h_M_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_h_modifier->model()->rowCount();
    const int columnCount = ui->tableView_h_modifier->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("strTitle")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"

        "<img src="":/picture/App_LOGO.ico"" alt=""logo"" height=""90"" width=""90"">"
        "<center> <h2 style=""color:orange"">-Historique Des Commandes Recemment Modifie-</h2><br></br><br></br><br></br><table border=0.5 cellspacing=1 cellpadding=3>\n";

    // headers
    out << "<thead><tr bgcolor=""#333""><th><font color=""orange"">Ligne</font></th>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView_h_modifier->isColumnHidden(column))
            out << QString("<th><font color=""orange"">%1</font></th>").arg(ui->tableView_h_modifier->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr><td bgcolor=""lightgray"">" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableView_h_modifier->isColumnHidden(column))
            {
                QString data = ui->tableView_h_modifier->model()->data(ui->tableView_h_modifier->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table> </center>\n"
        "</body>\n"
        "</html>\n";

    QString fileName = QFileDialog::getSaveFileName((QWidget * )0, "Sauvegarder en PDF", QString(), "*.pdf");
    if(fileName!="")
    {
        if (QFileInfo(fileName).suffix().isEmpty())
        {
            fileName.append(".pdf");
        }

        QPrinter printer (QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QTextDocument doc;
        doc.setHtml(strStream);
        doc.setPageSize(printer.pageRect().size()); //This is necessary if you want to hide the page number
        doc.print(&printer);
    }
}

void gerer_commande::on_pushButton_pdf_h_S_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_h_supprimer->model()->rowCount();
    const int columnCount = ui->tableView_h_supprimer->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("strTitle")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"

        "<img src="":/picture/App_LOGO.ico"" alt=""logo"" height=""90"" width=""90"">"
        "<center> <h2 style=""color:orange"">-Historique Des Commandes Recemment Supprime-</h2><br></br><br></br><br></br><table border=0.5 cellspacing=1 cellpadding=3>\n";

    // headers
    out << "<thead><tr bgcolor=""#333""><th><font color=""orange"">Ligne</font></th>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView_h_supprimer->isColumnHidden(column))
            out << QString("<th><font color=""orange"">%1</font></th>").arg(ui->tableView_h_supprimer->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr><td bgcolor=""lightgray"">" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableView_h_supprimer->isColumnHidden(column))
            {
                QString data = ui->tableView_h_supprimer->model()->data(ui->tableView_h_supprimer->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table> </center>\n"
        "</body>\n"
        "</html>\n";

    QString fileName = QFileDialog::getSaveFileName((QWidget * )0, "Sauvegarder en PDF", QString(), "*.pdf");
    if(fileName!="")
    {
        if (QFileInfo(fileName).suffix().isEmpty())
        {
            fileName.append(".pdf");
        }

        QPrinter printer (QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QTextDocument doc;
        doc.setHtml(strStream);
        doc.setPageSize(printer.pageRect().size()); //This is necessary if you want to hide the page number
        doc.print(&printer);
    }
}
// Imprimer Historique : --------------------------------------------------------------------------------

void gerer_commande::on_pushButton_imprimer_h_A_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_h_Ajouter->model()->rowCount();
    const int columnCount = ui->tableView_h_Ajouter->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("strTitle")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"

        "<img src="":/picture/App_LOGO.ico"" alt=""logo"" height=""90"" width=""90"">"
        "<center> <h2 style=""color:orange"">-Historique Des Commandes Recemment Ajoute-</h2><br></br><br></br><br></br><table border=0.5 cellspacing=1 cellpadding=3>\n";

    // headers
    out << "<thead><tr bgcolor=""#333""><th><font color=""orange"">Ligne</font></th>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView_h_Ajouter->isColumnHidden(column))
            out << QString("<th><font color=""orange"">%1</font></th>").arg(ui->tableView_h_Ajouter->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr><td bgcolor=""lightgray"">" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableView_h_Ajouter->isColumnHidden(column))
            {
                QString data = ui->tableView_h_Ajouter->model()->data(ui->tableView_h_Ajouter->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table> </center>\n"
        "</body>\n"
        "</html>\n";
    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete(document);

}

void gerer_commande::on_pushButton_imprimer_h_M_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_h_modifier->model()->rowCount();
    const int columnCount = ui->tableView_h_modifier->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("strTitle")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"

        "<img src="":/picture/App_LOGO.ico"" alt=""logo"" height=""90"" width=""90"">"
        "<center> <h2 style=""color:orange"">-Historique Des Commandes Recemment Modifie-</h2><br></br><br></br><br></br><table border=0.5 cellspacing=1 cellpadding=3>\n";

    // headers
    out << "<thead><tr bgcolor=""#333""><th><font color=""orange"">Ligne</font></th>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView_h_modifier->isColumnHidden(column))
            out << QString("<th><font color=""orange"">%1</font></th>").arg(ui->tableView_h_modifier->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr><td bgcolor=""lightgray"">" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableView_h_modifier->isColumnHidden(column))
            {
                QString data = ui->tableView_h_modifier->model()->data(ui->tableView_h_modifier->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table> </center>\n"
        "</body>\n"
        "</html>\n";
    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete(document);

}

void gerer_commande::on_pushButton_imprimer_h_s_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_h_supprimer->model()->rowCount();
    const int columnCount = ui->tableView_h_supprimer->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("strTitle")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"

        "<img src="":/picture/App_LOGO.ico"" alt=""logo"" height=""90"" width=""90"">"
        "<center> <h2 style=""color:orange"">-Historique Des Commandes Recemment Supprime-</h2><br></br><br></br><br></br><table border=0.5 cellspacing=1 cellpadding=3>\n";

    // headers
    out << "<thead><tr bgcolor=""#333""><th><font color=""orange"">Ligne</font></th>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView_h_supprimer->isColumnHidden(column))
            out << QString("<th><font color=""orange"">%1</font></th>").arg(ui->tableView_h_supprimer->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr><td bgcolor=""lightgray"">" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableView_h_supprimer->isColumnHidden(column))
            {
                QString data = ui->tableView_h_supprimer->model()->data(ui->tableView_h_supprimer->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table> </center>\n"
        "</body>\n"
        "</html>\n";
    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete(document);
}
//Button 'Deselecte' an item from the table  :
void gerer_commande::on_pushButton_clicked()
{
   selected="";
}

void gerer_commande::on_pushButton_temperature_clicked()
{
    scenario_02 s;
    s.exec();
}

void gerer_commande::on_pushButton_retour_clicked()
{
    accueil a;
    a.setData(nom_u,role);
    hide();
    a.setModal(true);
    a.exec();
}
