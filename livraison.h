#ifndef LIVRAISON_H
#define LIVRAISON_H
#include "glivraison.h"
#include "QMessageBox"
#include <QDialog>
#include <QtQuickWidgets>
namespace Ui {
class livraison;
}

class livraison : public QDialog
{
    Q_OBJECT

public:
    explicit livraison(QWidget *parent = nullptr);
    ~livraison();
     QString role,nom_u;
private slots:
    void on_pushButton_clicked();

    void on_lineEdit_ID_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_8_clicked();

    void on_checkBox_7_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_lineEdit_recherche_textChanged(const QString &arg1);

    void on_lineEdit_recherche_returnPressed();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();
    //void on_quickWidget_sceneGraphError(const QQuickWindow::SceneGraphError &error, const QString &message);

    void on_pushButton_2_clicked();

private:
    Ui::livraison *ui;
    Glivraison Gtmp;
    QQuickWidget * map;
};

#endif // LIVRAISON_H
