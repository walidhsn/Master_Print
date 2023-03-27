#include "livraison.h"
#include "glivraison.h"
#include "ui_livraison.h"
#include <QString>
#include <QIntValidator>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlError>
#include <QPdfWriter>
#include <QPainter>
#include<QFileDialog>
#include<QFile>
#include <QDateTime>
#include <accueil.h>
livraison::livraison(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::livraison)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);
    ui->tableView->setModel(Gtmp.afficher()) ;
    ui->lineEdit_Prix->setValidator(new QIntValidator(0,20000,this));
    ui->lineEdit_Adresse->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]*"),this));
    ui->lineEdit_Prix_2->setValidator(new QIntValidator(0,20000,this));
    ui->lineEdit_Adresse_2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]*"),this));
    QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery("SELECT id FROM livraison");
        ui->comboBox->setModel(model);


     //ui->lineEdit_Date->setValidator( new QIntValidator(100, 999, this));
}

livraison::~livraison()
{
    delete ui;
}

void livraison::on_pushButton_clicked()
{
QString id=ui->lineEdit_ID->text();

QString adresse=ui->lineEdit_Adresse->text();
QString prix=ui->lineEdit_Prix->text();
    Glivraison livr(id,adresse,prix);


bool test=livr.ajouter()  ;
if(test)
{
    ui->tableView->setModel(Gtmp.afficher()) ;
    QMessageBox::information(nullptr, QObject::tr("ok si fadi"),
                                                       QObject::tr("ajout effectué.\n"
                                                                   "Click Cancel to exit."), QMessageBox::Cancel);
}
else QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("ajout non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

}



//void livraison::on_lineEdit_ID_cursorPositionChanged(int arg1, int arg2)
//{

//}


void livraison::on_pushButton_4_clicked()
{
        QString id=ui->lineEdit_ID1_2->text();
        bool test=Gtmp.supprimer(id);

        if(test){

            //refresh
            ui->tableView->setModel(Gtmp.afficher());
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("Suppression effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("Suppression non effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

}



void livraison::on_pushButton_3_clicked()   //modifier
{

 QSqlQueryModel * modal=new   QSqlQueryModel;
 QSqlQuery *qry=new QSqlQuery;
 //qry->prepare("select id from livraison");
 //qry->exec();

 modal->setQuery(*qry);
  QString id=ui->lineEdit_ID1_2->text();
 //QString id=ui->lineEdit_ID_2->text();
 QString adresse=ui->lineEdit_Adresse_2->text();
 QString prix=ui->lineEdit_Prix_2->text();
 Glivraison gl(id,adresse,prix);
 bool test=gl.modifier();
 QMessageBox msgBox;

 if(test)
 {
     msgBox.setText("modification avec succés");

             ui->tableView->setModel(gl.afficher());

 }
 else
     msgBox.setText("modification avec succés");
 msgBox.exec();
 }



void livraison::on_checkBox_2_clicked()
{

    ui->tableView->setModel(Gtmp.tri_croissant_prix()) ;


}

void livraison::on_checkBox_3_clicked()
{
    ui->tableView->setModel(Gtmp.tri_croissant_adresse()) ;

}

void livraison::on_checkBox_8_clicked()
{
   ui->tableView->setModel(Gtmp.tri_decroissant_prix()) ;
}

void livraison::on_checkBox_7_clicked()
{
    ui->tableView->setModel(Gtmp.tri_decroissant_adresse()) ;

}

void livraison::on_tableView_activated(const QModelIndex &index)
{
    QString id=ui->tableView->model()->data(index).toString();
QSqlQuery qry;
qry.prepare("select * from livraison where id=:id");
qry.bindValue(":id",id);

if (qry.exec())
{
        while(qry.next())
        {
            ui->lineEdit_ID1_2->setText((qry.value(0).toString()));          
            ui->lineEdit_Adresse_2->setText((qry.value(1).toString()));
              ui->lineEdit_Prix_2->setText((qry.value(2).toString()));
        }
}
else
{
    QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}
}

void livraison::on_lineEdit_recherche_textChanged(const QString &arg1)
{
     //refresh
     ui->tableView->setModel(Gtmp.afficher());
     ui->tableView->setModel(Gtmp.rechercher(arg1));

}

void livraison::on_pushButton_5_clicked()
{


        QPdfWriter fichier_pdf("G:\\ListeLivraisons.pdf");//C:\Users\Mega-PC\Desktop

       QPainter painter(&fichier_pdf);
       int i = 4000;

       QImage img("G:\\Integration_QT\\Master-Print\\App_LOGO.png");
                 QPoint imageCoordinates(200,200);
                 painter.drawImage(imageCoordinates,img);

                 QString  d_info=QDateTime::currentDateTime().toString();

              painter.setPen(Qt::red);
              painter.setFont(QFont("Time New Roman", 25));
              painter.drawText(3000,1400,"Liste Des Livraisons");
              painter.setPen(Qt::black);
              painter.setFont(QFont("Time New Roman", 15));
              painter.drawRect(100,100,9400,2500);
              painter.drawRect(100,3000,9400,500);
              painter.setFont(QFont("Time New Roman", 9));
              painter.drawText(400,3300,"Identifiant");
              painter.drawText(1350,3300,"Adresse livraison");
              painter.drawText(2200,3300,"      Prix livraison");
              painter.drawText(3400,3300,"date livraison");
              painter.drawRect(100,8000,9400,500);
                                painter.drawText(3400,8300,d_info);


              QSqlQuery query;
              query.prepare("select * from livraison");
              query.exec();
              while (query.next())
              {
                  painter.drawText(400,i,query.value(0).toString());
                  painter.drawText(1350,i,query.value(1).toString());
                  painter.drawText(2300,i,query.value(2).toString());
                  painter.drawText(3400,i,query.value(3).toString());



                 i = i + 350;
              }
              QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
              QObject::tr("PDF Enregistré.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }



void livraison::on_pushButton_7_clicked() //map
{
    hide();
    map= new QQuickWidget();
    map->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
   /*QQuickWidget * map = new QQuickWidget();
    d->showNormal(map->setSource(QUrl(QStringLiteral("qrc:/map.qml")))))
    //map->show();
    //ui->quickWidget->setSource();
    //ui->quickWidget->show();*/
}


/*void livraison::on_pushButton_6_clicked()//excel
{
    QTableView *table;
                       table = ui->tableView;

                       QString filters("CSV files (.xlsx);;All files (.*)");
                       QString defaultFilter("CSV files (*.xlsx)");
                       QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                          filters, &defaultFilter);
                       QFile file(fileName);

                       QAbstractItemModel *model =  table->model();
                       if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                           QTextStream data(&file);
                           QStringList strList;
                           for (int i = 0; i < model->columnCount(); i++) {
                               if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                                   strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                               else
                                   strList.append("");
                           }
                           data << strList.join(";") << "\n";
                           for (int i = 0; i < model->rowCount(); i++) {
                               strList.clear();
                               for (int j = 0; j < model->columnCount(); j++) {

                                   if (model->data(model->index(i, j)).toString().length() > 0)
                                       strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                                   else
                                       strList.append("");
                               }
                               data << strList.join(";") + "\n";
                           }
                           file.close();
                           QMessageBox::information(nullptr, QObject::tr("Export excel"),
                                                     QObject::tr("Export avec succes .\n"
                                                                 "Click OK to exit."), QMessageBox::Ok);
                       }
}
*/
void livraison::on_pushButton_6_clicked()

    {
    QTableView *table;
       table = ui->tableView;

       QString filters("CSV files (*.csv);;All files (*.*)");
       QString defaultFilter("CSV files (*.csv)");
       QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                          filters, &defaultFilter);
       fileName.append(".csv");
       QFile file(fileName);

       QAbstractItemModel *model =  table->model();
       if (file.open(QFile::WriteOnly | QFile::Truncate)) {
           QTextStream data(&file);
           QStringList strList;
           for (int i = 0; i < model->columnCount(); i++) {
               if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                   strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
               else
                   strList.append("");
           }
           data << strList.join(";") << "\n";
           for (int i = 0; i < model->rowCount(); i++) {
               strList.clear();
               for (int j = 0; j < model->columnCount(); j++) {

                   if (model->data(model->index(i, j)).toString().length() > 0)
                       strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                   else
                       strList.append("");
               }
               data << strList.join(";") + "\n";
           }
           file.close();
           QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
       }}


void livraison::on_pushButton_8_clicked()
{
    QTableView *table;
       table = ui->tableView;

       QString filters("CSV files (*.csv);;All files (*.*)");
       QString defaultFilter("CSV files (*.csv)");
       QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                          filters, &defaultFilter);
       fileName.append(".csv");
       QFile file(fileName);

       QAbstractItemModel *model =  table->model();
       if (file.open(QFile::WriteOnly | QFile::Truncate)) {
           QTextStream data(&file);
           QStringList strList;
           for (int i = 0; i < model->columnCount(); i++) {
               if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                   strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
               else
                   strList.append("");
           }
           data << strList.join(";") << "\n";
           for (int i = 0; i < model->rowCount(); i++) {
               strList.clear();
               for (int j = 0; j < model->columnCount(); j++) {

                   if (model->data(model->index(i, j)).toString().length() > 0)
                       strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                   else
                       strList.append("");
               }
               data << strList.join(";") + "\n";
           }
           file.close();
           QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
       }
}


/*void livraison::on_quickWidget_sceneGraphError(const QQuickWindow::SceneGraphError &error, const QString &message)
{

}*/

void livraison::on_pushButton_2_clicked()
{
    accueil a;
    a.setData(nom_u,role);
    hide();
    a.setModal(true);
    a.exec();
}
