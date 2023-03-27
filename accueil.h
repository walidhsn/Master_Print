#ifndef ACCUEIL_H
#define ACCUEIL_H

#include <QDialog>

namespace Ui {
class accueil;
}

class accueil : public QDialog
{
    Q_OBJECT

public:
    explicit accueil(QWidget *parent = nullptr);
    ~accueil();

private slots:
    void on_pushButton_employes_clicked();

    void on_pushButton_commandes_clicked();

    void on_pushButton_materiaux_clicked();

    void on_pushButton_livraisons_clicked();

    void on_pushButton_clients_clicked();

    void on_pushButton_produits_clicked();

public:
    void setData(QString nomU,QString typeU);
    QString role,nom_u;
private:
    Ui::accueil *ui;
};

#endif // ACCUEIL_H
