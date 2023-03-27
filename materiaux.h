#ifndef MATERIAUX_H
#define MATERIAUX_H
#include "materiel.h"
#include <QDialog>

#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPdfWriter>
#include <QFile>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QDataStream>
namespace Ui {
class materiaux;
}

class materiaux : public QDialog
{
    Q_OBJECT

public:
    explicit materiaux(QWidget *parent = nullptr);
    ~materiaux();
     QString role,nom_u;
private slots:
    void sendMail();
    void mailSent(QString);

    void on_sendBtn_clicked();

    void on_pushButton_5_clicked();


    void on_pushButton_6_clicked();




    void on_recherche_textChanged(const QString &arg1);

    void on_checkBox_4_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_9_clicked();

    void on_checkBox_5_clicked();

    void on_checkBox_6_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::materiaux *ui;
    materiel mat;
    QString selected;



};

#endif // MATERIAUX_H
