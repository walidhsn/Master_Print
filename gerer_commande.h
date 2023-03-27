#ifndef GERER_COMMANDE_H
#define GERER_COMMANDE_H
#include <commande.h>
#include <QDialog>

namespace Ui {
class gerer_commande;
}

class gerer_commande : public QDialog
{
    Q_OBJECT

public:
    explicit gerer_commande(QWidget *parent = nullptr);
    ~gerer_commande();
     QString role,nom_u;
private slots:
    void on_pushButton_historique_clicked();

    void on_pushButton_Ajouter_clicked();

    void on_pushButton_refresh_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_supprimer_clicked();

    void on_pushButton_modifier_clicked();

    void on_pushButton_modifier_2_clicked();

    void on_pushButton_annuler_clicked();

    void on_radioButton_id_clicked();

    void on_radioButton_date_clicked();

    void on_radioButton_croissant_clicked();

    void on_radioButton_decroissant_clicked();

    void on_radioButton_5_clicked();

    void on_lineEdit_rechercher_textChanged(const QString &arg1);

    void on_radioButton_6_clicked();

    void on_radioButton_7_clicked();

    void on_radioButton_8_clicked();

    void on_radioButton_clicked();

    void on_radioButton_9_clicked();

    void on_radioButton_13_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_10_clicked();



    void on_radioButton_14_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_11_clicked();

    void on_radioButton_15_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_12_clicked();

    void on_radioButton_16_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_tabWidget_commande_tabBarClicked(int index);

    void on_pushButton_supprimerH_a_clicked();

    void on_pushButton_supprimer_H_m_clicked();

    void on_pushButton_supprimer_H_s_clicked();

    void on_pushButton_refresh_h_A_clicked();

    void on_pushButton_refresh_h_M_clicked();

    void on_pushButton_refresh_h_S_clicked();

    void on_pushButton_exportPdf_clicked();

    void on_pushButton_imprimer_clicked();

    void on_pushButton_pdf_h_A_clicked();

    void on_pushButton_pdf_h_M_clicked();

    void on_pushButton_pdf_h_S_clicked();

    void on_pushButton_imprimer_h_A_clicked();

    void on_pushButton_imprimer_h_M_clicked();

    void on_pushButton_imprimer_h_s_clicked();

    void on_pushButton_clicked();

    void on_pushButton_temperature_clicked();

    void on_pushButton_retour_clicked();

private:
    Ui::gerer_commande *ui;
    Commande com;
    QString selected;

};

#endif // GERER_COMMANDE_H
