#include "produit.h"
#include <QMessageBox>

Produit::Produit(int qte , int id,QString typei)
{
    //date_renouv=date;
    type=typei;
    qte_prod=qte;
    id_prod=id;
}
bool Produit::ajouter(){
    QSqlQuery query;
    QString res = QString::number(id_prod);

    query.prepare("insert into produit (ident,qte,type)""values (:id,:qte,:type)");
    query.bindValue(":id",res);
    query.bindValue(":qte",qte_prod);
    query.bindValue(":type",type);
    //query.bindValue(":date",date_renouv);

    return query.exec();
}
   QSqlQueryModel * Produit::afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();  //
    //QSqlTableModel *model = new QSqlTableModel;
    model->setQuery("select * from produit");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("type"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Needed Quantity"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Disponibility"));
    return model;
}
bool Produit::supprimer(int id){
    QSqlQuery query;
    QString res=QString::number(id);

    query.prepare("Delete from produit where IDENT= :id");
    query.bindValue(":id",res);
    return query.exec();
}

bool Produit::modifier()
{
    //bool test=false;

    QSqlQuery query;
    QString res = QString::number(id_prod);

          query.prepare("UPDATE  Produit set qte=:qte,type=:type where IDENT=:id");
          query.bindValue(":id",res);
          query.bindValue(":qte",qte_prod);
          query.bindValue(":type",type);
          return query.exec();

//return test;
}
QSqlQueryModel *Produit::tri_croissant_ident(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from Produit order by IDENT asc");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDEN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("QTE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE"));
    return model;

}
QSqlQueryModel *Produit::tri_decroissant_ident(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from Produit order by IDENT desc");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDEN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("QTE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE"));
    return model;

}

QSqlQueryModel *Produit::rechercher(QString arg){
    QSqlQueryModel *model= new QSqlQueryModel();
          QSqlQuery   *query= new QSqlQuery();
          query->prepare("select * from Produit where ident like '"+arg+"%' or type like '"+arg+"%'");
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
