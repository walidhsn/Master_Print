#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "comptes.h"
#include "arduino.h"
#include "employe.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_refresh_users_clicked();

    void on_tab_users_activated(const QModelIndex &index);

    void on_modifierU_clicked();

    void on_supprimerU_clicked();

    void on_CreerCompte_clicked();

    void on_connexion_clicked();

    void on_confirmer_reset_clicked();

    void on_sauvegarder_mdp_clicked();

    void on_afficher_mdp_clicked();

private:
    Ui::MainWindow *ui;
    comptes cmpt;
    QByteArray data; // variable contenant les données reçues
    Arduino A; // objet temporaire

};
#endif // MAINWINDOW_H
