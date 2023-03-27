#include "comptes.h"
#include <QDebug>
comptes::comptes()
{

}
comptes::comptes(QString typeU,QString nomU,QString addr_email,QString passwd,QString rf){
    type=typeU;
    nomUtilisateur=nomU;
    mdp=passwd;
    email=addr_email;
    rfid=rf;
}

bool comptes::ajouter_compte(){
    QSqlQuery query;
    query.prepare("insert into comptes(type,nomutilisateur,email,mdp,rfid) values(:type,:nomutilisateur,:email,:mdp,:rfid)");
    query.bindValue(":type",type);
    query.bindValue(":nomutilisateur",nomUtilisateur);
    query.bindValue(":email",email);
    query.bindValue(":mdp",mdp);
    query.bindValue(":rfid",rfid);

    return query.exec();

}
QSqlQueryModel *comptes::afficher_compte(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from comptes");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom d'utilisateur"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Email"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Mot de passe"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("RFID"));
    return model;
}
bool comptes::modifier_compte(QString nomU,QString addr_email,QString passwd,QString rf){
    QSqlQuery query;
    query.prepare("update comptes set email=:email,mdp=:mdp,rfid=:rfid where nomutilisateur=:nomutilisateur");
    query.bindValue(":nomutilisateur",nomU);
    query.bindValue(":email",addr_email);
    query.bindValue(":mdp",passwd);
    query.bindValue(":rfid",rf);

    return query.exec();
}
bool comptes::supprimer_compte(QString nomU){
    QSqlQuery query;
    query.prepare("delete from comptes where nomutilisateur=:nomutilisateur");
    query.bindValue(":nomutilisateur",nomU);
    return query.exec();
}
int comptes::SeConnecter(QString nomU,QString mdp){
    int count=0;
    QSqlQuery query;
    query.prepare("select * from comptes where nomutilisateur=:nomutilisateur and mdp=:mdp");
    query.bindValue(":nomutilisateur",nomU);
    query.bindValue(":mdp",mdp);

    if(query.exec()){
        while(query.next())
        {
            count++;
        }
    }
    return count;
}
int comptes::verif_mdp(QString nomU,QString mdpOld){
    int count=0;
    QSqlQuery query;
    query.prepare("select * from comptes where nomutilisateur=:nomutilisateur and mdp=:mdp");
    query.bindValue(":nomutilisateur",nomU);
    query.bindValue(":mdp",mdpOld);
    if(query.exec()){
        while(query.next())
        {
            count++;
        }
    }
    return count;
}
bool comptes::reset_mdp(QString nomU,QString mdpNew){
    QSqlQuery query;
    query.prepare("update comptes set mdp=:mdp where nomutilisateur=:nomutilisateur");
    query.bindValue(":nomutilisateur",nomU);
    query.bindValue(":mdp",mdpNew);

    return query.exec();
}
QString comptes::afficher_RFID(QString nomU)
{
    QSqlQuery query;
    query.prepare("select * from comptes where nomutilisateur=:nomutilisateur");
    query.bindValue(":nomutilisateur",nomU);
    if(query.exec())
    {
        while(query.next())
        {
           QString rfid=query.value(4).toString();
           return rfid;
        }
    }
}
QString comptes::afficher_type(QString nomU)
{
    QSqlQuery query;
    query.prepare("select * from comptes where nomutilisateur=:nomutilisateur");
    query.bindValue(":nomutilisateur",nomU);
    if(query.exec())
    {
        while(query.next())
        {
           QString typeU=query.value(0).toString();
           return typeU;
        }
    }
}


QString comptes::getnomUtilisateur(){
    return nomUtilisateur;
}
QString comptes::getmdp(){
    return mdp;
}
QString comptes::getemail(){
    return email;
}
QString comptes::gettype()
{
    return type;
}

void comptes::setnomUtilisateur(QString nomU){
    nomUtilisateur=nomU;
}
void comptes::setmdp(QString passwd){
    mdp=passwd;
}
void comptes::setemail(QString addrEmail){
    email=addrEmail;
}
void comptes::settype(QString t)
{
    type=t;
}


