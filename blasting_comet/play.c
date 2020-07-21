#include "play.h"

ALLEGRO_DISPLAY *display;           //显示设备
ALLEGRO_EVENT_QUEUE *event_queue;	//事件队列
ALLEGRO_TIMER *timer = NULL;        //计时器
ALLEGRO_BITMAP *background = NULL;  //背景
ALLEGRO_FONT *font = NULL;          //字体

int game_init()
{
    if (!al_init()) return 1;               //初始化失败返回1
    al_install_mouse();                     //初始化 鼠标
    al_install_keyboard();                  //初始化 键盘

    al_init_font_addon();                   //初始化字体插件
    al_init_ttf_addon();                    //初始化TTF插键
    font = al_load_ttf_font("./data/msyh.ttf", 20, 0 );//加载字体
    if(!font) return 1;

    //设置窗口
    display = al_create_display(WIN_WIDTH, WIN_HEIGHT);
    al_flip_display();
    if (!display)  return 2;                //窗口初始化失败返回2
    al_set_window_title(display, "-爆-破-彗-星-");//设置标题

    timer=al_create_timer(1.0/FPS);         //初始化计时器
    if(!timer) return 3;                    //计时器初始化失败返回3

    if(!al_init_image_addon()) return 4;    //图像插件初始化失败，返回4
    if(!load_audio())   return 5;           //初始化音频插件
    if (!al_reserve_samples(8)) return 6;

    if(!load_bullet()) return 7;            //加载子弹数据 bullets
    if(!load_prop()) return 8;              //初始化道具 gropes

    if(!load_img_aud()) return 9;           //加载部分图片和音效

    event_queue = al_create_event_queue();//初始化事件队列，接受到的消息将存储在该队列
    //指定要接收哪个设备的消息
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    return 0;
}

void inti_thread(th_data *arg, hero_fi *pfi, bull *pfibu, bull *pembu, goods *pgo, boom *pbo)
{
    arg->mutex = al_create_mutex();
    arg->cond = al_create_cond();

    arg->props = pgo;
    arg->em_die = pbo;
    arg->fi = pfi;
    arg->fi_bu = pfibu;
    arg->em_bu = pembu;
    arg->time = 0;
    arg->ready = false;
}

//加载部分图片和音频
bool load_img_aud()
{
    //声音
    img_aud.bgm_boom = al_load_sample("./data/bgm/boom.wav");   //爆炸音效
    img_aud.bgm_shoot =  al_load_sample("./data/bgm/shoot.wav");//射击音效
    if(!img_aud.bgm_shoot || !img_aud.bgm_boom) return false;   //加载音效失败z

    //边框图片
    img_aud.frame[0] = al_load_bitmap("./data/image/frame1.png");//选择框，未选中
    if(!img_aud.frame[0])
    {
        return false;
    }
    img_aud.frame[1] = al_load_bitmap("./data/image/frame2.png");//选择框，选中
    if(!img_aud.frame[1])
    {
        al_destroy_bitmap(img_aud.frame[0]);
        return false;
    }
    img_aud.frame[2] = al_load_bitmap("./data/image/frame3.png");//展示
    if(!img_aud.frame[2])
    {
        al_destroy_bitmap(img_aud.frame[0]);
        al_destroy_bitmap(img_aud.frame[1]);
        return false;
    }
    img_aud.frame[3] = al_load_bitmap("./data/image/frame4.png");//提示框
    if(!img_aud.frame[3])
    {
        al_destroy_bitmap(img_aud.frame[0]);
        al_destroy_bitmap(img_aud.frame[1]);
        al_destroy_bitmap(img_aud.frame[2]);
        return false;
    }

    //爆炸效果
    img_aud.boom[3] = al_load_bitmap("./data/image/boom1.png");
    if(!img_aud.boom[3])
    {
        return false;
    }
    img_aud.boom[2] = al_load_bitmap("./data/image/boom2.png");
    if(!img_aud.boom[2])
    {
        al_destroy_bitmap(img_aud.boom[3]);
        return false;
    }
    img_aud.boom[1] = al_load_bitmap("./data/image/boom3.png");
    if(!img_aud.boom[1])
    {
        al_destroy_bitmap(img_aud.boom[3]);
        al_destroy_bitmap(img_aud.boom[2]);
        return false;
    }
    img_aud.boom[0] = al_load_bitmap("./data/image/boom4.png");
    if(!img_aud.boom[0])
    {
        al_destroy_bitmap(img_aud.boom[3]);
        al_destroy_bitmap(img_aud.boom[2]);
        al_destroy_bitmap(img_aud.boom[1]);
        return false;
    }

    img_aud.blood[0] = al_load_bitmap("./data/image/blood_list1.png");//血条空
    if(!img_aud.blood[0])
    {
        return false;
    }
    img_aud.blood[1] = al_load_bitmap("./data/image/blood_list2.png");//血条满
    if(!img_aud.blood[1])
    {
        al_destroy_bitmap(img_aud.blood[0]);
        return false;
    }

    return true;
}

//处理游戏数据，
int game_data(th_data *data)
{
    em_shoot_fi(data->fi, data->em_bu);                         //敌人击中主机
    data->fi->grade += attack_ememies(data->props, data->fi_bu, data->em_die);//来自主机的击中处理
    em_hit_anaist(data->fi, data->props, data->em_die);         //发生碰撞
    move_bullte(data->fi_bu);                                   //移动主机的子弹
    move_bullte(data->em_bu);                                   //移动敌人的子弹
    ememies_shoot(data->em_bu, data->props, data->time);        //所有存在敌人发射子弹
    move_goods(data->props);                                    //移动敌人

    return 0;
}

int frame_run()
{
    int x = 0, y = 0;       //鼠标位置
    double angle = 0;       //弧度
    bool redraw = true;     //ture绘制图像

    //加载背景音乐
    ALLEGRO_SAMPLE *bg_music = al_load_sample("./data/bgm/frame.wav");
    if(!bg_music) return 0;
    ALLEGRO_SAMPLE_ID bgid;//用来停止音乐

    //加载飞机图片
    ALLEGRO_BITMAP *fi_image = al_load_bitmap("./data/image/player.png");
    if(!fi_image) return 0;

    //加载背景
    ALLEGRO_BITMAP *back = al_load_bitmap("./data/image/framebg.jpg");
    if(!back) return 0;

    //读取排行榜，和 初始化选择框内容
    FILE *stream = fopen("./data/map/rank.txt","r");
    char rank[5][9];//rank保存，缓冲区
    fscanf(stream ,"%s%s%s%s%s", rank[0], rank[1], rank[2], rank[3], rank[4]);
    char *str[3][6] = {
        {"start game", "rank", "exit game", "", "", ""},
        {"#1", "#2", "#3", "#4", "#5", "back"},
        {rank[0], rank[1], rank[2], rank[3], rank[4], "back"}
    };
    fclose(stream);

    int sw = -1;            //鼠标选择的选项框，没有选择=-1,从上到下 0～n
    int sh = 0;             //界面文字的深度，初始为0层
    int num = 3;            //选择栏数量，第0层，数量为3
    int mouse = -1;         //鼠标操作，只有左键有操作

    play_bg_music(bg_music, &bgid, 1.0);//播放音乐
    al_start_timer(timer);//开始计时
    while(1)
    {
       ALLEGRO_EVENT ev;
       al_wait_for_event(event_queue, &ev);

       if(ev.type == ALLEGRO_EVENT_TIMER)
       {
          redraw = true;
       }
       if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
       {
          break;
       }
       if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)   //鼠标按下
       {
           mouse = ev.mouse.button;//保存按下的键，
       }
       if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)          //鼠标移动
       {
           x = ev.mouse.x;//更新鼠标位置
           y = ev.mouse.y;
           sw = found_mouse(x, y, num);//判断鼠标是否指向某个选择框，没有返回-1
       }
       if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
       {
           if(mouse == 1 && sw != -1)
           {
               if(sh == 0)
               {
                   if(sw == 0) sh = 1;                  //进入选择关卡界面
                   else if(sw == 1) sh = 2;             //进入排行榜
                   else if(sw == 2) break;              //退出游戏
                   num = 6;
               }
               else if(sh == 1)
               {
                   if(sw == 5)
                   {
                       sh = 0;                          //返回主界面
                       num = 3;
                   }
                   else
                   {
                       stop_music(&bgid);               //暂停音乐
                       int grade;
                       int xx = atoi(str[2][sw]+3);
                       if((grade = game_run(sw+1)) > xx)
                       {
                           sprintf(str[2][sw],"#%d:%05d", sw+1, grade);
                       }
                       play_bg_music(bg_music, &bgid, 1.0);//从新播放音乐
                   }
               }
               else if(sh == 2)
               {
                   if(sw == 5)
                   {
                       sh = 0;//返回主界面
                       num = 3;
                   }
               }
           }
           mouse = 0;//
       }
       if(redraw && al_is_event_queue_empty(event_queue))
       {
          redraw = false;

          al_draw_bitmap(back, 0, 0, 1);//绘制背景
          draw_option(img_aud.frame[0], img_aud.frame[1], sw, num, str[sh]);//绘制选项
          al_draw_bitmap(img_aud.frame[2], 0, 0, 1);
          al_draw_tinted_scaled_rotated_bitmap_region(fi_image,130, 0, 65, 65
                                                      , al_map_rgba_f(0.7, 0.7, 0.7, 0.7)
                                                      , 32.5, 32.5, 89, 89, 1, 1, angle+=0.01, 1);

          al_flip_display();
       }
    }

    //将排行榜写入文件
    stream = fopen("./data/map/rank.txt","w");
    fprintf(stream, "%s\n%s\n%s\n%s\n%s\n", rank[0], rank[1], rank[2], rank[3], rank[4]);
    return 0;
}

//运行游戏
int game_run(int n)
{
    al_clear_to_color(al_map_rgb(0,0,0));//黑一会
    al_flip_display();
    al_rest(0.1);

    int grade = 0;                                  //游戏分数
    bool redraw = true;                             //为ture时候绘制图像
    short time = 0;                                 //时间，帧
    char str[50];                                   //缓冲区

    hero_fi fi;                                     //主机
    bull fi_bu,em_bu;                               //主机和敌人子弹保存位置，头节点
    goods props;                                    //道具，头节点
    boom fi_em;                                     //敌人死亡，


    if(!inti_fighter(&fi, "./data/image/player.png", 65, 65))  return 0;//初始化主机
    if(!inti_bullets(&fi_bu) || !inti_bullets(&em_bu))   return 0;       //初始化子弹节点
    if(!inti_grops(&props, &fi_em)) return 0;                           //初始化道具，敌人死亡节点

    th_data data;                                   //线程
    inti_thread(&data, &fi, &fi_bu, &em_bu, &props, &fi_em);
    ALLEGRO_THREAD *thread = al_create_thread(Func_Thread, &data);

    //加载地图信息
    inti_map();                                     //初始化地图信息
    sprintf(str,"./data/map/map%d.txt",n);
    FILE *fp = fopen(str,"r");
    if(!fp) return 0;

    sprintf(str,"./data/image/bg-%d.jpg",n);
    background = al_load_bitmap(str);               //加载背景图片
    if(!background) return 0;
    unsigned int back_dpostion = WIN_HEIGHT;        //背景绘制位置

    sprintf(str,"./data/bgm/pass%d.wav",n);
    ALLEGRO_SAMPLE *bg_music = al_load_sample(str); //加载背景音乐
    if(!bg_music) return 0;
    ALLEGRO_SAMPLE_ID bgid;
    play_bg_music(bg_music, &bgid, 1.0);

    al_start_thread(thread);
    while(1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);//等待一个事件

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            if(is_move(&fi, KEY_UP, 0))      fi.pos_y -= fi.unch_data.speedy;
            if(is_move(&fi, KEY_DOWN, 0))    fi.pos_y += fi.unch_data.speedy;
            if(is_move(&fi, KEY_LEFT, 0))    fi.pos_x -= fi.unch_data.speedx;
            if(is_move(&fi, KEY_RIGHT, 0))   fi.pos_x += fi.unch_data.speedx;
            if(is_move(&fi, KEY_SHOOW, time))       fi_em.aud_shoot = shoot_bullet(&fi_bu, &fi, fi.level);
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            goto end;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {//每当按下一个键时，就会生成 ALLEGRO_EVENT_KEY_DOWN 事件。
           switch(ev.keyboard.keycode)
           {
            case ALLEGRO_KEY_W://上
                fi.key[KEY_UP] = true;
                break;
            case ALLEGRO_KEY_S://下
                fi.key[KEY_DOWN] = true;
                break;
            case ALLEGRO_KEY_A://左
                fi.key[KEY_LEFT] = true;
                break;
            case ALLEGRO_KEY_D://右
                fi.key[KEY_RIGHT] = true;
                break;
            case ALLEGRO_KEY_J://发射
                fi.key[KEY_SHOOW] = true;
                break;
           }
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_UP)
        {//每当释放密钥时，就会生成 ALLEGRO_EVENT_KEY_UP 事件。
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_W:
                fi.key[KEY_UP] = false;
                break;
            case ALLEGRO_KEY_S:
                fi.key[KEY_DOWN] = false;
                break;
            case ALLEGRO_KEY_A:
                fi.key[KEY_LEFT] = false;
                break;
            case ALLEGRO_KEY_D:
                fi.key[KEY_RIGHT] = false;
                break;
            case ALLEGRO_KEY_J:
                fi.key[KEY_SHOOW] = false;
                break;
            case ALLEGRO_KEY_ESCAPE://按下ESC退出
                goto end;
           }
        }

        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;
            time = (time+ 1) % FPS;

            if(fi_em.aud_shoot)//有子弹发射，播放射击音频
            {
                play_once_music(img_aud.bgm_shoot, 1.5);
                fi_em.aud_shoot= false;
            }
            if(fi_em.aud_boom)//有敌人死亡，播放爆炸音效
            {
                play_once_music(img_aud.bgm_boom, 0.8);
                fi_em.aud_boom = false;
            }

            draw_game_bgbl(back_dpostion -= 2, fi.health);//背景移动图像速度为2
            if(back_dpostion <= 0) back_dpostion = WIN_HEIGHT;


            draw_fighter(&fi);
            if(fi.health <= 0)
            {
                grade = fi.grade;
                sprintf(str, "You're dead. Your garde is %d. ", grade);
                draw_tips(img_aud.frame[3], str);
                al_flip_display();
                al_rest(4);
                goto end;
            }

            if(time==0||time==30)                               //每办秒(30帧）读取一次
            {
                if(!read_map(&props, fp))                               //读到999进入if
                {
                    grade = fi.grade + fi.health;
                    sprintf(str, "You pass the customs. Your garde is %d.", grade);
                    draw_tips(img_aud.frame[3], str);
                    al_flip_display();
                    al_rest(3);
                    goto end;
                }
            }

            draw_booms(&fi_em);             //绘制爆炸效果
            draw_propes(&props);            //敌人和道具
            draw_bulltes(&fi_bu);           //主机子弹
            draw_bulltes(&em_bu);           //敌人子弹
            al_flip_display();              //刷新

            al_lock_mutex(data.mutex);
            data.time = time;
            data.ready = true;
            al_unlock_mutex(data.mutex);

        }
    }

    end:stop_music(bg_music);
    al_destroy_sample(bg_music);
    al_destroy_mutex(data.mutex);
    al_destroy_cond(data.cond);
    al_destroy_thread(thread);

    distory_bull(&fi_bu);
    distory_bull(&em_bu);
    distory_fighter(&fi);
    distory_boom(&fi_em);
    distory_goods(&props);

    fclose(fp);//关闭地图
    return grade;
}

//绘制游戏背景和血条
void draw_game_bgbl(int sy, int health)
{
    al_draw_bitmap_region(background, 0, sy, WIN_WIDTH, WIN_HEIGHT, 0, 0, 1);//游戏背景
    //信息栏和游戏界面分割位置
    al_draw_line( 0, WIN_HEIGHT-WIN_GARDE, WIN_WIDTH, WIN_HEIGHT-WIN_GARDE, al_map_rgb(255,255,255), 1);
    al_draw_bitmap(img_aud.blood[0], 0, WIN_HEIGHT-WIN_GARDE, 1);//先绘制空血条，血量最高500
    al_draw_bitmap_region(img_aud.blood[1], 399-380*health/500, 0, 61+380*health/500, 50, 0, WIN_HEIGHT-WIN_GARDE, 1);
}

//鼠标指向位置
int found_mouse(int x, int y, int n)
{
    int down_bound = WIN_HEIGHT/2 + n*25;   //下界，所有选择框上下范围
    int i = WIN_HEIGHT/2 - n*25;            //up_bound 上界
    int sp = -1;
    if(x > 215 && x < 425 && y < down_bound)//扩大了5PX判定范围
    {
        for(; i <= down_bound; i+=50){
            if(y<i) break;
            sp++;
        }
    }
    return sp;
}

//绘制选项框和内容
void draw_option(ALLEGRO_BITMAP *unsel, ALLEGRO_BITMAP *sel, int sw, int n, char **strs)
{
    int stx = WIN_HEIGHT/2 - n*25;
    for(int i=0; i<n ;i++)
    {
        if(sw != i){//未选中
            al_draw_bitmap(unsel, 220, stx, 1);
            al_draw_text(font, al_map_rgb(255, 255, 190), 320, stx + 7, ALLEGRO_ALIGN_CENTER, strs[i]);
        }
        else
        {
            al_draw_bitmap(sel, 220, stx, 1);
            al_draw_text(font, al_map_rgb(255, 200, 255), 320, stx + 7, ALLEGRO_ALIGN_CENTER, strs[i]);
        }
        stx += 50;
    }
}

//绘制提示信息
void draw_tips(ALLEGRO_BITMAP *bimmap, char *str)
{
    al_draw_bitmap(bimmap, 0, 400, 0.5);//图片是frame4.png
    al_draw_text(font, al_map_rgb(255, 255, 255), 320, 400, ALLEGRO_ALIGN_CENTER, str);
}

void *Func_Thread(ALLEGRO_THREAD *thr, void *arg)
{
    th_data *data = arg;
    while(!al_get_thread_should_stop(thr))
    {
        if(data->ready)
        {
            al_lock_mutex(data->mutex);
            game_data(data);//游戏信息处理
            data->ready = false;
            al_unlock_mutex(data->mutex);
        }
        al_rest(0.01);
    }
    return NULL;
}

int game_distory()
{
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    distory_bullets();
    distory_grop();

    al_destroy_bitmap(img_aud.frame[0]);
    al_destroy_bitmap(img_aud.frame[1]);
    al_destroy_bitmap(img_aud.frame[2]);
    al_destroy_bitmap(img_aud.frame[3]);
    al_destroy_bitmap(img_aud.boom[0]);
    al_destroy_bitmap(img_aud.boom[1]);
    al_destroy_bitmap(img_aud.boom[2]);
    al_destroy_bitmap(img_aud.boom[3]);
    al_destroy_bitmap(img_aud.blood[0]);
    al_destroy_bitmap(img_aud.blood[1]);

    return 0;
}
