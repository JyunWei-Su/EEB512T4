#include "myHeader.h"

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

void layout_init()
{
    ALLEGRO_BITMAP *enlarge = NULL, *narrow = NULL, *stop = NULL, *frame = NULL, *pause = NULL, *cross = NULL;

    //導入圖片
    enlarge = al_load_bitmap("./pic/enlarge.png");
    narrow = al_load_bitmap("./pic/narrow.png");
    stop = al_load_bitmap("./pic/stop.png");
    frame = al_load_bitmap("./pic/frame.png");
    pause = al_load_bitmap("./pic/pause.png");
    cross = al_load_bitmap("./pic/cross.png");

    //將圖片導入buffer
    al_draw_bitmap(frame, 0, 0, 0);
    al_draw_bitmap(pause, 20, 5, 0);
    al_draw_bitmap(stop, 80, 5, 0);
    al_draw_bitmap(enlarge, 140, 5, 0);
    al_draw_bitmap(narrow, 200, 5, 0);
    al_draw_bitmap(cross, 260, 5, 0);

    //顯示圖片
    al_flip_display();

    //釋放不需要的動態記憶體空間
    al_destroy_bitmap(enlarge);
    al_destroy_bitmap(narrow);
    al_destroy_bitmap(stop);
    al_destroy_bitmap(frame);
    al_destroy_bitmap(pause);
    al_destroy_bitmap(cross);
}

void playing(ALLEGRO_MOUSE_STATE *mouse, ALLEGRO_SAMPLE_INSTANCE *instance, int *state)
{
    //play_state表示音樂是否在播放狀態, pause_state表示是否是暫停, 是:1 否:0
    int play_state = 1, pause_state = 0;
    float gain = 0.5;
    unsigned int position; //目前聲音播放到的時間點
    ALLEGRO_BITMAP *play = NULL, *frame = NULL, *pause = NULL;

    //導入圖片
    play = al_load_bitmap("./pic/play.png");
    frame = al_load_bitmap("./pic/frame.png");
    pause = al_load_bitmap("./pic/pause.png");

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
            if(mouse->x >= 20 && mouse->x <= 70 && mouse->y >= 5 && mouse->y <=55)
            {
                if(play_state == 1)
                {
                    if(pause_state == 1)
                    {
                        //play按鈕變成pause按鈕並從上次播放到的時間點播放
                        al_draw_bitmap_region(frame, 20, 5, 50, 50, 20, 5, 0);
                        al_draw_bitmap(pause, 20, 5, 0);
                        pause_state = 0;
                        al_set_sample_instance_position(instance, position);//設定聲音播放的時間點
                        al_set_sample_instance_playing(instance, true);
                    }
                    else
                    {
                        //pause按鈕變成play按鈕並儲存目前播放到的時間點
                        al_draw_bitmap_region(frame, 20, 5, 50, 50, 20, 5, 0);
                        al_draw_bitmap(play, 20, 5, 0);
                        pause_state = 1;
                        play_state = 1;
                        position = al_get_sample_instance_position(instance);//得到聲音目前播放到的時間點
                        al_set_sample_instance_playing(instance, false);
                    }
                }
                else
                {
                    //play按鈕變成pause按鈕並從頭播放
                    al_draw_bitmap_region(frame, 20, 5, 50, 50, 20, 5, 0);
                    al_draw_bitmap(pause, 20, 5, 0);
                    pause_state = 0;
                    play_state = 1;
                    al_set_sample_instance_playing(instance, true);
                }
            }
            else if(mouse->x >= 80 && mouse->x <= 130 && mouse->y >= 5 && mouse->y <=55)
            {
                if(play_state == 1)
                {
                     //pause按鈕變成play按鈕並停止聲音播放
                    al_draw_bitmap_region(frame, 20, 5, 50, 50, 20, 5, 0);
                    al_draw_bitmap(play, 20, 5, 0);
                    pause_state = 0;
                    play_state = 0;
                    al_set_sample_instance_playing(instance, false);
                }
            }
            else if(mouse->x >= 140 && mouse->x <= 190 && mouse->y >= 5 && mouse->y <=55)
            {
                //將聲音增加原始聲音的0.05倍
                gain = gain + 0.05;
                al_set_sample_instance_gain(instance, gain);
            }
            else if(mouse->x >= 200 && mouse->x <= 250 && mouse->y >= 5 && mouse->y <=55)
            {
                //將聲音減少原始聲音的0.05倍
                if(gain >= 0) //聲音大小不會小於0
                {
                    gain = gain - 0.05;
                }
                al_set_sample_instance_gain(instance, gain);
            }
            else if(mouse->x >= 260 && mouse->x <= 310 && mouse->y >= 5 && mouse->y <=55)
            {
                //程式結束執行
                *state = 0;
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
    al_destroy_bitmap(frame);
    al_destroy_bitmap(pause);
}
