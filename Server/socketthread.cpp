#include "socketthread.h"
#include<QTime>


int readcount=0;
QSemaphore mutex(1),wrt(1);

QStringList name_list={"","李白","韩信","赵云","橘子","芈月","项羽","马克","狼狗"};
socketthread::socketthread(qintptr p, QStringList *online_user):ptr(p),user(online_user)
{
    qDebug()<<"建立新线程，p="<<p;     //QThread构造函数依然在 旧线程
    socket=new socket_m(this->ptr);
    myname="";
    connect(socket,SIGNAL(disconnected()),this,SLOT(onDisconnect()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}
socketthread::~socketthread()
{
    socket->abort();
    delete socket;
}
bool socketthread::checkSignIn(QString name,QString password)
{
    bool ret=sql.loguser(name,password);
    return ret;
}

bool socketthread::checkSignUp(QString name, QString password, QString pet)
{
    bool ret=sql.signup(name,password,pet);
    return ret;
}

void socketthread::onReadyRead()
{
    qDebug()<<"线程"<<ptr<<"收到消息";
    QString data=socket->readAll();
    QStringList list=data.split("#");
    bool ret=0;
    QString sendData=list[0];
    if(list[0]=="z")     //注册
    {
        ret=checkSignUp(list[1],list[2],list[3]);
        if(ret)
            sendData+="#true";
        else
            sendData+="#false";


    }
    else if(list[0]=="d")  //登录
    {
        if(user->indexOf(list[1])==-1)
        {
            ret=checkSignIn(list[1],list[2]);
            if(ret)
                sendData+="#true";
            else
                sendData+="#false";

            if(list[0]=="d"&&ret)
            {
                QStringList ulist=sql.get_data(list[1]);
                for(int i=0;i<ulist.size();i++)
                {
                    sendData+="#";
                    sendData+=ulist[i];
                }
                myname=list[1];             //登录成功，在线用户列表中添加某用户。
                wrt.acquire();
                user->append(myname);
                wrt.release();
            }
        }
        else
            sendData+="#reload";         //重复登陆

    }
    else if(list[0]=="a")               //请求所有用户
    {
        QStringList ulist=sql.get_user_list();
        sendData+="#";

        for(int i=0;i<ulist.size();i++)
        {
            sendData+=ulist[i];
            sendData+="*";
        }
    }
    else if(list[0]=="o")           //在线用户
    {
        //读取在线用户列表
        mutex.acquire();            //互斥访问
        readcount++;
        if(readcount == 1)
            wrt.acquire();
        mutex.release();

        QStringList ulist=*user;    //读操作
        sendData+="#";
        for(int i=0;i<ulist.size();i++)
        {
            sendData+=ulist[i];
            sendData+="*";
        }
        mutex.acquire();            //读者减一
        readcount--;
        if(readcount==0)            //若此为最后一个读者，则释放写信号量
            wrt.release();
        mutex.release();
    }
    else if(list[0]=="detail")                  //某用户的详细数据
    {
        QStringList ulist=sql.get_data(list[1]);
        for(int i=0;i<ulist.size();i++)
        {
            sendData+="#";
            sendData+=ulist[i];
        }

    }
    else if(list[0]=="rand_p")
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        sendData+="#";
        for(int i=0;i<15;i++){      //发给客户端15个随机精灵号
            int r=qrand()%8+1;
            sendData.append(QString::number(r)+"*");
        }

    }
    else if(list[0]=="result")
    {
        sql.result_refresh(list,myname);

    }
    else
        return;


    socket->write(sendData.toLatin1());

    socket->waitForBytesWritten();
    if((list[0]=="d"&&ret==false)||list[0]=="z")
     {
        socket->abort();
        this->quit();
     }


}
void socketthread::onDisconnect()
{
    user->removeOne(myname);
    qDebug()<<"线程 p="<<this->ptr<<" 结束";
    this->quit();
}

void socketthread::run()
{
    qDebug()<<"开始新线程";
    this->exec();
}
