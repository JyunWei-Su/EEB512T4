#include "myHeader.h"

int main()
{
    int state = 1; //聲音播放的程式是否繼續執行, 是:1 否:0
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *instance = NULL;
    ALLEGRO_MIXER *mixer = NULL;
    ALLEGRO_VOICE *voice = NULL;
    ALLEGRO_MOUSE_STATE mouse;

    allegro_init(); //初始化所有需要用到的allegro函式
    sample = al_load_sample("./music/test2.wav");//讀取要的音樂
    display = al_create_display(330, 60);//創建視窗
    instance = al_create_sample_instance(sample);//創建聲音物件

    voice_init(instance, &mixer, &voice);//初始化聲音的播放

    layout_init();//剛打開的介面

    if(state == 1)
    {
        playing(&mouse, instance, &state);
    }

    //釋放所有動態記憶體空間
    al_destroy_voice(voice);
    al_destroy_mixer(mixer);
    al_destroy_sample_instance(instance);
    al_destroy_sample(sample);
    al_destroy_display(display);
    return 0;
}
