#ifndef _RESOURSE_H_
#define _RESOURSE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //for utf
#include <inttypes.h> /* strtoimax */
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> //圖形
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h> //對話視窗
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

#define PATH_IMG_BKG "./img/back900.png"
#define PATH_IMG_ICON "./img/icon.tga"
#define PATH_IMG_COIN "./img/coin.png"
#define PATH_IMG_CHAR "./img/char.png"
#define PATH_IMG_MENU_BUTTON "./img/menuButton.png"
#define PATH_IMG_MODE_BUTTON "./img/menuButton.png"
#define PATH_IMG_HOME_BUTTON_1 "./img/homeButton_1.png"
#define PATH_IMG_HOME_BUTTON_2 "./img/homeButton_2.png"
#define PATH_FNT_DFT "./DFT_TL9.TTC"
#define PATH_SFX_BACKGROUND "./sfx/bkg.wav"
#define PATH_FILE_SCORE "user.score"
#define PATH_FONT_HIMAJI "./font/KFhimajiFACE.otf"

#define COLOR_SCORE al_map_rgb(255, 255, 255)
#define COLOR_CLEAR al_map_rgb(0,0,0)
#define COLOR_MENU_BUTTON_A al_map_rgb(199, 258, 250)
#define COLOR_MENU_BUTTON_B al_map_rgb(20, 119, 130)
#define COLOR_MODE_BUTTON_A al_map_rgb(199, 258, 250)
#define COLOR_MODE_BUTTON_B al_map_rgb(20, 119, 130)

#define SIZE_IMG_BKG_WIDTH 4800
#define SIZE_IMG_BKG_HEIGHT 900
#define SIZE_IMG_SCOREBOARD_ICON_WIDTH 64
#define SIZE_IMG_SCOREBOARD_ICON_HEIGHT 64
#define SIZE_IMG_MENU_BUTTON_WIDTH 480
#define SIZE_IMG_MENU_BUTTON_HEIGHT 90
#define SIZE_IMG_MODE_BUTTON_WIDTH 480
#define SIZE_IMG_MODE_BUTTON_HEIGHT 90
#define SIZE_IMG_HOME_BUTTON_WIDTH 128
#define SIZE_IMG_HOME_BUTTON_HEIGHT 128

/*Game State*/
#define RANG_CANDY_MOVE_CONDITION 0.3

#define SCORE_DATA 10 //rank 資料筆數
#define NUM_MENU_BUTTON 4
#define NUM_MODE_BUTTON 3
#define NUM_SAMPLES 3 //聲音數量
#define SCALE_MENU_BUTTON 1.2
#define SCALE_MODE_BUTTON 1.2
#define OFFSET_MENU 1.5
#define OFFSET_MODE 1.5
#define OFFSET_SCOREBOARD_TEXT 320

#define FILE_EXIT_ID 1 //待整併

typedef enum GameState {
    GAME_NONE, GAME_TEST, GAME_FINISH,
    GAME_OPERATE, GAME_DRAW,
    GAME_MODE_SELECT, GAME_RULE, GAME_RANK, GAME_MENU, GAME_ABOUT,
    GAME_PLAYING,
} GameState;

typedef enum PlayMode {
    MODE_EASY, MODE_MEDIUM, MODE_HARD,
} PlayMode;

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

typedef struct ScoreStut{
    int chars;
    int coins;
    int score;
} ScoreStut;

typedef struct ButtonStut{
    float start_x, start_y;
    float end_x, end_y;
    char *text;
    bool isSelected;
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *img2;
} ButtonStut;

typedef struct ScoreboardStut{
    float start_x, start_y;
    float end_x, end_y;
    ALLEGRO_BITMAP *img;
} ScoreboardStut;

typedef struct BackgroundStut{
    float x, y;
    ALLEGRO_BITMAP *Img;    //back ground Img
    int state;
} BackgroundStut;

typedef struct FontStut{
    ALLEGRO_FONT *font24;
    ALLEGRO_FONT *font36;
    ALLEGRO_FONT *font48;
    ALLEGRO_FONT *font64;
    ALLEGRO_FONT *font90;
    ALLEGRO_FONT *font120;
} FontStut;

typedef struct SoundStut{
    ALLEGRO_MIXER *mixer; // for sfx
    ALLEGRO_VOICE *voice;

    ALLEGRO_SAMPLE *sfx_background;  /* pointer to sound file */
    ALLEGRO_SAMPLE_INSTANCE *sfi_background; //https://www.allegro.cc/forums/thread/611901

} SoundStut;

typedef struct AllegroObjStut{
    ALLEGRO_DISPLAY *display;  //display
    ALLEGRO_BITMAP *iconImg;    //ICON Img
    BackgroundStut background;

    ALLEGRO_EVENT_QUEUE *event_queue; //拿來存事件 #1 (目前用於視窗X叉叉)

    ALLEGRO_EVENT events;                     //拿來存事件 #2 (目前用於視窗X叉叉)
    ALLEGRO_TIMER *timer;

    ScoreboardStut chars;
    ScoreboardStut coins;

    FontStut font_a;
    SoundStut sound;
    ButtonStut menuButton[NUM_MENU_BUTTON]; //初始介面選單
    ButtonStut modeButton[NUM_MODE_BUTTON]; //遊戲難度選單
    ButtonStut homeButton;
    ALLEGRO_KEYBOARD_STATE keyboard_state;
} AllegroObjStut;


typedef struct LayoutParmStut{
    int X;
} LayoutParmStut;

typedef struct MouseStut{
    int x, y;
    bool isClick;
} MouseStut;

typedef struct MainDataStut{
    struct tm *tm;
    int game_state; //遊戲進行狀態
    int breakPoint;
    int game_mode; //遊戲模式
    MouseStut mouse;
    ScoreStut score;
} MainDataStut;

/* AllegroObjStut Function*/
AllegroObjStut *ClocAlgObj();
void AllegroDriverInit();
void AllegroObjectInit(AllegroObjStut *allegroObj);
void image_init(AllegroObjStut *allegroObj);
void font_init(AllegroObjStut *allegroObj);
void score_board_init(AllegroObjStut *allegroObj);
void menu_button_init(AllegroObjStut *allegroObj);
void home_button_init(AllegroObjStut *allegroObj);
void mode_button_init(AllegroObjStut *allegroObj);
void sound_init(AllegroObjStut *allegroObj);
/* MainDataStut Function*/
MainDataStut *ClocMainData();
void MainDataInit(MainDataStut *mainData);

/* LayoutParmStut Function*/
LayoutParmStut *ClocLayoutParm();

void LayoutParmInit(LayoutParmStut *layoutParm);

#endif //_RESOURSE_H_

    //ALLEGRO_BITMAP *candyBkgImg; //main layout img
    //ALLEGRO_BITMAP **candyImgs; //candy Imgs: candyImg[n]

    //ALLEGRO_MENU *menu; //待整併
    //LLEGRO_MENU *menu_1; //待整併
    //FILE *fileStream;
    //int scoreFileIsRead;
    //int row;
    //int col;
    //int round;
        //int mouse_x, mouse_y;
    //int mouse_click, mouse_click_x, mouse_click_y;
    //NameStut usrName;
    //ScoreDataStut *scoreData;
