#include "combat.h"
#include "play.h"

//敌人出现的纵坐标
const int EM_START_Y = -50;

/*加载道具的信息*/
bool load_prop()
{
    //黄色普通飞机，
    propes[0].data.image = al_load_bitmap("./data/image/ep_1.png");
    if(!propes[0].data.image) return false;
    propes[0].data.width = 65;
    propes[0].data.height = 42;
    propes[0].data.speedx = 1;
    propes[0].data.speedy = 2;
    propes[0].data.sh_speed = 50;
    propes[0].init_health = 50;//主角伤害暂时固定为 10
    propes[0].garde  = 10;
    propes[0].type = PROP_EMEMY;
    propes[0].init_shmode = SHOOT_ONE;
    propes[0].bullet = &bullets[3];//给敌人飞机附加子弹类型

    //蓝色普通飞机，均衡
    propes[1].data.image = al_load_bitmap("./data/image/ep_2.png");
    if(!propes[1].data.image) return false;
    propes[1].data.width = 55;
    propes[1].data.height = 44;
    propes[1].data.speedx = 2;
    propes[1].data.speedy = 3;
    propes[1].data.sh_speed = 50;
    propes[1].init_health = 35;
    propes[1].garde  = 6;
    propes[1].type = PROP_EMEMY;
    propes[1].init_shmode = SHOOT_ONE;
    propes[1].bullet = &bullets[3];

    //红色普通飞机，急速
    propes[2].data.image = al_load_bitmap("./data/image/ep_3.png");
    if(!propes[2].data.image) return false;
    propes[2].data.width = 40;
    propes[2].data.height = 30;
    propes[2].data.speedx = 3;
    propes[2].data.speedy = 4;
    propes[2].data.sh_speed = 50;
    propes[2].init_health = 20;
    propes[2].garde  = 4;
    propes[2].type = PROP_EMEMY;
    propes[2].init_shmode = SHOOT_ONE;
    propes[2].bullet = &bullets[3];

    //黄色高级飞机
    propes[3].data.image = al_load_bitmap("./data/image/ep_4.png");
    if(!propes[3].data.image) return false;
    propes[3].data.width = 80;
    propes[3].data.height = 56;
    propes[3].data.speedx = 2;
    propes[3].data.speedy = 1;
    propes[3].data.sh_speed = 50;
    propes[3].init_health = 100;
    propes[3].garde  = 20;
    propes[3].type = PROP_EMEMY;
    propes[3].init_shmode = SHOOT_WTWO;
    propes[3].bullet = &bullets[3];

    //红白高级飞机
    propes[4].data.image = al_load_bitmap("./data/image/ep_5.png");
    if(!propes[4].data.image) return false;
    propes[4].data.width = 60;
    propes[4].data.height = 44;
    propes[4].data.speedx = 2;
    propes[4].data.speedy = 3;
    propes[4].data.sh_speed = 50;
    propes[4].init_health = 45;
    propes[4].garde  = 15;
    propes[4].type = PROP_EMEMY;
    propes[4].init_shmode = SHOOT_HTWO;
    propes[4].bullet = &bullets[4];

    //绿色主角机
    propes[5].data.image = al_load_bitmap("./data/image/ep_6.png");
    if(!propes[5].data.image) return false;
    propes[5].data.width = 57;
    propes[5].data.height = 60;
    propes[5].data.speedx = 2;
    propes[5].data.speedy = 2;
    propes[5].data.sh_speed = 50;
    propes[5].init_health = 60;
    propes[5].garde  = 15;
    propes[5].type = PROP_EMEMY;
    propes[5].init_shmode = FAST_ONE;
    propes[5].bullet = &bullets[4];

    //紫白色飞行器
    propes[6].data.image = al_load_bitmap("./data/image/ep_7.png");
    if(!propes[6].data.image) return false;
    propes[6].data.width = 40;
    propes[6].data.height = 36;
    propes[6].data.speedx = 3;
    propes[6].data.speedy = 3;
    propes[6].data.sh_speed = 50;
    propes[6].init_health = 20;
    propes[6].garde  = 7;
    propes[6].type = PROP_EMEMY;
    propes[6].init_shmode = SHOOT_ONE;
    propes[6].bullet = &bullets[4];

/*****************************/

    //BOOS 1
    propes[7].data.image = al_load_bitmap("./data/image/boos_1.png");
    if(!propes[7].data.image) return false;
    propes[7].data.width = 200;
    propes[7].data.height = 60;
    propes[7].data.speedx = 1;
    propes[7].data.speedy = 1;
    propes[7].data.sh_speed = 50;
    propes[7].init_health = 10000;
    propes[7].garde  = 1000;
    propes[7].type = PROP_EMEMY;
    propes[7].init_shmode = NONE;

    propes[7].bullet = NULL;

    //BOOS_2
    propes[8].data.image = al_load_bitmap("./data/image/boos_2.png");
    if(!propes[8].data.image) return false;
    propes[8].data.width = 200;
    propes[8].data.height = 145;
    propes[8].data.speedx = 1;
    propes[8].data.speedy = 1;
    propes[8].data.sh_speed = 50;
    propes[8].init_health = 12000;
    propes[8].garde  = 1000;
    propes[8].type = PROP_EMEMY;
    propes[8].init_shmode = NONE;
    propes[8].bullet = NULL;


    //BOOS 3 9
    //boos 4 10
    //boos 5 11

/*****************************/

    //生命回复道具
    propes[12].data.image = al_load_bitmap("./data/image/health_up.png");
    if(!propes[12].data.image) return false;
    propes[12].data.width = 40;
    propes[12].data.height = 22;
    propes[12].data.speedx = 2;
    propes[12].data.speedy = 3;
    propes[12].data.sh_speed = 50;
    propes[12].init_health = 1;
    propes[12].garde  = 0;
    propes[12].type = PROP_HEALTH;
    propes[12].init_shmode = NONE;
    propes[12].bullet = NULL;
    //武器升级道具
    propes[13].data.image = al_load_bitmap("./data/image/myb_up.png");
    if(!propes[13].data.image) return false;
    propes[13].data.width = 30;
    propes[13].data.height = 30;
    propes[13].data.speedx = 2;
    propes[13].data.speedy = 3;
    propes[13].data.sh_speed = 50;
    propes[13].init_health = 1;
    propes[13].garde  = 0;
    propes[13].type = PROP_BUUP;
    propes[13].init_shmode = NONE;
    propes[13].bullet = NULL;

    return true;
}

/*每次开始游戏，初始化em_die,和 boom*/
bool inti_grops(goods *pgo, boom* pbo)
{
    memset(pgo, 0, sizeof(goods));
    memset(pbo, 0, sizeof(boom));
    pbo->image[0] = al_load_bitmap("./data/image/boom1.png");
    pbo->image[1] = al_load_bitmap("./data/image/boom2.png");
    pbo->image[2] = al_load_bitmap("./data/image/boom3.png");
    pbo->image[3] = al_load_bitmap("./data/image/boom4.png");
    if(!pbo->image[0] || !pbo->image[1] || !pbo->image[2] || !pbo->image[3])
        return false;
    return true;
}

//主机被敌人击中
void em_shoot_fi(hero_fi *fi, bull *pbu)
{
    bull *p = pbu->pnext;
    //飞机位置
    int rect1[4];
    rect1[0] = fi->pos_x;
    rect1[1] = rect1[0] + fi->unch_data.width;
    rect1[2] = fi->pos_y;
    rect1[3] = rect1[2] + fi->unch_data.height;

    while(p){
        int rect2[4];//敌人子弹位置
        rect2[0] = p->pos_x;
        rect2[1] = rect2[0] + p->data->unch_data.width;
        rect2[2] = p->pos_y;
        rect2[3] = rect2[2] + p->data->unch_data.height;

        bull *q = p;
        p = p->pnext;
        if(is_collision(rect1, rect2)){     //飞机与子弹碰撞
            fi->health -= q->data->hurt;    //生命减少
            de_bull(q);                     //删除
        }
    }
}

/*添加一个道具，传入头节点，
 * dx:出现的横坐标
 * type：道具类型
 * mode：移动方式
 * limiter:移动限制位置
 */
bool add_goods(goods *pgo, int dx, int type, int momode, int limiter)
{
    //申请节点
    goods *pnew = (goods*)malloc(sizeof(goods));
    if(!pnew) return false;
    //连接节点
    goods *p_next = pgo->pnext;
    if(p_next != NULL)
        p_next->plast = pnew;
    pnew->pnext = pgo->pnext;
    pgo->pnext = pnew;
    pnew->plast = pgo;
    //增加数据
    pnew->unch_data = &propes[type];
    pnew->health = pnew->unch_data->init_health;
    pnew->pos_x = dx;
    pnew->pos_y = EM_START_Y;
    pnew->sh_time = 0;
    pnew->momode = momode;
    pnew->shmode = pnew->unch_data->init_shmode;
    pnew->limiter = limiter;

    return true;
}

/*添加一个BOOS，存放在goods的头节点中*/
bool add_boos(goods *pgo, int type, int momode, int dy)
{
    pgo->unch_data = &propes[type];
    pgo->health = pgo->unch_data->init_health;
    pgo->pos_x = (WIN_WIDTH - pgo->unch_data->data.width)/2 ;
    pgo->pos_y = EM_START_Y*2;
    pgo->sh_time = 0;
    pgo->momode = momode;
    pgo->shmode = pgo->unch_data->init_shmode;
    pgo->limiter = 50;
    return true;
}

/*删除物品节点*/
void de_goods(goods *pgo)
{
    if(pgo){
        if(pgo->pnext){//下一个节点不为空
            pgo->plast->pnext = pgo->pnext;
            pgo->pnext->plast = pgo->plast;
            free(pgo);
        }
        else if(pgo->plast){//不是头节点
            pgo->plast->pnext = NULL;
            free(pgo);
        }
        else{
            pgo->unch_data = NULL;
        }
    }
}

/*移动一个道具*/
bull* move_good(goods *pgo)
{
    if(pgo){//不为空
        goods *p_next = pgo->pnext;
        if(!move_grop_mode(pgo, pgo->momode)){//判断是否出界
            de_goods(pgo);//删除该位置
        }
        return p_next;
    }
    return NULL;
}

/*移动所有道具*/
void move_goods(goods *pgo)
{
    if(pgo->unch_data != NULL){//单独处理头节点
        move_good(pgo);
    }
    goods *p = pgo->pnext;
    while((p = move_good(p)) != NULL);
}

/*绘制道具（一个）*/
goods* draw_prop(goods *pgo)
{
    if(pgo){
        al_draw_bitmap(pgo->unch_data->data.image, pgo->pos_x, pgo->pos_y, 0);
        return pgo->pnext;
    }
    return NULL;
}

/*绘制所有道具*/
void draw_propes(goods *pgo)
{
    if(pgo->unch_data){
        draw_prop(pgo);
    }
    goods *p = pgo->pnext;
    while((p = draw_prop(p)) != NULL);
}

/*击中敌人(单个)判定，一个子弹,rect[],敌机的四个坐标*/
bull *attack_em(goods *pgo, bull *pbu, boom *pbo, int rect[])
{
    if(pbu){
        bull *p_next = pbu->pnext;
        //子弹位置
        int rect_s[4];
        rect_s[0] = pbu->pos_x;
        rect_s[1] = rect_s[0] + pbu->data->unch_data.width;
        rect_s[2] = pbu->pos_y;
        rect_s[3] = rect_s[2] + pbu->data->unch_data.height;

        if(is_collision(rect, rect_s)){
            pgo->health -= pbu->data->hurt;     //敌人生命减少
            de_bull(pbu);
        }
        return p_next;
    }
    return NULL;
}

/*击中敌人(单个)判断,所有主机子弹*/
goods *attack_ememy(int *grade, goods *pgo, bull *pbu, boom *pbo)
{
    if(pgo){
        goods *p_next = pgo->pnext;
        //飞机位置
       int rect[4];
       rect[0] = pgo->pos_x;
       rect[1] = rect[0] + pgo->unch_data->data.width;
       rect[2] = pgo->pos_y;
       rect[3] = rect[2] + pgo->unch_data->data.height;

       bull *p = pbu->pnext;
       if(pgo->unch_data->type == PROP_EMEMY){
           while((p = attack_em(pgo, p, pbo, rect)) != NULL){
               if(pgo->health <= 0){
                   pbo->aud_boom = true;                        //爆炸音效
                   add_emdienode(pbo, rect);                    //死亡位置
                   *grade += pgo->unch_data->garde;
                   de_goods(pgo);
                   break;
               }
           }
       }
       return p_next;
    }
    return NULL;
}

/*击中敌人(全部)判定，所有主机子弹,返回得分*/
int attack_ememies(goods *pgo, bull *p_fi_bu, boom *pbo)
{
    int grade = 0;
    if(pgo->unch_data){
        attack_ememy(&grade, pgo, p_fi_bu, pbo);
    }
    goods *p = pgo->pnext;
    while((p = attack_ememy(&grade, p, p_fi_bu, pbo)) != NULL);

    return grade;
}

/*添加敌人死亡位置，绘制爆炸效果*/
bool add_emdienode(boom *pbo, int rect[])
{
    em_die *pnew = (em_die*)malloc(sizeof(em_die));
    if(!pnew) return false;

    em_die *phead = &pbo->head;//头节点
    //插入节点
    em_die *p_next = phead->pnext;
    if(p_next)
        p_next->plast = pnew;
    pnew->pnext = phead->pnext;
    phead->pnext = pnew;
    pnew->plast = phead;
    //添加数据
    pnew->pos_x = rect[0];
    pnew->pos_y = rect[2];
    pnew->boom_lv = 32;

    return true;
}

/*删除爆炸效果的节点*/
void de_boom(em_die *pbo)
{
    if(pbo){
        if(pbo->pnext){//下一个节点不为空
           pbo->plast->pnext = pbo->pnext;
           pbo->pnext->plast = pbo->plast;
        }
        else{
            pbo->plast->pnext = NULL;
        }
        free(pbo);
    }
}

/*绘制一个节点的爆炸图像*/
em_die* draw_boom(em_die *pbo, ALLEGRO_BITMAP *image[])
{
    if(pbo){
        em_die *p_next = pbo->pnext;
        al_draw_bitmap(image[(--pbo->boom_lv)/8], pbo->pos_x, pbo->pos_y, 0);
        if(pbo->boom_lv<0)
            de_boom(pbo);
        return p_next;
    }
    return NULL;
}
/*绘制一个链表中所有爆炸图像*/
void draw_booms(boom *pbo)
{
    em_die *p = pbo->head.pnext;
    while((p = draw_boom(p, pbo->image)) != NULL);
}

/*判断两个矩形是否重叠，有返回true*/
bool is_collision(int *rect1, int *rect2)
{
    //rect[x1, x2, y1, y2]
    if( (rect2[0] > rect1[0] && rect2[0] < rect1[1]) ||
        (rect2[1] > rect1[0] && rect2[1] < rect1[1]) ||
        (rect1[0] > rect2[0] && rect1[0] < rect2[1]) ||
        (rect1[1] > rect2[0] && rect1[1] < rect2[1]) )
    {
        if( (rect2[2] > rect1[2] && rect2[2] < rect1[3]) ||
            (rect2[3] > rect1[2] && rect2[3] < rect1[3]) ||
            (rect1[2] > rect2[2] && rect1[2] < rect2[3]) ||
            (rect1[3] > rect2[2] && rect1[3] < rect2[3]) )
            return true;
    }
    return false;
}

/*道具与主机发生碰撞后，数据处理，不变链表*/
void acr_after(goods *pgo, hero_fi *fi, boom *pbo)
{
    switch (pgo->unch_data->type) {
    case PROP_BUUP:
        if(fi->level<5)
            fi->level++;
        break;
    case PROP_EMEMY:
        pbo->aud_boom = true;
        fi->health -= pgo->health;
        break;
    case PROP_HEALTH:
        fi->health += 100;
        if(fi->health > 500)
            fi->health = 500;
    default:
        break;
    }
}

/*单个敌人是否与rect相交*/
goods *ememy_acr_fighter(goods *pgo, boom *pbo, hero_fi *fi, int rect[])
{
    if(pgo){
        goods *p_next = pgo->pnext;
        //道具位置
        int rect_s[4];
        rect_s[0] = pgo->pos_x;
        rect_s[1] = rect_s[0] + pgo->unch_data->data.width;
        rect_s[2] = pgo->pos_y;
        rect_s[3] = rect_s[2] + pgo->unch_data->data.height;

        if(is_collision(rect, rect_s)){
            acr_after(pgo, fi, pbo);
            de_goods(pgo);
        }
        return p_next;
    }
    return NULL;
}

/*所有道具与飞机相交*/
void em_hit_anaist(hero_fi *fi, goods *pgo, boom *pbo)
{
    //主机位置
    int rect[4];
    rect[0] = fi->pos_x;
    rect[1] = rect[0] + fi->unch_data.width;
    rect[2] = fi->pos_y;
    rect[3] = rect[2] + fi->unch_data.height;

    if(pgo->unch_data != NULL){
        ememy_acr_fighter(pgo, pbo, fi, rect);
    }
    goods *p = pgo->pnext;
    while((p = ememy_acr_fighter(p, pbo, fi, rect)) != NULL);
}

/*释放propes图像*/
void distory_grop()
{
    //普通敌人
    al_destroy_bitmap(propes[0].data.image);
    al_destroy_bitmap(propes[1].data.image);
    al_destroy_bitmap(propes[2].data.image);
    al_destroy_bitmap(propes[3].data.image);
    al_destroy_bitmap(propes[4].data.image);
    al_destroy_bitmap(propes[5].data.image);
    al_destroy_bitmap(propes[6].data.image);
    //BOOS
    al_destroy_bitmap(propes[7].data.image);
    al_destroy_bitmap(propes[8].data.image);
    al_destroy_bitmap(propes[9].data.image);
    //al_destroy_bitmap(propes[10].image);
    //al_destroy_bitmap(propes[11].image);

    al_destroy_bitmap(propes[12].data.image);
    al_destroy_bitmap(propes[13].data.image);
}

/*销毁goods链表*/
void distory_goods(goods *pgo)
{
    goods *p = pgo->pnext,*q;
    while(p){
        q = p->pnext;
        free(p);
        p = q;
    }
}

void distory_boom(boom *pbo)
{
    em_die *p = pbo->head.pnext,*q;
    while(p){
        q = p->pnext;
        free(p);
        p = q;
    }
}

