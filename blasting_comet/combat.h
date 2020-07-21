#ifndef FIGLT_H
#define FIGLT_H

#include "fighter.h"

//敌人数量最大值
#define MAX_EMEMY 30
//其人出现位置 Y轴-100
#define START -50
//定位到道具
#define PROP(n) (props.data[n])
//敌人攻击间隔(fps)
#define EM_TIME_STEP 50

typedef struct _bul bul;
typedef struct _bull bull;

/*物品类型*/
enum prop_type{
    PROP_EMEMY,//敌人
    PROP_HEALTH,//加血道具
    PROP_BUUP,//武器升级道具
};

/*物品数据*/

typedef struct _em_pr
{
    prop data;              //物品属性

    int type;               //物品类型
    bul *bullet;            //子弹属性
    int init_health;        //初始生命
    int init_shmode;        //初始攻击方式
    int garde;              //击败得分
}em_pr;

/*敌人飞机和增益道具*/
typedef struct _em_prop{
    em_pr *unch_data;         //物品不变的属性

    int health;             //生命
    int pos_x,pos_y;        //坐标
    int sh_time;            //射击时间
    int momode;             //移动方式
    int shmode;             //攻击方式
    int limiter;            //移动限制位置

    struct _em_prop *plast;           //上一个物品
    struct _em_prop *pnext;           //下一个

}goods;

/*保存敌人死亡时的位置，绘制爆炸的教过*/
typedef struct _em_die{
    int boom_lv;        //初始等于32
    int pos_x,pos_y;    //坐标

    struct _em_die *plast;      //上一个
    struct _em_die *pnext;      //下一个
}em_die;

typedef struct _boom{
    bool aud_shoot;             //主机射击
    bool aud_boom;              //敌人死亡
    ALLEGRO_BITMAP *image[4];   //爆炸图像
    em_die head;            //节点，位置
}boom;

//敌人飞机和道具的信息
em_pr propes[15];//保存道具信息

/*加载道具的信息*/
bool load_prop();
/*每次开始游戏，初始化em_die,和 boom*/
bool inti_grops(goods *pgo, boom* pbo);

//主机被敌人击中
void em_shoot_fi(hero_fi *fi, bull *pbu);

/*添加一个道具，传入头节点，
 * dx:出现的横坐标
 * type：道具类型
 * mode：移动方式
 * limiter:移动限制位置
 */
bool add_goods(goods *pgo, int dx, int type, int momode, int limiter);
/*添加一个BOOS，存放在goods的头节点中*/
bool add_boos(goods *pgo, int type, int momode, int dy);

/*删除物品节点*/
void de_goods(goods *pgo);

/*移动一个道具*/
bull* move_good(goods *pgo);
/*移动所有道具*/
void move_goods(goods *pgo);

/*绘制道具（一个）*/
goods* draw_prop(goods *pgo);
/*绘制所有道具*/
void draw_propes(goods *pgo);

/*击中敌人(单个)判定，一个子弹,rect[],敌机的四个坐标*/
bull *attack_em(goods *pgo, bull *bull, boom *pbo, int rect[]);
/*击中敌人(单个)判断,所有主机子弹*/
goods *attack_ememy(int *grade, goods *pgo, bull *pbu, boom *pbo);
/*击中敌人(全部)判定，所有主机子弹,返回得分*/
int attack_ememies(goods *pgo, bull *p_fi_bu, boom *pbo);

/*添加敌人死亡位置，绘制爆炸效果*/
bool add_emdienode(boom *pbo, int rect[]);

/*删除爆炸效果的节点*/
void de_boom(em_die *pbo);

/*绘制一个节点的爆炸图像*/
em_die* draw_boom(em_die *pbo, ALLEGRO_BITMAP *image[]);
/*绘制一个链表中所有爆炸图像*/
void draw_booms(boom *pbo);

/*判断两个矩形是否重叠，有返回true*/
bool is_collision(int *rect1, int *rect2);

/*道具与主机发生碰撞后，数据处理，不变链表*/
void acr_after(goods *pgo, hero_fi *fi, boom *pbo);
/*单个敌人是否与rect相交*/
goods *ememy_acr_fighter(goods *pgo, boom *pbo, hero_fi *fi, int rect[]);
/*所有道具与飞机相交*/
void em_hit_anaist(hero_fi *fi, goods *pgo, boom *pbo);

/*释放propes图像*/
void distory_grop();

/*销毁goods链表*/
void distory_goods(goods *pgo);

void distory_boom(boom *pbo);


#endif // FIGLT_H
