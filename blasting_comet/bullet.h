#ifndef BULLET_H
#define BULLET_H

#include "fighter.h"
#include "combat.h"

/*子弹类型，保存子弹的数据*/
typedef struct _bul{
    prop unch_data;
    int hurt;                   //伤害
}bul;

/*子弹链表，保存界中子弹的位置*/
typedef struct _bull
{
    bul *data;                  //子弹属性
    int pos_x,pos_y;            //位置

    struct _bull *plast;                //上一个子弹
    struct _bull *pnext;                //下一个
}bull;

bul bullets[7];//一共有7种子弹，前3种主机的

/*加载bullets子弹类型*/
bool load_bullet();
/*初始化子弹数组*/
bool inti_bullets(bull *pbu);

/*加入一个子弹*/
bool add_one_bull(bull *pbu, bul *bu_type, int dx, int dy);
/*主机发射子弹*/
bool shoot_bullet(bull *pbu, hero_fi *fi, int level);

/*判断敌人能否射击*/
bool is_em_shoot(struct _em_prop *pgo, int time);
/*敌人单个发射子弹*/
goods *ememy_shoot(bull *pbu, struct _em_prop *pgo, int time);
/*所有存在的敌人发射子弹*/
void ememies_shoot(bull *pbu, struct _em_prop *pgo, int time);

/*删除子弹*/
void de_bull(bull *pbu);
/*判断（x,y）是否超出屏幕，是返回false*/
bool is_beyond_display(int dx, int dy);

/*移动单个子弹,并返回下一个子弹地址*/
bull* move_bull(bull *pbu);
/*移动所有子弹,传入头节点*/
void move_bullte(bull *pbu);

/*绘制一个子弹，并返回它的下一个节点*/
bull *draw_bull(bull *pbu);
/*绘制子弹,传入头节点*/
void draw_bulltes(bull *pbu);

/*释放bullets,在main钟*/
void distory_bullets();

/*销毁bull链表*/
void distory_bull(bull *pbu);

#endif // BULLET_H
