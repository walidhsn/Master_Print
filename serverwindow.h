#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QWidget>
#include <QDialog>
namespace Ui {
class ServerWindow;
}
class ChatServer;
class ServerWindow : public QDialog
{
    Q_OBJECT
    //Q_DISABLE_COPY(ServerWindow)
public:
    explicit ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow();

private:
    Ui::ServerWindow *ui;
    ChatServer *m_chatServer;
private slots:
    //void toggleStartServer();
    //void logMessage(const QString &msg);
};

#endif // SERVERWINDOW_H
