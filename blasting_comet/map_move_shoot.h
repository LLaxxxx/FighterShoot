#ifndef MOVE_MODE_H
#define MOVE_MODE_H

#include <stdio.h>
#include "combat.h"
#include "play.h"

//敌人移动方式
enum MOVE_MODE{
    STOP        = 0,            //停止
    WALK_U      = 1,            //向上
    WALK_D      = 2,            //向下
    WALK_L      = 3,            //向左
    WALK_R      = 4,            //向右
    WALK_DL     = 5,            //向左下
    WALK_DR     = 6,            //向右下
    WALK_UL     = 7,            //向左上
    WALK_UR     = 8,            //向右上

    WALK_D_ST   = 10,           //下，停止
    WALK_D_U    = 11 ,          //下，上
    WALK_D_L    = 12,           //下，左
    WALK_D_R    = 13,           //下，右
    WALK_D_DL   = 14,           //下，左下
    WALK_D_DR   = 15,           //下，右下
    WALK_D_UL   = 16,           //下，左上
    WALK_D_UR   = 17,           //下，右上

    WALK_U_ST   = 20,           //上，停止
    WALK_U_D    = 21,           //上，下
    WALK_U_L    = 22,           //上，左
    WALK_U_R    = 23,           //上，右
    WALK_U_DL   = 24,           //上，左下
    WALK_U_DR   = 25,           //上，右下
    WALK_U_UL   = 26,           //上，左上
    WALK_U_UR   = 27,           //上，右上
};

//敌人攻击方式
enum SHOOT_MODE{
    //普通敌人
    NONE            = 0,            //不攻击
    SHOOT_ONE       = 1,            //发射一个
    SHOOT_HTWO      = 2,            //竖向，快数发射两个
    SHOOT_WTWO      = 3,            //横向，一次发射两个
    FAST_ONE        = 4,            //快速射击15
    FAST_HTWO       = 5,
    FAST_WTWO       = 6,
    //BOOS
    FASTEST_WWTTO   = 7,            //急速40，宽间距，两个
    SHOOT_MESSY     = 8,            //随机数量射击
    FASTEST_ONE     = 9,            //急速射击30
    FASTEST_HTWO    = 10,
    FASTEST_WTWO    = 11,
    SHOOT_ACROSS    = 12,            //交叉射击


};

//超过边界返回 false;

bool move_ST();//停下

bool move_U(goods *pgo);//上

bool move_D(goods *pgo);//下

bool move_L(goods *pgo);//左

bool move_R(goods *pgo);//右

bool move_DL(goods *pgo);//左下

bool move_DR(goods *pgo);//右下

bool move_UL(goods *pgo);//左上

bool move_DR(goods *pgo);//右上

bool run_down_in_turn(goods *pgo, bool fun1(), bool fun2(), int lim);

bool run_up_in_turn(goods *pgo, bool fun1(), bool fun2(), int lim);

/*移动*/
bool move_grop_mode(goods *pgo, int mode);


/*发射失败返回 false****************************/

//纵向两个
bool shoot_htwo(goods *pgo, bull *pbu, int spacing);

//横向发射num个子弹，间隔为spacing
bool shoot_nbullets(goods *pgo, bull *pbu, int spacing, int num);

//随机横向数量射击，3～6个
bool rand_num_shoot(goods *pgo, bull *pbu, int spacing);

//交叉射击，间距变化有规律，横向两个
bool shoot_across(goods *pgo, bull *pbu);

//快速射击
bool fast_shoot(goods *pgo, bull *pbu, int spacing, int num, int cut, bool fun());

/*移动*/
bool em_shoot_mode(goods *pgo, bull *pbu, int mode);

/************************/

void inti_map();//

//读取文件，添加敌人到pgo
bool read_map(goods *pgo, FILE *fp);

#endif // MOVE_MODE_H
