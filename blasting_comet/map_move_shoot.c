#include "map_move_shoot.h"

int data[4];//保存读取数据
int offset; //BOOS出现后读取字节数
bool bo_appear;//控制boos出现

/****************************************************************/

//移出范围返回false
//停下
bool move_ST()
{
    return true;
}

//上
bool move_U(goods *pgo)
{
    pgo->pos_y -= pgo->unch_data->data.speedy;
    if(pgo->pos_y < 0) return false;
    return true;
}

//下
bool move_D(goods *pgo)
{
    pgo->pos_y += pgo->unch_data->data.speedy;
    if(pgo->pos_y > WIN_HEIGHT) return false;
    return true;
}

//左
bool move_L(goods *pgo)
{
    pgo->pos_x -= pgo->unch_data->data.speedx;
    if(pgo->pos_x < 0) return false;
    return true;
}

//右
bool move_R(goods *pgo)
{
    pgo->pos_x += pgo->unch_data->data.speedx;
    if(pgo->pos_x > WIN_WIDTH) return false;
    return true;
}

//左下
bool move_DL(goods *pgo)
{
    pgo->pos_x -= pgo->unch_data->data.speedx;
    pgo->pos_y += pgo->unch_data->data.speedy;
    if(pgo->pos_x < 0 || pgo->pos_y > WIN_HEIGHT) return false;
    return true;
}

//右下
bool move_DR(goods *pgo)
{
    pgo->pos_x += pgo->unch_data->data.speedx;
    pgo->pos_y += pgo->unch_data->data.speedy;
    if(pgo->pos_x > WIN_WIDTH || pgo->pos_y > WIN_HEIGHT) return false;
    return true;
}

//左上
bool move_UL(goods *pgo)
{
    pgo->pos_x -= pgo->unch_data->data.speedx;
    pgo->pos_y -= pgo->unch_data->data.speedy;
    if(pgo->pos_x < 0 || pgo->pos_y < 0) return false;
    return true;
}

//右上
bool move_UR(goods *pgo)
{
    pgo->pos_x += pgo->unch_data->data.speedx;
    pgo->pos_y -= pgo->unch_data->data.speedy;
    if(pgo->pos_x > WIN_WIDTH|| pgo->pos_y < 0) return false;
    return true;
}

//先下再XXX
bool run_down_in_turn(goods *pgo, bool fun1(), bool fun2(), int lim)
{
    return (pgo->pos_y < lim)? fun1(pgo): fun2(pgo);
}

//先上再XXX
bool run_up_in_turn(goods *pgo, bool fun1(), bool fun2(), int lim)
{
    return (pgo->pos_y > lim)? fun1(pgo): fun2(pgo);
}

//选择移动方式
bool move_grop_mode(goods *pgo, int mode)
{
    switch(mode){
    case STOP:
        return true;
    case WALK_U:
        return move_U(pgo);
    case WALK_D:
        return move_D(pgo);
    case WALK_L:
        return move_L(pgo);
    case WALK_R:
        return move_R(pgo);
    case WALK_DL:
        return move_DL(pgo);
    case WALK_DR:
        return move_DR(pgo);
    case WALK_UL:
        return move_UL(pgo);
    case WALK_UR:
        return move_UR(pgo);
    case WALK_D_ST:
        return run_down_in_turn(pgo, move_D, move_ST, pgo->limiter);
    case WALK_D_U:
        return run_down_in_turn(pgo, move_D, move_U, pgo->limiter);
    case WALK_D_L:
        return run_down_in_turn(pgo, move_D, move_L, pgo->limiter);
    case WALK_D_R:
        return run_down_in_turn(pgo, move_D, move_R, pgo->limiter);
    case WALK_D_DL:
        return run_down_in_turn(pgo, move_D, move_DL, pgo->limiter);
    case WALK_D_DR:
        return run_down_in_turn(pgo, move_D, move_DR, pgo->limiter);
    case WALK_D_UL:
        return run_down_in_turn(pgo, move_D, move_UL, pgo->limiter);
    case WALK_D_UR:
        return run_down_in_turn(pgo, move_D, move_UR, pgo->limiter);
    case WALK_U_ST:
        return run_up_in_turn(pgo, move_U, move_ST, pgo->limiter);
    case WALK_U_D:
        return run_up_in_turn(pgo, move_U, move_D, pgo->limiter);
    case WALK_U_L:
        return run_up_in_turn(pgo, move_U, move_L, pgo->limiter);
    case WALK_U_R:
        return run_up_in_turn(pgo, move_U, move_R, pgo->limiter);
    case WALK_U_DL:
        return run_up_in_turn(pgo, move_U, move_DL, pgo->limiter);
    case WALK_U_DR:
        return run_up_in_turn(pgo, move_U, move_DR, pgo->limiter);
    case WALK_U_UL:
        return run_up_in_turn(pgo, move_U, move_UL, pgo->limiter);
    case WALK_U_UR:
        return run_up_in_turn(pgo, move_U, move_UR, pgo->limiter);
    default:
        return true;
    }
}

/****************************************************************/

//纵向两个
bool shoot_htwo(goods *pgo, bull *pbu, int spacing)
{
    //敌人头部位置
    int x = pgo->pos_x + pgo->unch_data->data.width/2;
    int y = pgo->pos_y + pgo->unch_data->data.height;

    x = x - pgo->unch_data->bullet->unch_data.width/2;
    if(add_one_bull(pbu, pgo->unch_data->bullet, x, y))
        return add_one_bull(pbu, pgo->unch_data->bullet, x, y - spacing);
    return false;
}

//横向发射num个子弹，间隔为spacing
bool shoot_nbullets(goods *pgo, bull *pbu, int spacing, int num)
{
    int spac = spacing + pgo->unch_data->bullet->unch_data.width;
    int dx = pgo->pos_x + (pgo->unch_data->data.width - pgo->unch_data->bullet->unch_data.width - spac*(num-1))/2;
    int dy = pgo->pos_y + pgo->unch_data->data.height;
    for(int i=0; i<num; i++)
    {
        if(!add_one_bull(pbu, pgo->unch_data->bullet, dx, dy))
            return false;
        dx += spac;
    }
    return true;
}

//随机横向数量射击，3～6个
bool rand_num_shoot(goods *pgo, bull *pbu, int spacing)
{
    int num = rand()%4 + 3;//每次发射子弹数随机（3～6）
    if(!shoot_nbullets(pgo, pbu, spacing, num))
        return false;
    return true;
}

//交叉射击，间距变化有规律，横向两个
bool shoot_across(goods *pgo, bull *pbu)
{
    static short acr_spa = 0;//交叉射击的间隔
    static short acr[15] = {0, 1, 2, 3, 4, 5 ,6 ,7 ,7 ,6 ,5 ,4 ,3 ,2 ,1};
    if(acr_spa == 15) acr_spa = 0;
    return shoot_nbullets(pgo, pbu, acr[acr_spa++] * 20, 2);
}

//快速射击
bool fast_shoot(goods *pgo, bull *pbu, int spacing, int num, int cut, bool fun())
{
    if(fun(pgo, pbu, spacing, num))
    {
        if(pgo->sh_time >= cut)
                pgo->sh_time -= cut;
        else
             pgo->sh_time = pgo->sh_time + FPS - cut;

        return true;
    }
    return false;
}

//选择射击类型
bool em_shoot_mode(goods *pgo, bull *pbu, int mode)
{
    switch(mode)
    {
    case NONE:
        return true;
    case SHOOT_ONE:
        return shoot_nbullets(pgo, pbu, 0, 1);
    case SHOOT_HTWO:
        return shoot_htwo(pgo, pbu, 30);
    case SHOOT_WTWO:
        return shoot_nbullets(pgo, pbu, 5, 2);
    case FAST_ONE:
        return fast_shoot(pgo, pbu, 0, 1, 15, shoot_nbullets);
    case FAST_HTWO:
        return fast_shoot(pgo, pbu, 30, 1, 15 , shoot_htwo);
    case FAST_WTWO:
        return fast_shoot(pgo, pbu, 5, 2, 15, shoot_nbullets);
    //BOOS
    case FASTEST_WWTTO:
        return fast_shoot(pgo, pbu, 160, 2, 40, shoot_nbullets);
    case SHOOT_MESSY:
        return fast_shoot(pgo, pbu, 100, 0, 0, rand_num_shoot);
    case FASTEST_ONE:
        return fast_shoot(pgo, pbu, 0, 1, 30, shoot_nbullets);
    case FASTEST_HTWO:
        return fast_shoot(pgo, pbu, 30, 1, 30 , shoot_htwo);
    case FASTEST_WTWO:
        return fast_shoot(pgo, pbu, 5, 2, 30, shoot_nbullets);
    case SHOOT_ACROSS:
        return fast_shoot(pgo, pbu, 0, 0, 40, shoot_across);
    default:
        return false;
    }
}

/*******************************/

void inti_map()
{
    offset = 0;       //初始为0,BOOS出现后，每read_map()一次，减少16
    bo_appear = false;//boos出现为true
}

bool read_map(goods *pgo, FILE *fp)
{
    //从fp中，读出资格整形数字，保存到data钟
    fscanf(fp,"%d%d%d%d",data,data+1,data+2,data+3);

    //BOOS没有出现
    if(bo_appear == false)
    {
        offset = 0;
        if(data[0]==999)        //游戏结束
            return false;
        else if(data[0]==800)   //添加一个BOOS
        {
            add_boos(pgo, data[1], WALK_D_ST, 50);
            bo_appear = true;
        }
        else if(data[1]!=-1)    //-1时不填加
            add_goods(pgo, data[0], data[1], data[2], data[3]);
    }
    //BOOS出现后
    else
    {
        offset -= 16;
        if(pgo->health > 0)
        {
            switch(data[0])
            {
            case 0://修改移动方式
                pgo->momode = data[1];
                pgo->limiter = data[3];
                break;
            case 1://修改攻击方式
                pgo->shmode = data[1];
                break;
            case 2://写该子弹类型
                pgo->unch_data->bullet = &bullets[data[1]];
                break;
            case 801://BOOS活动结束，文件读取位置倒退
                fseek(fp, offset, SEEK_CUR);
                offset = 0;
                break;
            }
        }
        else
        {
            //直接读取到 data[0]==801
            while(fscanf(fp,"%d%d%d%d",data,data+1,data+2,data+3)==4 && data[0]!=801 );
            bo_appear = false;  //boos消失
        }
    }
    return true;
}
