#include "pokemon.h"
const int Pokemon_Base::Gr_max=15;
Pokemon_Base::Pokemon_Base()
{
    this->p_name="";
    this->p_type=T_Attack;       //默认Attack属性
    this->type_num=0;
    this->grade=1;

    this->Hp_max=500;
    this->Atk_max=100;
    this->Def_max=50;
    this->Spe_max=10;
    this->crit_rate_max=0;
    this->dodge_rate_max=0;
    this->exp=0;
    this->exp_thrd=30;
    this->skill_rate[0]=50;
    this->skill_rate[1]=30;
    this->skill_rate[2]=20;
    for(int i=0;i<=NUM;i++)
        this->state[i]=false;

    this->Hp=Hp_max;
    this->Atk=Atk_max;
    this->Def=Def_max;
    this->Spe=Spe_max;
    this->crit_rate=crit_rate_max;
    this->dodge_rate=dodge_rate_max;
}

//以后改------------------------------------------
int Pokemon_Base::UP_GRADE(int t_exp)
{
    this->exp+=t_exp;
    int key=0;
    while(exp>=exp_thrd)
    {
        if(grade<Gr_max)
        {
            key++;
            this->grade++;
            this->ATB_CH();
            exp_thrd+=(30*this->grade);
        }
    }
    return key;
}

void Pokemon_Base::SET_GRADE(int grade)
{
    if(grade>Gr_max)
        grade=Gr_max;

    for(int i=1;i<grade;i++)
    {
        this->grade++;
        this->ATB_CH();
        exp_thrd+=(30*this->grade);
    }
}

GET_DAM Pokemon_Base::GET_HURT(AT_DETAIL atd)
{
    GET_DAM getdam;
    getdam.sk_name=atd.sk_name;
    int d_random = rand()%100+1;
    int dam = 0;
    int get_exp=0;

    getdam.is_dead=false;
    getdam.att_ret=false;
    if(d_random<=dodge_rate)        //躲避
    {
        dam = 0;
        getdam.is_doge=true;
    }
    else
    {
        getdam.is_doge=false;

        if(atd.kind==Ex_Arm)
            dam = atd.hurt - (this->Def)/2;
        else if(atd.kind==Gain_DF)
            dam=0;
        else
            dam = atd.hurt - this->Def;

        if((atd.career+1)%4==this->p_career)
           {
            dam*=1.3;
            getdam.att_ret=true;
           }


        if(dam<0)                   //物防太高
            dam=0;
    }


    int hp_temple=Hp;

    qDebug()<<"this hp q"<<this->get_Hp();
    this->Hp -= dam;
     qDebug()<<"this  hp"<<this->get_Hp();

    if(hp_temple<=dam)
       dam=hp_temple;

    if(this->Hp<=0)
    {
        this->Hp=0;
        get_exp = this->grade*10;
        getdam.is_dead=true;

    }

    getdam.get_exp=get_exp;
    getdam.get_hurt=dam;



    QString kind;
    switch (atd.kind) {
    case G_Attack:
        kind="普通攻击";
        break;
    case Hit_Fly:
        kind="击飞眩晕";
        break;
    case Ex_Arm:
        kind="破甲攻击";
        break;
    case Gain_D:
        kind="闪避增益";
        break;
    case Gain_C:
        kind="暴击增益";
        break;
    case Gain_DF:
        kind="物防增益";
        break;
    default:
        break;
    }

    qDebug()<<this->p_name<<"   受到攻击  "<<atd.sk_name<<"\t"<<kind<<"\t"<<dam<<"\t血量: "<<this->get_Hp()<<"\t物防:\t"<<Def<<"\t躲避率:\t"<<this->dodge_rate;
    if(get_exp)
        qDebug()<<this->p_name<<"   死亡！";

    return getdam;
}

void Pokemon_Base::OUT_PUT()
{
   qDebug()<<"Atk:\t"<<this->Atk;
   qDebug()<<"Hp:\t"<<this->Hp;
   qDebug()<<"Def:\t"<<this->Def;
   qDebug()<<"Spe:\t"<<this->Spe;
   qDebug()<<"grade:\t"<<this->grade;
   qDebug()<<"exp:\t"<<this->exp;
}

bool Pokemon_Base::get_state(int k)const
{
    return this->state[k];
}
int Pokemon_Base::get_Hp()const
{
    return this->Hp;
}

int Pokemon_Base::get_Spe()const
{
    return this->Spe;
}
int Pokemon_Base::get_Def()const
{
    return this->Def;
}
QString Pokemon_Base::get_name()const
{
    return this->p_name;
}
int Pokemon_Base::get_grade()const
{
    return this->grade;
}
int Pokemon_Base::get_exp()const
{
    return this->exp;
}
int Pokemon_Base::get_typenum()const
{
    return this->type_num;
}
int Pokemon_Base::get_Hp_max()const
{
    return this->Hp_max;
}
void Pokemon_Base::set_exp(int k)
{
    this->exp=k;
}
void Pokemon_Base::set_state(int k,bool s)
{
    this->state[k]=s;
}
void Pokemon_Base::set_name(QString s)
{
    this->p_name=s;
}
void Pokemon_Base::set_Def(int k)
{
    this->Def=k;
}
void Pokemon_Base::set_Hp(int k)
{
    this->Hp=k;
}
void Pokemon_Base::set_crit_rate(int c)
{
    this->crit_rate=c;
}
void Pokemon_Base::set_crit_rate_max(int c)
{
    this->crit_rate=c;
    this->crit_rate_max=c;
}
void Pokemon_Base::set_dodge_rate(int d)
{
    this->dodge_rate=d;
}
void Pokemon_Base::set_dodge_rate_max(int d)
{
    this->dodge_rate_max=d;
    this->dodge_rate=d;
}
int Pokemon_Base::get_crit_rate()const
{
    return this->crit_rate;
}
int Pokemon_Base::get_crit_rate_max()const
{
    return this->crit_rate_max;
}
int Pokemon_Base::get_dodge_rate()const
{
    return this->dodge_rate;
}
int Pokemon_Base::get_dodge_rate_max()const
{
    return this->dodge_rate_max;
}
void Pokemon_Base::refresh()
{
    this->Hp=Hp_max;
    this->Atk=Atk_max;
    this->Def=Def_max;
    this->Spe=Spe_max;
    this->crit_rate=crit_rate_max;
    this->dodge_rate=dodge_rate_max;

    for(int i=0;i<=NUM;i++)
        this->state[i]=false;

}


//--------------------------------------------------------
Pokemon_ATT::Pokemon_ATT()
{
    this->p_type=T_Attack;
    this->Atk_max+=20;
    this->Atk=Atk_max;
}

void Pokemon_ATT::ATB_CH()
{
    this->Atk_max+=20;
    this->Hp_max+=30;
    this->Def_max+=5;
    this->Spe_max+=1;
    this->crit_rate_max+=1;
    this->dodge_rate_max+=1;

    this->Hp=Hp_max;
    this->Atk=Atk_max;
    this->Def=Def_max;
    this->Spe=Spe_max;
    this->crit_rate=crit_rate_max;
    this->dodge_rate=dodge_rate_max;
}

Pokemon_HP::Pokemon_HP()
{
    this->p_type=T_Hp;
    this->Hp_max+=60;
    this->Hp=Hp_max;
}
void Pokemon_HP::ATB_CH()
{
    this->Atk_max+=10;
    this->Hp_max+=60;
    this->Def_max+=5;
    this->Spe_max+=1;
    this->crit_rate_max+=1;
    this->dodge_rate_max+=1;

    this->Hp=Hp_max;
    this->Atk=Atk_max;
    this->Def=Def_max;
    this->Spe=Spe_max;
    this->crit_rate=crit_rate_max;
    this->dodge_rate=dodge_rate_max;

}
//-------------------------------------------------------

Pokemon_DEF::Pokemon_DEF()
{
    this->p_type=T_Defence;
    this->Def_max+=10;
    this->Def=Def_max;
}
void Pokemon_DEF::ATB_CH()
{
    this->Atk_max+=10;
    this->Hp_max+=30;
    this->Def_max+=12;
    this->Spe_max+=1;
    this->crit_rate_max+=1;
    this->dodge_rate_max+=1;

    this->Hp=Hp_max;
    this->Atk=Atk_max;
    this->Def=Def_max;
    this->Spe=Spe_max;
    this->crit_rate=crit_rate_max;
    this->dodge_rate=dodge_rate_max;
}

//-------------------------------------------------------
Pokemon_SP::Pokemon_SP()
{
    this->p_type=T_Speed;
    this->Spe_max+=2;
    this->Spe=Spe_max;
}
void Pokemon_SP::ATB_CH()
{
    this->Atk_max+=10;
    this->Hp_max+=30;
    this->Def_max+=5;
    this->Spe_max+=2;
    this->crit_rate_max+=1;
    this->dodge_rate_max+=1;

    this->Hp=Hp_max;
    this->Atk=Atk_max;
    this->Def=Def_max;
    this->Spe=Spe_max;
    this->crit_rate=crit_rate_max;
    this->dodge_rate=dodge_rate_max;
}

//-------------------------------------------------------
Pokemon_T_ZY::Pokemon_T_ZY()
{
    this->type_num=3;
    this->p_name="赵云";
    p_career=C_Warrior;
    skill.push_back("G_Attack");
    skill.push_back("惊雷之龙");
    skill.push_back("天翔之龙");

}


AT_DETAIL Pokemon_T_ZY::ATTACK(int sk=-1 )
{
    int CRIT_FLAG = 0,FS_FLAG = 0,SS_FLAG = 0;
    int c_random = rand()%100+1;
    int first_skill = rand()%100+1;
    int second_skill = rand()%100+1;

    AT_DETAIL atd;
    atd.hurt=0;
    atd.kind=G_Attack;
    atd.sk_name="";
    atd.is_crit=false;
    atd.career=p_career;

    if(c_random <= this->crit_rate)
        CRIT_FLAG = 1;

    if(second_skill <= this->skill_rate[2])
        SS_FLAG = 1;
    else if(first_skill <= this->skill_rate[1])
        FS_FLAG = 1;

    if(SS_FLAG)
    {
       atd.kind= Hit_Fly;
       atd.hurt = (int)(this->Atk*0.8);
       atd.sk_name=this->skill[2];
    }
    else if(FS_FLAG)
    {
        atd.kind = G_Attack;
        atd.hurt = (int)(this->Atk*1.2);
        atd.sk_name=this->skill[1];
    }
    else
    {
        atd.hurt = (int)(this->Atk);
        atd.sk_name=this->skill[0];
    }

    if(Hp>Hp_max)
        Hp=Hp_max;

    QString is_crit="NO";
    if(CRIT_FLAG)
    {
        atd.hurt*=2;
        is_crit="YES";
        atd.is_crit=true;

    }
    qDebug()<<this->p_name<<"   发动攻击  "<<atd.sk_name<<"\t"<<"暴击:\t"<<is_crit<<"\t暴击率:\t"<<crit_rate<<"\t伤害:  "<<atd.hurt;
    return atd;

}
QStringList Pokemon_T_ZY::data()
{
    QStringList list;
    QString career;
    switch(type_num)
    {

    case 1:
        career="刺客";
        break;
    case 2:
        career="刺客";
        break;
    case 3:
        career="战士";
        break;
    case 4:
        career="战士";
        break;
    case 5:
        career="坦克";
        break;
    case 6:
        career="坦克";
        break;
    case 7:
        career="射手";
        break;
    case 8:
        career="射手";
        break;
    default:
        break;

    }
    list.append(p_name);
    list.append(QString::number(grade));
    list.append(QString::number(type_num));
    list.append(career);
    list.append(QString::number(Hp));
    list.append(QString::number(Atk));
    list.append(QString::number(Def));
    list.append(QString::number(Spe));
    list.append(QString::number(crit_rate));
    list.append(QString::number(dodge_rate));
    list.append(QString::number(exp));
    list.append(skill[0]);
    list.append(skill[1]);
    list.append(skill[2]);

    return list;
}
//-------------------------------------------------------
Pokemon_T_HX::Pokemon_T_HX()
{
    this->type_num=2;
    this->p_name="韩信";
    p_career=C_Assassin;
    skill.push_back("G_Attack");
    skill.push_back("背水一战");
    skill.push_back("国士无双");
}
AT_DETAIL Pokemon_T_HX::ATTACK(int sk=-1)
{
    int CRIT_FLAG = 0,FS_FLAG = 0,SS_FLAG = 0;
    int c_random = rand()%100+1;
    int first_skill = rand()%100+1;
    int second_skill = rand()%100+1;

    AT_DETAIL atd;
    atd.hurt=0;
    atd.kind=G_Attack;
    atd.sk_name="";
    atd.is_crit=false;
    atd.career=p_career;

    if(c_random <= this->crit_rate)
        CRIT_FLAG = 1;

    if(second_skill <= this->skill_rate[2])
        SS_FLAG = 1;
    else if(first_skill <= this->skill_rate[1])
        FS_FLAG = 1;

    if(SS_FLAG)
    {
       atd.kind= Hit_Fly;
       atd.hurt = (int)(this->Atk*0.8);
       atd.sk_name=this->skill[2];
    }
    else if(FS_FLAG)
    {
        atd.kind = G_Attack;
        atd.hurt = (int)(this->Atk*1.2);
        atd.sk_name=this->skill[1];
    }
    else
    {
        atd.hurt = (int)(this->Atk);
        atd.sk_name=this->skill[0];
    }

    if(Hp>Hp_max)
        Hp=Hp_max;

    QString is_crit="NO";
    if(CRIT_FLAG)
    {
        atd.hurt*=2;
        is_crit="YES";
        atd.is_crit=true;

    }

     qDebug()<<this->p_name<<"   发动攻击  "<<atd.sk_name<<"\t"<<"暴击:\t"<<is_crit<<"\t暴击率:\t"<<crit_rate<<"\t伤害:  "<<atd.hurt;
    return atd;
}
QStringList Pokemon_T_HX::data()
{
    QStringList list;
    QString career;
    switch(type_num)
    {

    case 1:
        career="刺客";
        break;
    case 2:
        career="刺客";
        break;
    case 3:
        career="战士";
        break;
    case 4:
        career="战士";
        break;
    case 5:
        career="坦克";
        break;
    case 6:
        career="坦克";
        break;
    case 7:
        career="射手";
        break;
    case 8:
        career="射手";
        break;
    default:
        break;

    }
    list.append(p_name);
    list.append(QString::number(grade));
    list.append(QString::number(type_num));
    list.append(career);
    list.append(QString::number(Hp));
    list.append(QString::number(Atk));
    list.append(QString::number(Def));
    list.append(QString::number(Spe));
    list.append(QString::number(crit_rate));
    list.append(QString::number(dodge_rate));
    list.append(QString::number(exp));
    list.append(skill[0]);
    list.append(skill[1]);
    list.append(skill[2]);
    return list;
}

//-------------------------------------------------------
Pokemon_T_MK::Pokemon_T_MK()
{
    this->type_num=7;
    this->p_name="马可";
    p_career=C_Archer;
    skill.push_back("G_Attack");
    skill.push_back("华丽左轮");                //破甲效果
    skill.push_back("漫游之枪");                //提升躲避率（无伤害）
}

AT_DETAIL Pokemon_T_MK::ATTACK(int sk=-1)
{
    int CRIT_FLAG = 0,FS_FLAG = 0,SS_FLAG = 0;
    int c_random = rand()%100+1;
    int first_skill = rand()%100+1;
    int second_skill = rand()%100+1;

    AT_DETAIL atd;
    atd.hurt=0;
    atd.kind=G_Attack;
    atd.sk_name="";
    atd.is_crit=false;
    atd.career=p_career;

    if(c_random <= this->crit_rate)
        CRIT_FLAG = 1;

    if(second_skill <= this->skill_rate[2])
        SS_FLAG = 1;
    else if(first_skill <= this->skill_rate[1])
        FS_FLAG = 1;

    if(SS_FLAG)
    {
       atd.kind= Gain_D;
       atd.hurt =(int)(this->Atk*0.8);
       atd.sk_name=this->skill[2];
       this->set_state(is_gain_d,true);
       this->dodge_rate+=GAIN;
    }
    else if(FS_FLAG)
    {
        atd.kind = Ex_Arm;
        atd.hurt = (int)(this->Atk);
        atd.sk_name=this->skill[1];
    }
    else
    {
        atd.hurt = (int)(this->Atk);
        atd.sk_name=this->skill[0];
    }

    if(Hp>Hp_max)
        Hp=Hp_max;

    QString is_crit="NO";

    if(CRIT_FLAG)
    {
        atd.hurt*=2;
        is_crit="YES";
        atd.is_crit=true;
    }
     qDebug()<<this->p_name<<"   发动攻击  "<<atd.sk_name<<"\t"<<"暴击:\t"<<is_crit<<"\t暴击率:\t"<<crit_rate<<"\t伤害:  "<<atd.hurt;
    return atd;
}
QStringList Pokemon_T_MK::data()
{
    QStringList list;
    QString career;
    switch(type_num)
    {

    case 1:
        career="刺客";
        break;
    case 2:
        career="刺客";
        break;
    case 3:
        career="战士";
        break;
    case 4:
        career="战士";
        break;
    case 5:
        career="坦克";
        break;
    case 6:
        career="坦克";
        break;
    case 7:
        career="射手";
        break;
    case 8:
        career="射手";
        break;
    default:
        break;

    }
    list.append(p_name);
    list.append(QString::number(grade));
    list.append(QString::number(type_num));
    list.append(career);
    list.append(QString::number(Hp));
    list.append(QString::number(Atk));
    list.append(QString::number(Def));
    list.append(QString::number(Spe));
    list.append(QString::number(crit_rate));
    list.append(QString::number(dodge_rate));
    list.append(QString::number(exp));
    list.append(skill[0]);
    list.append(skill[1]);
    list.append(skill[2]);

    return list;
}
//-------------------------------------------------------
Pokemon_T_XY::Pokemon_T_XY()
{
    this->type_num=6;
    this->p_name="项羽";
    p_career=C_Tank;
    skill.push_back("G_Attack");
    skill.push_back("无畏冲锋");                //击飞，少量伤害。
    skill.push_back("破釜沉舟");                //物防增益

}
AT_DETAIL Pokemon_T_XY::ATTACK(int sk=-1)
{
    int CRIT_FLAG = 0,FS_FLAG = 0,SS_FLAG = 0;
    int c_random = rand()%100+1;
    int first_skill = rand()%100+1;
    int second_skill = rand()%100+1;

    AT_DETAIL atd;
    atd.hurt=0;
    atd.kind=G_Attack;
    atd.sk_name="";
    atd.is_crit=false;
    atd.career=p_career;

    if(c_random <= this->crit_rate)
        CRIT_FLAG = 1;

    if(second_skill <= this->skill_rate[2])
        SS_FLAG = 1;
    else if(first_skill <= this->skill_rate[1])
        FS_FLAG = 1;

    if(SS_FLAG)
    {
       atd.kind= Gain_DF;
       atd.hurt = 0;
       atd.sk_name=this->skill[2];
       this->set_state(is_gain_df,true);
       this->Def=Def*3/2;
    }
    else if(FS_FLAG)
    {
        atd.kind = Hit_Fly;
        atd.hurt = (int)(this->Atk*0.6);
        atd.sk_name=this->skill[1];
    }
    else
    {
        atd.hurt = (int)(this->Atk);
        atd.sk_name=this->skill[0];
    }

    if(Hp>Hp_max)
        Hp=Hp_max;

    QString is_crit="NO";
    if(CRIT_FLAG)
    {
        atd.hurt*=2;
        is_crit="YES";
        atd.is_crit=true;
    }

      qDebug()<<this->p_name<<"   发动攻击  "<<atd.sk_name<<"\t"<<"暴击:\t"<<is_crit<<"\t暴击率:\t"<<crit_rate<<"\t伤害:  "<<atd.hurt;
    return atd;
}

QStringList Pokemon_T_XY::data()
{
    QStringList list;
    QString career;
    switch(type_num)
    {

    case 1:
        career="刺客";
        break;
    case 2:
        career="刺客";
        break;
    case 3:
        career="战士";
        break;
    case 4:
        career="战士";
        break;
    case 5:
        career="坦克";
        break;
    case 6:
        career="坦克";
        break;
    case 7:
        career="射手";
        break;
    case 8:
        career="射手";
        break;
    default:
        break;

    }
    list.append(p_name);
    list.append(QString::number(grade));
    list.append(QString::number(type_num));
    list.append(career);
    list.append(QString::number(Hp));
    list.append(QString::number(Atk));
    list.append(QString::number(Def));
    list.append(QString::number(Spe));
    list.append(QString::number(crit_rate));
    list.append(QString::number(dodge_rate));
    list.append(QString::number(exp));
    list.append(skill[0]);
    list.append(skill[1]);
    list.append(skill[2]);
    return list;

}
//-------------------------------------------------------
Pokemon_T_MY::Pokemon_T_MY()
{
    this->type_num=5;
    this->p_name="芈月";
    p_career=C_Tank;
    skill.push_back("G_Attack");
    skill.push_back("嗜血仆从");                //吸血技能
    skill.push_back("暗影之月");                //闪避
}
AT_DETAIL Pokemon_T_MY::ATTACK(int sk=-1)
{
    int CRIT_FLAG = 0,FS_FLAG = 0,SS_FLAG = 0;
    int c_random = rand()%100+1;
    int first_skill = rand()%100+1;
    int second_skill = rand()%100+1;

    AT_DETAIL atd;
    atd.hurt=0;
    atd.kind=G_Attack;
    atd.sk_name="";
    atd.is_crit=false;
    atd.career=p_career;

    if(c_random <= this->crit_rate)
        CRIT_FLAG = 1;

    if(second_skill <= this->skill_rate[2])
        SS_FLAG = 1;
    else if(first_skill <= this->skill_rate[1])
        FS_FLAG = 1;

    if(SS_FLAG)
    {
       atd.kind= Gain_D;
       atd.hurt = (int)(this->Atk*0.6);
       atd.sk_name=this->skill[2];
       this->set_state(is_gain_d,true);
       this->dodge_rate+=GAIN;
    }
    else if(FS_FLAG)
    {
        atd.kind = G_Attack;
        atd.hurt = (int)(this->Atk*0.6);
        atd.sk_name=this->skill[1];
        this->set_Hp(this->get_Hp()*11/10);

    }
    else
    {
        atd.hurt = (int)(this->Atk);
        atd.sk_name=this->skill[0];
    }

    if(Hp>Hp_max)
        Hp=Hp_max;

    QString is_crit="NO";
    if(CRIT_FLAG)
    {
        atd.hurt*=2;
        is_crit="YES";
        atd.is_crit=true;

    }

     qDebug()<<this->p_name<<"   发动攻击  "<<atd.sk_name<<"\t"<<"暴击:\t"<<is_crit<<"\t暴击率:\t"<<crit_rate<<"\t伤害:  "<<atd.hurt;
    return atd;
}
QStringList Pokemon_T_MY::data()
{
    QStringList list;
    QString career;
    switch(type_num)
    {

    case 1:
        career="刺客";
        break;
    case 2:
        career="刺客";
        break;
    case 3:
        career="战士";
        break;
    case 4:
        career="战士";
        break;
    case 5:
        career="坦克";
        break;
    case 6:
        career="坦克";
        break;
    case 7:
        career="射手";
        break;
    case 8:
        career="射手";
        break;
    default:
        break;

    }
    list.append(p_name);
    list.append(QString::number(grade));
    list.append(QString::number(type_num));
    list.append(career);
    list.append(QString::number(Hp));
    list.append(QString::number(Atk));
    list.append(QString::number(Def));
    list.append(QString::number(Spe));
    list.append(QString::number(crit_rate));
    list.append(QString::number(dodge_rate));
    list.append(QString::number(exp));
    list.append(skill[0]);
    list.append(skill[1]);
    list.append(skill[2]);
    return list;
}

//-------------------------------------------------------
Pokemon_T_LB::Pokemon_T_LB()
{
    this->type_num=1;
    this->p_name="李白";
    this->set_dodge_rate_max(this->get_dodge_rate_max()+20);//李白自带20%闪避率
    p_career=C_Assassin;
    skill.push_back("G_Attack");
    skill.push_back("神来之笔");                //提升躲避率
    skill.push_back("青莲剑歌");                //躲避率加伤害
}

AT_DETAIL Pokemon_T_LB::ATTACK(int sk=-1)
{
    int CRIT_FLAG = 0,FS_FLAG = 0,SS_FLAG = 0;
    int c_random = rand()%100+1;
    int first_skill = rand()%100+1;
    int second_skill = rand()%100+1;

    AT_DETAIL atd;
    atd.hurt=0;
    atd.kind=G_Attack;
    atd.sk_name="";
    atd.is_crit=false;
    atd.career=p_career;

    if(second_skill <= this->skill_rate[2])
        SS_FLAG = 1;
    else if(first_skill <= this->skill_rate[1])
        FS_FLAG = 1;

    if(SS_FLAG)
    {
       atd.kind= Gain_D;
       atd.hurt = (int)(this->Atk*1.0);
       atd.sk_name=this->skill[2];
       this->set_state(is_gain_d,true);
       this->dodge_rate+=GAIN;
    }
    else if(FS_FLAG)
    {
        atd.kind = Gain_D;
        atd.hurt = (int)(this->Atk*0.8);
        atd.sk_name=this->skill[1];
        this->set_state(is_gain_d,true);
        this->dodge_rate +=GAIN;

    }
    else
    {
        atd.hurt = (int)(this->Atk);
        atd.sk_name=this->skill[0];
    }

    if(Hp>Hp_max)
        Hp=Hp_max;

    if(c_random <= this->crit_rate)
        CRIT_FLAG = 1;

    QString is_crit="NO";
    if(CRIT_FLAG)
    {
        atd.hurt*=2.0;
        is_crit="YES";
        atd.is_crit=true;

    }

     qDebug()<<this->p_name<<"   发动攻击  "<<atd.sk_name<<"\t"<<"暴击:\t"<<is_crit<<"\t暴击率:\t"<<crit_rate<<"\t伤害:  "<<atd.hurt;
    return atd;
}

QStringList Pokemon_T_LB::data()
{
    QStringList list;
    QString career;
    switch(type_num)
    {

    case 1:
        career="刺客";
        break;
    case 2:
        career="刺客";
        break;
    case 3:
        career="战士";
        break;
    case 4:
        career="战士";
        break;
    case 5:
        career="坦克";
        break;
    case 6:
        career="坦克";
        break;
    case 7:
        career="射手";
        break;
    case 8:
        career="射手";
        break;
    default:
        break;

    }
    list.append(p_name);
    list.append(QString::number(grade));
    list.append(QString::number(type_num));
    list.append(career);
    list.append(QString::number(Hp));
    list.append(QString::number(Atk));
    list.append(QString::number(Def));
    list.append(QString::number(Spe));
    list.append(QString::number(crit_rate));
    list.append(QString::number(dodge_rate));
    list.append(QString::number(exp));
    list.append(skill[0]);
    list.append(skill[1]);
    list.append(skill[2]);

    return list;
}
//-------------------------------------------------------
Pokemon_T_JZ::Pokemon_T_JZ()
{
    this->type_num=4;
    this->p_name="橘子";
    p_career=C_Warrior;
    skill.push_back("G_Attack");
    skill.push_back("居    合");
    skill.push_back("细    雪");
}

AT_DETAIL Pokemon_T_JZ::ATTACK(int sk=-1)
{
    int CRIT_FLAG = 0,FS_FLAG = 0,SS_FLAG = 0;
    int c_random = rand()%100+1;
    int first_skill = rand()%100+1;
    int second_skill = rand()%100+1;

    AT_DETAIL atd;
    atd.hurt=0;
    atd.kind=G_Attack;
    atd.sk_name="";
    atd.is_crit=false;
    atd.career=p_career;

    if(second_skill <= this->skill_rate[2])
        SS_FLAG = 1;
    else if(first_skill <= this->skill_rate[1])
        FS_FLAG = 1;

    if(SS_FLAG)
    {
       atd.kind= G_Attack;
       atd.hurt = (int)(this->Atk*0.8);
       atd.sk_name=this->skill[2];
       this->set_Hp(this->get_Hp()+(this->Atk)*0.2);


    }
    else if(FS_FLAG)
    {
        atd.kind = Hit_Fly;
        atd.hurt = (int)(this->Atk*0.8);
        atd.sk_name=this->skill[1];

    }
    else
    {
        atd.hurt = (int)(this->Atk);
        atd.sk_name=this->skill[0];
    }

    if(Hp>Hp_max)
        Hp=Hp_max;

    if(c_random <= this->crit_rate)
        CRIT_FLAG = 1;

    QString is_crit="NO";
    if(CRIT_FLAG)
    {
        atd.hurt*=2;
        is_crit="YES";
        atd.is_crit=true;

    }

     qDebug()<<this->p_name<<"   发动攻击  "<<atd.sk_name<<"\t"<<"暴击:\t"<<is_crit<<"\t暴击率:\t"<<crit_rate<<"\t伤害:  "<<atd.hurt;
    return atd;
}

QStringList Pokemon_T_JZ::data()
{
    QStringList list;
    QString career;
    switch(type_num)
    {

    case 1:
        career="刺客";
        break;
    case 2:
        career="刺客";
        break;
    case 3:
        career="战士";
        break;
    case 4:
        career="战士";
        break;
    case 5:
        career="坦克";
        break;
    case 6:
        career="坦克";
        break;
    case 7:
        career="射手";
        break;
    case 8:
        career="射手";
        break;
    default:
        break;

    }
    list.append(p_name);
    list.append(QString::number(grade));
    list.append(QString::number(type_num));
    list.append(career);
    list.append(QString::number(Hp));
    list.append(QString::number(Atk));
    list.append(QString::number(Def));
    list.append(QString::number(Spe));
    list.append(QString::number(crit_rate));
    list.append(QString::number(dodge_rate));
    list.append(QString::number(exp));
    list.append(skill[0]);
    list.append(skill[1]);
    list.append(skill[2]);
    return list;

}
//-------------------------------------------------------
Pokemon_T_LG::Pokemon_T_LG()
{
    this->type_num=8;
    this->p_career=C_Archer;
    this->p_name="狼狗";
    skill.push_back("G_Attack");
    skill.push_back("百兽陷阱");
    skill.push_back("可汗狂猎");

}
AT_DETAIL Pokemon_T_LG::ATTACK(int sk=-1)
{
    int CRIT_FLAG = 0,FS_FLAG = 0,SS_FLAG = 0;
    int c_random = rand()%100+1;
    int first_skill = rand()%100+1;
    int second_skill = rand()%100+1;

    AT_DETAIL atd;
    atd.hurt=0;
    atd.kind=G_Attack;
    atd.sk_name="";
    atd.is_crit=false;
    atd.career=p_career;

    if(second_skill <= this->skill_rate[2])
        SS_FLAG = 1;
    else if(first_skill <= this->skill_rate[1])
        FS_FLAG = 1;

    if(SS_FLAG)
    {
        atd.kind = Hit_Fly;
        atd.hurt = (int)(this->Atk*0.6);
        atd.sk_name=this->skill[2];
    }
    else if(FS_FLAG)
    {
        atd.kind= G_Attack;
        atd.hurt = (int)(this->Atk*1.2);
        atd.sk_name=this->skill[1];
    }
    else
    {
        atd.hurt = (int)(this->Atk);
        atd.sk_name=this->skill[0];
    }

    if(Hp>Hp_max)
        Hp=Hp_max;

    if(c_random <= this->crit_rate)
        CRIT_FLAG = 1;

    QString is_crit="NO";
    if(CRIT_FLAG)
    {
        atd.hurt*=2;
        is_crit="YES";
        atd.is_crit=true;

    }

     qDebug()<<this->p_name<<"   发动攻击  "<<atd.sk_name<<"\t"<<"暴击:\t"<<is_crit<<"\t暴击率:\t"<<crit_rate<<"\t伤害:  "<<atd.hurt;
    return atd;
}
QStringList Pokemon_T_LG::data()
{
    QStringList list;
    QString career;
    switch(type_num)
    {

    case 1:
        career="刺客";
        break;
    case 2:
        career="刺客";
        break;
    case 3:
        career="战士";
        break;
    case 4:
        career="战士";
        break;
    case 5:
        career="坦克";
        break;
    case 6:
        career="坦克";
        break;
    case 7:
        career="射手";
        break;
    case 8:
        career="射手";
        break;
    default:
        break;

    }
    list.append(p_name);
    list.append(QString::number(grade));
    list.append(QString::number(type_num));
    list.append(career);
    list.append(QString::number(Hp));
    list.append(QString::number(Atk));
    list.append(QString::number(Def));
    list.append(QString::number(Spe));
    list.append(QString::number(crit_rate));
    list.append(QString::number(dodge_rate));
    list.append(QString::number(exp));
    list.append(skill[0]);
    list.append(skill[1]);
    list.append(skill[2]);
    return list;

}
