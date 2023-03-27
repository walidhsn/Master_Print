#include "materiel.h"
#include <QDate>
#include <QPdfWriter>
#include <QPainter>
#include <QSystemTrayIcon>
#include <QWidget>

#include<QMessageBox>
materiel::materiel()
{
    id=0;
    Nb_p=0;
    cout=0;

    nom=" ";
    Heure_f=" ";
    date=QDate();
}

materiel::materiel(QString nom,QString Heure_f,QDate date,int Nb_p,int cout,int id)
{
    this->nom=nom;
    this->Heure_f=Heure_f;
    this->date=date;

    this->Nb_p=Nb_p;
    this->cout=cout;
    this->id=id;



}

int materiel::getNb_p(){return Nb_p;}
int materiel::getcout(){return cout;}
int materiel::getid(){return id;}
QString materiel::getnom(){return nom;}
QString materiel::getHeure_f(){return Heure_f;}
QDate materiel::getdate(){return date;}



void materiel::setNb_p(int Nb_p){this->Nb_p=Nb_p  ;}
void materiel::setcout(int cout){this->cout=cout  ;}
void materiel::setid(int id){this->id=id  ;}
void materiel::setnom(QString nom){this->nom=nom   ;}
void materiel::setHeure_f(QString Heure_f){this->Heure_f=Heure_f   ;}
void materiel::setdate(QDate date){this->date=date   ;}



bool materiel::ajouter()
{
    QSqlQuery query;
    QString res =QString::number(id);


          query.prepare("INSERT into MATERIAUX (NOMBRE, COUT, NOM, HEURE, MAINTENANCE) "
                        "VALUES (:Nb_p, :cout, :nom, :Heure_f, :date)");

          query.bindValue(":ID" , res);
          query.bindValue(":nom" , nom);
          query.bindValue(":Heure_f" , Heure_f);
          query.bindValue(":cout" , cout);
          query.bindValue(":Nb_p",Nb_p);
          query.bindValue(":date",date);



    return query.exec();
}

QSqlQuery * materiel::search_data(QString source)
{
    QSqlQuery * model = new QSqlQuery();
    model->prepare("select * from MATERIAUX where ID='"+source+"");
    model->exec();
  return model;
}
bool materiel::  supprimer(QString source)
{
     QSqlQuery query;
     query.prepare("DELETE from MATERIAUX where ID = :id ");
     query.bindValue(":id",source);
     return query.exec();
}



QSqlQueryModel * materiel::afficher()
{

    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from MATERIAUX");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nb_p "));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("date "));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("cout"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Heure_f "));




        return model;
}

bool materiel::modifier(int id ,int Nb_p,int cout ,QString nom , QString Heure_f ,QDate date )
{
    QSqlQuery query;

    query.prepare("UPDATE MATERIAUX SET NOM= :nom,HEURE= :Heure_f , MAINTENANCE= :date,NOMBRE= :Nb_p ,COUT= :cout where ID= :id ");

    query.bindValue(":nom",nom);
    query.bindValue(":Heure_f", Heure_f);
    query.bindValue(":date", date);
    query.bindValue(":Nb_p", Nb_p);
    query.bindValue(":cout",cout);
    query.bindValue(":id", id);

            return    query.exec();
}


QSqlQueryModel *materiel::tri_nom(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from MATERIAUX order by NOM ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nb_p "));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("date "));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("cout"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Heure_f "));

    return model;
}
QSqlQueryModel *materiel::tri_cout(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from MATERIAUX order by COUT DESC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nb_p "));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("date "));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("cout"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Heure_f "));

    return model;
}
QSqlQueryModel *materiel::tri_date(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from MATERIAUX order by MAINTENANCE DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nb_p "));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("date "));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("cout"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Heure_f "));

    return model;
}


/*
void  materiel::genererPDF(){

                     QPdfWriter pdf("C:/syrine/syrine.pdf");
                     QPainter painter(&pdf);

                         int i = 4000;
                         painter.setPen(Qt::red);
                         painter.setFont(QFont("Arial", 30));
                         painter.drawText(1100,1200,"Liste Des materiaux");
                         painter.setPen(Qt::black);
                         painter.setFont(QFont("Arial", 15));
                        // painter.drawText(1100,2000,afficheDC);


                         painter.drawRect(100,100,7300,2600);
                         painter.drawRect(0,3000,9600,500);


                         painter.setFont(QFont("Arial", 9));
                         painter.drawText(200,3300,"ID");
                         painter.drawText(1300,3300,"Nom");
                         painter.drawText(2200,3300,"Nombre");
                         painter.drawText(3200,3300,"Date");
                         painter.drawText(5200,3300,"Cout");
                         painter.drawText(7200,3300,"Heure");


                         QSqlQuery query;
                         query.prepare("select * from MATERIAUX");
                         query.exec();
                         while (query.next())
                         {
                             painter.drawText(200,i,query.value(0).toString());
                             painter.drawText(1300,i,query.value(1).toString());
                             painter.drawText(2200,i,query.value(2).toString());
                             painter.drawText(3200,i,query.value(3).toString());
                             painter.drawText(5200,i,query.value(4).toString());
                             painter.drawText(7200,i,query.value(5).toString());



                            i = i + 500;
                         }


      int reponse = QMessageBox::Yes;
          if (reponse == QMessageBox::Yes)
          {
              QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
              notifyIcon->show();
            notifyIcon->setIcon(QIcon("icon.jpg"));

              notifyIcon->showMessage("GESTION DES  MATERIAUX ","Liste MATERIAUX pret dans PDF",QSystemTrayIcon::Information,15000);

              painter.end();
          }
          if (reponse == QMessageBox::No)
          {
               painter.end();
          }
}
*/
