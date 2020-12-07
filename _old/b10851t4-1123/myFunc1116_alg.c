#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> //圖形
#include <allegro5/allegro_native_dialog.h> //對話視窗

//ALLEGRO_BITMAP* bitmap_c0 = NULL;

void MY_ALGO_DestroyCandyImgs(ALLEGRO_BITMAP **candyImgsAddr, int num)
// free imgs array
{
    int i = 0;
    for(i = 0; i < num; i++){
        al_destroy_bitmap(candyImgsAddr[i]);
    }
    free(candyImgsAddr);
}

ALLEGRO_BITMAP **MY_ALGO_CreateCandyImgs(int num)
// create imgs array
{
    ALLEGRO_BITMAP **addr = (ALLEGRO_BITMAP **) calloc(num, sizeof(ALLEGRO_BITMAP *));
    return addr;
}


void MY_ALGO_LoadCandyImgs(ALLEGRO_BITMAP **candyImgsAddr, int num)
//讀圖片
{
    int i = 0;
    char candyImgPath[20] = "./img/candy0.png";
    for(i = 0; i < num; i++){
        candyImgPath[11] = (char)(i + 48);//圖片編號
        candyImgsAddr[i] = al_load_bitmap(candyImgPath);
        //printf("addr: %s \n", candyImgPath);
    }
}

void MY_ALGO_DrawCandyImgs(int **mainArray, int row, int col, ALLEGRO_BITMAP **candyImgsAddr)
//畫圖片
{
    int x = 0, y = 0, n = 0;
    int i = 0, j = 0;

    y = 144;
    for(i = 0; i < row; i++){
        x = 32;
        for(j = 0; j < col; j++){
            n = mainArray[i][j]; // laod elmt in mainArray
            al_draw_bitmap(candyImgsAddr[n-1], x, y, 0); // Draw bitmap
            x += 80;
        }
        y += 80;
    }
}

void MY_ALGO_ErrMsg(char const *title, char const *text)
//錯誤對話框
{
    al_show_native_message_box(NULL, title, "", text, NULL, ALLEGRO_MESSAGEBOX_ERROR);
}

void MY_ALGO_MainProcess(int **mainArray, int row, int col, int numOfCandy, int displayWidth, int displayHeight)
//執行主要活動 num=fill Range
{
    int finish = 0;

    ALLEGRO_DISPLAY *display = NULL;  //display
    ALLEGRO_BITMAP *bkgImg = NULL;    //back ground Img
    ALLEGRO_BITMAP **candyImg = NULL; //candy Imgs: candyImg[n]
    ALLEGRO_EVENT_QUEUE *event_queue = NULL; //拿來存事件 #1 (目前用於視窗X叉叉)
    ALLEGRO_EVENT event;                     //拿來存事件 #2 (目前用於視窗X叉叉)
    ALLEGRO_KEYBOARD_STATE keyboard_state;

    /* Initialize Allegro */
    al_init();
    al_install_keyboard();
    al_init_image_addon();

    display = al_create_display(displayWidth, displayHeight); // Create allegro display
    event_queue = al_create_event_queue(); // Create allegro enevt detector #1
    al_register_event_source(event_queue, al_get_display_event_source(display)); // Create allegro enevt detector #2
    if(!event_queue) MY_ALGO_ErrMsg("Allegro5", "EVENT QUEUE HAS FAILED TO BE CREATED");

    /* Load bitmap(image) */
    bkgImg = al_load_bitmap("./img/bkg.png");
    candyImg = MY_ALGO_CreateCandyImgs(numOfCandy);
    MY_ALGO_LoadCandyImgs(candyImg, numOfCandy); //candy 0 's img is candyImg[0] ext...

    // draw and display
    al_draw_bitmap(bkgImg, 0, 0, 0);
    MY_ALGO_DrawCandyImgs(mainArray, row, col, candyImg);
    al_flip_display();

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
    al_destroy_bitmap(bkgImg);
    al_destroy_event_queue(event_queue);
    MY_ALGO_DestroyCandyImgs(candyImg, numOfCandy);

}
