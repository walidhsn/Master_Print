#ifndef GLIVRAISON_H
#define GLIVRAISON_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

//excel
#include <QObject>
#include <QTableView>
#include <QStringList>
#include <QSqlDatabase>


class Glivraison
{
public:
    Glivraison();
    Glivraison(QString,QString,QString);

QString getid_livraison();
QString getadresse_livraison();

QString getprix_livraison();

void setid_livraison(QString);
void setadresse_livraison(QString);
void setprix_livraison(QString);
bool ajouter();
QSqlQueryModel * afficher();
bool supprimer(QString);
bool modifier();
QSqlQueryModel *tri_croissant_prix();
QSqlQueryModel *tri_croissant_adresse();

QSqlQueryModel *tri_decroissant_prix();
QSqlQueryModel *tri_decroissant_adresse();

QSqlQueryModel *rechercher(QString arg);





private:
   QString id_livraison,adresse_livraison;      
   QString prix_livraison;






};

#endif // GLIVRAISON_H
