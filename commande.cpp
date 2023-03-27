#include "commande.h"

Commande::Commande()
{

}
Commande::~Commande()
{

}
Commande::Commande(int id_client,QString nom_commande,QString type_commande,QDateTime datetime_commande,int nbPage_commande,int etat_commande,float prix_commande)
{
    this->id_client=id_client;
    this->nom_commande=nom_commande;
    this->type_commande=type_commande;
    this->datetime_commande=datetime_commande;
    this->nbPage_commande=nbPage_commande;
    this->etat_commande=etat_commande;
    this->prix_commande=prix_commande;
}
Commande::Commande(int id_commande,int id_client,QString nom_commande,QString type_commande,QDateTime datetime_commande,int nbPage_commande,int etat_commande,float prix_commande,QString activity)
{
    this->id_commande=id_commande;
    this->id_client=id_client;
    this->nom_commande=nom_commande;
    this->type_commande=type_commande;
    this->datetime_commande=datetime_commande;
    this->nbPage_commande=nbPage_commande;
    this->etat_commande=etat_commande;
    this->prix_commande=prix_commande;
    this->activity=activity;
}
bool Commande::ajouter()
{
    QSqlQuery query;
    QString cin= QString::number(id_client);
    QString nb_page= QString::number(nbPage_commande);
    QString etat= QString::number(etat_commande);
    QString prix= QString::number(prix_commande);
    query.prepare("INSERT INTO Commande (cin_client,nom_commande,type_commande,date_commande,nb_page,etat_commande,prix_commande)"
                  "VALUES(:cin_client,:nom_commande,:type_commande,:date_commande,:nb_page,:etat_commande,:prix_commande)");
    query.bindValue(":cin_client",cin);
    query.bindValue(":nom_commande",nom_commande);
    query.bindValue(":type_commande",type_commande);
    query.bindValue(":date_commande",datetime_commande);
    query.bindValue(":nb_page",nb_page);
    query.bindValue(":etat_commande",etat);
    query.bindValue(":prix_commande",prix);
    return query.exec();
}
bool Commande::ajouter_historique()
{
    QSqlQuery query;
    QString id_c=QString::number(id_commande);
    QString cin= QString::number(id_client);
    QString nb_page= QString::number(nbPage_commande);
    QString etat= QString::number(etat_commande);
    QString prix= QString::number(prix_commande);
    query.prepare("INSERT INTO historique_commande (id_commande,cin_client,nom_commande,type_commande,date_commande,nb_page,etat_commande,prix_commande,activity)"
                  "VALUES(:id_commande,:cin_client,:nom_commande,:type_commande,:date_commande,:nb_page,:etat_commande,:prix_commande,:activity)");
    query.bindValue(":id_commande",id_c);
    query.bindValue(":cin_client",cin);
    query.bindValue(":nom_commande",nom_commande);
    query.bindValue(":type_commande",type_commande);
    query.bindValue(":date_commande",datetime_commande);
    query.bindValue(":nb_page",nb_page);
    query.bindValue(":etat_commande",etat);
    query.bindValue(":prix_commande",prix);
    query.bindValue(":activity",activity);
    return query.exec();
}
QSqlQueryModel * Commande::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from Commande");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_Commande"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Cin_Client"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom_Commande"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Nb_Pages"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Prix"));
    return model;
}
QSqlQueryModel * Commande::afficher(QString activity)
{
    QSqlQuery * query = new QSqlQuery();
    QSqlQueryModel * model = new QSqlQueryModel();
    query->prepare("select * from historique_commande where activity=:activity");
    query->bindValue(":activity",activity);
    query->exec();
    model->setQuery(*query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_Commande"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Cin_Client"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom_Commande"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Nb_Pages"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Prix"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Activity"));
    return model;
}
bool Commande::supprimer(QString source)
{
     QSqlQuery query;
     query.prepare("Delete from Commande where id_commande = :id or cin_client = :id");
     query.bindValue(":id",source);
     return query.exec();
}
bool Commande::supprimer_h(QString source)
{
     QSqlQuery query;
     query.prepare("Delete from historique_commande where activity=:activity");
     query.bindValue(":activity",source);
     return query.exec();
}
QSqlQuery * Commande::search_data(QString source)
{
    QSqlQuery * model = new QSqlQuery();
    model->prepare("select * from Commande where id_commande='"+source+"' or cin_client='"+source+"'");
    model->exec();
  return model;
}
QSqlQuery * Commande::search_data(QDateTime source,QString cin)
{
    QSqlQuery * model = new QSqlQuery();
    model->prepare("select * from Commande where date_commande=:date AND cin_client=:cin");
    model->bindValue(":date",source);
    model->bindValue(":cin",cin);
    model->exec();
  return model;
}
bool Commande::modifier(QString source)
{
    QSqlQuery query;
    QString cin= QString::number(id_client);
    QString nb_page= QString::number(nbPage_commande);
    QString etat= QString::number(etat_commande);
    QString prix= QString::number(prix_commande);
    query.prepare("UPDATE Commande SET cin_client=:cin_client,nom_commande=:nom_commande,type_commande=:type_commande,date_commande=:date_commande,nb_page=:nb_page,etat_commande=:etat_commande,prix_commande=:prix_commande WHERE id_commande=:id;");
    query.bindValue(":id",source);
    query.bindValue(":cin_client",cin);
    query.bindValue(":nom_commande",nom_commande);
    query.bindValue(":type_commande",type_commande);
    query.bindValue(":date_commande",datetime_commande);
    query.bindValue(":nb_page",nb_page);
    query.bindValue(":etat_commande",etat);
    query.bindValue(":prix_commande",prix);
    return query.exec();
}
QSqlQueryModel * Commande::tri_id()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from Commande ORDER BY id_commande ASC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_Commande"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Cin_Client"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom_Commande"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Nb_Pages"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Prix"));
    return model;
}
QSqlQueryModel * Commande::tri_date()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from Commande ORDER BY date_commande DESC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_Commande"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Cin_Client"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom_Commande"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Nb_Pages"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Prix"));
    return model;
}
QSqlQueryModel * Commande::tri_AZ()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from Commande ORDER BY nom_commande ASC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_Commande"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Cin_Client"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom_Commande"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Nb_Pages"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Prix"));
    return model;
}
QSqlQueryModel * Commande::tri_ZA()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from Commande ORDER BY nom_commande DESC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_Commande"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Cin_Client"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom_Commande"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Nb_Pages"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Prix"));
    return model;
}
// Trier l'historique :
QSqlQueryModel * Commande::tri_id(QString activity)
{
    QSqlQuery * query = new QSqlQuery();
    QSqlQueryModel * model = new QSqlQueryModel();
    query->prepare("select * from historique_commande where activity=:activity ORDER BY id_commande ASC");
    query->bindValue(":activity",activity);
    query->exec();
    model->setQuery(*query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_Commande"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Cin_Client"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom_Commande"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Nb_Pages"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Prix"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Activity"));
    return model;
}
QSqlQueryModel * Commande::tri_date(QString activity)
{
    QSqlQuery * query = new QSqlQuery();
    QSqlQueryModel * model = new QSqlQueryModel();
    query->prepare("select * from historique_commande where activity=:activity ORDER BY date_commande DESC");
    query->bindValue(":activity",activity);
    query->exec();
    model->setQuery(*query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_Commande"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Cin_Client"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom_Commande"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Nb_Pages"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Prix"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Activity"));
    return model;
}
QSqlQueryModel * Commande::tri_AZ(QString activity)
{
    QSqlQuery * query = new QSqlQuery();
    QSqlQueryModel * model = new QSqlQueryModel();
    query->prepare("select * from historique_commande where activity=:activity ORDER BY nom_commande ASC");
    query->bindValue(":activity",activity);
    query->exec();
    model->setQuery(*query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_Commande"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Cin_Client"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom_Commande"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Nb_Pages"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Prix"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Activity"));
    return model;
}
QSqlQueryModel * Commande::tri_ZA(QString activity)
{
    QSqlQuery * query = new QSqlQuery();
    QSqlQueryModel * model = new QSqlQueryModel();
    query->prepare("select * from historique_commande where activity=:activity ORDER BY nom_commande DESC");
    query->bindValue(":activity",activity);
    query->exec();
    model->setQuery(*query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_Commande"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Cin_Client"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom_Commande"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Nb_Pages"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Prix"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Activity"));
    return model;
}
//-----------------------------------------------------------------------|
// This Function Delete the Validated Orders That had 30 Days older than the current Date and add them to the history of the delelted Orders:
void Commande::auto_delete_validated()
{
    QSqlQuery * query = new QSqlQuery();
    query->prepare("select * from Commande where date_commande < current_date - interval '30' day AND etat_commande='1';");
    query->exec();
    if(query->isSelect())
    {
        while(query->next())
        {
                Commande c;
                QString act ="supprimer";
                int id = query->value(0).toInt();
                int cin = query->value(1).toInt();
                QString nom = query->value(2).toString();
                QString type = query->value(3).toString();
                QDateTime date = query->value(4).toDateTime();
                int nb = query->value(5).toInt();
                int etat = query->value(6).toInt();
                float prix = query->value(7).toFloat();
                Commande h(id,cin,nom,type,date,nb,etat,prix,act);
                bool test = h.ajouter_historique();
                if(test)
                {
                    qDebug()<< "True : L'Ajout des Commandes Verifie a L'historique Supprimer";
                }
                else
                   qDebug()<< "False : L'Ajout des Commandes Verifie a L'historique Supprimer a Echoue";
                bool test_s = c.supprimer(query->value(0).toString());
                if(test_s )qDebug()<< "True : Supprimer les Commandes Verifie";
                else  qDebug()<< "False : Supprimer les Commandes Verifie Echoue";
        }
    }
}
