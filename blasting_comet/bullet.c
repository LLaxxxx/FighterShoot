#include "bullet.h"
#include "play.h"

/*加载bullets子弹类型*/
bool load_bullet()
{
    //主角飞机子弹
    //一
    bullets[0].unch_data.image = al_load_bitmap("./data/image/myb_1.png");//1个
    if(!bullets[0].unch_data.image) return false;
    bullets[0].unch_data.speedy = -8;//向上移动
    bullets[0].unch_data.speedx = 0;
    bullets[0].hurt = 8;
    bullets[0].unch_data.height = 23;
    bullets[0].unch_data.width = 10;
    //二
    bullets[1].unch_data.image = al_load_bitmap("./data/image/myb_2.png");//2个
    if(!bullets[1].unch_data.image) return false;
    bullets[1].unch_data.speedy = -8;//向上移动
    bullets[1].unch_data.speedx = 0;
    bullets[1].hurt = 12;
    bullets[1].unch_data.height = 23;
    bullets[1].unch_data.width = 21;
    //三
    bullets[2].unch_data.image = al_load_bitmap("./data/image/myb_3.png");//3个
    if(!bullets[2].unch_data.image) return false;
    bullets[2].unch_data.speedy = -8;//向上移动
    bullets[2].unch_data.speedx = 0;
    bullets[2].hurt = 16;
    bullets[2].unch_data.height = 23;
    bullets[2].unch_data.width = 32;

    //敌人子弹，
    //红色圆型
    bullets[3].unch_data.image = al_load_bitmap("./data/image/emb_1.png");
    if(!bullets[3].unch_data.image) return false;
    bullets[3].unch_data.speedy = 7;//向下移动
    bullets[3].unch_data.speedx = 0;
    bullets[3].hurt = 10;
    bullets[3].unch_data.height = 15;
    bullets[3].unch_data.width = 15;

    //黄色长型
    bullets[4].unch_data.image = al_load_bitmap("./data/image/emb_2.png");
    if(!bullets[4].unch_data.image) return false;
    bullets[4].unch_data.speedy = 9;
    bullets[4].unch_data.speedx = 0;
    bullets[4].hurt = 5;
    bullets[4].unch_data.height = 17;
    bullets[4].unch_data.width = 10;

    //大红
    bullets[5].unch_data.image = al_load_bitmap("./data/image/emb_3.png");
    if(!bullets[5].unch_data.image) return false;
    bullets[5].unch_data.speedy = 6;
    bullets[5].unch_data.speedx = 0;
    bullets[5].hurt = 20;
    bullets[5].unch_data.height = 40;
    bullets[5].unch_data.width = 20;

    //导弹
    bullets[6].unch_data.image = al_load_bitmap("./data/image/emb_4.png");
    if(!bullets[6].unch_data.image) return false;
    bullets[6].unch_data.speedy = 6;
    bullets[6].unch_data.speedx = 0;
    bullets[6].hurt = 40;
    bullets[6].unch_data.height = 94;
    bullets[6].unch_data.width = 20;

    return true;
}

/*初始化子弹数组*/
bool inti_bullets(bull *pbu)
{
    pbu->data = NULL;
    pbu->plast = pbu->pnext = NULL;
    pbu->pos_x = pbu->pos_y = 0;
    return true;
}

/*加入一个子弹,传入头节点*/
bool add_one_bull(bull *pbu, bul *bu_type, int dx, int dy)
{
    bull *pnew = (bull*)malloc(sizeof(bull));//新节点
    if(!pnew) return false;
    bull *p_next = pbu->pnext;              //已存在的下一个节点
    //在头节点位置插入新节点
    pbu->pnext = pnew;
    pnew->pnext = p_next;
    pnew->plast = pbu;
    if(p_next != NULL)
        p_next->plast = pnew;
    //加入位置，和子弹类型
    pnew->data = bu_type;
    pnew->pos_x = dx;
    pnew->pos_y = dy;
    return true;
}

/*主机发射子弹*/
bool shoot_bullet(bull *pbu, hero_fi *fi, int level)
{
    //飞机头部坐标
    int x = fi->pos_x + fi->unch_data.width/2;
    int y = fi->pos_y;

    switch(level)
    {
    //0,1,2只发射一颗
    case 0:case 1:case 2:{
        int dx = x - bullets[level].unch_data.width/2;
        int dy = y - bullets[level].unch_data.height;

        return add_one_bull(pbu, &bullets[level], dx, dy);
    }
    //3,4,5只发射三颗
    case 3:case 4:case 5:{
        int lv = (level==3)? 1 : 2;

        int dx = x - bullets[lv].unch_data.width/2;
        int dy = y - bullets[lv].unch_data.height;
        //中间的子弹
        if(!add_one_bull(pbu, &bullets[lv], dx, dy)) break;
        dx = x - bullets[lv].unch_data.width*1.5;
        //左边的子弹
        if(!add_one_bull(pbu, &bullets[level - lv -2], dx, y)) break;
        dx = x + bullets[lv].unch_data.width*1.5 - bullets[level - lv -2].unch_data.width;
        //右边的子弹
        if(!add_one_bull(pbu, &bullets[level - lv -2], dx, y)) break;

        return true;
    }
    default: return false;
    }
    return false;
}

/*删除双链表节点*/
void de_bull(bull *pbu)
{
    if(pbu){
        if(pbu->pnext){//下一个节点不为空
           pbu->plast->pnext = pbu->pnext;
           pbu->pnext->plast = pbu->plast;
        }
        else{
            pbu->plast->pnext = NULL;
        }
        free(pbu);
    }
}

/*判断敌人能否射击*/
bool is_em_shoot(struct _em_prop *pgo, int time)
{
    return ((time - pgo->sh_time + FPS)%FPS >= pgo->unch_data->data.sh_speed);
}

/*敌人发射子弹*/
goods *ememy_shoot(bull *pbu, struct _em_prop *pgo, int time)
{
    if(pgo){
        goods *p_next = pgo->pnext;
        if(pgo->unch_data->type == PROP_EMEMY && is_em_shoot(pgo, time)){
            pgo->sh_time = time;
            em_shoot_mode(pgo, pbu, pgo->shmode);
        }
        return p_next;
    }
    return NULL;
}

/*所有存在的敌人发射子弹*/
void ememies_shoot(bull *pbu, struct _em_prop *pgo, int time)
{
    if(pgo->unch_data != NULL){
        ememy_shoot(pbu, pgo, time);
    }
    goods *p = pgo->pnext;
    while((p = ememy_shoot(pbu, p, time)) != NULL);
}

/*判断（x,y）是否超出屏幕，是返回false*/
bool is_beyond_display(int dx, int dy)
{
    return  dx>0 && dy>0 && dx<WIN_WIDTH && dy< WIN_HEIGHT;
}

/*移动单个子弹,并返回下一个子弹地址*/
bull * move_bull(bull *pbu)
{
    if(pbu){//不为空
        //修改坐标
        bull *p_next = pbu->pnext;
        pbu->pos_x += pbu->data->unch_data.speedx;
        pbu->pos_y += pbu->data->unch_data.speedy;
        //判断是否出界
        if(!is_beyond_display(pbu->pos_x, pbu->pos_y))
            de_bull(pbu);//删除该位置

        return p_next;
    }
    return NULL;
}

/*移动所有子弹,传入头节点*/
void move_bullte(bull *pbu)
{
    bull *p = pbu->pnext;
    while((p=move_bull(p)) != NULL);
}

/*绘制一个子弹，并返回它的下一个节点*/
bull *draw_bull(bull *pbu)
{
    if(pbu){
        bull *p_next = pbu->pnext;
        al_draw_bitmap(pbu->data->unch_data.image, pbu->pos_x, pbu->pos_y, 0);

        return p_next;
    }
    return NULL;
}

/*绘制所有子弹,传入头节点*/
void draw_bulltes(bull *pbu)
{
    bull *p = pbu->pnext;
    while((p = draw_bull(p)) != NULL);
}

/*释放bullets*/
void distory_bullets()
{
    al_destroy_bitmap(bullets[0].unch_data.image);
    al_destroy_bitmap(bullets[1].unch_data.image);
    al_destroy_bitmap(bullets[2].unch_data.image);
    al_destroy_bitmap(bullets[3].unch_data.image);
    al_destroy_bitmap(bullets[4].unch_data.image);
    al_destroy_bitmap(bullets[5].unch_data.image);
    al_destroy_bitmap(bullets[6].unch_data.image);

    //al_destroy_bitmap(bullets[7].image);
}

/*销毁bull链表*/
void distory_bull(bull *pbu)
{
    bull *p = pbu->pnext,*q;
    while(p){
        q = p->pnext;
        free(p);
        p = q;
    }
}
