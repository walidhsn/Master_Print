#ifndef PRODUITMAIN_H
#define PRODUITMAIN_H
#include "produit.h"
#include <QDialog>
#include "popup.h"
#include "seriallink.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
namespace Ui {
class produitmain;
}

class produitmain : public QDialog
{
    Q_OBJECT

public:
    explicit produitmain(QWidget *parent = nullptr);
    ~produitmain();
     QString role,nom_u;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_ajouter_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_supp_id_clicked();

    void on_pushButton_modifier_2_clicked();

    void on_checkBox_2_clicked();

    void on_Tri_ident_clicked();

    void on_Tri_ident_4_clicked();

    void on_rechercher_clicked();

    void on_comboBox_id_activated(int index);

    void on_TableAfficher_activated(const QModelIndex &index);

    void on_recherche_textChanged(const QString &arg1);

    void on_pushButton_pdf_clicked();

    void updateGUI(QByteArray data);
    void on_p_ledOn_clicked();

    void on_p_ledOff_clicked();

    void on_pushButton_clicked(bool checked);

    void on_pushButton_2_clicked();

    void on_pushButton_blue_clicked();

    void on_pushButton_simulation_clicked();

    void on_pushButton_stop_clicked();

    void on_tabWidget_crud_currentChanged(int index);

    void on_pushButton_retour_clicked();

private:
    Ui::produitmain *ui;
    Produit ptmp;
    PopUp *popUp;
    seriallink *arduino;
    QGraphicsPixmapItem *testt;
    QGraphicsPixmapItem *limitt;
    QGraphicsPixmapItem *limitt2;
    QGraphicsScene *graphic2;
};

#endif // PRODUITMAIN_H
