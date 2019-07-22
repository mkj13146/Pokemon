#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <QDebug>
using namespace std;

const int GAIN=30;
const int NUM=5;
const int c_state=0;         //是否处于控制状态
const int is_gain_c=1;      //是否处于暴击增益状态
const int is_gain_d=2;      //是否处于躲避增益状态
const int is_gain_df=3;     //是否处于物防增益状态

enum PokemonType
{
    T_Attack, //high attack
    T_Hp,	//high HP
    T_Defence, //high defence
    T_Speed	//high speed
};
enum ATK_KIND
{
    G_Attack,       //非控制技能
    Hit_Fly,         //击飞技能（控制）
    Ex_Arm,          //破甲
    Gain_D,           //闪避率增益技能
    Gain_C,            //暴击率增益技能
    Gain_DF             //物防增益技能

};
enum PO_CAREER
{
    C_Assassin,       //刺客
    C_Archer,         //射手
    C_Tank,           //坦克
    C_Warrior         //战士

    /*
     射手->坦克
     坦克->战士
     战士->刺客
     刺客->射手
     */
};
typedef struct ATTACK_DETAIL
{
    int hurt;
    ATK_KIND kind;
    QString sk_name;
    bool is_crit;
    PO_CAREER career;

}AT_DETAIL;

typedef struct
{
    QString sk_name;
    int get_exp;
    bool att_ret;       //是否属性克制
    bool is_doge;       //是否躲避
    int get_hurt;       //伤害值
    bool is_dead;       //是否死亡

}GET_DAM;


class Pokemon_Base
{
protected:
    QString p_name;
    PokemonType p_type;
    int type_num;           //宠物类型编号  1-8；
    float Atk;              //攻击力
    int Hp;                 //血量
    int Def;                //防御力
    int Spe;                //敏捷度（敏捷度越高，攻击间隔越小）
    int grade;              //等级
    int crit_rate;          //暴击率      0-100
    int dodge_rate;         //闪避率      0-100
    int exp;                //经验值
    int exp_thrd;           //下一级升级阈值
    int skill_rate[3];      //技能释放概率（3个）

    //浮动属性
    float Atk_max;
    int Hp_max;                 //最大生命值
    int Def_max;
    int Spe_max;
    int crit_rate_max;
    int dodge_rate_max;

    const static int Gr_max;    //最大等级
    PO_CAREER p_career;     //属性
    bool state[NUM];         //状态数组

public:

    Pokemon_Base ();
    QString get_name()const;
    int get_typenum()const;
    int get_Hp()const;
    int get_Hp_max()const;
    int get_Spe()const;
    int get_Def()const;
    int get_grade()const;
    int get_exp()const;
    int get_crit_rate()const;
    int get_crit_rate_max()const;
    int get_dodge_rate()const;
    int get_dodge_rate_max() const;
    bool get_state(int k)const;
    void set_exp(int k);
    void set_state(int k,bool s);
    void set_Def(int);
    void set_Hp(int);
    void set_dodge_rate(int);
    void set_crit_rate(int);
    void set_crit_rate_max(int);
    void set_dodge_rate_max(int);
    void set_name(QString);
    void refresh();
    GET_DAM GET_HURT (AT_DETAIL atd);     //受到伤害，处理
    int UP_GRADE (int t_exp);        //升级函数   判断是否升级  若可升级，修改grade以及exp_thrd
    void SET_GRADE (int grade);       //设置初始等级
    void OUT_PUT(void);


    virtual void ATB_CH ()=0;       //属性改变（升级后）
    virtual AT_DETAIL ATTACK (int sk=-1)=0;       //攻击函数
    virtual QStringList data()=0;


};

//---------------------------------------------------
class Pokemon_ATT:public Pokemon_Base
{

public:
    Pokemon_ATT ();
    virtual void ATB_CH ();

};

class Pokemon_HP:public Pokemon_Base
{
public:
    Pokemon_HP ();
    virtual void ATB_CH ();

};
class Pokemon_DEF:public Pokemon_Base
{
public:
    Pokemon_DEF();
    virtual void ATB_CH ();
};
class Pokemon_SP:public Pokemon_Base
{
public:
    Pokemon_SP();
    virtual void ATB_CH ();
};

//---------------------------------------------------


class Pokemon_T_ZY:public Pokemon_ATT
{
private:
    vector<QString> skill;
public:
    Pokemon_T_ZY();
    virtual AT_DETAIL ATTACK (int);
    virtual QStringList data();

};

class Pokemon_T_HX:public Pokemon_ATT
{
private:
    vector<QString> skill;

public:
    Pokemon_T_HX();
    virtual AT_DETAIL ATTACK (int);
    virtual QStringList data();
};

class Pokemon_T_MK:public Pokemon_SP
{
private:
    vector<QString> skill;
public:
    Pokemon_T_MK();
    virtual AT_DETAIL ATTACK (int);
    virtual QStringList data();
};

class Pokemon_T_XY:public Pokemon_DEF
{
private:
    vector<QString> skill;
public:
    Pokemon_T_XY();
    virtual AT_DETAIL ATTACK (int);
    virtual QStringList data();
};

class Pokemon_T_MY:public Pokemon_HP
{
private:
    vector<QString> skill;
public:
    Pokemon_T_MY();
    virtual AT_DETAIL ATTACK (int);
    virtual QStringList data();
};

class Pokemon_T_LB:public Pokemon_ATT
{
private:
    vector<QString> skill;
public:
    Pokemon_T_LB();
    virtual AT_DETAIL ATTACK (int);
    virtual QStringList data();
};

class Pokemon_T_JZ:public Pokemon_ATT
{
private:
    vector<QString> skill;
public:
    Pokemon_T_JZ();
    virtual AT_DETAIL ATTACK (int);
    virtual QStringList data();
};

class Pokemon_T_LG:public Pokemon_SP
{
private:
    vector<QString> skill;
public:
    Pokemon_T_LG();
    virtual AT_DETAIL ATTACK (int);
    virtual QStringList data();
};
#endif // POKEMON_H
