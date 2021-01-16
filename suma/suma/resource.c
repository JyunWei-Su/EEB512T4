#include "resource.h"
#include "defineHeader.h"

AllegroObjStut *ClocAlgObj()
{
    AllegroObjStut *addr = (AllegroObjStut *)calloc(1, sizeof(AllegroObjStut)); //分配空間
    return addr;
}

void AllegroDriverInit()
{
    /* first, set up Allegro and the graphics mode */
    al_init();              // initialize Allegro
    al_install_keyboard();  // install the keyboard for Allegro to use
    al_init_image_addon();
    al_install_audio();     // install sound driver
    al_init_acodec_addon(); //處理音檔用for .wav
    al_install_mouse();
    al_init_font_addon();   // install font addons
    al_init_ttf_addon();    //TureType Font addon also support .ttc
    al_init_native_dialog_addon();
    al_init_primitives_addon();
}

void AllegroObjectInit(AllegroObjStut *allegroObj)
{
    /* base Obj*/
    allegroObj->timer       = al_create_timer(1.0 / FPS);
    allegroObj->display     = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT); // Create allegro display
    allegroObj->event_queue = al_create_event_queue(); // Create allegro enevt detector #1
    al_register_event_source(allegroObj->event_queue, al_get_keyboard_event_source());
    al_register_event_source(allegroObj->event_queue, al_get_display_event_source(allegroObj->display)); // Create allegro enevt detector #2
    al_register_event_source(allegroObj->event_queue, al_get_timer_event_source(allegroObj->timer));
    //al_register_event_source(allegroObj->event_queue, al_get_default_menu_event_source());
    al_register_event_source(allegroObj->event_queue, al_get_mouse_event_source());
    //if(!allegroObj->event_queue) MY_ALGO_ErrMsg("Allegro5", "EVENT QUEUE HAS FAILED TO BE CREATED");
    al_start_timer(allegroObj->timer);

    /*Load bitmap(image) */
    image_init(allegroObj);
    font_init(&allegroObj->font_a, PATH_FONT_HIMAJI);
    font_init(&allegroObj->font_b, PATH_FONT_FANCYH);
    sound_init(allegroObj);
    menu_button_init(allegroObj);
    mode_button_init(allegroObj);
    home_button_init(allegroObj);
    score_board_init(allegroObj);
    role_init(allegroObj);
    //coin_init_old(allegroObj);
    coin_init(allegroObj);
    obscale_init(allegroObj);

    new_meteor_init(allegroObj);

    floor_init(allegroObj); //FTT
    meteor_init(allegroObj);


    /* window title and menu*/
    al_set_window_title(allegroObj->display,"SUMA");
    al_set_display_icon(allegroObj->display, allegroObj->iconImg);
    //menu_init(allegroObj);

    //al_hide_mouse_cursor(allegroObj->display);
}

void sound_init(AllegroObjStut *allegroObj)
{
    //創建聲音輸出buffer 創建聲音輸出連接口
    //allegroObj->sound.mixer = al_get_default_mixer(); //硬體設備不同 容易出錯
    //allegroObj->sound.voice = al_get_default_voice(); //硬體設備不同 容易出錯
    //for test
    allegroObj->sound.mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32,ALLEGRO_CHANNEL_CONF_2);
    allegroObj->sound.voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16,ALLEGRO_CHANNEL_CONF_2);
    //printf("@@@ mixer : %x, voice : %x", allegroObj->sound.mixer, allegroObj->sound.voice);

    // SAMPLES
    al_reserve_samples( NUM_SAMPLES );
    allegroObj->sound.sfx_background = al_load_sample( PATH_SFX_BACKGROUND );
    allegroObj->sound.sfi_background = al_create_sample_instance(allegroObj->sound.sfx_background);
    allegroObj->sound.buttonMoveIn.sfx = al_load_sample( PATH_SFX_BUTTON_MOVEIN );
    allegroObj->sound.buttonMoveIn.sfi = al_create_sample_instance(allegroObj->sound.buttonMoveIn.sfx);


    al_attach_sample_instance_to_mixer(allegroObj->sound.sfi_background, allegroObj->sound.mixer);//將聲音物件link buffer
    al_attach_sample_instance_to_mixer(allegroObj->sound.buttonMoveIn.sfi, allegroObj->sound.mixer);
    al_attach_mixer_to_voice(allegroObj->sound.mixer, allegroObj->sound.voice); //將buffer link 輸出連接口

}

void score_board_init(AllegroObjStut *allegroObj)
{
    allegroObj->sb_coins.img = al_load_bitmap( PATH_IMG_COIN);
    allegroObj->sb_coins.start_x = SIZE_IMG_SCOREBOARD_ICON_WIDTH/3;
    allegroObj->sb_coins.start_y = SIZE_IMG_SCOREBOARD_ICON_HEIGHT/4;
    allegroObj->sb_coins.end_x = allegroObj->sb_coins.start_x + OFFSET_SCOREBOARD_TEXT;
    allegroObj->sb_coins.end_y = allegroObj->sb_coins.start_y + SIZE_IMG_SCOREBOARD_ICON_HEIGHT;
    allegroObj->sb_chars.img = al_load_bitmap( PATH_IMG_CHAR);
    allegroObj->sb_chars.start_x = allegroObj->sb_coins.end_x + SIZE_IMG_SCOREBOARD_ICON_WIDTH; //修正
    allegroObj->sb_chars.start_y = allegroObj->sb_coins.start_y;
    allegroObj->sb_chars.end_x = allegroObj->sb_chars.start_x + OFFSET_SCOREBOARD_TEXT;
    allegroObj->sb_chars.end_y = allegroObj->sb_chars.start_y + SIZE_IMG_SCOREBOARD_ICON_HEIGHT;
    allegroObj->probar.img = al_load_bitmap( PATH_IMG_PROBAR);
    allegroObj->probar.start_x = allegroObj->sb_chars.end_x + SIZE_IMG_SCOREBOARD_ICON_WIDTH;
    allegroObj->probar.start_y = allegroObj->sb_coins.start_y;
}


/*
void coin_init_old(AllegroObjStut *allegroObj)
{
    allegroObj->coin_old.imgs_runing = al_load_bitmap( PATH_IMG_COINS_ROTATE );
    allegroObj->coin_old.start_x=1500;
    allegroObj->coin_old.start_y=500;
    allegroObj->coin_old.persent = 3;
}*/


void coin_init(AllegroObjStut *allegroObj)
{
    if(allegroObj->coin.imgs_rotating == NULL) allegroObj->coin.imgs_rotating = al_load_bitmap( PATH_IMG_COINS_ROTATE );
    if(allegroObj->coin.imgs_crashing == NULL) allegroObj->coin.imgs_crashing = al_load_bitmap( PATH_IMG_COINS_CRASH );
    allegroObj->coin.objs = NULL;
    //這裡無須配置資料, 只需讀圖片, 配置在遊戲中配置
}

void obscale_init(AllegroObjStut *allegroObj)
{
    if(allegroObj->obscale.imgs_shining == NULL) allegroObj->obscale.imgs_shining = al_load_bitmap( PATH_IMG_OBSCALE_SHINING );
    if(allegroObj->obscale.imgs_crashing == NULL) allegroObj->obscale.imgs_crashing = al_load_bitmap( PATH_IMG_OBSCALE_CRASH );
    allegroObj->obscale.objs = NULL;
    //這裡無須配置資料, 只需讀圖片, 配置在遊戲中配置
}

void new_meteor_init(AllegroObjStut *allegroObj)
{
    if(allegroObj->newMeteor.imgs_runing == NULL) allegroObj->newMeteor.imgs_runing = al_load_bitmap( PATH_IMG_METEOR_SEQ_RUNING );
    allegroObj->newMeteor.objs = NULL;
    //if(allegroObj->newCoin.objs == NULL) allegroObj->newCoin.objs = (ObjectStut *)calloc(1, sizeof(ObjectStut));
}

void font_init(FontStut *font, const char *filePath)
{
    font->font24 = al_load_font( filePath, 24, 0);
    font->font36 = al_load_font( filePath, 36, 0);
    font->font48 = al_load_font( filePath, 48, 0);
    font->font64 = al_load_font( filePath, 64, 0);
    font->font90 = al_load_font( filePath, 90, 0);
    font->font120 = al_load_font( filePath, 120, 0);
}

void image_init(AllegroObjStut *allegroObj)
{
    allegroObj->background.img = al_load_bitmap( PATH_IMG_BKG );
    allegroObj->background.x = 0;
    allegroObj->iconImg = al_load_bitmap( PATH_IMG_ICON );
}


//FTT
void floor_init(AllegroObjStut *allegroObj)
{
    if(allegroObj->floor.img == NULL) allegroObj->floor.img = al_load_bitmap( PATH_IMG_FLOOR );
}

void home_button_init(AllegroObjStut *allegroObj)
{
    allegroObj->homeButton.img = al_load_bitmap( PATH_IMG_HOME_BUTTON_1 );
    allegroObj->homeButton.img2 = al_load_bitmap( PATH_IMG_HOME_BUTTON_2 );
    allegroObj->homeButton.isSelected = 0;
    allegroObj->homeButton.start_x = SIZE_IMG_HOME_BUTTON_WIDTH*0.5;
    allegroObj->homeButton.start_y = DISPLAY_HEIGHT - SIZE_IMG_HOME_BUTTON_HEIGHT*1.5;
    allegroObj->homeButton.end_x = allegroObj->homeButton.start_x + SIZE_IMG_HOME_BUTTON_WIDTH;
    allegroObj->homeButton.end_y = allegroObj->homeButton.start_y + SIZE_IMG_HOME_BUTTON_HEIGHT;
}

void role_init(AllegroObjStut *allegroObj)
{
    allegroObj->role.img = al_load_bitmap( PATH_IMG_ROLE_1 );
    allegroObj->role.imgs_runing = al_load_bitmap( PATH_IMG_ROLE_SEQ_RUNING );
    allegroObj->role.start_x=200;
    allegroObj->role.start_y=700;
    allegroObj->role.state = ROLE_NULL;
}

void meteor_init(AllegroObjStut *allegroObj)
{
    int i;
    allegroObj->meteor_n = rand()%NUMBER_METEOR+15; //隕石數量
    allegroObj->meteor.img = al_load_bitmap( PATH_IMG_METEOR);
    allegroObj->meteor.imgs_runing = al_load_bitmap( PATH_IMG_METEOR_SEQ_RUNING );
    // allegroObj->meteor.start_x = 500;
    //allegroObj->meteor.start_y = 0;
    //allegroObj->meteor.speed_y =1;
    allegroObj->meteors = (MeteorStut *)calloc(allegroObj->meteor_n, sizeof(MeteorStut));
    allegroObj->meteors_right_drop = (MeteorStut *)calloc(allegroObj->meteor_n, sizeof(MeteorStut));
    allegroObj->meteors_left_drop = (MeteorStut *)calloc(allegroObj->meteor_n, sizeof(MeteorStut));

    for (i = 0; i < allegroObj->meteor_n; i++)
    {
        //*meteors
        allegroObj->meteors[i].img = al_load_bitmap(PATH_IMG_METEOR );
        allegroObj->meteors[i].start_x = rand()%1600;
        allegroObj->meteors[i].start_y = 0;
        allegroObj->meteors[i].speed_y = rand()%SPEED_Y_METEOR+5;
        //*meteors_right_drop
        allegroObj->meteors_right_drop[i].img = al_load_bitmap(PATH_IMG_METEOR );
        allegroObj->meteors_right_drop[i].imgs_runing = al_load_bitmap( PATH_IMG_METEOR_SEQ_RUNING );
        allegroObj->meteors_right_drop[i].start_x = rand()%2000;
        allegroObj->meteors_right_drop[i].start_y = 0;
        allegroObj->meteors_right_drop[i].speed_x = rand()%SPEED_X_METEOR_RIGHT+1;
        allegroObj->meteors_right_drop[i].speed_y = rand()%SPEED_Y_METEOR_RIGHT+2;
        //*meteors_right_drop
        allegroObj->meteors_left_drop[i].img = al_load_bitmap(PATH_IMG_METEOR );
        allegroObj->meteors_left_drop[i].start_x = rand()%2000;
        allegroObj->meteors_left_drop[i].start_y = 0;
        allegroObj->meteors_left_drop[i].speed_x = rand()%SPEED_X_METEOR_RIGHT+1;
        allegroObj->meteors_left_drop[i].speed_y = rand()%SPEED_Y_METEOR_RIGHT+3;

    }
    //allegroObj->meteor.start_x=800;
    //allegroObj->meteor.start_y=0;
    //allegroObj->role.imgs_runing = al_load_bitmap( PATH_IMG_ROLE_SEQ_RUNING );
    //allegroObj->meteor.state = ROLE_NULL;
}

void menu_button_init(AllegroObjStut *allegroObj)
{
    int i;
    for(i = 0; i < NUM_MENU_BUTTON; i++)
    {
        allegroObj->menuButton[i].start_x = (float)(DISPLAY_WIDTH-SIZE_IMG_MENU_BUTTON_WIDTH)/2;
        allegroObj->menuButton[i].start_y = (float)(DISPLAY_HEIGHT/(NUM_MENU_BUTTON+2))*(i+OFFSET_MENU);
        allegroObj->menuButton[i].end_x = allegroObj->menuButton[i].start_x + SIZE_IMG_MENU_BUTTON_WIDTH;
        allegroObj->menuButton[i].end_y = allegroObj->menuButton[i].start_y + SIZE_IMG_MENU_BUTTON_HEIGHT;
        allegroObj->menuButton[i].img = al_load_bitmap( PATH_IMG_MENU_BUTTON );
        allegroObj->menuButton[i].isSelected = 0;
        switch(i)
        {
        case 0:
            allegroObj->menuButton[i].text = (char*)"Play";
            break;
        case 1:
            allegroObj->menuButton[i].text = (char*)"Rule";
            break;
        case 2:
            allegroObj->menuButton[i].text = (char*)"Rank";
            break;
        case 3:
            allegroObj->menuButton[i].text = (char*)"About";
            break;
        default:
            allegroObj->menuButton[i].text = (char*)"Default";
            break;
        }
        //printf("%f, %f\n", allegroObj->menuButton[i].start_x, allegroObj->menuButton[i].start_y);
    }
    //printf("%f, %f\n", allegroObj->menuButton[i].start_x, allegroObj->menuButton[i].start_y);
}

void mode_button_init(AllegroObjStut *allegroObj)
{
    int i;
    for(i = 0; i < NUM_MODE_BUTTON; i++)
    {
        allegroObj->modeButton[i].start_x = (float)(DISPLAY_WIDTH-SIZE_IMG_MODE_BUTTON_WIDTH)/2;
        allegroObj->modeButton[i].start_y = (float)(DISPLAY_HEIGHT/(NUM_MODE_BUTTON+2))*(i+OFFSET_MODE);
        allegroObj->modeButton[i].end_x = allegroObj->modeButton[i].start_x + SIZE_IMG_MODE_BUTTON_WIDTH;
        allegroObj->modeButton[i].end_y = allegroObj->modeButton[i].start_y + SIZE_IMG_MODE_BUTTON_HEIGHT;
        allegroObj->modeButton[i].img = al_load_bitmap( PATH_IMG_MODE_BUTTON );
        allegroObj->modeButton[i].isSelected = 0;
        switch(i)
        {
        case 0:
            allegroObj->modeButton[i].text = (char*)"Easy";
            break;
        case 1:
            allegroObj->modeButton[i].text = (char*)"Medium";
            break;
        case 2:
            allegroObj->modeButton[i].text = (char*)"Hard";
            break;
        default:
            allegroObj->modeButton[i].text = (char*)"Default";
            break;
        }
        //printf("%f, %f\n", allegroObj->modeButton[i].start_x, allegroObj->modeButton[i].start_y);
    }
    //printf("%f, %f\n", allegroObj->modeButton[i].start_x, allegroObj->modeButton[i].start_y);
}

void function_bar_init(AllegroObjStut *allegroObj)
{
    int x = 9;
}

MainDataStut *ClocMainData()
{
    MainDataStut *addr = (MainDataStut *)calloc(1, sizeof(MainDataStut)); //分配空間
    return addr;
}

void MainDataInit(MainDataStut *mainData)
{
    mainData->game_state = GAME_MENU;
    mainData->breakPoint = 0;
    mainData->score.chars = 0;
    mainData->score.coins = 0;
    mainData->score.score = 0;

    mainData->scoreFileData = (RankScoreDataStut *)calloc(sizeof(RankScoreDataStut), 1);
    mainData->scoreFileData->data = (RankRowStut *)calloc(sizeof(RankRowStut), NUM_SCORE_DATA);
    mainData->scoreFileData->fileIsRead = 0;
}

