#ifndef SCENARIO_02_H
#define SCENARIO_02_H
#include "arduino.h"
#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDateTime>

namespace Ui {
class scenario_02;
}

class scenario_02 : public QDialog
{
    Q_OBJECT

public:
    explicit scenario_02(QWidget *parent = nullptr);
    ~scenario_02();
    bool insert_temp(float,float,float,int,QDateTime);
    QSqlQuery * search(QDateTime source);
    QSqlQueryModel * afficher_temp();
    bool modifier_temp(int source,float,float,float,int,QDateTime);
private slots:
    void update_label();   // slot permettant la mise à jour du label état de la lampe 1,
    // ce slot est lancé à chaque réception d'un message de Arduino
    void update_lcd(const QString Humidity,const QString temp,const QString heat); // UPDATE THE LCD
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::scenario_02 *ui;

    QByteArray data; // variable contenant les données reçues
    QDateTime date_temp_01; // Date de Temperature dans la 1ére insertion
    Arduino A; // objet temporaire
    QString buffer; // tableau des valeur recçues
    int count,id_temp; // Variable to count the first insert
};

#endif // SCENARIO_02_H
