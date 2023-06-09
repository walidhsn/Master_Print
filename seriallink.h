#ifndef SERIALLINK_H
#define SERIALLINK_H

#include <QObject>
#include <QSerialPort>
class seriallink : public QObject
{
    Q_OBJECT
public:
    explicit seriallink(QObject *parent = nullptr);
    ~seriallink();


    void openConnection();
    void closeConnection();
    void write(const char* messageToWrite);
    bool isOpen();
    bool isWritable();
    //void clear();

private slots:
    void newData();
signals:
    void gotNewData(QByteArray data);
public:
    QSerialPort _serial;

};

#endif // SERIALLINK_H
