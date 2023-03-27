#ifndef PRODUIT_H
#define PRODUIT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>

class Produit
{
    QString type;
    int id_prod , qte_prod;
public:
    //Constructeurs
    Produit(){}
    Produit(int,int,QString);
    //Getters
    //QString get_daterenouv(){return date_renouv;}
    QString get_type(){return type;}
    int get_idprod(){return id_prod;}
    int get_qteprod(){return qte_prod;}
    //setters
    //void set_daterenouv(QString date){date_renouv=date;}
    void set_type(QString typei){type=typei;}
    void set_idprod(int id){id_prod=id;}
    void set_qteprod(int qte){qte_prod=qte;}

    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel *tri_croissant_ident();
    QSqlQueryModel *tri_decroissant_ident();
    QSqlQueryModel *rechercher(QString arg);
    //QSqlTableModel * afficher();
    bool supprimer(int);
    bool modifier();

};

#endif // PRODUIT_H
