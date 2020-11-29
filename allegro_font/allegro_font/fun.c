#include "myheader.h"
void Random_Picture( int row,int col,int a[][COL],ALLEGRO_BITMAP* bitmap1,ALLEGRO_BITMAP* bitmap2,ALLEGRO_BITMAP* bitmap3,ALLEGRO_BITMAP* bitmap4,ALLEGRO_BITMAP* bitmap5,ALLEGRO_BITMAP* bitmap6)
//input:row,col,Array2D,圖片1,圖片2,圖片3,圖片4,圖片5,圖片6
//output:無回傳值
//結果:印出隨機二微陣列和隨機排列之圖片
{
    int i,j;
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            a[i][j]=rand()%6;
            printf( "%d ", a[ i ][ j ] );
            if(a[i][j]==0)
            {
                al_draw_bitmap(bitmap1,j*100,i*100, 0);
            }
            else if(a[i][j]==1)
            {
                al_draw_bitmap(bitmap2,j*100,i*100, 0);
            }
            else if(a[i][j]==2)
            {
                al_draw_bitmap(bitmap3,j*100,i*100, 0);
            }
            else if(a[i][j]==3)
            {
                al_draw_bitmap(bitmap4,j*100,i*100, 0);
            }
            else if(a[i][j]==4)
            {
                al_draw_bitmap(bitmap5,j*100,i*100, 0);
            }
            else if(a[i][j]==5)
            {
                al_draw_bitmap(bitmap6,j*100,i*100, 0);
            }
        }
        printf( "\n" );
    }

}

void Close_By_Space(int select){
    ALLEGRO_KEYBOARD_STATE keyboard_state;
        while (select != 1)
    {
        // Save the state of the keyboard specified at the time
        al_get_keyboard_state(&keyboard_state);

        // Check whether SPACE was held down or not.
        if (al_key_down(&keyboard_state, ALLEGRO_KEY_ESCAPE))
        {
            select = 1;
        }

        // Delay
        al_rest(0.01);
    }

}

void Close_Event(int select){
    ALLEGRO_KEYBOARD_STATE keyboard_state;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL; //拿來存事件 #1 (目前用於視窗X叉叉)
ALLEGRO_EVENT event; //拿來存事件 #2 (目前用於視窗X叉叉)
    while (select!= 1){
al_get_keyboard_state(&keyboard_state); // Save the state of the keyboard specified at the time
if(al_wait_for_event_timed(event_queue, &event, 0.1)) printf("-----#####-----\n"); //偵測活動(可偵測視窗X叉叉)
if (al_key_down(&keyboard_state, ALLEGRO_KEY_ESCAPE))select = 1; // Check whether ESC was held down or not.
if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) select = 1; //檢查-視窗X叉叉
if (event.type == ALLEGRO_EVENT_DISPLAY_SWITCH_IN) al_flip_display(); //修正視窗縮小後重新開啟東西會不見
al_rest(0.01); // Delay
}

}
