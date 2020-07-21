#ifndef FIGHTER_H
#define FIGHTER_H

#include "allegro5/allegro_native_dialog.h"

/*主机动作*/
enum MKEYS{
    KEY_UP=0,   //上移W
    KEY_DOWN,   //下移S
    KEY_LEFT,   //左移A
    KEY_RIGHT,  //有移D
    KEY_SHOOW,  //攻击J
};

/*道具*/
typedef struct _prop
{
    ALLEGRO_BITMAP *image;  //图像
    int width,height;       //大小
    int speedx,speedy;      //速度
    int sh_speed;           //射击速度
}prop;

/*主机*/
typedef struct _hero_fi{
    prop unch_data;         //不变属性
    int health;             //生命值
    int pos_x,pos_y;        //坐标
    int grade;              //分数
    int level;              //武器等级
    int sh_time;            //射击时间
    bool key[5];            //动作
}hero_fi;

/*初始化主机*/
bool inti_fighter(hero_fi *fi, const char *fife, int w, int h);

/*判断主机能不能作出某种动作*/
bool is_move(hero_fi *fi, int act, int time);

/*绘制飞机，生命值大于0时*/
void draw_fighter(hero_fi *fi);

void distory_fighter(hero_fi *fi);



#endif // FIGHTER_H
