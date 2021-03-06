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
    font_init(&allegroObj->font_b, PATH_FONT_HANDYH);
    sound_init(allegroObj);
    menu_button_init(allegroObj);
    mode_button_init(allegroObj);
    home_button_init(allegroObj);
    score_board_init(allegroObj);
    role_init(allegroObj);
    stb_role_init(allegroObj);
    boss_init(allegroObj);
    coin_init(allegroObj);
    obscale_init(allegroObj);

    meteor_init(allegroObj);
    attackx_init(allegroObj);
    sub_role_init(allegroObj);
    floor_init(allegroObj);
    full_floor_init(allegroObj);
    meteor_init(allegroObj);
    allegroObj->ruleImg = al_load_bitmap(PATH_IMG_STB_GUIDE);

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
    allegroObj->sound.mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32,ALLEGRO_CHANNEL_CONF_2);
    allegroObj->sound.voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16,ALLEGRO_CHANNEL_CONF_2);
    //printf("@@@ mixer : %x, voice : %x", allegroObj->sound.mixer, allegroObj->sound.voice);

    // SAMPLES
    al_reserve_samples( NUM_SAMPLES );
    allegroObj->sound.sfx_background = al_load_sample( PATH_SFX_BACKGROUND );
    allegroObj->sound.sfi_background = al_create_sample_instance(allegroObj->sound.sfx_background);
    allegroObj->sound.buttonMoveIn.sfx = al_load_sample( PATH_SFX_BUTTON_MOVEIN );
    allegroObj->sound.buttonMoveIn.sfi = al_create_sample_instance(allegroObj->sound.buttonMoveIn.sfx);
    allegroObj->sound.coinCrash.sfx = al_load_sample( PATH_SFX_COINCRASH );
    allegroObj->sound.coinCrash.sfi = al_create_sample_instance( allegroObj->sound.coinCrash.sfx);
    allegroObj->sound.damageBook.sfx = al_load_sample( PATH_SFX_DAMAGE );
    allegroObj->sound.damageBook.sfi = al_create_sample_instance( allegroObj->sound.damageBook.sfx);
    allegroObj->sound.roleDead.sfx = al_load_sample( PATH_SFX_ROLEDEAD );
    allegroObj->sound.roleDead.sfi = al_create_sample_instance(allegroObj->sound.roleDead.sfx);


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


void coin_init(AllegroObjStut *allegroObj)
{
    if(allegroObj->coin.imgs_rotating == NULL) allegroObj->coin.imgs_rotating = al_load_bitmap( PATH_IMG_COINS_ROTATE );
    if(allegroObj->coin.imgs_crashing == NULL) allegroObj->coin.imgs_crashing = al_load_bitmap( PATH_IMG_COINS_CRASH );
    allegroObj->coin.objs = NULL;
    //這裡無須配置資料, 只需讀圖片, 配置在遊戲中配置
}

void sub_role_init(AllegroObjStut *allegroObj)
{
    if(allegroObj->subRole.img == NULL) allegroObj->subRole.img = al_load_bitmap( PATH_IMG_SUB_ROLE);
    if(allegroObj->subRole.imgs_runing == NULL) allegroObj->subRole.imgs_runing = al_load_bitmap( PATH_IMG_SUB_ROLE_SEQ_RUNING );
    allegroObj->subRole.objs = NULL;
}

void stb_role_init(AllegroObjStut *allegroObj)
{
    if(allegroObj->stbRole.img == NULL) allegroObj->stbRole.img = al_load_bitmap( PATH_IMG_STB_ROLE );
    if(allegroObj->stbRole.imgs_running == NULL) allegroObj->stbRole.imgs_running = al_load_bitmap( PATH_IMG_STB_ROLE_SEQ_RUNING );
    allegroObj->stbRole.objs = NULL;
    //這裡無須配置資料, 只需讀圖片, 配置在遊戲中配置
}

void obscale_init(AllegroObjStut *allegroObj)
{
    if(allegroObj->obscale.imgs_shining == NULL) allegroObj->obscale.imgs_shining = al_load_bitmap( PATH_IMG_OBSCALE_SHINING );
    if(allegroObj->obscale.imgs_crashing == NULL) allegroObj->obscale.imgs_crashing = al_load_bitmap( PATH_IMG_OBSCALE_CRASH );
    allegroObj->obscale.objs = NULL;
    //這裡無須配置資料, 只需讀圖片, 配置在遊戲中配置
}

void meteor_init(AllegroObjStut *allegroObj)
{
    if(allegroObj->meteor.imgs_runing == NULL) allegroObj->meteor.imgs_runing = al_load_bitmap( PATH_IMG_METEOR_SEQ_RUNING );
    allegroObj->meteor.objs = NULL;

}
void attackx_init(AllegroObjStut *allegroObj)
{
    if(allegroObj->attackx.imgs_runing[0] == NULL) allegroObj->attackx.imgs_runing[0] = al_load_bitmap( PATH_IMG_ATTACKX_1 );
    if(allegroObj->attackx.imgs_runing[1] == NULL) allegroObj->attackx.imgs_runing[1] = al_load_bitmap( PATH_IMG_ATTACKX_2 );
    if(allegroObj->attackx.imgs_runing[2] == NULL) allegroObj->attackx.imgs_runing[2] = al_load_bitmap( PATH_IMG_ATTACKX_3 );
    if(allegroObj->attackx.imgs_runing[3] == NULL) allegroObj->attackx.imgs_runing[3] = al_load_bitmap( PATH_IMG_ATTACKX_4 );
    if(allegroObj->attackx.imgs_runing[4] == NULL) allegroObj->attackx.imgs_runing[4] = al_load_bitmap( PATH_IMG_ATTACKX_5 );
    allegroObj->attackx.objs = NULL;
    allegroObj->attackx.id =rand()%5+1;

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

void floor_init(AllegroObjStut *allegroObj)
{
    if(allegroObj->floor.img == NULL) allegroObj->floor.img = al_load_bitmap( PATH_IMG_FLOOR );
}

void full_floor_init(AllegroObjStut *allegroObj)
{
    allegroObj->full_floor.start_x = 0;
    allegroObj->full_floor.start_y = DISPLAY_HEIGHT - SIZE_IMG_FLOOR_HEIGHT;
    allegroObj->full_floor.end_x = DISPLAY_WIDTH;
    allegroObj->full_floor.end_y = DISPLAY_HEIGHT;
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
    allegroObj->role.img = al_load_bitmap( PATH_IMG_ROLE );
    allegroObj->role.imgs_runing = al_load_bitmap( PATH_IMG_ROLE_SEQ_RUNING );
    allegroObj->role.start_x=800;
    allegroObj->role.start_y=DISPLAY_HEIGHT-OFFSET_FLOOR-SIZE_IMG_ROLE_HEIGHT;
    allegroObj->role.state = ROLE_NULL;
}

void role_reset(AllegroObjStut *allegroObj)
{
    allegroObj->role.start_x=800;
    allegroObj->role.start_y=DISPLAY_HEIGHT-OFFSET_FLOOR-SIZE_IMG_ROLE_HEIGHT-200;
    allegroObj->role.state = ROLE_DROP;
}

void boss_init(AllegroObjStut *allegroObj)
{
    //allegroObj->boss.img = al_load_bitmap( PATH_IMG_ROLE_1 );
    allegroObj->boss.imgs_runing = al_load_bitmap( PATH_IMG_BOSS_02 );
    allegroObj->boss.start_x=1300;
    allegroObj->boss.start_y=500;
    allegroObj->boss2.imgs_runing = al_load_bitmap( PATH_IMG_BOSS_03 );
    allegroObj->boss2.start_x=0;
    allegroObj->boss2.start_y=600;
    //allegroObj->boss.state = ROLE_NULL;
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
    mainData->timerCount = 0;

    mainData->scoreFileData = (RankScoreDataStut *)calloc(sizeof(RankScoreDataStut), 1);
    mainData->scoreFileData->data = (RankRowStut *)calloc(sizeof(RankRowStut), NUM_SCORE_DATA);
    mainData->scoreFileData->fileIsRead = 0;
    mainData->speed.background = 0;
    mainData->speed.object = 0;
    mainData->speed.background = 2.5;
    mainData->speed.object = 3.5;
}

void DestoryAllegroObj(AllegroObjStut *allegroObj)
{
    int i;
    al_pause_event_queue(allegroObj->event_queue, true);
    al_stop_timer(allegroObj->timer);

    al_destroy_bitmap(allegroObj->iconImg);
    al_destroy_bitmap(allegroObj->ruleImg);
    al_destroy_bitmap(allegroObj->background.img);

    al_destroy_event_queue(allegroObj->event_queue);
    al_destroy_timer(allegroObj->timer);

    al_destroy_bitmap(allegroObj->probar.img);
    al_destroy_bitmap(allegroObj->sb_chars.img);
    al_destroy_bitmap(allegroObj->sb_coins.img);
    al_destroy_bitmap(allegroObj->role.img);
    al_destroy_bitmap(allegroObj->role.imgs_runing);
    al_destroy_bitmap(allegroObj->boss.imgs_runing);
    al_destroy_bitmap(allegroObj->boss2.imgs_runing);

    al_destroy_bitmap(allegroObj->subRole.img);
    al_destroy_bitmap(allegroObj->subRole.imgs_runing);
    al_destroy_bitmap(allegroObj->stbRole.img);
    al_destroy_bitmap(allegroObj->stbRole.imgs_running);
    al_destroy_bitmap(allegroObj->coin.imgs_crashing);
    al_destroy_bitmap(allegroObj->coin.imgs_rotating);
    al_destroy_bitmap(allegroObj->obscale.imgs_crashing);
    al_destroy_bitmap(allegroObj->obscale.imgs_shining);
    for(i=0; i<5; i++)
    {
        al_destroy_bitmap(allegroObj->attackx.imgs_runing[i]);
    }
    //subrolestut subRole
    //standbyrolstut stbRole
    //CoinStut coin
    //ObscaleStut obsscale
    //attackXStut

    al_destroy_font(allegroObj->font_a.font24);
    al_destroy_font(allegroObj->font_a.font36);
    al_destroy_font(allegroObj->font_a.font48);
    al_destroy_font(allegroObj->font_a.font64);
    al_destroy_font(allegroObj->font_a.font90);
    al_destroy_font(allegroObj->font_a.font120);

    al_destroy_font(allegroObj->font_b.font24);
    al_destroy_font(allegroObj->font_b.font36);
    al_destroy_font(allegroObj->font_b.font48);
    al_destroy_font(allegroObj->font_b.font64);
    al_destroy_font(allegroObj->font_b.font90);
    al_destroy_font(allegroObj->font_b.font120);

    al_destroy_mixer(allegroObj->sound.mixer);
    al_destroy_voice(allegroObj->sound.voice);
    al_destroy_sample(allegroObj->sound.sfx_background);
    al_destroy_sample(allegroObj->sound.buttonMoveIn.sfx);
    al_destroy_sample(allegroObj->sound.coinCrash.sfx);
    al_destroy_sample(allegroObj->sound.damageBook.sfx);
    al_destroy_sample(allegroObj->sound.roleDead.sfx);

    al_destroy_sample_instance(allegroObj->sound.sfi_background);
    al_destroy_sample_instance(allegroObj->sound.buttonMoveIn.sfi);
    al_destroy_sample_instance(allegroObj->sound.coinCrash.sfi);
    al_destroy_sample_instance(allegroObj->sound.damageBook.sfi);
    al_destroy_sample_instance(allegroObj->sound.roleDead.sfi);
    for(i=0 ; i<NUM_MENU_BUTTON; i++)
    {
        al_destroy_bitmap(allegroObj->menuButton[i].img);
        al_destroy_bitmap(allegroObj->menuButton[i].img2);
    }
    for(i=0 ; i<NUM_MODE_BUTTON; i++)
    {
        al_destroy_bitmap(allegroObj->modeButton[i].img);
        al_destroy_bitmap(allegroObj->modeButton[i].img2);
    }

    al_destroy_bitmap(allegroObj->homeButton.img);
    al_destroy_bitmap(allegroObj->homeButton.img2);





    al_destroy_display(allegroObj->display);

}

