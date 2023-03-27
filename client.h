#ifndef CLIENT_H
#define CLIENT_H
#include "clients.h"
#include <QDialog>
#include <QString>
#include <QSqlQueryModel>
#include <QPaintEngine>
#include <QPainter>
#include <qpainter.h>
namespace Ui {
class client;

}

class client : public QDialog
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = nullptr);
    ~client();
     QString role,nom_u;
   // client();
private slots:
    void on_bouton_ajout_clicked();
    void on_bouton_supprimer_clicked();
    void on_table_client_activated(const QModelIndex &index);

    void on_bouton_modifier_clicked();


    void on_bouton_validerMod_clicked();

    void on_radioButton_croissant_clicked();

    void on_radioButton_decroissant_clicked();

    void on_radioButton_date_clicked();

    void on_recherche_textChanged(const QString &arg1);

    void on_bouton_PDF_clicked();

    void on_bouton_image_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::client *ui;
    Clients cl;
    QString selected;
};
//client cl;

#endif // CLIENT_H
