#include "glivraison.h"
#include<QSqlQuery>
#include<QDebug>
#include <QMessageBox>
#include <QtDebug>
#include <QVariant>
#include <QString>

Glivraison::Glivraison()
{
id_livraison="";
adresse_livraison="";
prix_livraison="";
}
Glivraison::Glivraison(QString id,QString adresse,QString prix)
{
    this->id_livraison=id;
    this->adresse_livraison=adresse;

    this->prix_livraison=prix;

}
QString Glivraison:: getid_livraison(){return id_livraison;}
QString Glivraison:: getadresse_livraison(){return adresse_livraison;}
QString Glivraison::getprix_livraison(){return prix_livraison;}

void Glivraison::setid_livraison(QString id){this->id_livraison=id;}
void Glivraison::setadresse_livraison(QString adresse){this->adresse_livraison=adresse;}

void Glivraison::setprix_livraison(QString prix){this->prix_livraison=prix;}

bool Glivraison::ajouter()
{
    //bool test=false;


    QSqlQuery query;
          query.prepare("INSERT INTO livraison (id, adresse,prix) " "VALUES (:id, :adresse, :prix)");
          //QString prix_livraison=QString::number(prix_livraison);
          query.bindValue(":id",id_livraison);
          query.bindValue(":adresse", adresse_livraison);
          query.bindValue(":prix", prix_livraison);
          return query.exec();

//return test;
}
bool Glivraison::supprimer(QString id_livraison)
{
    QSqlQuery query;


        query.prepare("Delete from livraison where ID like :id");
        query.bindValue(":id",id_livraison);
        return query.exec();

}
QSqlQueryModel * Glivraison::afficher()
{
   QSqlQueryModel * model = new QSqlQueryModel ();

   model->setQuery("select * from livraison");
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("adresse"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("prix"));
   //model->setHeaderData(2,Qt::Horizontal,QObject::tr("date"));

    return model;
}

bool Glivraison::modifier()
{
    //bool test=false;


    QSqlQuery query;
          query.prepare("UPDATE  livraison set id=:id, adresse=:adresse,prix=:prix where ID like :id");
          query.bindValue(":id",id_livraison);
          query.bindValue(":adresse", adresse_livraison);
          query.bindValue(":prix", prix_livraison);
          return query.exec();

//return test;
}


QSqlQueryModel *Glivraison::tri_croissant_prix(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from livraison order by prix asc");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("adresse"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prix"));

    return model;

}

QSqlQueryModel *Glivraison::tri_croissant_adresse(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from livraison order by adresse asc");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("adresse"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prix"));

    return model;

}

QSqlQueryModel *Glivraison::tri_decroissant_prix(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from livraison order by prix desc");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("adresse"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prix"));

    return model;

}

QSqlQueryModel *Glivraison::tri_decroissant_adresse(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from livraison order by adresse desc");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("adresse"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prix"));

    return model;

}


QSqlQueryModel *Glivraison::rechercher(QString arg){
    QSqlQueryModel *model= new QSqlQueryModel();
       QSqlQuery   *query= new QSqlQuery();
       query->prepare("select * from livraison where id like '"+arg+"%' or prix like '"+arg+"%' or adresse like '"+arg+"%'");
           query->exec();
           if (query->next()) {
           model->setQuery(*query);
           }
           else {
               QMessageBox::information(nullptr, QObject::tr("Rechercher"),
                               QObject::tr("Aucun résultat trouvé !.\n"
                                           "Cliquez sur OK pour quitter."), QMessageBox::Ok);
        }
    return model;
}



//excel


