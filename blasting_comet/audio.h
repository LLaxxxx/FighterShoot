#ifndef AUDIO_H
#define AUDIO_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

int load_audio();//加载音频插件

void stop_music(ALLEGRO_SAMPLE_ID * id);//停止播放音乐
void play_bg_music(ALLEGRO_SAMPLE *sample, ALLEGRO_SAMPLE_ID *id, double volume);//播放背景音乐，循环
void play_once_music(ALLEGRO_SAMPLE *sample, double volume);//播放游戏音效，一次

//al_destroy_sample(sample);//卸载音频插件

#endif // AUDIO_H
