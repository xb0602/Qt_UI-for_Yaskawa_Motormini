#include "udp.h"
UDP::UDP(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
}
UDP::~UDP(){
    socket->close();
}

bool UDP::udpConnect(QHostAddress address, quint16 port){
    bool status = socket->bind(address, port);
    //bool status = socket->bind(QHostAddress(::Any, port))
    qDebug() << "Connect status: " << status;
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    return status;
}
void UDP::udpDisConnect(){
    socket->close();
}
void UDP::sendData(QHostAddress address, quint16 port, QByteArray data){
    socket->writeDatagram(data, address, port);
}

void UDP::readyRead()
{
    buffer.resize(socket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
    emit dataRecieveSignal();
}
QByteArray UDP::getUdpData(){
    return buffer;
}
