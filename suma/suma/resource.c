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
    font_init(allegroObj);
    sound_init(allegroObj);
    menu_button_init(allegroObj);
    mode_button_init(allegroObj);
    home_button_init(allegroObj);
    score_board_init(allegroObj);
    role_init(allegroObj);
    floor_init(allegroObj);
    meteor_init(allegroObj);

    /*load Font*/
    //allegroObj->font_60 = al_load_font("DFT_TL9.TTC", 60, 0);
    //allegroObj->font_24 = al_load_font("DFT_TL9.TTC", 24, 0);

    /* load the sound file */
    //voice_init(allegroObj);

    /* window title and menu*/
    al_set_window_title(allegroObj->display,"SUMA");
    al_set_display_icon(allegroObj->display, allegroObj->iconImg);
    //menu_init(allegroObj);

    //al_hide_mouse_cursor(allegroObj->display);
}

void sound_init(AllegroObjStut *allegroObj)
{

    al_reserve_samples( NUM_SAMPLES );
    allegroObj->sound.sfx_background = al_load_sample( PATH_SFX_BACKGROUND );
    allegroObj->sound.sfi_background = al_create_sample_instance(allegroObj->sound.sfx_background);
    //創建聲音輸出buffer 創建聲音輸出連接口
    //allegroObj->sound.mixer = al_get_default_mixer(); //硬體設備不同 容易出錯
    //allegroObj->sound.voice = al_get_default_voice(); //硬體設備不同 容易出錯
    //for test
    allegroObj->sound.mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32,ALLEGRO_CHANNEL_CONF_2);
    allegroObj->sound.voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16,ALLEGRO_CHANNEL_CONF_2);
    //printf("@@@ mixer : %x, voice : %x", allegroObj->sound.mixer, allegroObj->sound.voice);

    al_attach_sample_instance_to_mixer(allegroObj->sound.sfi_background, allegroObj->sound.mixer);//將聲音物件link buffer
    al_attach_mixer_to_voice(allegroObj->sound.mixer, allegroObj->sound.voice); //將buffer link 輸出連接口
}

void score_board_init(AllegroObjStut *allegroObj)
{
    allegroObj->coins.img = al_load_bitmap( PATH_IMG_COIN);
    allegroObj->coins.start_x = SIZE_IMG_SCOREBOARD_ICON_WIDTH/3;
    allegroObj->coins.start_y = SIZE_IMG_SCOREBOARD_ICON_HEIGHT/4;
    allegroObj->coins.end_x = allegroObj->coins.start_x + OFFSET_SCOREBOARD_TEXT;
    allegroObj->coins.end_y = allegroObj->coins.start_y;
    allegroObj->chars.img = al_load_bitmap( PATH_IMG_CHAR);
    allegroObj->chars.start_x = allegroObj->coins.end_x + SIZE_IMG_SCOREBOARD_ICON_WIDTH; //修正
    allegroObj->chars.start_y = allegroObj->coins.start_y;
    allegroObj->chars.end_x = allegroObj->chars.start_x + OFFSET_SCOREBOARD_TEXT;
    allegroObj->chars.end_y = allegroObj->chars.start_y;
}

void font_init(AllegroObjStut *allegroObj)
{
    allegroObj->font_a.font24 = al_load_font( PATH_FONT_HIMAJI, 24, 0);
    allegroObj->font_a.font36 = al_load_font( PATH_FONT_HIMAJI, 36, 0);
    allegroObj->font_a.font48 = al_load_font( PATH_FONT_HIMAJI, 48, 0);
    allegroObj->font_a.font64 = al_load_font( PATH_FONT_HIMAJI, 64, 0);
    allegroObj->font_a.font90 = al_load_font( PATH_FONT_HIMAJI, 90, 0);
    allegroObj->font_a.font120 = al_load_font( PATH_FONT_HIMAJI, 120, 0);
}

void image_init(AllegroObjStut *allegroObj)
{
    allegroObj->background.img = al_load_bitmap( PATH_IMG_BKG );
    allegroObj->background.x = 0;
    allegroObj->iconImg = al_load_bitmap( PATH_IMG_ICON );
}

void floor_init(AllegroObjStut *allegroObj)
{
    allegroObj->floor.img = al_load_bitmap( PATH_IMG_FLOOR );
    allegroObj->floor.start_x = DISPLAY_WIDTH;
    allegroObj->floor.start_y = DISPLAY_HEIGHT - SIZE_IMG_FLOOR_HEIGHT;
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
}

