#include "clients.h"

Clients::Clients()
{

}
Clients::Clients(int CIN,QString nom,QString prenom,QString adresse,int numtel,QDate dateinscrit)
{
  this->CIN=CIN;
  this->nom=nom;
  this->prenom=prenom;
  this->adresse=adresse;
  this->numtel=numtel;
  this->dateinscrit=dateinscrit;

}


/*Clients::Clients(int CIN,QString nom,QString prenom,QString adresse,int numtel)
{
    this->CIN=CIN;
    this->nom=nom;
    this->prenom=prenom;
    this->adresse=adresse;
    this->numtel=numtel;


}*/
int Clients::getCIN()
{
    return CIN;
}
QString Clients:: getnom()
{
    return nom;
}
QString Clients::getprenom()
{
    return prenom;
}
QString Clients::getadresse()
{
    return adresse;
}
int Clients::getnumtel()
{
    return numtel;
}
QDate Clients::getdateinscrit()
{
    return dateinscrit;
}
void Clients::setcin(int CIN)
{
    this->CIN=CIN;
}
void Clients::setnom(QString nom)
{
    this->nom=nom;
}
void Clients::setprenom(QString prenom)
{
    this->prenom=prenom;
}
void Clients::setadresse(QString adresse)
{
    this->adresse=adresse;
}
void Clients::setnumtel(int numtel)
{
    this->numtel=numtel;
}
void Clients::setdateinscrit(QDate dateinscrit)
{
    this->dateinscrit=dateinscrit;
}
bool Clients::ajouterClient()
{
    QString CIN_string=QString::number(CIN);
    QString tel_string=QString::number(numtel);
    QSqlQuery query;


          query.prepare("INSERT INTO client (CIN,nom,prenom,adresse,numtel) "
                        "VALUES (:CIN, :nom, :prenom,:adresse,:numtel)");
          query.bindValue(0,CIN_string );
          query.bindValue(1, nom);
          query.bindValue(2, prenom);
          query.bindValue(3, adresse);
          query.bindValue(4,tel_string);
         //query.bindValue(":dateinscrit",getdateinscrit());

          return query.exec();


}
/*bool Clients::supprimerClient(int CIN)
{
    QSqlQuery query;


          query.prepare("delete from client where CIN=:CIN");
          query.bindValue(0,CIN );

          return query.exec();

}*/
bool Clients::supprimerClient(QString source)
{

    QSqlQuery query;
     query.prepare("Delete from client where CIN = :CIN ");
     query.bindValue(":CIN",source);
     return query.exec();
}
QSqlQueryModel * Clients::afficherClient()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM client");
    // QSqlTableModel *model = new QSqlTableModel;
    // model->setTable("client");
     //model->setEditStrategy(QSqlTableModel::OnManualSubmit);
     //    model->select();
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("Numero telephone"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date inscription"));



    return model;
}

bool Clients::modifierClient(QString source)
{
    QSqlQuery query;
     QString CIN_string=QString::number(CIN);
     QString tel_string=QString::number(numtel);


    query.prepare("UPDATE client SET CIN=:CIN,nom=:nom,prenom=:prenom,adresse=:adresse,numtel=:numtel WHERE CIN=:CIN;");
    query.bindValue(":CIN",CIN_string);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":adresse",adresse);
    query.bindValue(":numtel",numtel);
    //query.bindValue(":dateinscrit",getdateinscrit());

    return query.exec();
}
QSqlQueryModel * Clients::tri_AZ()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from client ORDER BY nom ASC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("adresse"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("numtel"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("dateinscrit"));
    return model;
}
QSqlQueryModel * Clients::tri_ZA()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from client ORDER BY prenom DESC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("adresse"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("numtel"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("dateinscrit"));
    return model;
}
QSqlQueryModel * Clients::tri_date()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from client ORDER BY dateinscrit ASC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("adresse"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("numtel"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("dateinscrit"));
    return model;
}
void Clients::statistiques(QWidget * w)
{
    int tunis = 0,ariana=0,jendouba=0,beja=0,bizerte=0,kairouan=0,gafsa=0,gabes=0,nabeul=0,tozeur=0,siliana=0;
                QSqlQuery query("SELECT COUNT(*) FROM client WHERE adresse='tunis'");
                while(query.next())
                {
                    tunis = query.value(0).toInt();
                }
                QSqlQuery query2("SELECT COUNT(*) FROM client WHERE adresse='ariana'");
                while(query2.next())
                {
                   ariana= query2.value(0).toInt();
                }
                QSqlQuery query3("SELECT COUNT(*) FROM client WHERE adresse='beja'");
                while(query3.next())
                {
                   beja= query3.value(0).toInt();
                }
                QSqlQuery query4("SELECT COUNT(*) FROM client WHERE adresse='jendouba'");
                while(query4.next())
                {
                   jendouba= query4.value(0).toInt();
                }
                QSqlQuery query5("SELECT COUNT(*) FROM client WHERE adresse='bizerte'");
                while(query5.next())
                {
                   bizerte= query5.value(0).toInt();
                }
                QSqlQuery query6("SELECT COUNT(*) FROM client WHERE adresse='kairouan'");
                while(query6.next())
                {
                   kairouan= query6.value(0).toInt();
                }
                QSqlQuery query7("SELECT COUNT(*) FROM client WHERE adresse='gafsa'");
                while(query7.next())
                {
                   gafsa= query7.value(0).toInt();
                }
                QSqlQuery query8("SELECT COUNT(*) FROM client WHERE adresse='nabeul'");
                while(query8.next())
                {
                   nabeul= query8.value(0).toInt();
                }
                QSqlQuery query9("SELECT COUNT(*) FROM client WHERE adresse='siliana'");
                while(query9.next())
                {
                   siliana= query9.value(0).toInt();
                }
                QSqlQuery query10("SELECT COUNT(*) FROM client WHERE adresse='tozeur'");
                while(query10.next())
                {
                   tozeur= query10.value(0).toInt();
                }



            QPieSeries *series = new QPieSeries();

            series->append("tunis",tunis);
            series->append("ariana",ariana);
            series->append("beja",beja);
            series->append("jendouba",jendouba);
            series->append("bizerte",bizerte);
            series->append("kairouan",kairouan);
            series->append("gafsa",gafsa);
            series->append("nabeul",nabeul);
            series->append("tozeur",tozeur);
            series->append("siliana",siliana);




            series->setHoleSize(0.8);
            series->setPieSize(1.0);

            QPieSlice * I = series->slices().at(0);
            QPieSlice * C = series->slices().at(1);
            QPieSlice * D = series->slices().at(2);
            QPieSlice * E = series->slices().at(3);
            QPieSlice * F = series->slices().at(4);
            QPieSlice * G = series->slices().at(5);
            QPieSlice * H = series->slices().at(6);
            QPieSlice * J = series->slices().at(7);
            QPieSlice * K = series->slices().at(8);
            QPieSlice * L = series->slices().at(9);







            /*I->setLabelVisible(true);
            C->setLabelVisible(true);
            D->setLabelVisible(true);
            E->setLabelVisible(true);
            F->setLabelVisible(true);
            G->setLabelVisible(true);
            H->setLabelVisible(true);
            J->setLabelVisible(true);
            K->setLabelVisible(true);
            L->setLabelVisible(true);*/







            I->setBrush(QColor::fromRgb(255, 0, 0));
            C->setBrush(QColor::fromRgb(0, 0, 255));
            D->setBrush(QColor::fromRgb(0, 255, 255));
            E->setBrush(QColor::fromRgb(128, 128, 128));
            F->setBrush(QColor::fromRgb(128, 0, 0));
            G->setBrush(QColor::fromRgb(0, 128, 0));
            H->setBrush(QColor::fromRgb(0, 128, 128));
            J->setBrush(QColor::fromRgb(128, 0, 128));
            K->setBrush(QColor::fromRgb(128, 128, 0));
            L->setBrush(QColor::fromRgb(255, 255, 0));








            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Adresses des clients");
            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignBottom);
            chart->setAnimationOptions(QChart::AllAnimations);

            QChartView * chartview = new QChartView(chart);
            chartview->resize(w->width(),w->height());
            chartview->setParent(w);

}
QSqlQuery * Clients::search_data(QString source)
{
    QSqlQuery * model = new QSqlQuery();
    model->prepare("select * from client where CIN='"+source+"' ");
    model->exec();
  return model;
}
