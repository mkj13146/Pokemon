#include "tcpclient.h"
#include "ui_tcpclient.h"
#include  <QPixmap>

#define ip "127.0.0.1"
#define port 8000
QStringList name_list={"","李白","韩信","赵云","橘子","芈月","项羽","马克","狼狗"};
TcpClient::TcpClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpClient)
{
    //数据初始化

    pet=NULL;
    pet2=NULL;
    total_f=0;
    win_f=0;
    u_total_f=0;
    u_win_f=0;

    ui->setupUi(this);
    QPixmap pix_left(":/new/prefix1/img/LB.png"),pix_right(":/new/prefix1/img/HX.png");
    int w = ui->label_pic_left->width();
    int h = ui->label_pic_left->height();
    int w2= ui->label_pic_right->width();
    int h2= ui->label_pic_right->height();
    ui->label_pic_left->setPixmap(pix_left.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_pic_right->setPixmap(pix_right.scaled(w2,h2,Qt::KeepAspectRatio));


    ui->passwardLineEdit->setEchoMode(QLineEdit::Password);  //密码方式显示文本
    init();

    ui->stackedWidget->setCurrentIndex(0);
    ui->textBrowser_seg->setStyleSheet("QTextBrowser{border-width:0;border-style:outset}");


}

void TcpClient::table_show()            //信息页面显示
{

    ui->table_list->setColumnCount(2);
    ui->table_list->setRowCount(5);                //待修改
    ui->table_list->setHorizontalHeaderLabels(QStringList()<<"名称"<<"等级");
    ui->table_list->setColumnWidth(0,115);
    ui->table_list->setColumnWidth(1,115);
    ui->table_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_list->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->table_detail->setColumnCount(2);
    ui->table_detail->setRowCount(15);
    ui->table_detail->horizontalHeader()->setVisible(false);
    ui->table_detail->setColumnWidth(0,115);
    ui->table_detail->setColumnWidth(1,115);
    ui->table_detail->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_detail->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_detail->setItem(0,0,new QTableWidgetItem("名称"));
    ui->table_detail->setItem(1,0,new QTableWidgetItem("等级"));
    ui->table_detail->setItem(2,0,new QTableWidgetItem("类号"));
    ui->table_detail->setItem(3,0,new QTableWidgetItem("职业"));
    ui->table_detail->setItem(4,0,new QTableWidgetItem("血量"));
    ui->table_detail->setItem(5,0,new QTableWidgetItem("攻击力"));
    ui->table_detail->setItem(6,0,new QTableWidgetItem("防御力"));
    ui->table_detail->setItem(7,0,new QTableWidgetItem("敏捷度"));
    ui->table_detail->setItem(8,0,new QTableWidgetItem("暴击率"));
    ui->table_detail->setItem(9,0,new QTableWidgetItem("闪避率"));
    ui->table_detail->setItem(10,0,new QTableWidgetItem("经验值"));
    ui->table_detail->setItem(11,0,new QTableWidgetItem("技能一"));
    ui->table_detail->setItem(12,0,new QTableWidgetItem("技能二"));
    ui->table_detail->setItem(13,0,new QTableWidgetItem("技能三"));

    ui->table_list_user->setColumnCount(2);
    ui->table_list_user->setRowCount(5);             //待修改
    ui->table_list_user->setHorizontalHeaderLabels(QStringList()<<"名称"<<"等级");
    ui->table_list_user->setColumnWidth(0,115);
    ui->table_list_user->setColumnWidth(1,115);
    ui->table_list_user->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_list_user->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->table_list_ser->setColumnCount(2);
    ui->table_list_ser->setRowCount(10);
    ui->table_list_ser->setHorizontalHeaderLabels(QStringList()<<"名称"<<"等级");
    ui->table_list_ser->setColumnWidth(0,100);
    ui->table_list_ser->setColumnWidth(1,100);
    ui->table_list_ser->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_list_ser->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->table_detail_ser->setColumnCount(2);
    ui->table_detail_ser->setRowCount(15);
    ui->table_detail_ser->horizontalHeader()->setVisible(false);
    ui->table_detail_ser->setColumnWidth(0,115);
    ui->table_detail_ser->setColumnWidth(1,115);
    ui->table_detail_ser->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_detail_ser->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_detail_ser->setItem(0,0,new QTableWidgetItem("名称"));
    ui->table_detail_ser->setItem(1,0,new QTableWidgetItem("等级"));
    ui->table_detail_ser->setItem(2,0,new QTableWidgetItem("类号"));
    ui->table_detail_ser->setItem(3,0,new QTableWidgetItem("职业"));
    ui->table_detail_ser->setItem(4,0,new QTableWidgetItem("血量"));
    ui->table_detail_ser->setItem(5,0,new QTableWidgetItem("攻击力"));
    ui->table_detail_ser->setItem(6,0,new QTableWidgetItem("防御力"));
    ui->table_detail_ser->setItem(7,0,new QTableWidgetItem("敏捷度"));
    ui->table_detail_ser->setItem(8,0,new QTableWidgetItem("暴击率"));
    ui->table_detail_ser->setItem(9,0,new QTableWidgetItem("闪避率"));
    ui->table_detail_ser->setItem(10,0,new QTableWidgetItem("经验值"));
    ui->table_detail_ser->setItem(11,0,new QTableWidgetItem("技能一"));
    ui->table_detail_ser->setItem(12,0,new QTableWidgetItem("技能二"));
    ui->table_detail_ser->setItem(13,0,new QTableWidgetItem("技能三"));

    ui->table_list_song->setColumnCount(2);
    ui->table_list_song->setRowCount(3);
    ui->table_list_song->setHorizontalHeaderLabels(QStringList()<<"名称"<<"等级");
    ui->table_list_song->setColumnWidth(0,110);
    ui->table_list_song->setColumnWidth(1,110);
    ui->table_list_song->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_list_song->setSelectionBehavior(QAbstractItemView::SelectRows);

    on_refresh_button_clicked();

}
void TcpClient::detail_show(QTableWidget* table,QStringList p_list)           //详细信息注入
{
    table->setRowCount(p_list.size()-1);
    QStringList list;
    QString pet_name;
    for(int i=0;i<p_list.size()-1;i++)
    {
        list=p_list[i].split("*");
        pet_name=name_list[list[0].toInt()];

        table->setItem(i,0,new QTableWidgetItem(pet_name));
        table->setItem(i,1,new QTableWidgetItem(list[2]));
    }
}
TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::init()
{
    tcpSocket=new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));   //发生错误时执行displayError函数
    connect(ui->comboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(get_user(QString)));
    connect(ui->comboBox_2,SIGNAL(currentIndexChanged(QString)),this,SLOT(get_detail_pet(QString)));
}

void TcpClient::connectServer()
{
    tcpSocket->abort();   //取消已有的连接
    qDebug()<<"尝试建立新连接";
    tcpSocket->connectToHost(ip,port);
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessages()));
}

void TcpClient::on_sendBtn_clicked()                //登陆
{
    connectServer();
    QString userName=ui->userLineEdit->text();
    QString password=ui->passwardLineEdit->text();
    if(userName=="" || password=="")
        QMessageBox::information(this,"警告","输入不能为空",QMessageBox::Ok);
    QString bs="d";
    QString data=bs+"#"+userName+"#"+password;       //d  表示登陆
    tcpSocket->write(data.toLatin1());
    qDebug()<<data;

}


void TcpClient::on_signBtn_clicked()            //注册
{
    connectServer();
    QString userName=ui->userLineEdit->text();
    QString password=ui->passwardLineEdit->text();
    if(userName=="" || password=="")
        QMessageBox::information(this,"警告","输入不能为空",QMessageBox::Ok);
    QString as="z";
    QString pet_list="";
    QString pet_temp="";
    QString data=as+"#"+userName+"#"+password+"#"+pet_list;
    QString pet_name;
    int random;
    for(int i=0;i<3;i++)
    {
        random=rand()%8+1;
        pet_name=name_list[random];
        pet_temp=QString::number(random)+"*"+pet_name+"*"+"1"+"*"+"0"+"|";
        pet_list+=pet_temp;
    }
    data+=pet_list;
    tcpSocket->write(data.toLatin1());
}


void TcpClient::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpSocket->errorString();   //输出出错信息
}


void TcpClient::readMessages()
{
    QString data=tcpSocket->readAll();
    if(data!="")
    qDebug()<<data;
    QStringList list=data.split("#");                   //接受消息并以#分开
    if(list[0]=="z" && list[1]=="true")
        QMessageBox::information(this,"信息提示","注册成功!",QMessageBox::Ok);
    else if(list[0]=="z" && list[1]=="false")
        QMessageBox::information(this,"信息提示","注册失败,用户名已经被注册!",QMessageBox::Ok);
    else if(list[0]=="d" && list[1]=="reload")
        QMessageBox::information(this,"信息提示","该用户已登录!",QMessageBox::Ok);
    else if(list[0]=="d" && list[1]=="true")
        {
            //成功登录，信息处理
            QMessageBox::information(this,"信息提示","登录成功!",QMessageBox::Ok);
            table_show();
            ui->stackedWidget->setCurrentIndex(1);
            user_name=ui->userLineEdit->text();
            p_list=list[3].split("|");
            total_f=list[4].toFloat();
            win_f=list[5].toFloat();            
            detail_show(ui->table_list,p_list);
            on_table_list_cellPressed(0,0);
            u_update();
        }
    else if(list[0]=="d" && list[1]=="false")
         QMessageBox::information(this,"信息提示","登录失败,用户名或密码错误!",QMessageBox::Ok);


    else if(list[0]=="a"||list[0]=="o")             //返回在线用户列表或所有用户列表，根据combox2当前值确定是那种情况
    {
        QStringList user_list=list[1].split("*");
        ui->comboBox_2->clear();

        for(int i=0;i<user_list.size()-1;i++)
            ui->comboBox_2->addItem(user_list[i]);

    }
    else if(list[0]=="detail")                      //返回用户详细信息
    {

        u_p_list=list[2].split("|");
        u_total_f=list[3].toFloat();
        u_win_f=list[4].toFloat();
        float win_rat;
        if(u_total_f==0)
        {
           ui->label_win_rat->setText("胜率: --");
        }
        else
        {
            win_rat=u_win_f/u_total_f;
            ui->label_win_rat->setText("胜率: "+QString::number(win_rat*100,'f',0)+"%");
        }
         detail_show(ui->table_list_user,u_p_list);
    }
    else if(list[0]=="rand_p")                      //返回服务端生成的随机精灵列表
    {
        pet_ser=list[1].split("*");
        pet_ser_show();
        on_table_list_ser_cellClicked(0,0);
    }
    else
        return;
}
void TcpClient::pet_ser_show()                     //显示服务端精灵列表
{
    ui->table_list_ser->setRowCount(pet_ser.size()-1);
    QString pet_name;
    for(int i=0;i<pet_ser.size()-1;i++)
    {
        pet_name=name_list[pet_ser[i].toInt()];
        ui->table_list_ser->setItem(i,0,new QTableWidgetItem(pet_name));
        ui->table_list_ser->setItem(i,1,new QTableWidgetItem(QString::number(i+1)));
    }
}
void TcpClient::u_update()                         //当前登录用户的数据更新（精灵信息，胜率，等等）
{
    float win_rat;
    if(total_f!=0)
    {
        win_rat=win_f/total_f;
        ui->textBrowser->clear();
        ui->textBrowser->append("用户: "+user_name);
        ui->textBrowser->append("胜率: "+QString::number(win_rat*100,'f',0)+"%");
    }
    else
    {
        ui->textBrowser->clear();
        ui->textBrowser->append("用户: "+user_name);
        ui->textBrowser->append("胜率: --");
    }

    //根据 p_list 更新数据
    detail_show(ui->table_list,p_list);
    badge_update();

    qDebug()<<"gengxin";
}
void TcpClient::badge_update()                  //奖牌信息更新
{
    //宠物个数>=5,>=10,>=15    对应铜，银，金
    //满级宠物个数>=3,>=6,>=9   对应铜，银，金
    int num=p_list.size()-1,full_grade_num=0;
    QString str1,str2;
    for(int i=0;i<num;i++)
    {
        if(p_list[i][2]==15)                //满级
            full_grade_num++;
    }
    if(num>=15)
        str1="宠物个数勋章: 金牌";
    else if(num>=10&&num<15)
        str1="宠物个数勋章: 银牌";
    else if(num>=5&&num<10)
        str1="宠物个数勋章: 铜牌";
    else
        str1="宠物个数勋章: 铁牌";

    if(full_grade_num>=9)
        str2="满级宠物勋章: 金牌";
    else if(full_grade_num>=6&&full_grade_num<9)
        str2="满级宠物勋章: 银牌";
    else if(full_grade_num>=3&&full_grade_num<6)
        str2="满级宠物勋章: 铜牌";
    else
        str2="满级宠物勋章: 铁牌";
    ui->textBrowser_2->clear();
    ui->textBrowser_2->append(str1);
    ui->textBrowser_2->append(str2);


}
void TcpClient::on_table_list_cellPressed(int row, int column)  //根据当前行，确定详细信息显示
{
    ui->PVP_fight->setEnabled(true);
    ui->leval_fight->setEnabled(true);

    if(pet)
        delete pet;

    QStringList list=p_list[row].split("*");
    QStringList data;
    QPixmap pix;

    int w1 = ui->label_pic_2->width();
    int h1 = ui->label_pic_2->height();

    switch(list[0].toInt())
    {
    case 1:
        pet=new Pokemon_T_LB;
        pix.load(":/new/prefix1/img/LB.png");
        break;
    case 2:
        pet=new Pokemon_T_HX;
        pix.load(":/new/prefix1/img/HX.png");
        break;
    case 3:
        pet=new Pokemon_T_ZY;
        pix.load(":/new/prefix1/img/ZY.png");
        break;
    case 4:
        pet=new Pokemon_T_JZ;
        pix.load(":/new/prefix1/img/JZ.png");
        break;
    case 5:
        pet=new Pokemon_T_MY;
        pix.load(":/new/prefix1/img/MY.png");
        break;
    case 6:
        pet=new Pokemon_T_XY;
        pix.load(":/new/prefix1/img/XY.png");
        break;
    case 7:
        pet=new Pokemon_T_MK;
        pix.load(":/new/prefix1/img/MK.png");
        break;
    case 8:
        pet=new Pokemon_T_LG;
        pix.load(":/new/prefix1/img/LG.png");
        break;
    default:
        break;

    }
    ui->label_pic_2->setPixmap(pix.scaled(w1,h1,Qt::KeepAspectRatio));

    pet->SET_GRADE(list[2].toInt());
    pet->set_exp(list[3].toInt());
    data=pet->data();
    for(int i=0;i<14;i++)
        ui->table_detail->setItem(i,1,new QTableWidgetItem(data[i]));
}

void TcpClient::get_user(QString str)               //槽函数，当下拉菜单项目改变时，请求更新数据
{
    QString request;
    if(ui->comboBox->currentIndex()==0)                 //所有用户
    {
        request="a#";
    }
    else if(ui->comboBox->currentIndex()==1)            //在线用户
    {
        request="o#";

    }
    else
    {
        qDebug()<<"get_user------error";
        return;
    }
    tcpSocket->write(request.toLatin1());
}

void TcpClient::get_detail_pet(QString str)         //槽函数，当选取用户改变时，数据更新。
{
    QString name=ui->comboBox_2->currentText();
    if(name!="")
    {
        QString data="detail#"+name;
        qDebug()<<data;
        tcpSocket->write(data.toLatin1());
    }
}
void TcpClient::on_back_clicked()
{
    //退出登录  回到登陆界面

     tcpSocket->abort();
     ui->stackedWidget->setCurrentIndex(0);
}

void TcpClient::on_push_begin_fight_clicked()
{
    //开始战斗
    FM=new FightManager(pet,pet2);

    connect(FM,SIGNAL(fight_end_sig(int)),this,SLOT(fight_end_slot(int)));
    connect(FM,SIGNAL(back_clicked()),this,SLOT(on_back_clicked()));
    FM->show();
    FM->Print();

}

void TcpClient::on_back_ser_clicked()
{
    // 取消决斗 返回page2
   ui->stackedWidget->setCurrentIndex(1);

}


void TcpClient::on_refresh_button_clicked()             //更新按钮
{
    QString request;
    if(ui->comboBox->currentIndex()==0)                 //所有用户
    {
        request="a#";
    }
    else if(ui->comboBox->currentIndex()==1)            //在线用户
    {
        request="o#";

    }
    else
    {
        qDebug()<<"get_user------error";
        return;
    }
    tcpSocket->write(request.toLatin1());
    u_update();

}

void TcpClient::on_leval_fight_clicked()
{
    //升级对战：
    fight_flag=1;
    ui->stackedWidget->setCurrentIndex(2);
    ui->push_begin_fight->setText("开始对战");
    QString data="rand_p#";
    tcpSocket->write(data.toLatin1());
}
void TcpClient::on_PVP_fight_clicked()
{

    // 决斗
    fight_flag=2;
    ui->stackedWidget->setCurrentIndex(2);
    ui->push_begin_fight->setText("开始决斗");
    QString data="rand_p#";
    tcpSocket->write(data.toLatin1());
}
void TcpClient::on_table_list_user_cellClicked(int row, int column)
{

    ui->PVP_fight->setEnabled(false);
    ui->leval_fight->setEnabled(false);         //选取其他用户，不可战斗
    if(pet)
        delete pet;

    QStringList list=u_p_list[row].split("*");
    QStringList data;
    QPixmap pix;

    int w1 = ui->label_pic_2->width();
    int h1 = ui->label_pic_2->height();

    switch(list[0].toInt())
    {
    case 1:
        pet=new Pokemon_T_LB;
        pix.load(":/new/prefix1/img/LB.png");
        break;
    case 2:
        pet=new Pokemon_T_HX;
        pix.load(":/new/prefix1/img/HX.png");
        break;
    case 3:
        pet=new Pokemon_T_ZY;
        pix.load(":/new/prefix1/img/ZY.png");
        break;
    case 4:
        pet=new Pokemon_T_JZ;
        pix.load(":/new/prefix1/img/JZ.png");
        break;
    case 5:
        pet=new Pokemon_T_MY;
        pix.load(":/new/prefix1/img/MY.png");
        break;
    case 6:
        pet=new Pokemon_T_XY;
        pix.load(":/new/prefix1/img/XY.png");
        break;
    case 7:
        pet=new Pokemon_T_MK;
        pix.load(":/new/prefix1/img/MK.png");
        break;
    case 8:
        pet=new Pokemon_T_LG;
        pix.load(":/new/prefix1/img/LG.png");
        break;
    default:
        break;

    }
    ui->label_pic_2->setPixmap(pix.scaled(w1,h1,Qt::KeepAspectRatio));

    pet->SET_GRADE(list[2].toInt());
    pet->set_exp(list[3].toInt());
    data=pet->data();
    for(int i=0;i<14;i++)
        ui->table_detail->setItem(i,1,new QTableWidgetItem(data[i]));

}

void TcpClient::on_pushButton_re_clicked()
{
    QString data="rand_p#";
    tcpSocket->write(data.toLatin1());
}

void TcpClient::on_table_list_ser_cellClicked(int row, int column)
{
    if(pet2)
        delete pet2;

    QStringList data;
    QPixmap pix;

    int w1 = ui->label_pic_ser->width();
    int h1 = ui->label_pic_ser->height();

    switch(pet_ser[row].toInt())
    {
    case 1:
        pet2=new Pokemon_T_LB;
        pix.load(":/new/prefix1/img/LB.png");
        break;
    case 2:
        pet2=new Pokemon_T_HX;
        pix.load(":/new/prefix1/img/HX.png");
        break;
    case 3:
        pet2=new Pokemon_T_ZY;
        pix.load(":/new/prefix1/img/ZY.png");
        break;
    case 4:
        pet2=new Pokemon_T_JZ;
        pix.load(":/new/prefix1/img/JZ.png");
        break;
    case 5:
        pet2=new Pokemon_T_MY;
        pix.load(":/new/prefix1/img/MY.png");
        break;
    case 6:
        pet2=new Pokemon_T_XY;
        pix.load(":/new/prefix1/img/XY.png");
        break;
    case 7:
        pet2=new Pokemon_T_MK;
        pix.load(":/new/prefix1/img/MK.png");
        break;
    case 8:
        pet2=new Pokemon_T_LG;
        pix.load(":/new/prefix1/img/LG.png");
        break;
    default:
        break;

    }
    ui->label_pic_ser->setPixmap(pix.scaled(w1,h1,Qt::KeepAspectRatio));

    pet2->SET_GRADE(row+1);
    pet2->set_exp(0);
    data=pet2->data();
    for(int i=0;i<14;i++)
        ui->table_detail_ser->setItem(i,1,new QTableWidgetItem(data[i]));

}

void TcpClient::fight_end_slot(int flag)   // 0输，1赢，2同归于尽
{


    if(flag!=2)
    {

        QString data="result#";
        int k=ui->table_list->currentRow();
        QStringList temp=p_list[k].split("*");                       //暂存需要修改的项目
        temp[2]=QString::number(pet->get_grade());
        temp[3]=QString::number(pet->get_exp());
        p_list[k]=temp.join("*");

        total_f++;
        if(fight_flag==1)           //升级对战
        {
            if(flag==1)
                win_f++;
        }
        else if(fight_flag==2)      //决斗
        {
            if(flag==1)             //决斗赢了
            {
                win_f++;
                // 构造数据包发给服务器
                QString new_pet;
                int num=ui->table_list_ser->currentRow();
                new_pet+=pet_ser[num]+"*";
                new_pet+=name_list[pet_ser[num].toInt()]+"*";
                new_pet+=QString::number(num+1)+"*"+"0";
                p_list.insert(p_list.size()-1,new_pet);
            }
            else                    //决斗输了
            {
                // 构造数据包发给服务器
                se_pet_out();
                return;
            }
        }

        data+=QString::number(p_list.size()-1)+"#";
        data+=p_list.join("|")+"#";
        data+=QString::number(total_f)+"#";
        data+=QString::number(win_f);

        tcpSocket->write(data.toLatin1());
        u_update();
    }
}

void TcpClient::se_pet_out()                        //决斗失败，选择一个宠物送出
{
    ui->stackedWidget->setCurrentIndex(3);
    int num=p_list.size()-1;
    if(num<=3)
    {
        ui->table_list_song->setRowCount(num);
        detail_show(ui->table_list_song,p_list);
    }
    else                                            //随机选择三个
    {
        ui->table_list_song->setRowCount(3);

        QStringList list;
        QString pet_name;

        for(int i=0;i<3;i++)
        {
            rand_sel[i]=rand()%num;
            list=p_list[rand_sel[i]].split("*");
            pet_name=name_list[list[0].toInt()];
            ui->table_list_song->setItem(i,0,new QTableWidgetItem(pet_name));
            ui->table_list_song->setItem(i,1,new QTableWidgetItem(list[2]));

        }
    }
}

void TcpClient::on_table_list_song_cellClicked(int row, int column)
{
    QPixmap pix;
    QStringList list;
    int w1 = ui->label_pic_song->width();
    int h1 = ui->label_pic_song->height();

    if(p_list.size()-1<=3)
        list=p_list[row].split("*");
    else
        list=p_list[rand_sel[row]].split("*");

        switch(list[0].toInt())
        {
        case 1:
            pix.load(":/new/prefix1/img/LB.png");
            break;
        case 2:
            pix.load(":/new/prefix1/img/HX.png");
            break;
        case 3:
            pix.load(":/new/prefix1/img/ZY.png");
            break;
        case 4:
            pix.load(":/new/prefix1/img/JZ.png");
            break;
        case 5:
            pix.load(":/new/prefix1/img/MY.png");
            break;
        case 6:
            pix.load(":/new/prefix1/img/XY.png");
            break;
        case 7:
            pix.load(":/new/prefix1/img/MK.png");
            break;
        case 8:
            pix.load(":/new/prefix1/img/LG.png");
            break;
        default:
            break;

        }
        ui->label_pic_song->setPixmap(pix.scaled(w1,h1,Qt::KeepAspectRatio));

}

void TcpClient::on_confirm_clicked()                //确认送出
{
    QString data="result#";
    int num=ui->table_list_song->currentRow();

    if(p_list.size()>0)                             //调整客户端宠物列表并发送包更新数据库
    {

        if(p_list.size()-1<=3)
            p_list.removeOne(p_list[num]);
        else
            p_list.removeOne(p_list[rand_sel[num]]);

        if(p_list.size()==1)
        {
             int num=rand()%8+1;
             p_list.insert(0,QString::number(num)+"*"+name_list[num]+"*"+"1*0");
        }
    }

    else if(p_list.size()==0)
    {
        int num=rand()%8+1;
        p_list.append(QString::number(num)+"*"+name_list[num]+"*"+"1*0");
        p_list.append("");
    }

        data+=QString::number(p_list.size()-1)+"#";
        data+=p_list.join("|")+"#";
        data+=QString::number(total_f)+"#";
        data+=QString::number(win_f);

        tcpSocket->write(data.toLatin1());
        tcpSocket->waitForBytesWritten();
        ui->stackedWidget->setCurrentIndex(1);
        u_update();

}

