#include "audio.h"

//加载音频插件
int load_audio()
{
    if(!al_install_audio())//安装音频子系统
    {
       return 0;
    }
    if(!al_init_acodec_addon())//安装音频编解码器
    {
       return 0;
    }
    return 1;
}

//停止播放音乐
void stop_music(ALLEGRO_SAMPLE_ID *id)
{
    al_stop_sample(id);
}

//播放背景音乐，循环
void play_bg_music(ALLEGRO_SAMPLE *sample, ALLEGRO_SAMPLE_ID *id, double volume)
{
    al_play_sample(sample, volume, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, id);
}

//播放游戏音效，一次
void play_once_music(ALLEGRO_SAMPLE *sample, double volume)
{
    al_play_sample(sample, volume, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

//al_destroy_sample(sample);//卸载音频插件
