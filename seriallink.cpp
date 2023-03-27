#include "seriallink.h"
#include <QDebug>
seriallink::seriallink(QObject *parent) : QObject(parent)
{
    _serial.setPortName("COM4");
    _serial.setBaudRate(QSerialPort::Baud9600);
    _serial.setDataBits(QSerialPort::Data8);
    _serial.setParity(QSerialPort::NoParity);
    _serial.setStopBits(QSerialPort::OneStop);
    _serial.setFlowControl(QSerialPort::NoFlowControl);


    connect(&_serial,&QSerialPort::readyRead,this,&seriallink::newData);
}
seriallink::~seriallink(){
    closeConnection();
}
void seriallink::openConnection(){
    if(!_serial.open(QIODevice::ReadWrite))
        qDebug() << "connexion impossible";
    else
        qDebug() << "connexion ok";
}

void seriallink::write(const char *messageToWrite){
    _serial.write(messageToWrite);
}
void seriallink::closeConnection(){
    _serial.close();
}

bool seriallink::isOpen(){
    return _serial.isOpen();
}
bool seriallink::isWritable(){
    return _serial.isWritable();
}
void seriallink::newData(){
   // int trouve=0;
    /*QByteArray serialInData;
    //
    //while(trouve!=1){
    serialInData = _serial.readAll();
    //
    if(serialInData[0] != '<' || serialInData[serialInData.length()] != '>')
    {

        //ErrorMessage("missing"); //this is my custom error debugger which shows message
        _serial.clear();

    }
    else{
       emit gotNewData(serialInData);
    }*/


    if(_serial.isReadable()){
        emit gotNewData(_serial.readAll());
    }

}
/*void seriallink::clear(){
    _serial.clear();
}*/
