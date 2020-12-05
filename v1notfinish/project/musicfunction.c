#include "defineHeader.h"
#include <stdio.h>
#include <stdlib.h>
void allegro_init()
{
    al_init();
    al_init_image_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_install_mouse();
    al_reserve_samples(2);//預定聲音物件的空間
}

void voice_init(ALLEGRO_SAMPLE_INSTANCE *instance, ALLEGRO_MIXER **mixer, ALLEGRO_VOICE **voice)
{
    //創建聲音輸出buffer
    *mixer = al_create_mixer(al_get_sample_instance_frequency(instance), al_get_sample_instance_depth(instance), al_get_sample_instance_channels(instance));
    //創建聲音輸出連接口
    *voice = al_create_voice(al_get_sample_instance_frequency(instance), al_get_sample_instance_depth(instance), al_get_sample_instance_channels(instance));
    al_attach_sample_instance_to_mixer(instance, *mixer);//將聲音物件link buffer
    al_attach_mixer_to_voice(*mixer, *voice);//將buffer link 輸出連接口
}


void playing(ALLEGRO_MOUSE_STATE *mouse, ALLEGRO_SAMPLE_INSTANCE *instance, int *state)
{
    //play_state表示音樂是否在播放狀態, pause_state表示是否是暫停, 是:1 否:0
    int play_state = 1, pause_state = 0;
    float gain = 0.5;
    unsigned int position; //目前聲音播放到的時間點
    ALLEGRO_BITMAP *play = NULL, *pause = NULL, *background = NULL;

    //導入圖片
    play = al_load_bitmap("./img/mucic_icon/loudspeaker.jpg");
    pause = al_load_bitmap("./img/music_icon/nosound.jpg");
    //background = al_load_bitmap("./img/bkg.png");
    //設定聲音初始狀態
    al_set_sample_instance_gain(instance, gain);//設定聲音播放的大小
    al_set_sample_instance_playmode(instance, ALLEGRO_PLAYMODE_LOOP);//設定聲音播放的模式(單一, 循環, 雙向?)
    al_set_sample_instance_playing(instance, true);//設定聲音播放的狀態(play or not)
    while(*state == 1)
    {
        al_get_mouse_state(mouse); //偵測滑鼠目前的狀態
        if(mouse->buttons & 1) //偵測滑鼠左鍵
        {
            //偵測play或pause圖片的位置
            if(mouse->x >= 1400 && mouse->x <= 1440 && mouse->y >= 850 && mouse->y <=890)
            {
                if(play_state == 1)
                {
                    if(pause_state == 1)
                    {
                        //play按鈕變成pause按鈕並從上次播放到的時間點播放
                        //al_draw_bitmap_region(background, 1400, 850, 40, 40, 1400, 850, 0);
                        al_draw_bitmap(pause, 1400, 850, 0);
                        pause_state = 0;
                        al_set_sample_instance_position(instance, position);//設定聲音播放的時間點
                        al_set_sample_instance_playing(instance, true);
                    }
                    else
                    {
                        //pause按鈕變成play按鈕並儲存目前播放到的時間點
                        //al_draw_bitmap_region(background, 1400, 850, 40, 40, 1400, 850, 0);
                        al_draw_bitmap(play, 1400, 850, 0);
                        pause_state = 1;
                        play_state = 1;
                        position = al_get_sample_instance_position(instance);//得到聲音目前播放到的時間點
                        al_set_sample_instance_playing(instance, false);
                    }
                }
                else
                {
                    //play按鈕變成pause按鈕並從頭播放
                    //al_draw_bitmap_region(background, 1400, 850, 40, 40, 1400, 850, 0);
                    al_draw_bitmap(pause, 1400, 850, 0);
                    pause_state = 0;
                    play_state = 1;
                    al_set_sample_instance_playing(instance, true);
                }
            }
            else if(mouse->x >= 1450 && mouse->x <= 1490 && mouse->y >= 850 && mouse->y <=890)
            {
                //將聲音增加原始聲音的0.05倍
                gain = gain + 0.05;
                al_set_sample_instance_gain(instance, gain);
            }
            else if(mouse->x >= 1500 && mouse->x <= 1540 && mouse->y >= 850 && mouse->y <=890)
            {
                //將聲音減少原始聲音的0.05倍
                if(gain >= 0) //聲音大小不會小於0
                {
                    gain = gain - 0.05;
                }
                al_set_sample_instance_gain(instance, gain);
            }
            //印出現在滑鼠所在的位置
            printf("mouse_position(%d, %d)\n", mouse->x, mouse->y);
        }
        //顯示圖片
        al_flip_display();
        //程式暫停0.1秒
        al_rest(0.1);
    }

    //釋放不需要的動態記憶體空間
    al_destroy_bitmap(play);
    al_destroy_bitmap(pause);
}


