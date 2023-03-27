#include "employes.h"
#include <QMessageBox>

employes::employes(){
    matricule=nom=prenom=fonction="";
    salaire=0;

}

employes::employes(QString matricule,QString nom,QString prenom,QString fonction,float salaire){
    this->nom=nom;
    this->prenom=prenom;
    this->matricule=matricule;
    this->fonction=fonction,
    this->salaire=salaire;
}


QString employes::getnom(){return nom;}
QString employes::getprenom(){return prenom;}
QString employes::getmatricule(){return matricule;}
QString employes::getfonction(){return fonction;}
QString employes::getdate(){return date_embauche;}
float employes::getsalaire(){return salaire;}

//Setters
void employes::setnom(QString n){nom=n;}
void employes::setprenom(QString p){prenom=p;}
void employes::setmatricule(QString matr){matricule=matr;}
void employes::setfonction(QString fonc){fonction=fonc;}
void employes::setdate(QString d){date_embauche=d;}
void employes::setsalaire(float s){salaire=s;}

//CRUD
bool employes::ajouter(){
    QSqlQuery query;
    QString res = QString::number(salaire);
    query.prepare("insert into employes (matricule,nom,prenom,salaire,fonction)" "values(:matricule,:nom,:prenom,:salaire,:fonction)");
    query.bindValue(":matricule",matricule);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":salaire",res);
    query.bindValue(":fonction",fonction);

    return query.exec();


}
QSqlQueryModel *employes::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from employes");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Matricule"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Date d'embauche"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Salaire"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Fonction"));
    return model;

}
bool employes::modifier(QString matricule,QString nom,QString prenom,QString fonction,float salaire)
{
    QSqlQuery query;
    QString res = QString::number(salaire);
    query.prepare("update employes set nom=:nom,prenom=:prenom,fonction=:fonction,salaire=:salaire where matricule=:matricule");
    query.bindValue(":matricule",matricule);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":salaire",res);
    query.bindValue(":fonction",fonction);

    return query.exec();
}
bool employes::supprimer(QString matricule){
QSqlQuery query;
query.prepare("delete from employes where matricule=:matricule");
query.bindValue(":matricule",matricule);

return query.exec();
}

QSqlQueryModel *employes::tri_croissant_nom(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from employes order by nom asc");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Matricule"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Date d'embauche"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Salaire"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Fonction"));

    return model;
}
QSqlQueryModel *employes::tri_croissant_prenom(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from employes order by prenom asc");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Matricule"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Date d'embauche"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Salaire"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Fonction"));

    return model;

}
QSqlQueryModel *employes::tri_croissant_salaire(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from employes order by salaire asc");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Matricule"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Date d'embauche"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Salaire"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Fonction"));

    return model;

}
QSqlQueryModel *employes::tri_croissant_fonction(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from employes order by fonction asc");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Matricule"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Date d'embauche"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Salaire"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Fonction"));

    return model;

}
QSqlQueryModel *employes::rechercher(QString arg){
    QSqlQueryModel *model= new QSqlQueryModel();
       QSqlQuery   *query= new QSqlQuery();
       query->prepare("select * from employes where matricule like '"+arg+"%' or nom like '"+arg+"%' or prenom like '"+arg+"%'");
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
