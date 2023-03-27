#ifndef EMPLOYE_H
#define EMPLOYE_H
#include "employes.h"
#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class employe;
}


class employe : public QDialog
{
    Q_OBJECT

public:
    explicit employe(QWidget *parent = nullptr);
    ~employe();

private slots:
    void on_ajouter_clicked();

    void on_supprimer_clicked();

    void on_modifier_clicked();

    void on_annuler_clicked();

    void on_refresh_clicked();

    void on_tab_emp_activated(const QModelIndex &index);

    void on_radioButton_tri_nom_clicked();

    void on_radioButton_tri_prenom_clicked();

    void on_radioButton_tri_salaire_clicked();

    void on_radioButton_tri_fonction_clicked();

    void on_PDF_clicked();

    void on_lineEdit_rec_textChanged(const QString &arg1);

    void on_lancerChat_clicked();

    void on_pushButton_clicked();

public:
    void setData(QString data);
    QString role,nom_u;
private:
    Ui::employe *ui;
    employes etmp;

};

#endif // EMPLOYE_H
