#include "socket_m.h"
#include<QByteArray>
#include<QDataStream>
socket_m::socket_m(qintptr p)
{
    this->setSocketDescriptor(p);
    this->connect(this,SIGNAL(disconnected()),this,SLOT(on_discon()));
}


void socket_m::on_discon()
{
    qDebug()<<"有一个客户端断开！";
}
