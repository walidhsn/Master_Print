#ifndef MATERIEL_H
#define MATERIEL_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QtDebug>
#include <QDate>
class materiel
{
    QString nom,Heure_f;

QDate date ;

    int Nb_p,cout,id;

public:
    materiel();
    materiel(QString,QString,QDate,int,int,int);


    int getNb_p();
    int getcout();
    int getid();
    QString getnom();
    QString getHeure_f();
    QDate getdate();


    void setNb_p(int);
    void setcout(int);
    void setid(int);
    void setnom(QString);
    void setHeure_f(QString);
    void setdate(QDate);


    bool ajouter();

    QSqlQueryModel * afficher();

 bool modifier(int id ,int Nb_p , int cout,QString nom ,QString Heure_f,QDate date);

 bool supprimer(QString source);
 QSqlQuery * search_data(QString source);
 QSqlQueryModel *tri_nom();
 QSqlQueryModel *tri_cout();
 QSqlQueryModel *tri_date();
void  genererPDF();



};

#endif // MATERIEL_H
