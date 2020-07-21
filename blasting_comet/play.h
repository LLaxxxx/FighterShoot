#ifndef PLAY_H
#define PLAY_H

#include "bullet.h"
#include "combat.h"
#include "fighter.h"
#include "map_move_shoot.h"
#include "audio.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define FPS         60  //FPS
#define WIN_WIDTH   640 //窗口宽度
#define WIN_HEIGHT  800 //窗口高度
#define WIN_GARDE   50  //分数窗口高度

typedef struct _thread_data{
    ALLEGRO_MUTEX *mutex;
    ALLEGRO_COND  *cond;

    hero_fi *fi;        //主机
    bull *fi_bu;        //主机子弹
    bull *em_bu;        //敌人子弹
    goods *props;       //道具
    boom *em_die;       //敌人死亡
    int time;           //时间
    bool ready;
}th_data;

struct _img_aud{
    ALLEGRO_BITMAP *frame[4];   //边框
    ALLEGRO_BITMAP *boom[4];    //爆炸图像
    ALLEGRO_BITMAP *blood[2];   //血条

    ALLEGRO_SAMPLE *bgm_shoot;  //射击音效
    ALLEGRO_SAMPLE *bgm_boom;   //爆炸音效
}img_aud;


int game_init();                                                    //初始化游戏
int frame_run();                                                    //进入游戏界面循环
int game_run(int n);                                                //进入游戏循环
int game_data(th_data *data);                                       //处理数据

void inti_thread(th_data *arg, hero_fi *pfi, bull *pfibu, bull *pembu, goods *pgo, boom *pbo);       //线程数据初始化

bool load_img_aud();                                //加载一些音频和图片***
void draw_game_bgbl(int sy, int health);                        //绘制游戏背景和血条
int found_mouse(int x, int y, int n);               //找到鼠标指向的选项
void draw_option(ALLEGRO_BITMAP *sel, ALLEGRO_BITMAP *unsel, int sw, int n,char **strs);//绘制选项栏
void draw_tips(ALLEGRO_BITMAP *bimmap, char *str);  //绘制提示信息，只出现屏幕中间
void *Func_Thread(ALLEGRO_THREAD *, void *); //线程***

int game_distory();             //释放资源
#endif // PLAY_H

