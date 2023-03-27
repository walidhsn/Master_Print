#ifndef COMPTES_H
#define COMPTES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>

class comptes
{
private:
    QString type,nomUtilisateur,mdp,email,rfid;


public:
    comptes();
    comptes(QString,QString,QString,QString,QString);

    bool ajouter_compte();
    QSqlQueryModel *afficher_compte();
    bool modifier_compte(QString,QString,QString,QString);
    bool supprimer_compte(QString nomU);
    int  SeConnecter(QString,QString);
    int verif_mdp(QString nomU,QString mdpOld);
    bool reset_mdp(QString nomU,QString mdpNew);
    QString afficher_RFID(QString nomU);
    QString afficher_type(QString nomU);


    QString getnomUtilisateur();
    QString getmdp();
    QString getemail();
    QString getrfid();
    QString gettype();

    void setnomUtilisateur(QString nomU);
    void setmdp(QString passwd);
    void setemail(QString addrEmail);
    void setrfid(QString rf);
    void settype(QString t);






};

#endif // COMPTES_H
