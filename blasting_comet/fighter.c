#include "fighter.h"
#include "play.h"

/*初始化主机*/
bool inti_fighter(hero_fi *fi, const char *fife, int w, int h)
{
    memset(fi, 0, sizeof(hero_fi));                                                 //分数和状态初始为0
    fi->unch_data.image = al_load_bitmap(fife);
    if(!fi->unch_data.image) return false;                                          //飞机图像
    fi->unch_data.height = h;                                                       //飞机高度
    fi->unch_data.width = w;                                                        //飞机宽度
    fi->unch_data.speedx = fi->unch_data.speedy = 7;                                //速度
    fi->pos_y = WIN_HEIGHT - fi->unch_data.height-WIN_GARDE - fi->unch_data.speedy; //初始Y坐标
    fi->pos_x = (WIN_WIDTH - fi->unch_data.width)/2;                                //初始X坐标
    fi->health = 500;                                                               //生命值
    fi->unch_data.sh_speed = 10;                                                    //射击时间10帧
    //剩下的全部初始化为0
    return true;
}

/*判断主机能不能作出某种动作*/
bool is_move(hero_fi *fi, int act, int time)
{
    switch(act)
    {
    case KEY_UP:
        return fi->key[KEY_UP] && fi->pos_y >= fi->unch_data.speedy;
    case KEY_DOWN:
        return fi->key[KEY_DOWN] && fi->pos_y <= WIN_HEIGHT - fi->unch_data.height - WIN_GARDE - fi->unch_data.speedy;
    case KEY_LEFT:
        return fi->key[KEY_LEFT] && fi->pos_x >= fi->unch_data.speedx;
    case KEY_RIGHT:
        return fi->key[KEY_RIGHT] && fi->pos_x <= WIN_WIDTH - fi->unch_data.width - fi->unch_data.speedx;
    case KEY_SHOOW:{
        if(fi->key[KEY_SHOOW] && (time-  fi->sh_time + FPS)%FPS >= fi->unch_data.sh_speed)
        {
            fi->sh_time = time;
            return true;
        }
        return false;
    }
    default:
        return false;
    }
}

/*绘制飞机，生命值大于0时*/
void draw_fighter(hero_fi *fi)
{
    if(fi->health>0){
        ALLEGRO_BITMAP *image = fi->unch_data.image;
        if(fi->key[KEY_LEFT]){
            al_draw_bitmap_region(image, 260, 0, fi->unch_data.width, fi->unch_data.height, fi->pos_x, fi->pos_y, 1);
        }
        else if(fi->key[KEY_RIGHT]){
            al_draw_bitmap_region(image, 0, 0, fi->unch_data.width, fi->unch_data.height, fi->pos_x, fi->pos_y, 1);
        }
        else{
            al_draw_bitmap_region(image, 130, 0, fi->unch_data.width, fi->unch_data.height, fi->pos_x, fi->pos_y, 1);
        }
    }
}

/**/
void distory_fighter(hero_fi *fi)
{
    al_destroy_bitmap(fi->unch_data.image);
}
