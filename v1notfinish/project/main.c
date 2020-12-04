#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "defineHeader.h"

int main(){
    int finish = 0;
    int row = 9, col = 9;
    int **mainArray;
    int state = 1; //聲音播放的程式是否繼續執行, 是:1 否:0

    ALLEGRO_DISPLAY *display = NULL;  //display
    ALLEGRO_BITMAP *bkgImg = NULL;    //back ground Img
    ALLEGRO_BITMAP **candyImg = NULL; //candy Imgs: candyImg[n]
    ALLEGRO_EVENT_QUEUE *event_queue = NULL; //拿來存事件 #1 (目前用於視窗X叉叉)
    ALLEGRO_EVENT event;                     //拿來存事件 #2 (目前用於視窗X叉叉)
    ALLEGRO_KEYBOARD_STATE keyboard_state;
    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *instance = NULL;
    ALLEGRO_MIXER *mixer = NULL;
    ALLEGRO_VOICE *voice = NULL;
    ALLEGRO_MOUSE_STATE mouse;
    ALLEGRO_BITMAP *enlarge = NULL, *narrow = NULL, *loudspeaker = NULL;
    allegro_init();
    /* Initialize Allegro */
    al_install_keyboard();

    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT); // Create allegro display
    event_queue = al_create_event_queue(); // Create allegro enevt detector #1
    al_register_event_source(event_queue, al_get_display_event_source(display)); // Create allegro enevt detector #2
    if(!event_queue) MY_ALGO_ErrMsg("Allegro5", "EVENT QUEUE HAS FAILED TO BE CREATED");

    sample = al_load_sample("./music/test2.wav");//讀取要的音樂
    instance = al_create_sample_instance(sample);//創建聲音物件
    voice_init(instance, &mixer, &voice);//初始化聲音的播放
    /* Load bitmap(image) */
    bkgImg = al_load_bitmap("./img/bkg.png");
    candyImg = MY_ALGO_CreateCandyImgs(FillRange);
    MY_ALGO_LoadCandyImgs(candyImg, FillRange); //candy 0 's img is candyImg[0] ext...

    /*執行主要function*/
    srand(time(0));
    mainArray = CreateAndRandIntArray2d(row, col, 1, FillRange); //先填入1~6 而後輸出的時候再扣1(0拿來當作要消除之用)
    PrintfIntArray2dAddAValue(mainArray, row, col, "mainArray:\n", " ", -1); // print initial mainArray
    nl;

    // draw and display
    al_draw_bitmap(bkgImg, 0, 0, 0);
    MY_ALGO_DrawCandyImgs(mainArray, row, col, candyImg);
    enlarge = al_load_bitmap("./img/music_icon/plus.png");
    narrow = al_load_bitmap("./img/music_icon/minus.png");
    loudspeaker = al_load_bitmap("./img/music_icon/loudspeaker.jpg");

    //將圖片導入buffer
    al_draw_bitmap(loudspeaker, 1400, 850, 0);
    al_draw_bitmap(enlarge, 1450, 850, 0);
    al_draw_bitmap(narrow, 1500, 850, 0);
    al_flip_display();

    if(state == 1)
    {
        playing(&mouse, instance, &state);
    }

    while (finish != 1){
        al_get_keyboard_state(&keyboard_state); // Save the state of the keyboard specified at the time
        if(al_wait_for_event_timed(event_queue, &event, 0.1)) printf("-----#####-----\n"); //偵測活動(可偵測視窗X叉叉)
        if (al_key_down(&keyboard_state, ALLEGRO_KEY_ESCAPE)) finish = 1; // Check whether ESC was held down or not.
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) finish = 1; //檢查-視窗X叉叉
        if (event.type == ALLEGRO_EVENT_DISPLAY_SWITCH_IN) al_flip_display(); //修正視窗縮小後重新開啟東西會不見
        al_rest(0.01); // Delay
    }
    /* Cleanup, Free Dynamic Memory */
    al_destroy_display(display);
    MY_ALGO_DestroyCandyImgs(candyImg, FillRange);
    FreeArray2d(mainArray, row);
    al_destroy_voice(voice);
    al_destroy_mixer(mixer);
    al_destroy_sample_instance(instance);
    al_destroy_sample(sample);
    al_destroy_bitmap(enlarge);
    al_destroy_bitmap(narrow);
    al_destroy_bitmap(loudspeaker);
    return 0;
}
