#include "materiaux.h"
#include "ui_materiaux.h"
#include "materiel.h"
#include <QMessageBox>
#include<QDesktopServices>
#include "smtp.h"
#include <accueil.h>


materiaux::materiaux(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::materiaux)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);
    ui->tableView->setModel (mat.afficher ());
    selected="";

    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));

}

materiaux::~materiaux()
{
    delete ui;
}


//ajouter

void materiaux::on_pushButton_5_clicked()
{
    QString nom=ui->nom->text();
    QString heure=ui->heure->text();
    QDate maintenance=ui->maintenance->date();

    int nombre=ui->nombre->text().toInt();
    int cout=ui->cout->text().toInt();
    int id=ui->id->text().toInt();

    materiel m (nom,heure,maintenance,nombre,cout,id);

     bool test=m.ajouter() ;

     if(test)
     {
ui->tableView->setModel(mat.afficher());

         QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Ajout effectué\n"
                                  "click Cance to exit."), QMessageBox::Cancel);
     }


     else

         QMessageBox::critical (nullptr, QObject::tr("Not OK"),
                     QObject::tr("Ajout non effectué.\n to exit.click Cancel"),QMessageBox::Cancel);

}


//modifier
void materiaux::on_pushButton_6_clicked()
{
    QString nom=ui->nom4->text();
    QString heure=ui->heure4->text();
    QDate date=ui->date4->date();

    int nombre=ui->nb4->text().toInt();
    int cout=ui->cout4->text().toInt();
    int id=ui->id4->text().toInt();
    materiel m (nom,heure,date,nombre,cout,id);

        bool    test1=m.modifier(id,nombre,cout,nom,heure,date);

 //si id existe on modifie sinon msg erreur

        if (test1)
              {
            ui->tableView->setModel(mat.afficher());

                  QMessageBox::information(nullptr,QObject::tr("OK"),
                                       QObject::tr("modification établie"),
                                       QMessageBox::Ok);}
              else{
              QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                      QObject::tr("modification non établie"),
                                      QMessageBox::Cancel);}
}
/*
//supprimer
void materiaux::on_pushButton_10_clicked()
{
    materiel m1; m1.setid(ui->idsup->text().toInt());
    bool test=m1.supprimer(m1.getid());
    QMessageBox msgBox;
    if(test)
    {
        ui->tableView->setModel(mat.afficher());
        msgBox.setText("suppression avec succes.");
    }
    else
          msgBox.setText("echec d'ajout");
                msgBox.exec();

}
*/
void materiaux::on_tableView_activated(const QModelIndex &index)
{

    selected=ui->tableView->model()->data(index).toString();
    qDebug()<< selected;

    int id=ui->tableView->model()->data(index).toInt();

    QSqlQuery query;
    query.prepare("select * from MATERIAUX where ID =:id");
    query.bindValue(":id",id);
    if(query.exec())
    {
        while(query.next())
        {
            ui->id4->setText(query.value(0).toString());
            ui->nom4->setText(query.value(1).toString());
             ui->nb4->setText(query.value(2).toString());
            ui->date4->setDate(query.value(3).toDate());

            ui->cout4->setText(query.value(4).toString());
            ui->heure4->setText(query.value(5).toString());

        }
    }
}





void materiaux::on_recherche_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
      QSqlQuery   *query= new QSqlQuery();
      query->prepare("SELECT * FROM MATERIAUX WHERE ID LIKE '"+arg1+"%' or HEURE LIKE '"+arg1+"%' or NOM LIKE '"+arg1+"%' or MAINTENANCE LIKE '"+arg1+"%' or COUT LIKE '"+arg1+"%'");
       query->exec();
       if (query->next()) {
       model->setQuery(*query);
       ui->tableView->setModel(model);
       }
       else {
           QMessageBox::information(nullptr, QObject::tr("Rechercher"),
                           QObject::tr("Aucun résultat trouvé !.\n"
                                       "Cliquez sur OK pour quitter."), QMessageBox::Ok);
           ui->recherche->clear();}
}



//suppression
void materiaux::on_pushButton_clicked()
{
    if(selected!="")
    {
        bool test=mat.supprimer(selected);
        if(test)
        {
            ui->tableView->setModel(mat.afficher());
            QMessageBox::information(nullptr, QObject::tr("Succès"),
                        QObject::tr("Supprimé avec succès.\n"
                                    "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
            selected="";
        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("Échoué"),
                        QObject::tr("ERREUR : La suppression a échoué. sélectionnez l'identifiant ou Cin Or (aucune colonne n'est sélectionnée ou la ligne n'existe pas)\n"
                                    "Cliquez sur Annuler pour Quitter."), QMessageBox::Cancel);
            selected="";
        }
    }
    else
    {
        QMessageBox::information(nullptr, QObject::tr("Sélectionner"),
                    QObject::tr("Veuillez sélectionner l'Id ou le Cin du client (Double clic).\n"
                                "Cliquez sur OK pour Quitter."), QMessageBox::Ok);
    }
}

//modification
void materiaux::on_pushButton_9_clicked()
{
    materiel m;
    int id=ui->id4->text().toInt();
    QString nom=ui->nom4->text();
    QString heure=ui->heure4->text();
    int nombre=ui->nb4->text().toInt();
    QDate date=ui->date4->date();
    int cout=ui->cout4->text().toInt();



        bool test=m.modifier(id,nombre,cout,nom,heure,date);
        if(test)
        {
            ui->tableView->setModel(mat.afficher());

            QMessageBox::information(nullptr,QObject::tr("OK"),
                    QObject::tr("Modification effectuée \n"
                                "Click cancel to exit."),QMessageBox::Cancel);

        }
        else{
            QMessageBox::critical(nullptr,QObject::tr("OK"),
                    QObject::tr("Modification non effectuée \n"
                                "Click cancel to exit."),QMessageBox::Cancel);
        }
}
//tri par nom
void materiaux::on_checkBox_4_clicked()
{
    ui->tableView->setModel(mat.tri_nom());

}
//tri par cout
void materiaux::on_checkBox_5_clicked()
{
    ui->tableView->setModel(mat.tri_cout());

}


void materiaux::on_checkBox_6_clicked()
{
    ui->tableView->setModel(mat.tri_date());

}

//pdf
void materiaux::on_pushButton_2_clicked()
{/*
    materiel M;
    M.genererPDF();
    QString link="C:/syrine/syrine.pdf";
    QDesktopServices::openUrl(QUrl(link));
    */
        QString strStream;
        QTextStream out(&strStream);

        const int rowCount = ui->tableView->model()->rowCount();
        const int columnCount = ui->tableView->model()->columnCount();

        out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg("strTitle")
            <<  "</head>\n"
            "<body bgcolor=#ffffff link=#5000A0>\n"

            "<img src="":/resources/App_LOGO.ico"" alt=""logo"" height=""90"" width=""90"">"
            "<center> <h2 style=""color:orange"">-Tableau Des Materiaux-</h2><br></br><br></br><br></br><table border=0.5 cellspacing=1 cellpadding=3>\n";

        // headers
        out << "<thead><tr bgcolor=""#333""><th><font color=""orange"">Ligne</font></th>";
        for (int column = 0; column < columnCount; column++)
            if (!ui->tableView->isColumnHidden(column))
                out << QString("<th><font color=""orange"">%1</font></th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
        out << "</tr></thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++)
        {
            out << "<tr><td bgcolor=""lightgray"">" << row + 1 << "</td>";
            for (int column = 0; column < columnCount; column++)
            {
                if (!ui->tableView->isColumnHidden(column))
                {
                    QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                    out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                }
            }
            out << "</tr>\n";
        }
        out <<  "</table> </center>\n"
            "</body>\n"
            "</html>\n";

        QString fileName = QFileDialog::getSaveFileName((QWidget * )0, "Sauvegarder en PDF", QString(), "*.pdf");
        if(fileName!="")
        {
            if (QFileInfo(fileName).suffix().isEmpty())
            {
                fileName.append(".pdf");
            }

            QPrinter printer (QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setPaperSize(QPrinter::A4);
            printer.setOutputFileName(fileName);

            QTextDocument doc;
            doc.setHtml(strStream);
            doc.setPageSize(printer.pageRect().size()); //This is necessary if you want to hide the page number
            doc.print(&printer);
        }
        QString link="C:/syrine/syrine.pdf";
        QDesktopServices::openUrl(QUrl(link));
}

void materiaux::sendMail()
{

    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void materiaux::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}


void materiaux::on_sendBtn_clicked()
{

}


void materiaux::on_pushButton_3_clicked()
{
    accueil a;
    a.setData(nom_u,role);
    hide();
    a.setModal(true);
    a.exec();
}
