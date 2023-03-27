#include "client.h"
#include "ui_client.h"
#include <QtDebug>
#include <QString>
#include <QMessageBox>
#include <QIntValidator>
#include <QObject>
#include <QSqlQuery>
#include <QLineEdit>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QPixmap>
#include <QImage>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <accueil.h>
client::client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::client)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);
   ui->cinAjout->setValidator(new QIntValidator(100, 99999999, this));
   ui->cinModif->setValidator(new QIntValidator(100, 99999999, this));
    ui->telAjout->setValidator(new QIntValidator(100, 99999999, this));
    ui->numModif->setValidator(new QIntValidator(100, 99999999, this));

   ui->table_client->setModel(cl.afficherClient());
}

client::~client()
{
    delete ui;
}
/*client::client()
{
    CIN=0;
    nom=" ";
    prenom=" ";
    adresse=" ";
    numtel=0;
    dateinscrit=" ";
}*/

void client::on_bouton_ajout_clicked()
{
    int CIN=ui->cinAjout->text().toInt();
    QString nom=ui->nomAjout->text();
    QString prenom=ui->prenomAjout->text();
    QString adresse=ui->comboBox->currentText();
    int numtel=ui->telAjout->text().toInt();
    QDate d=QDate::currentDate();


    //QString dateinscrit=ui->dateinscritAjout->text();

    Clients C(CIN,nom,prenom,adresse,numtel,d);
    bool test=C.ajouterClient();
    if(test)
    {
        ui->table_client->setModel(cl.afficherClient());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->cinAjout->clear();
        ui->nomAjout->clear();
        ui->prenomAjout->clear();
        //ui->adresseAjout->clear();
        ui->telAjout->clear();
        ui->label_image->clear();

    }
    else
    QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
/*void client::on_bouton_supprimer_clicked()
{
    Clients C;

    C.setcin(ui->CIN_supp->text().toInt());
    bool test;
    test=C.supprimerClient(C.getCIN());
    if(test)
    {
          ui->table_client->setModel(cl.afficherClient());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("suppression avec succes.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("Echec de suppression.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
*/
void client::on_bouton_supprimer_clicked()
{
    if(selected!="")
        {
            bool test=cl.supprimerClient(selected);
            if(test)
            {

                ui->table_client->setModel(cl.afficherClient());
                QMessageBox::information(nullptr, QObject::tr("Success"),
                            QObject::tr("Deleted successfuly .\n"
                                        "Click OK to exit."), QMessageBox::Ok);
                selected="";
            }
            else {
                QMessageBox::critical(nullptr, QObject::tr("Failed"),
                            QObject::tr("ERROR :Deleting failed. select Cin Or (there's no colom selected or the row doesn't exist)\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                selected="";
            }
        }
        else
        {
            QMessageBox::information(nullptr, QObject::tr("Select"),
                        QObject::tr("Please select the Cin of the client (Double Click).\n"
                                    "Click OK to exit."), QMessageBox::Ok);
        }
}

void client::on_table_client_activated(const QModelIndex &index)
{
    selected = ui->table_client->model()->data(index).toString();
    qDebug()<< selected;
}

void client::on_bouton_modifier_clicked()
{
    if(selected!="")
       {
           QSqlQuery * m = cl.search_data(selected);
           if(m->isSelect())
           {
               //ui->table_client->setSelectionModel(ui->tab_modif);
               //ui->table_client->setModel(cl.afficherClient());
            // ui->table_client->setTabletTracking(ui->tab_modif);
               while(m->next())
               {
                   selected=m->value(0).toString();
                   ui->cinModif->setText(m->value(0).toString());
                   ui->nomModif->setText(m->value(1).toString());
                   ui->prenomModif->setText(m->value(2).toString());
                   ui->adresseModif->setText(m->value(3).toString());
                   ui->numModif->setText(m->value(4).toString());
                  // ui->dateModif->setText(m->value(5).toString());

               }
           }
           else
           {
               QMessageBox::critical(nullptr, QObject::tr("Failed"),
                           QObject::tr("ERROR : while selecting the data\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
           }
       }
       else
       {
           QMessageBox::information(nullptr, QObject::tr("Select"),
                       QObject::tr("Please select the Id or Cin of the client (Double Click).\n"
                                   "Click OK to exit."), QMessageBox::Ok);
       }
}

void client::on_bouton_validerMod_clicked()
{
    if(selected!="")
    {
        int CIN = ui->cinModif->text().toInt();
        QString nom = ui->nomModif->text();
        QString prenom = ui->prenomModif->text();
        QString adresse = ui->adresseModif->text();
        int numtel = ui->numModif->text().toInt();
        QDate d=QDate::currentDate();

       // QString dateinscrit = ui->dateModif->text();



       // QDateTime date = QDateTime::currentDateTime();


        if(nom=="" || prenom=="" || adresse=="" )
        {
            QMessageBox::information(nullptr, QObject::tr("Miss information"),
                        QObject::tr("Please Enter Values OR (0 or 1) in Etat OR Insert 8 degits in Cin .\n"
                                    "Click OK to exit."), QMessageBox::Ok);
        }
        else
        {
            Clients C(CIN,nom,prenom,adresse,numtel,d);
            bool test = C.modifierClient(selected);
            if(test)
            {
                QMessageBox::information(nullptr, QObject::tr("Success"),
                            QObject::tr("Update successfuly .\n"
                                        "Click OK to exit."), QMessageBox::Ok);
                ui->table_client->setModel(cl.afficherClient());
                selected="";
                ui->cinModif->clear();
                ui->nomModif->clear();
                ui->prenomModif->clear();
                ui->adresseModif->clear();
                ui->numModif->clear();
                //ui->dateModif->clear();
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Failed"),
                            QObject::tr("ERROR :Update failed.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }
        }
    }
    else
    {
        QMessageBox::information(nullptr, QObject::tr("Select"),
                    QObject::tr("Please select the Id or Cin of the client (Double Click) From the Liste.\n"
                                "Click OK to exit."), QMessageBox::Ok);
         selected="";
    }
}



/*void client::on_bouton_validerMod_clicked()
{
    if(selected!="")
        {
            bool verif=false;
            int CIN = ui->cinModif->text().toInt();
            QString nom = ui->nomModif->text();
            QString prenom = ui->prenomModif->text();
            QString adresse = ui->adresseModif->text();
            int numtel = ui->numModif->text().toInt();
            QString dateinscrit = ui->dateModif->text();

            if( nom=="" || prenom=="" )
            {
                QMessageBox::information(nullptr, QObject::tr("Miss information"),
                            QObject::tr("Please Enter Values OR (0 or 1) in Etat OR Insert 8 degits in Cin .\n"
                                        "Click OK to exit."), QMessageBox::Ok);
            }
            else
            {
                Clients C(CIN,nom,prenom,adresse,numtel,dateinscrit);
                bool test = C.modifierClient(selected);
                if(test)
                {
                    QMessageBox::information(nullptr, QObject::tr("Success"),
                                QObject::tr("Update successfuly .\n"
                                            "Click OK to exit."), QMessageBox::Ok);
                    ui->table_client->setModel(cl.afficherClient());
                   // ui->tabWidget_commande->setCurrentWidget(ui->tab_liste);
                    selected="";
                    ui->cinModif->clear();
                    ui->nomModif->clear();
                    ui->prenomModif->clear();
                    ui->adresseModif->clear();
                    ui->numModif->clear();
                    ui->dateModif->clear();
                }
                else
                {
                    QMessageBox::critical(nullptr, QObject::tr("Failed"),
                                QObject::tr("ERROR :Update failed.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
                }
            }
        }
        else
        {
            QMessageBox::information(nullptr, QObject::tr("Select"),
                        QObject::tr("Please select the Id or Cin of the client (Double Click) From the Liste.\n"
                                    "Click OK to exit."), QMessageBox::Ok);
             selected="";
        }
}*/



void client::on_radioButton_croissant_clicked()
{
     ui->table_client->setModel(cl.tri_AZ());
}

void client::on_radioButton_decroissant_clicked()
{

    ui->table_client->setModel(cl.tri_ZA());
}

void client::on_radioButton_date_clicked()
{
    ui->table_client->setModel(cl.tri_date());
}


void client::on_recherche_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM client WHERE CIN LIKE '"+arg1+"%' or nom LIKE '"+arg1+"%' or prenom LIKE '"+arg1+"%' or numtel LIKE '"+arg1+"%' or adresse LIKE '"+arg1+"%'");
        query->exec();
        if (query->next()) {
        model->setQuery(*query);
        ui->table_client->setModel(model);
        }
        else {
            QMessageBox::information(nullptr, QObject::tr("Rechercher"),
                            QObject::tr("Aucun résultat trouvé !.\n"
                                        "Cliquez sur OK pour quitter."), QMessageBox::Ok);
            ui->recherche->clear();}




}


void client::on_bouton_PDF_clicked()
{
    QPdfWriter fichierClient_pdf("C:\\listeClients.pdf");

       QPainter painter(&fichierClient_pdf);
       int i = 4000;
       QImage img(":/picture/App_LOGO.ico");
                 QPoint imageCoordinates(-200,150);
                 painter.drawImage(imageCoordinates,img);
              painter.setPen(Qt::blue);
              painter.setFont(QFont("Time New Roman", 25));
              painter.drawText(3000,1400,"Liste des clients");
              painter.setPen(Qt::black);
              painter.setFont(QFont("Time New Roman", 15));
              painter.drawRect(100,100,9400,2500);
              painter.drawRect(100,3000,9400,500);
              painter.setFont(QFont("Time New Roman", 9));
              painter.drawText(400,3300,"CIN");
              painter.drawText(2000,3300,"Nom");
              painter.drawText(3400,3300,"Prenom");
              painter.drawText(4700,3300,"adresse");
              painter.drawText(6200,3300,"numtel");
              painter.drawText(7600,3300,"dateinscrit");
              painter.drawRect(100,3000,9400,9000);

              QSqlQuery query;
              query.prepare("select * from client");
              query.exec();
              while (query.next())
              {
                  painter.drawText(400,i,query.value(0).toString());
                  painter.drawText(2000,i,query.value(1).toString());
                  painter.drawText(3400,i,query.value(2).toString());
                  painter.drawText(4700,i,query.value(3).toString());
                  painter.drawText(6200,i,query.value(4).toString());
                  painter.drawText(7600,i,query.value(5).toString());


                 i = i + 350;
              }
              int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                  if (reponse == QMessageBox::Yes)
                  {
                      QDesktopServices::openUrl(QUrl::fromLocalFile("C:\\Users\\User\\Desktop\\listeClients.pdf"));

                      painter.end();
                  }
                  if (reponse == QMessageBox::No)
                  {
                      painter.end();
                  }
              /*QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
              QObject::tr("PDF Enregistré.\n" "Click Cancel to exit."), QMessageBox::Cancel);*/
}
void client::on_bouton_image_clicked()
{
    QFileDialog dialog(this);
       dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
       dialog.setViewMode(QFileDialog::Detail);
       QString fileName = QFileDialog::getOpenFileName(this,
       tr("Open Images"), "C:\\Users\\User\\Desktop\\images", tr("Image Files (*.png *.jpg *.bmp)"));
       if (!fileName.isEmpty())
       {
           QImage image(fileName);
           //QString buttonText=ui->nomAjout->text();

           QSqlQuery qry;
           ui->label_image->setPixmap(QPixmap::fromImage(image));
           qry.prepare("INSERT INTO client (image) ""VALUES (:fileName)");

           if(qry.exec())
           {

              QMessageBox::information(this,tr("Update Result"),tr("<font color=black>Profile Photo Update Completed"));
           }


       }
}

















/*void client::on_bouton_image_clicked()
{
     QSqlQuery query;
    QFileDialog dialog(this);
      dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
      dialog.setViewMode(QFileDialog::Detail);

      QString fileName = QFileDialog::getOpenFileName(this,
         tr("Open Images"), "C:\\Users\\User\\Desktop\\images", tr("Image Files (*.png *.jpg *.bmp *.xpm)"));
      if (!fileName.isEmpty())
      {
           QImage image(fileName);
           ui->label_image->setPixmap(fileName);
           ui->label_image->resize(300,450);
           QString buttonText=ui->nomAjout->text();
           QSqlQuery qry;
           //qry.prepare("INSERT INTO client (image) ""VALUES (:fileName");
           //qry.bindValue(6,fileName);
           qry.prepare("update CLIENT set (image) =:fileName where NOM=:buttonText+");
           qry.bindValue(":image",fileName);


           if(qry.exec()){

              QMessageBox::information(this,tr("Update Result"),tr("<font color=black>Profile Photo Update Completed"));
       }
      }



    QSqlQuery qry;
    qry.prepare("select * from CLIENT where CIN='"+buttonText+"'");
    if(qry.exec())
        while(qry.next())
        {
            QPixmap pro_pic;
            QString location=qry.value(10).toString();
            pro_pic.load(location);
            ui->label_image->setPixmap(pro_pic);
            ui->label_image->setScaledContents(true);
        }


      QString imagePath = QFileDialog::getSaveFileName(this,tr("Save File"),"",tr("JPEG (.jpg *.jpeg);;PNG (.png)" ));
      QImage imageObject;
      imageObject.load(imagePath);

     //imageObject = image.toImage();
   //  imageObject.save(imagePath);

      //query.exec("INSERT INTO client (image)"
                 //"VALUES("+ ui->label_image->text() +") ");

      query.prepare( "INSERT INTO client (image) VALUES (:fileName)" );
      query.bindValue(5, fileName);

}*/
/*void client::on_bouton_image_clicked()
{
    QFileDialog dialog(this);
      dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
      dialog.setViewMode(QFileDialog::Detail);

    QString picpath=QFileDialog::getOpenFileName
            (
                this,
            tr("Open File"),
            "C:\\Users\\User\\Desktop\\images",
            "All File (*.*);;JPG File (*.jpg);;PNG File (*.png)"
                );
    QString buttonText=ui->nomAjout->text();
    QSqlQuery qry;
    qry.prepare("update CLIENT set image ='"+picpath+"' where CIN='"+buttonText+"'");
    if(qry.exec()){

       QMessageBox::information(this,tr("Update Result"),tr("<font color=black>Profile Photo Update Completed"));

    QSqlQuery qry;
    qry.prepare("select * from CLIENT where CIN='"+buttonText+"'");
    if(qry.exec())
        while(qry.next())
        {
            QPixmap pro_pic;
            QString location=qry.value(10).toString();
            pro_pic.load(location);
            ui->label_image->setPixmap(pro_pic);
            ui->label_image->setScaledContents(true);
        }
    }
}*/

void client::on_tabWidget_currentChanged(int index)
{

    Clients c;
     c.statistiques(ui->widget);

}

void client::on_pushButton_clicked()
{
    accueil a;
    a.setData(nom_u,role);
    hide();
    a.setModal(true);
    a.exec();
}
