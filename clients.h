#ifndef CLIENTS_H
#define CLIENTS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QDebug>
#include <QDateTime>
#include <QImage>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QtCharts>


class Clients
{
public:
    Clients();
    Clients(int,QString,QString,QString,int);
    Clients(int ,QString ,QString ,QString ,int, QDate );

    int getCIN();
    QString getnom();
    QString getprenom();
    QString getadresse();
    int getnumtel();
    QDate getdateinscrit();

    void setcin(int);
    void setnom(QString);
    void setprenom(QString);
    void setadresse(QString);
    void setnumtel(int);
    void setdateinscrit(QDate);
    bool ajouterClient();
    bool supprimerClient(QString);
    QSqlQueryModel* afficherClient();
    bool modifierClient(QString);
    QSqlQuery * search_data(QString source);
    QSqlQueryModel * tri_AZ();
    QSqlQueryModel * tri_ZA();
    QSqlQueryModel * tri_date();
    void statistiques(QWidget*);



private:
    int CIN,numtel;
    QString nom,prenom,adresse,image;
    QDate dateinscrit;
   // QImage image;

};

#endif // CLIENTS_H
