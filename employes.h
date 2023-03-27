#ifndef EMPLOYES_H
#define EMPLOYES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class employes
{
private:
    QString matricule,nom,prenom,fonction,date_embauche;
    float salaire;
public:
    employes();
    employes(QString,QString,QString,QString,float);

   QString getnom();
   QString getprenom();
   QString getmatricule();
   QString getfonction();
   QString getdate();
   float getsalaire();
   void setnom(QString n);
   void setprenom(QString p);
   void setmatricule(QString matr);
   void setfonction(QString fonc);
   void setdate(QString d);
   void setsalaire(float s);
   bool ajouter();
   QSqlQueryModel *afficher();
   bool modifier(QString,QString,QString,QString,float);
   bool supprimer(QString matricule);
   QSqlQueryModel *tri_croissant_nom();
   QSqlQueryModel *tri_croissant_prenom();
   QSqlQueryModel *tri_croissant_salaire();
   QSqlQueryModel *tri_croissant_fonction();
   QSqlQueryModel *rechercher(QString arg);

};

#endif // EMPLOYES_H
