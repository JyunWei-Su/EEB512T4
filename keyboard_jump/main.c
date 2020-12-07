#include "defineHeader.h"

int main()
{
    int state = 1; //聲音播放的程式是否繼續執行, 是:1 否:0
    int row = 9, col = 9;
    int **mainArray;
    int test = 0;
    int finish; //判定while迴圈

    ALLEGRO_DISPLAY *display = NULL;  //display
    ALLEGRO_BITMAP *bkgImg = NULL;    //back ground Img
    ALLEGRO_BITMAP *Role = NULL;
    ALLEGRO_BITMAP **candyImg = NULL; //candy Imgs: candyImg[n]
    ALLEGRO_BITMAP *loudspeaker = NULL, *voiceU = NULL, *voiceD = NULL; //music icon
    ALLEGRO_EVENT_QUEUE *event_queue = NULL; //拿來存事件 #1 (目前用於視窗X叉叉)
    ALLEGRO_EVENT event;                     //拿來存事件 #2 (目前用於視窗X叉叉)

    ALLEGRO_SAMPLE *sample = NULL; //音檔放置
    ALLEGRO_SAMPLE_INSTANCE *instance = NULL; //聲音變數
    ALLEGRO_MIXER *mixer = NULL;
    ALLEGRO_VOICE *voice = NULL;

    ALLEGRO_KEYBOARD_STATE keyboard_state;
    ALLEGRO_MOUSE_STATE mouse;
    ALLEGRO_KEYBOARD_STATE KBstate; //鍵盤設定

    Match match;
    Paddle* paddlePtr = &match.paddle;
    /* Initialize Allegro */
    allegro_init();
    al_install_keyboard();
    initPaddle(paddlePtr, Role);
    /*載入音樂*/
    sample = al_load_sample("./music/test2.wav");//讀取要的音樂
    instance = al_create_sample_instance(sample);//創建聲音物件

    /*載入icon圖片*/
    loudspeaker = al_load_bitmap("./img/music_icon/loudspeaker.jpg");
    voiceU = al_load_bitmap("./img/music_icon/plus.png");
    voiceD = al_load_bitmap("./img/music_icon/minus.png");

    Role = al_load_bitmap("slime0.png");
    voice_init(instance, &mixer, &voice);//初始化聲音的播放
    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT); // Create allegro display

    event_queue = al_create_event_queue(); // Create allegro enevt detector #1
    al_register_event_source(event_queue, al_get_display_event_source(display)); // Create allegro enevt detector #2
    if(!event_queue)
        MY_ALGO_ErrMsg("Allegro5", "EVENT QUEUE HAS FAILED TO BE CREATED");

    /* Load bitmap(image) */
    bkgImg = al_load_bitmap("./img/back900.png");
    candyImg = MY_ALGO_CreateCandyImgs(FillRange);
    al_draw_bitmap(bkgImg, 0, 0, 0);
    /*Load voice icon*/
    al_draw_bitmap(loudspeaker, DISPLAY_WIDTH-150,DISPLAY_HEIGHT-50, 0);
    al_draw_bitmap(voiceU, DISPLAY_WIDTH-100, DISPLAY_HEIGHT-50, 0);
    al_draw_bitmap(voiceD, DISPLAY_WIDTH-50, DISPLAY_HEIGHT-50, 0);

    MY_ALGO_LoadCandyImgs(candyImg, FillRange); //candy 0 's img is candyImg[0] ext...

    //鍵盤讀入並跳躍
    while(finish == 0)
    {
        al_draw_bitmap(bkgImg, 0, 0, 0); //背景
        al_get_keyboard_state(&KBstate);
        if(al_key_down(&KBstate, ALLEGRO_KEY_ESCAPE))
        {
            finish = 1;
        }
        JumpPaddle(&match.paddle, &KBstate);  //移動
        Gravity0(0,3,&match.paddle); //重力(未按照現實)
        al_draw_bitmap(Role, paddlePtr->xLeft, paddlePtr->yLeft, 0); //畫腳色在視窗上
        al_rest(0.01);
        al_flip_display(); //顯示在視窗上
        al_clear_to_color(al_map_rgb(0, 0, 0)); //避免殘影
    }
    /* window title */
    al_set_window_title(display,"our game");

    /*執行主要function*/
    srand(time(0));
    mainArray = CreateAndRandIntArray2d(row, col, 1, FillRange); //先填入1~6 而後輸出的時候再扣1(0拿來當作要消除之用)
    PrintfIntArray2dAddAValue(mainArray, row, col, "mainArray:\n", " ", -1); // print initial mainArray
    nl;

    //MY_ALGO_DrawCandyImgs(mainArray, row, col, candyImg);
    al_flip_display();

    if(state == 1)
    {
        playing(&mouse, instance, &state);
    }

    /* Cleanup, Free Dynamic Memory */
    al_destroy_display(display);
    MY_ALGO_DestroyCandyImgs(candyImg, FillRange);
    FreeArray2d(mainArray, row);
    al_destroy_bitmap(voiceU);
    al_destroy_bitmap(voiceD);
    al_destroy_bitmap(loudspeaker);
    al_destroy_voice(voice);
    al_destroy_mixer(mixer);
    al_destroy_sample_instance(instance);
    al_destroy_sample(sample);

    return 0;
}
