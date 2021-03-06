#ifndef _RESOURSE_H_
#define _RESOURSE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //for utf
#include <inttypes.h> /* strtoimax */
#include <math.h>
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
#include <allegro5/allegro_primitives.h> // 畫線

#define PATH_IMG_BKG "./img/back900.png"
#define PATH_IMG_ICON "./img/icon.tga"
#define PATH_IMG_COIN "./img/coin.png"
#define PATH_IMG_COINS_ROTATE "./img/coins.png"
#define PATH_IMG_COINS_CRASH "./img/coinCrashs.png"
#define PATH_IMG_OBSCALE_SHINING "./img/book150.png"
#define PATH_IMG_OBSCALE_CRASH "./img/coinCrashs.png" //**銝���Ｚ��頝臬��隤�??
#define PATH_IMG_CHAR "./img/char.png"
#define PATH_IMG_PROBAR "./img/progressbar.png"
#define PATH_IMG_MENU_BUTTON "./img/menuButton.png"
#define PATH_IMG_MODE_BUTTON "./img/menuButton.png"
#define PATH_IMG_HOME_BUTTON_1 "./img/homeButton_1.png"
#define PATH_IMG_HOME_BUTTON_2 "./img/homeButton_2.png"
#define PATH_IMG_ROLE "./img/role.png"
#define PATH_IMG_ROLE_SEQ_RUNING "./img/roles.png"
#define PATH_IMG_SUB_ROLE "./img/sub_role.png"
#define PATH_IMG_SUB_ROLE_SEQ_RUNING "./img/sub_roles.png"
#define PATH_IMG_STB_ROLE "./img/stb_role.png"
#define PATH_IMG_STB_ROLE_SEQ_RUNING "./img/stb_roles.png"
#define PATH_IMG_STB_GUIDE "./img/guide.png"

#define PATH_IMG_FLOOR "./img/floor.png"
#define PATH_IMG_METEOR "./img/meteor.png"
#define PATH_IMG_METEOR_SEQ_RUNING "./img/meteors80.png"
#define PATH_IMG_ATTACKX_1 "./img/attackx1.png"
#define PATH_IMG_ATTACKX_2 "./img/attackx2.png"
#define PATH_IMG_ATTACKX_3 "./img/attackx3.png"
#define PATH_IMG_ATTACKX_4 "./img/attackx4.png"
#define PATH_IMG_ATTACKX_5 "./img/attackx5.png"
#define PATH_IMG_BOSS_01 "./img/boss01.png"
#define PATH_IMG_BOSS_02 "./img/boss02.png"
#define PATH_IMG_BOSS_03 "./img/boss03.png"


#define PATH_FNT_DFT "./DFT_TL9.TTC"
#define PATH_SFX_BACKGROUND "./sfx/bkg.wav"
#define PATH_SFX_BUTTON_MOVEIN "./sfx/button02a.wav"
#define PATH_SFX_COINCRASH "./sfx/coin.wav"
#define PATH_SFX_DAMAGE "./sfx/damage.wav"
#define PATH_SFX_ROLEDEAD "./sfx/roledead.wav"
#define PATH_FILE_SCORE "user.score"
#define PATH_FONT_HIMAJI "./font/KFhimajiFACE.otf"
#define PATH_FONT_FANCYH "./font/FancyHeart.otf"
#define PATH_FONT_GRAFTI "./font/Graffiti.ttf"
#define PATH_FONT_LEECAP "./font/LeeCaps.ttf"
#define PATH_FONT_HANDYH "./font/Nouveau.ttf"

#define COLOR_SCORE al_map_rgb(255, 255, 255)
#define COLOR_PAUSE_TEXT al_map_rgb(0, 0, 0)
#define COLOR_CLEAR al_map_rgb(0,0,0)
#define COLOR_MENU_BUTTON_A al_map_rgb(199, 0, 250)
#define COLOR_MENU_BUTTON_B al_map_rgb(20, 119, 130)
#define COLOR_MODE_BUTTON_A al_map_rgb(199, 0, 250)
#define COLOR_MODE_BUTTON_B al_map_rgb(20, 119, 130)

#define SIZE_IMG_BKG_WIDTH 4800
#define SIZE_IMG_BKG_HEIGHT 900
#define SIZE_IMG_SCOREBOARD_ICON_WIDTH 64
#define SIZE_IMG_SCOREBOARD_ICON_HEIGHT 64
#define SIZE_IMG_PROBAR_WIDTH 640
#define SIZE_IMG_PROBAR_HEIGHT 64
#define SIZE_IMG_COIN_WIDTH 64
#define SIZE_IMG_COIN_HEIGHT 64
#define SIZE_IMG_ROLE_WIDTH 84
#define SIZE_IMG_ROLE_HEIGHT 210
#define SIZE_IMG_FLOOR_WIDTH 1600
#define SIZE_IMG_FLOOR_HEIGHT 130
#define SIZE_IMG_OBSCALE_WIDTH 150
#define SIZE_IMG_OBSCALE_HEIGHT 150
#define SIZE_IMG_METEOR_WIDTH 80
#define SIZE_IMG_METEOR_HEIGHT 80
#define SIZE_IMG_METEOR_BIG_WIDTH 200
#define SIZE_IMG_METEOR_BIG_HEIGHT 200
#define SIZE_IMG_ATTACKX_WIDTH 300
#define SIZE_IMG_ATTACKX_HEIGHT 65
#define SIZE_IMG_BOSS_WIDTH 200
#define SIZE_IMG_BOSS_HEIGHT 300
#define SIZE_IMG_BOSS2_WIDTH 265
#define SIZE_IMG_BOSS2_HEIGHT 200
#define SIZE_IMG_MENU_BUTTON_WIDTH 480
#define SIZE_IMG_MENU_BUTTON_HEIGHT 90
#define SIZE_IMG_MODE_BUTTON_WIDTH 480
#define SIZE_IMG_MODE_BUTTON_HEIGHT 90
#define SIZE_IMG_HOME_BUTTON_WIDTH 128
#define SIZE_IMG_HOME_BUTTON_HEIGHT 128

#define SIZE_TEXT_RANK_LEADONG 48


#define NUM_SCORE_DATA 10 //rank 資料筆數
#define NUM_MENU_BUTTON 4
#define NUM_MODE_BUTTON 3
#define NUM_IMG_ROLE_SEQUENCE 10
#define NUM_IMG_METEOR_SEQUENCE 12
#define NUM_IMG_COIN_SEQUENCE 16
#define NUM_IMG_ATTACKX 1
#define NUM_IMG_BOSS_SEQUENCE 1
#define NUM_SAMPLES 3 //聲音數量
#define SCALE_MENU_BUTTON 1.2
#define SCALE_MODE_BUTTON 1.2

#define OFFSET_MENU 1.5
#define OFFSET_MODE 1.5
#define OFFSET_SCOREBOARD_TEXT 320
#define OFFSET_PROBAR_X 5
#define OFFSET_PROBAR_Y 1
#define OFFSET_PRONUMBER_X 610
#define OFFSET_PRONUMBER_Y 65
#define OFFSET_FLOOR 75
#define OFFSET_PLAYMODE_X 1480
#define OFFSET_PLAYMODE_y 30

/*Role_Define*/
#define OFFSET_ROLE_JUMP 10
#define OFFSET_ROLE_JUMP_X 3
#define OFFSET_ROLE_WALK 10
#define MAX_ROLE_Y 300
#define MIN_ROLE_Y 600
#define MAX_ROLE_X 1500
#define MIN_ROLE_X 0
#define GRAVITY 6
#define TIME_PER_IMG_ROLE 0.1
#define TIME_PER_IMG_COIN 0.1
#define TIME_PER_IMG_METEOR 0.1

#define SPEED_ROLE_JUMP 5.5
#define OFFSET_SUB_ROLE_DELAY 6
#define TIME_ROLE_JUMP_MAINTAIN 80

/*Meteor_Define*/
#define NUMBER_METEOR 30
#define SPEED_Y_METEOR 7
#define SPEED_X_METEOR 0
#define SPEED_Y_METEOR_RIGHT 5
#define SPEED_X_METEOR_RIGHT 3
/* Game persend*/
#define GAME_PERSEND_100 10000
#define GAME_PERSEND_70  7200
#define GAME_PERSEND_50  5040
#define GAME_PERSEND_25  2700
#define GAME_PERSEND_APPEND  3
#define GAME_PERSEND_MID_TIME  2500
#define GAME_PERSEND_FINAL_TIME  5800

#define FILE_EXIT_ID 1 //待整併

/**  enum  **/
typedef enum GameState
{
    GAME_NONE, GAME_FINISH,
    GAME_MODE_SELECT, GAME_RULE, GAME_RANK, GAME_MENU, GAME_ABOUT,
    GAME_PLAYING_NORMAL,
    GAME_PLAYING_END,
    GAME_PAUSE,
} GameState;

typedef enum PlayMode
{
    MODE_EASY, MODE_MEDIUM, MODE_HARD,
} PlayMode;

typedef enum RoleState
{
    ROLE_JUMP, ROLE_DROP, ROLE_MUST_DROP, ROLE_NULL, ROLE_DESTORY,
    ROLE_DROP_FLOOR,
} RoleState;

typedef enum BossState
{
    BOSS_NULL,BOSS_BEYOND_X,BOSS_BEYOND_Y,
} BossState;

typedef enum CoinState
{
    COIN_NULL, COIN_CRASH, COIN_MOVEOUT, COIN_DESTORY,
} CoinState;

typedef enum FloorState
{
    FLOOR_ACTIVE, FLOOR_STANDBY,
} FloorState;

typedef enum ObscaleState
{
    OBSCALE_NULL, OBSCALE_CRASH_MAIN,OBSCALE_CRASH_FOLLOWER, OBSCALE_MOVEOUT, OBSCALE_DESTORY,
} ObscaleState;

typedef enum StbRoleState
{
    STB_ROLE_NULL, STB_ROLE_CRASH, STB_ROLE_DESTORY,
} StandbyRoleState;

/**  struct  **/
typedef struct tm TmStut;

typedef struct RankRowStut
{
    int id;
    int score;
    char name[20];
    char time[20];
} RankRowStut;

typedef struct RankNameStut
{
    char name[20];
    int len;
} RankNameStut;

typedef struct RankScoreDataStut
{
    bool fileIsRead;
    RankRowStut *data; //form data[0] to data[SCORE_DATA-1]
    RankRowStut temp;
} RankScoreDataStut;

typedef struct ScoreStut
{
    int chars;
    int coins;
    int score;
    int probar;
} ScoreStut;

typedef struct SoundEffectStut
{
    ALLEGRO_SAMPLE *sfx;
    ALLEGRO_SAMPLE_INSTANCE *sfi;
    bool readyToPlay;
} SoundEffectStut;

/** Gaming Objects**/

typedef struct ObjectStut
{
    float start_x, start_y;
    float end_x, end_y;
    float speed_x, speed_y;
    int imgCount, imgNow;
    int state;
    int id;
    ObjectStut *nextObj;
} ObjectStut;

typedef struct CoinStut
{
    ALLEGRO_BITMAP *imgs_rotating;
    ALLEGRO_BITMAP *imgs_crashing;
    ObjectStut *objs;
    int n;
} CoinStut;

typedef struct SubRoleStut
{
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *imgs_runing;
    ObjectStut *objs;
    int n;
} SubRoleStut;

typedef struct FloorStut
{
    ALLEGRO_BITMAP *img;
    ObjectStut *objs;
    int n;
} FloorStut;

typedef struct ObscaleStut
{
    ALLEGRO_BITMAP *imgs_shining;
    ALLEGRO_BITMAP *imgs_crashing;
    ObjectStut *objs;
    int n;
} ObscaleStut;

typedef struct StandbyRoleStut
{
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *imgs_running;
    ObjectStut *objs;
    int n;
} StandbyRoleStut;

typedef struct MeteorStut
{
    ALLEGRO_BITMAP *imgs_runing;
    ObjectStut *objs;
    int n;
} MeteorStut;
typedef struct AttackXStut
{
    ALLEGRO_BITMAP *imgs_runing[5];
    ObjectStut *objs;
    int n,id;
} AttackXStut;

typedef struct RoleStut
{
    float start_x, start_y;
    float end_x, end_y;
    unsigned long long int keyDownRecord;
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *imgs_runing;
    int imgCount, nowImg;
    int state;
} RoleStut;
typedef struct BossStut
{
    float start_x, start_y;
    float end_x, end_y;
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *imgs_runing;
    int imgCount, nowImg;
    int state;
} BossStut;

/*
typedef struct MeteorStu
{
    float start_x, start_y;
    float end_x, end_y;
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *imgs_runing;
    int imgCount, nowImg;
    int speed_x,speed_y;
    int state;
} MeteorStut;*/

typedef struct ButtonStut
{
    float start_x, start_y;
    float end_x, end_y;
    char *text;
    bool isSelected;
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *img2;
} ButtonStut;

typedef struct FunctionBarStut
{
    ALLEGRO_MENU *main_menu;
} FunctionBarStut;

typedef struct ScoreboardStut
{
    float start_x, start_y;
    float end_x, end_y;
    ALLEGRO_BITMAP *img;
} ScoreboardStut;

typedef struct BackgroundStut
{
    float x, y;
    ALLEGRO_BITMAP *img;    //back ground Img
    int state;
} BackgroundStut;

typedef struct FontStut
{
    ALLEGRO_FONT *font24;
    ALLEGRO_FONT *font36;
    ALLEGRO_FONT *font48;
    ALLEGRO_FONT *font64;
    ALLEGRO_FONT *font90;
    ALLEGRO_FONT *font120;
} FontStut;

typedef struct SoundStut
{
    ALLEGRO_MIXER *mixer; // for sfx
    ALLEGRO_VOICE *voice;
    ALLEGRO_SAMPLE_ID id;

    ALLEGRO_SAMPLE *sfx_background;  /* pointer to sound file */
    ALLEGRO_SAMPLE_INSTANCE *sfi_background; //https://www.allegro.cc/forums/thread/611901

    SoundEffectStut buttonMoveIn;
    SoundEffectStut coinCrash;
    SoundEffectStut damageBook;
    SoundEffectStut roleDead;

} SoundStut;

typedef struct AllegroObjStut
{
    ALLEGRO_DISPLAY *display;  //display
    ALLEGRO_BITMAP *iconImg;    //ICON Img
    ALLEGRO_BITMAP *ruleImg;
    BackgroundStut background;

    ALLEGRO_EVENT_QUEUE *event_queue; //拿來存事件 #1 (目前用於視窗X叉叉)

    ALLEGRO_EVENT events;                     //拿來存事件 #2 (目前用於視窗X叉叉)
    ALLEGRO_TIMER *timer;

    ScoreboardStut probar;
    ScoreboardStut sb_chars;
    ScoreboardStut sb_coins;

    RoleStut role;
    BossStut boss;
    BossStut boss2;
    BossStut boss3;
    SubRoleStut subRole;
    StandbyRoleStut stbRole;
    CoinStut coin;
    ObscaleStut obscale;

     MeteorStut meteor;
    AttackXStut attackx;

    FloorStut floor;
    ObjectStut full_floor;
    int meteor_n;

    FontStut font_a;
    FontStut font_b;

    FunctionBarStut fnucBar;

    SoundStut sound;
    ButtonStut menuButton[NUM_MENU_BUTTON]; //初始介面選單
    ButtonStut modeButton[NUM_MODE_BUTTON]; //遊戲難度選單
    ButtonStut homeButton;
    ALLEGRO_KEYBOARD_STATE keyboard_state;
} AllegroObjStut;

typedef struct MouseStut
{
    int x, y;
    bool isClick;
} MouseStut;

typedef struct SpeedStut
{
    float background;
    float object;
} SpeedStut;

typedef struct NameStut{
    char name[20];
    int len;
}NameStut;

typedef struct MainDataStut
{
    unsigned long long int timerCount;
    TmStut *tm;
    GameState game_state; //遊戲進行狀態
    GameState game_state_pause; //上一階段(pause用)
    int breakPoint;
    int game_mode; //遊戲模式
    int game_percent; //0-10000

    MouseStut mouse;
    ScoreStut score;
    SpeedStut speed;
    RankNameStut usrName;
    RankScoreDataStut *scoreFileData;
} MainDataStut;

/* AllegroObjStut Function*/
AllegroObjStut *ClocAlgObj();
void AllegroDriverInit();
void AllegroObjectInit(AllegroObjStut *allegroObj);
void image_init(AllegroObjStut *allegroObj);
void font_init(FontStut *font, const char *filePath);
void score_board_init(AllegroObjStut *allegroObj);
void menu_button_init(AllegroObjStut *allegroObj);
void home_button_init(AllegroObjStut *allegroObj);
void mode_button_init(AllegroObjStut *allegroObj);
void sound_init(AllegroObjStut *allegroObj);
void role_init(AllegroObjStut *allegroObj);
void stb_role_init(AllegroObjStut *allegroObj);
void obscale_init(AllegroObjStut *allegroObj);
void coin_init_old(AllegroObjStut *allegroObj);
void floor_init(AllegroObjStut *allegroObj);
/* MainDataStut Function*/
MainDataStut *ClocMainData();
void MainDataInit(MainDataStut *mainData);
void role_reset(AllegroObjStut *allegroObj);
void coin_init(AllegroObjStut *allegroObj);
void function_bar_init(AllegroObjStut *allegroObj);
void meteor_init(AllegroObjStut *allegroObj);
void attackx_init(AllegroObjStut *allegroObj);
void sub_role_init(AllegroObjStut *allegroObj);
void meteor_init(AllegroObjStut *allegroObj);
void boss_init(AllegroObjStut *allegroObj);
void Gravity(AllegroObjStut *allegroObj); //運算
void DestoryAllegroObj(AllegroObjStut *allegroObj);
#endif //_RESOURSE_H_

//ALLEGRO_MENU *menu; //待整併
//LLEGRO_MENU *menu_1; //待整併
