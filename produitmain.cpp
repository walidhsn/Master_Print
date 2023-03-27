#include "produitmain.h"
#include "ui_produitmain.h"
#include "produit.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QPdfWriter>
#include <QPainter>
#include "QZXing.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QDateTime>
#include <QGraphicsPixmapItem>
#include <QThread>
#include <accueil.h>
produitmain::produitmain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::produitmain)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);
    ui->TableAfficher->setModel(ptmp.afficher());
    ui->lineEdit_id_ajouter->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_qte_ajouter->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_type_ajouter->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]*"),this));
    ui->lineEdit_id_modifier->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_qte_modifier->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_type_modifier->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]*"),this));
    popUp = new PopUp();
    /*QString data = "text to be encoded";
    QImage barcode = QZXing::encodeData(data);

    QGraphicsScene *graphic = new QGraphicsScene(this);
    graphic->addPixmap( QPixmap::fromImage(barcode));
    ui->graphicsView->setScene(graphic);*/

    arduino = new seriallink;
    arduino->openConnection();
    connect(arduino,&seriallink::gotNewData,this,&produitmain::updateGUI);
    QPixmap test;
    QPixmap limit;
    QPixmap limit2;
    test.load("G:\\Integration_QT\\Master-Print\\img2.jpg");
    limit.load("G:\\Integration_QT\\Master-Print\\img1.png");
   // limit2.load("C:/Users/lamlo/Desktop/Projet Qt/limite2");
    testt = new QGraphicsPixmapItem(test);
    //testt->setScale(0.1);
    testt->setPos(120,330);
    //testt->setBoundingRegionGranularity(0);
    //testt->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);

    limitt = new QGraphicsPixmapItem(limit);
    //limitt->setScale(0.1);
    limitt->setPos(100,300);
    limitt->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);

    /*limitt2 = new QGraphicsPixmapItem(limit2);
    //limitt2->setScale(0.1);
    limitt2->setPos(400,0);
    limitt2->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);*/
    //testt->boundingRect();
    graphic2 = new QGraphicsScene(this);
    graphic2->setSceneRect(0,0,400,400);
    graphic2->addItem(testt);
    graphic2->addItem(limitt);
    //graphic2->addItem(limitt2);
   //testt->setBoundingRegionGranularity);
   // graphic2->setIte();
    ui->graphicsView_ard->setScene(graphic2);

}

produitmain::~produitmain()
{
    delete ui;
}


void produitmain::on_pushButton_ajouter_clicked()
{
    int id=ui->lineEdit_id_ajouter->text().toInt();
    int qte=ui->lineEdit_qte_ajouter->text().toInt();
    //QString date=ui->lineEdit_date_ajouter->text();
    QString type=ui->lineEdit_type_ajouter->text();


    Produit p(qte,id,type);

    bool test=p.ajouter();
    if(test){
        popUp->setPopupText("ajouter!!");
        popUp->show();

        ui->TableAfficher->setModel(ptmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("Ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("Ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}


void produitmain::on_pushButton_supp_id_clicked()
{
    int id = ui->lineEdit_id_supp->text().toInt();
    bool test=ptmp.supprimer(id);

    if(test){
        ui->TableAfficher->setModel(ptmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("Suppression effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("Suppression non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void produitmain::on_pushButton_modifier_2_clicked()
{
    QSqlQueryModel * modal=new   QSqlQueryModel;
     QSqlQuery *qry=new QSqlQuery;
     qry->prepare("select id from Produit");
     qry->exec();

     modal->setQuery(*qry);

     int id=ui->lineEdit_id_modifier->text().toInt();
     int qte=ui->lineEdit_qte_modifier->text().toInt();
     //QString date=ui->lineEdit_date_ajouter->text();
     QString type=ui->lineEdit_type_modifier->text();
     Produit p(qte,id,type);
     bool test=p.modifier();
     QMessageBox msgBox;

     if(test)
     {
         ui->TableAfficher->setModel(ptmp.afficher());
         msgBox.setText("modification avec succés");

                 //ui->TableAfficher->setModel(p.afficher());

     }
     else
         msgBox.setText("modification echoué");
     msgBox.exec();
}


void produitmain::on_Tri_ident_clicked()
{

    ui->TableAfficher->setModel(ptmp.tri_croissant_ident());
}

void produitmain::on_Tri_ident_4_clicked()
{
    ui->TableAfficher->setModel(ptmp.tri_decroissant_ident());
}




void produitmain::on_TableAfficher_activated(const QModelIndex &index)
{
    //setParent(this);
    QString id=ui->TableAfficher->model()->data(index).toString();
   QSqlQuery qry;
   qry.prepare("select * from Produit where ident=:id");
   qry.bindValue(":id",id);

   if (qry.exec())
   {
           while(qry.next())
           {
               ui->lineEdit_id_modifier->setText((qry.value(0).toString()));
               ui->lineEdit_type_modifier->setText((qry.value(1).toString()));
               ui->lineEdit_qte_modifier->setText((qry.value(2).toString()));
               QString data = "ID:" + qry.value(0).toString() + "\n" + "Type:" + qry.value(1).toString() + "\n" + "Needed Quantity:" + qry.value(2).toString() ;
               QImage barcode = QZXing::encodeData(data);


               QGraphicsScene *graphic = new QGraphicsScene(this);

               graphic->addPixmap( QPixmap::fromImage(barcode));
               ui->graphicsView->setScene(graphic);
               //graphic2->addPixmap(test);



           }
   }
   else
   {
       QMessageBox::critical(this,tr("error::"),qry.lastError().text());
   }

}

void produitmain::on_recherche_textChanged(const QString &arg1)
{
    //refresh
    ui->TableAfficher->setModel(ptmp.afficher());
    ui->TableAfficher->setModel(ptmp.rechercher(arg1));
}

void produitmain::on_pushButton_pdf_clicked()
{
    QPdfWriter fichier_pdf("G:\\ListeProduits.pdf");
    QString  d_info=QDateTime::currentDateTime().toString();

           QPainter painter(&fichier_pdf);
           int i = 4000;
           painter.setFont(QFont("Time New Roman", 9));
                  painter.drawRect(100,8000,9400,500);
                  painter.drawText(7300,0,d_info);
                  painter.setPen(Qt::red);
                  painter.setFont(QFont("Time New Roman", 25));
                  painter.drawText(3000,1400,"Liste Des Produits");
                  painter.setPen(Qt::black);

                  painter.setFont(QFont("Time New Roman", 15));
                  painter.drawRect(100,100,9400,2500);
                  painter.drawRect(100,3000,9400,500);
                  painter.setFont(QFont("Time New Roman", 9));
                  painter.drawText(400,3300,"Identifiant");
                  painter.drawText(1350,3300,"Type");
                  painter.drawText(2200,3300,"Quantité");
                  painter.drawText(3400,3300,"Date Ajout Produit");
                 // painter.setFont(QFont("Time New Roman", 9));

                  QImage img("G:\\Integration_QT\\Master-Print\\App_LOGO.png");
                  QPoint imageCoordinates(10,200);
                  painter.drawImage(imageCoordinates,img);



                  QSqlQuery query;
                  query.prepare("select * from Produit");
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
void produitmain::updateGUI(QByteArray data){
     QSqlQuery query;
    ui->lcd_byte_received->display(ui->lcd_byte_received->value()+data.size());
    if(data.toStdString()=="on" || data.toStdString()=="of"){
        ui->lineEdit_ard->setText(data);
    }
    else{
    int X;
    int Y;
    X=testt->pos().x();
    if(data.toInt()<0){
        Y=330;
        graphic2->update();
        testt->setPos(X,Y);
        graphic2->update();

        //QString res = QString::number(id_prod);

              query.prepare("UPDATE  Produit set disponibility=:disp where type like 'papier' ");
              //query.bindValue(":id",res);
              //query.bindValue(":qte",qte_prod);
              query.bindValue(":disp","OUI");
              query.exec();


    }
    if(data.toInt()>5){
     Y=330-data.toInt()-80;
    //X=testt->pos().x()+(testt->pixmap().size().width()/2);
    //Y=testt->pos().y()+data.toInt()+(testt->pixmap().size().height()/2);
    /*if(data.toInt()>0){
    X=testt->pos().x();
    Y=testt->pos().y()+data.toInt()+100;
    }
    else if(data.toInt()<0){
        X=testt->pos().x();
        Y=testt->pos().y()+data.toInt()-10;
    }

    //X=testt->boundingRect().x();
    //Y=testt->boundingRect().y()+data.toInt();
*/
        if(X < 500 && Y<400 && X>0 && Y>0){
    //if(testt->collidingItems().isEmpty()){
            graphic2->update();
            testt->setPos(X,Y);
            graphic2->update();

            //QString res = QString::number(id_prod);



        }
        query.prepare("UPDATE  Produit set disponibility=:disp where type like 'papier' ");
        //query.bindValue(":id",res);
        //query.bindValue(":qte",qte_prod);
        query.bindValue(":disp","NON");
        query.exec();
    }
    //else {
      //  testt->setPos(200,200);
    //}
   // arduino->startTimer(1000);

    //ui->graphicsView_ard->setScene(graphic2);
    /*if(data.toInt()>0 && X < 500 && Y<400 && X>0 && Y>0){
        X=testt->pos().x();
        Y=testt->pos().y()+10;
        graphic2->update();
        testt->setPos(X,Y);
        graphic2->update();
    }
    else if(data.toInt()<0 && X < 500 && Y<400 && X>0 && Y>0){
        X=testt->pos().x();
        Y=testt->pos().y()-10;
        graphic2->update();
        testt->setPos(X,Y);
        graphic2->update();
    }*/
    //ui->TableAfficher->setModel(ptmp.afficher());
   arduino->_serial.flush();
  }
}

void produitmain::on_pushButton_blue_clicked()
{
    if (arduino->isWritable())
        arduino->write("b");
    else
        qDebug() << "couldn't write to serial!";
}



void produitmain::on_pushButton_simulation_clicked()
{
    if (arduino->isWritable())
        arduino->write("s");
    else
        qDebug() << "couldn't write to serial!";

}

void produitmain::on_pushButton_stop_clicked()
{
    if (arduino->isWritable())
        arduino->write("e");
    else
        qDebug() << "couldn't write to serial!";

}

void produitmain::on_tabWidget_crud_currentChanged(int index)
{
    ui->TableAfficher->setModel(ptmp.afficher());
}
void produitmain::on_pushButton_retour_clicked()
{
    accueil a;
    a.setData(nom_u,role);
    hide();
    a.setModal(true);
    a.exec();
}
