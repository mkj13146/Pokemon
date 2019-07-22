#include "tcpserver.h"
#include "ui_tcpserver.h"
#include "sql.h"

TcpServer::TcpServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    this->server=new server_m;
}

TcpServer::~TcpServer()
{
    delete ui;
    delete server;
}


void TcpServer::on_startBtn_clicked()
{
    if(!server->listen(QHostAddress::Any,8000))
    {
        qDebug()<<server->errorString();
        return;
    }
    else
    {
         qDebug()<<"开启服务器";
         ui->startBtn->setEnabled(false);
    }
}


