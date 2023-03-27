#include "scenario_02.h"
#include "ui_scenario_02.h"

scenario_02::scenario_02(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scenario_02)
{
    ui->setupUi(this);
    buffer ="";
    count=0;
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
     ui->tableView_temperature->setModel(afficher_temp());
}
void scenario_02::update_label()
{
    // INPUT :
    QStringList bufferSplit= buffer.split(",");
    if(bufferSplit.length()<5)
    {
        data=A.read_from_arduino();
        buffer += QString::fromStdString(data.toStdString());
    }
    else
    {
        if(bufferSplit[3]=="1")

            ui->label_etat->setText("ON"); // si les données reçues de arduino via la liaison série sont égales à 1
        // alors afficher ON

        else if (bufferSplit[3]=="0")

            ui->label_etat->setText("OFF");   // si les données reçues de arduino via la liaison série sont égales à 0
         //alors afficher ON
        scenario_02::update_lcd(bufferSplit[0],bufferSplit[1],bufferSplit[2]);
        buffer="";
        // Connexion avec Base de Donnees :
        if(!count)
        {
            float humidity=bufferSplit[0].toFloat(),temp=bufferSplit[1].toFloat(),heat=bufferSplit[2].toFloat();
            int state=bufferSplit[3].toInt();
            date_temp_01= QDateTime::currentDateTime();
            bool test = scenario_02::insert_temp(humidity,temp,heat,state,date_temp_01);
            if(test)
            {
                QSqlQuery *m = search(date_temp_01);
                if(m->next())
                {
                    id_temp = m->value(0).toInt();
                    qDebug()<<id_temp;
                    count=1;
                }
            }
            else
            {
                qDebug()<<"--error d'insertion";
            }
        }
        else
        {
            //Update Last Variables :
            float humidity=bufferSplit[0].toFloat(),temp=bufferSplit[1].toFloat(),heat=bufferSplit[2].toFloat();
            int state=bufferSplit[3].toInt();
            QDateTime date_02= QDateTime::currentDateTime(); // Update date
            bool test = scenario_02::modifier_temp(id_temp,humidity,temp,heat,state,date_02);
            if(test)
            {
                qDebug() << " - Update = TRUE";
                ui->tableView_temperature->setModel(afficher_temp());
            }
            else qDebug() << " - Update = False";
        }

    }

}
scenario_02::~scenario_02()
{
    delete ui;
    A.close_arduino();
}
// OutPut :
void scenario_02::on_pushButton_clicked()
{
     A.write_to_arduino("1"); //envoyer 1 à arduino
}

void scenario_02::on_pushButton_2_clicked()
{
     A.write_to_arduino("0"); //envoyer 0 à arduino
}
//--------------------------------------------------|
void scenario_02::update_lcd(const QString Humidity,const QString temp,const QString heat)
{
    ui->lcdNumber_Humidity->display(Humidity);
    ui->lcdNumber_temp->display(temp);
    ui->lcdNumber_heat->display(heat);
}
bool scenario_02::insert_temp(float humidity,float temp,float heat,int state,QDateTime date_temp)
{
    QSqlQuery query;
    QString Hu = QString::number(humidity);
    QString Te = QString::number(temp);
    QString He = QString::number(heat);
    QString St = QString::number(state);
    query.prepare("INSERT INTO temperature (humidity,temperature,heat,etat,date_temp)"
                  "VALUES(:humidity,:temperature,:heat,:etat,:date_temp)");
    query.bindValue(":humidity",Hu);
    query.bindValue(":temperature",Te);
    query.bindValue(":heat",He);
    query.bindValue(":etat",St);
    query.bindValue(":date_temp",date_temp);
    return query.exec();
}
QSqlQuery * scenario_02::search(QDateTime source)
{
    QSqlQuery * model = new QSqlQuery();
    model->prepare("select id_temp from temperature where date_temp=:date");
    model->bindValue(":date",source);
    model->exec();
  return model;
}
QSqlQueryModel * scenario_02::afficher_temp()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from temperature");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Humidite"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Temperature"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Tempe_Ressentie"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date"));
    return model;
}
bool scenario_02::modifier_temp(int source,float humidity,float temp,float heat,int state,QDateTime date_temp)
{
    QSqlQuery query;
    QString Hu = QString::number(humidity);
    QString Te = QString::number(temp);
    QString He = QString::number(heat);
    QString St = QString::number(state);
    query.prepare("UPDATE temperature SET humidity=:humidity,temperature=:temperature,heat=:heat,etat=:etat,date_temp=:date_temp WHERE id_temp=:id_temp;");
    query.bindValue(":humidity",Hu);
    query.bindValue(":temperature",Te);
    query.bindValue(":heat",He);
    query.bindValue(":etat",St);
    query.bindValue(":date_temp",date_temp);
    query.bindValue(":id_temp",source);
    return query.exec();
}

