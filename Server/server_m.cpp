#include "server_m.h"
#include"socket_m.h"
#include"socketthread.h"
#include<QMessageBox>
server_m::server_m()
{

    sql.open();
    sql.createtable();    //一台机子第一次运行时才运行这句
    online_user=new QStringList;

}
server_m::~server_m()
{
     sql.close();
}
void server_m::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<"有新的连接";
     socketthread * thread=new socketthread(socketDescriptor,online_user);
    thread->start();
}
