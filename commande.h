#ifndef COMMANDE_H
#define COMMANDE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDateTime>
#include <QMessageBox>
#include <QtDebug>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPdfWriter>
#include <QFile>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QDataStream>

class Commande
{
public:
    //Cons & Des :
    Commande();
    Commande(int,QString,QString,QDateTime,int,int,float);
    Commande(int,int,QString,QString,QDateTime,int,int,float,QString);
    ~Commande();
    //Functions :
    bool ajouter();
    bool ajouter_historique();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher(QString activity);
    QSqlQueryModel * tri_id();
    QSqlQueryModel * tri_date();
    QSqlQueryModel * tri_AZ();
    QSqlQueryModel * tri_ZA();
    QSqlQueryModel * tri_id(QString activity);
    QSqlQueryModel * tri_date(QString activity);
    QSqlQueryModel * tri_AZ(QString activity);
    QSqlQueryModel * tri_ZA(QString activity);
    bool supprimer(QString);
    bool supprimer_h(QString);
    bool modifier(QString);
    QSqlQuery * search_data(QString);
    QSqlQuery * search_data(QDateTime,QString);
    void auto_delete_validated();
    //Getter :
    int getid_client(){return id_client;}
    QString getNom_commande(){return nom_commande;}
    QString getType_commande(){return type_commande;}
    QDateTime getDate_commande(){return datetime_commande;}
    int getNb_pageCommande(){return nbPage_commande;}
    int getEtat_commande(){return etat_commande;}
    float getPrix_commande(){return prix_commande;}
    //Setter :
    void setid_client(int id_client){this->id_client=id_client;}
    void setNom_commande(QString nom_commande){this->nom_commande=nom_commande;}
    void setType_commande(QString type_commande){this->type_commande=type_commande;}
    void setDate_commande(QDateTime datetime_commande){this->datetime_commande=datetime_commande;}
    void setnb_pageCommande(int nbPage_commande){this->nbPage_commande=nbPage_commande;}
    void setEtat_commande(int etat_commande){this->etat_commande=etat_commande;}
    void setPrix_commande(float prix_commande){this->prix_commande=prix_commande;}
private:
    QString nom_commande,type_commande,activity;
    QDateTime datetime_commande;
    int id_client,nbPage_commande,etat_commande,id_commande;
    float prix_commande;
};

#endif // COMMANDE_H
