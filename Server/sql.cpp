#include "sql.h"

MySql::MySql()
{

}
MySql::~MySql()
{

    if(db.isOpen()){
        db.close();
    }
    delete query;
}
void MySql::open()                                  //打开数据库
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("User");
    if(db.open())
        {
            qDebug()<<"Database connected successfully!";
            createtable();
            return;
        }
    else
        {
            qDebug()<<"Database connected failed!";
            return;
        }
}
void MySql::close()                                 //关闭
{
    db.close();
}
void MySql::createtable()                           //创建用户列表
{
    query=new QSqlQuery;

    query->exec("create table user(name VARCHAR(30) PRIMARY KEY UNIQUE NOT NULL,password VARCHAR(30),poke_num int,poke_list VARCHAR(60),total_f int,win_f int)");

    /*创建root用户*/
    query->exec("insert into user value('root', 'root')");
    if(!query->exec())
    {
        qDebug() << "Error: Fail to create table_user." << query->lastError();
    }
    else
    {
        qDebug() << "Table_user created!";
    }

}


bool MySql::loguser(QString name, QString password)       //登录检查
{
    QString str=QString("select * from user where name='%1' and password='%2'").arg(name).arg(password);
    query=new QSqlQuery;
    query->exec(str);
    return query->next();

}


bool MySql::signup(QString name, QString password, QString pet)     //注册检查
{
    QString str=QString("select * from user where name='%1").arg(name);
    query=new QSqlQuery;
    query->exec(str);
    query->next();

    int poke_num=3;
    int total_f=0;
    int win_f=0;

    str=QString("insert into user values('%1','%2','%3','%4','%5','%6')").arg(name).arg(password).arg(poke_num).arg(pet).arg(total_f).arg(win_f);
    bool ret=query->exec(str);
    qDebug()<<ret;
    return ret;
}
void MySql::delete_user(QString name)
{
     QString str=QString("delete * from user where name='%1").arg(name);
     query=new QSqlQuery;
     if(!query->exec())
     {
         qDebug()<<query->lastError();
     }
     else
     {
          qDebug()<<"a user deleted";
     }

}
QStringList MySql::get_data(QString name)     //获取名称为name的用户的详细信息以QStringList 返回
{
    QStringList list;
    QString select_sql = "select poke_num, poke_list,total_f,win_f from user where name = :name";
    query=new QSqlQuery;
    query->prepare(select_sql);
    query->bindValue(":name",name);

    if(!query->exec())
    {
        qDebug()<<query->lastError();
    }
    else if(query->first())
    {
        for(int i=0;i<4;i++)
        list.append(query->value(i).toString());        //将信息加入list


        for(int i=0;i<list.size();i++)
        qDebug()<<list[i];                              //测试输出
    }

    return list;
}
QStringList MySql::get_user_list()    //获取所有用户列表（用户名）
{
    QStringList list;
    QString select_sql = "select name from user";
    query=new QSqlQuery;
    query->prepare(select_sql);
    if(!query->exec())
    {
        qDebug()<<query->lastError();
    }
    else if(query->first())
    {
        list.append(query->value(0).toString());
        while(query->next())
            list.append(query->value(0).toString());        //逐条加入列表

        for(int i=0;i<list.size();i++)                      //测试输出
        qDebug()<<list[i];
    }

    return list;
}
void MySql::result_refresh(QStringList list,QString name)   //战斗后数据更新
{
    int poke_num=list[1].toInt();
    int total_f=list[3].toInt();
    int win_f=list[4].toInt();
    QString select_sql = QString("update user set poke_num='%1',poke_list='%2',total_f='%3',win_f='%4' where name='%5'").arg(poke_num).arg(list[2]).arg(total_f).arg(win_f).arg(name);
    query=new QSqlQuery;
    query->prepare(select_sql);
    if(!query->exec())
    {
        qDebug()<<query->lastError();
    }
    else
    {
        qDebug()<<"更新成功";
    }

}
