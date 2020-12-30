#ifndef _RESOURSE_H_
#define _RESOURSE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //for utf
#include <inttypes.h> /* strtoimax */
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> //圖形
#include <allegro5/allegro_native_dialog.h> //對話視窗
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_video.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>



#define IMG_PATH_BKG "./img/background.png"


#define SFX_PATH_BKG "./sfx/bkg.wav"
#define SFX_PATH_ELMT "./sfx/elmt.wav"
#define SFX_PATH_DROP "./sfx/drop.wav"

#define FNT_PATH_DFT "./DFT_TL9.TTC"
#define FILE_PATH_SCORE "user.score"

#define COLOR_SCORE al_map_rgb(0,0,0)

/*Game State*/
#define GAME_STATE_TEST 7777
#define GAME_STATE_NULL 9999
#define GAME_STATE_FINISH 9900
#define GAME_STATE_BKG_DRAW 9930
#define GAME_STATE_PEOPLE_MOVE 9940
#define GAME_STATE_CRASH_9950


#define TIME_ELMT 0.4 //0.6
#define TIME_PER_DROP 0.1 //0.3
#define TIME_SCORE 0.5 //2

#define RANG_CANDY_MOVE_CONDITION 0.3

#define SCORE_DATA 10 //rank 資料筆數

#define FILE_EXIT_ID 1 //待整併

typedef struct RowStut{
    int id;
    int score;
    char name[20];
    char time[20];
}RowStut;

typedef struct NameStut{
    char name[20];
    int len;
}NameStut;

typedef struct ScoreDataStut{
    RowStut *data; //form data[0] to data[SCORE_DATA-1]
    RowStut temp;
} ScoreDataStut;

typedef struct AllegroObjStut{
    ALLEGRO_DISPLAY *display;  //display
    ALLEGRO_BITMAP *iconImg;    //ICON Img
    ALLEGRO_BITMAP *bkgImg;    //back ground Img

    //ALLEGRO_BITMAP *btnStartImg;
    //ALLEGRO_BITMAP *btnRankImg;
    //ALLEGRO_BITMAP *mainImg; //main layout img
    //ALLEGRO_BITMAP *handImg; //main layout img
    //ALLEGRO_BITMAP *candyBkgImg; //main layout img
    //ALLEGRO_BITMAP **candyImgs; //candy Imgs: candyImg[n]
    ALLEGRO_EVENT_QUEUE *event_queue; //拿來存事件 #1 (目前用於視窗X叉叉)
    ALLEGRO_EVENT events;                     //拿來存事件 #2 (目前用於視窗X叉叉)
    ALLEGRO_TIMER *timer;
    ALLEGRO_MIXER *mixer; // for sfx
    ALLEGRO_VOICE *voice;
    //ALLEGRO_SAMPLE *sfx_elmt;       /* pointer to sound file */
    //ALLEGRO_SAMPLE *sfx_drop;       /* pointer to sound file */
    //ALLEGRO_SAMPLE *sfx_bkg;  /* pointer to sound file */
    //ALLEGRO_SAMPLE_INSTANCE *sfi_elmt; //https://www.allegro.cc/forums/thread/611901
    //ALLEGRO_SAMPLE_INSTANCE *sfi_drop;
    //ALLEGRO_SAMPLE_INSTANCE *sfi_bkg;

    //ALLEGRO_FONT *font_60;
    //ALLEGRO_FONT *font_24;

    //ALLEGRO_MENU *menu; //待整併
    //LLEGRO_MENU *menu_1; //待整併
    ALLEGRO_KEYBOARD_STATE keyboard_state;
} AllegroObjStut;


typedef struct LayoutParmStut{
    int title_start_x;
    int title_start_y;
    int main_layout_center_x;
    int main_layout_center_y;
    int main_layout_actual_width;
    int main_layout_actual_height;
    int main_layout_start_x;
    int main_layout_start_y;
    int main_layout_candy_mask;
    int score_center_x;
    int score_center_y;
} LayoutParmStut;

typedef struct MainDataStut{
    struct tm *tm;
//    FILE *fileStream;
    //int scoreFileIsRead;
    //int row;
    //int col;
    //int round;
    int bkg_x;
    //int elmtStep; //消除的時候使用(消除的過程總共拆為TIME_ELMT*FPS步)
    //int elmtStepTotal; //TIME_ELMT*FPS
    //int dropStep;
    //int dropMax;
    //int dropStepTotal;
    //int scoreStep; //顯示分數的時候使用(消除的過程總共拆為TIME_SCORE*FPS步)
    //int scoreStepTotal; //TIME_SCORE*FPS
    int game_state; //遊戲進行狀態
    //int mouse_x, mouse_y;
    //int mouse_click, mouse_click_x, mouse_click_y;
    //NameStut usrName;
    //ScoreDataStut *scoreData;
    int breakPoint;
} MainDataStut;


void PrintTest_JWS();
AllegroObjStut *ClocAlgObj();
void AllegroDriverInit();
void AllegroObjectInit(AllegroObjStut *allegroObj);
void image_init(AllegroObjStut *allegroObj);

MainDataStut *ClocMainData();
void InitMainData(MainDataStut *mainData);
void CheckEvent(MainDataStut *mainData, AllegroObjStut *allegroObj);
void CheckGameState(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawDisplayAndFlip(MainDataStut *mainData, AllegroObjStut *allegroObj);
#endif //_RESOURSE_H_
