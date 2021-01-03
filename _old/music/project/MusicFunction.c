#include "defineHeader.h"

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
    //init all voice value(mixer，voice)
    *mixer = al_create_mixer(al_get_sample_instance_frequency(instance), al_get_sample_instance_depth(instance), al_get_sample_instance_channels(instance));
    *voice = al_create_voice(al_get_sample_instance_frequency(instance), al_get_sample_instance_depth(instance), al_get_sample_instance_channels(instance));
    al_attach_sample_instance_to_mixer(instance, *mixer);
    al_attach_mixer_to_voice(*mixer, *voice);
}

void playing(ALLEGRO_MOUSE_STATE *mouse, ALLEGRO_SAMPLE_INSTANCE *instance, int *state){
    //play_state表示音樂是否在播放狀態, pause_state表示是否是暫停, 是:1 否:0
    int play_state = 1, pause_state = 0;
    float gain = 0.5; //增益(初值設0.5)
    unsigned int position; //聲音撥放到的位置
    ALLEGRO_BITMAP *loudspeaker = NULL, *background= NULL, *nosound = NULL;

    //導入圖片
    loudspeaker = al_load_bitmap("./img/music_icon/loudspeaker.jpg");
    background = al_load_bitmap("./img/back900.png");
    nosound = al_load_bitmap("./img/music_icon/nosound.jpg");

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
            if(mouse->x >= DISPLAY_WIDTH-150 && mouse->x <= DISPLAY_WIDTH-110 && mouse->y >= DISPLAY_HEIGHT-50 && mouse->y <=DISPLAY_HEIGHT-10)
            {
                if(play_state == 1)
                {
                    if(pause_state == 1)
                    {
                        //play按鈕變成pause按鈕並從上次播放到的時間點播放
                        al_draw_bitmap_region(background, DISPLAY_WIDTH-150, DISPLAY_HEIGHT-50, 40, 40, DISPLAY_WIDTH-150, DISPLAY_HEIGHT-50, 0);
                        al_draw_bitmap(loudspeaker, DISPLAY_WIDTH-150, DISPLAY_HEIGHT-50, 0);
                        pause_state = 0;
                        al_set_sample_instance_position(instance, position);//設定聲音播放的時間點
                        al_set_sample_instance_playing(instance, true);
                    }
                    else
                    {
                        //pause按鈕變成play按鈕並儲存目前播放到的時間點
                        al_draw_bitmap_region(background, DISPLAY_WIDTH-150, DISPLAY_HEIGHT-50, 40, 40, DISPLAY_WIDTH-150, DISPLAY_HEIGHT-50, 0);
                        al_draw_bitmap(nosound,DISPLAY_WIDTH-150, DISPLAY_HEIGHT-50, 0);
                        pause_state = 1;
                        play_state = 1;
                        position = al_get_sample_instance_position(instance);//得到聲音目前播放到的時間點
                        al_set_sample_instance_playing(instance, false);
                    }
                }
                    else
                   {
                    //play按鈕變成pause按鈕並從頭播放
                    al_draw_bitmap_region(background, DISPLAY_WIDTH-150, DISPLAY_HEIGHT-50, 40, 40, DISPLAY_WIDTH-150, DISPLAY_HEIGHT-50, 0);
                    al_draw_bitmap(loudspeaker,DISPLAY_WIDTH-150, DISPLAY_HEIGHT-50, 0);
                    pause_state = 0;
                    play_state = 1;
                    al_set_sample_instance_playing(instance, true);
                   }
            }
            else if(mouse->x >= DISPLAY_WIDTH-100 && mouse->x <= DISPLAY_WIDTH-60 && mouse->y >= DISPLAY_HEIGHT-50 && mouse->y <=DISPLAY_HEIGHT-10)
            {
                //將聲音增加原始聲音的0.1倍
                gain = gain + 0.1;
                al_set_sample_instance_gain(instance, gain);
            }
            else if(mouse->x >= DISPLAY_WIDTH-50 && mouse->x <=DISPLAY_WIDTH-10 && mouse->y >= DISPLAY_HEIGHT-50 && mouse->y <=DISPLAY_HEIGHT-10)
            {
                //將聲音減少原始聲音的0.1倍
                if(gain >= 0) //聲音大小不會小於0
                {
                    gain = gain - 0.1;
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
    al_destroy_bitmap(loudspeaker);
    al_destroy_bitmap(background);
    al_destroy_bitmap(nosound);
}
