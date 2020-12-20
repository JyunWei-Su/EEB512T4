#include "../own/header_JWS.h"
#include "../defineHeader.h"

void PrintTest_JWS(){
    printf("This is a print test by JWS.\n");
}

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
    if(!allegroObj->event_queue) MY_ALGO_ErrMsg("Allegro5", "EVENT QUEUE HAS FAILED TO BE CREATED");
    al_start_timer(allegroObj->timer);

    /*Load bitmap(image) */
    image_init(allegroObj);

    /*load Font*/
    //allegroObj->font_60 = al_load_font("DFT_TL9.TTC", 60, 0);
    //allegroObj->font_24 = al_load_font("DFT_TL9.TTC", 24, 0);

    /* load the sound file */
    //voice_init(allegroObj);

    /* window title and menu*/
    al_set_window_title(allegroObj->display,"Team 4 Game");
    al_set_display_icon(allegroObj->display, allegroObj->iconImg);
    //menu_init(allegroObj);

    //al_hide_mouse_cursor(allegroObj->display);
}

void image_init(AllegroObjStut *allegroObj)
{
    allegroObj->bkgImg = al_load_bitmap("./img/back900.png");
    allegroObj->iconImg = al_load_bitmap("./img/icon.tga");
}

MainDataStut *ClocMainData()
{
    MainDataStut *addr = (MainDataStut *)calloc(1, sizeof(MainDataStut)); //分配空間
    return addr;
}

void InitMainData(MainDataStut *mainData)
{
    mainData->bkg_x = 0;
    mainData->game_state = GAME_STATE_BKG_DRAW;
    mainData->breakPoint = 0;
}

void CheckEvent(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int result = 0;
    if(!al_is_event_queue_empty(allegroObj->event_queue))
    {
        while(al_get_next_event(allegroObj->event_queue, &allegroObj->events))
        {
            if(mainData->game_state == GAME_STATE_FINISH) break;
            switch(allegroObj->events.type)//用->還是.
            {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                //result = MY_ALGO_Y_N_Msg("Notice", "Shutdown This Game?\nYou can press Q or Esc to return to MENU.");
                //if(result == 1) mainData->game_state = GAME_STATE_FINISH;
                mainData->game_state = GAME_STATE_FINISH;
                break;
            case ALLEGRO_EVENT_MENU_CLICK:
                //if (allegroObj->events.user.data1 == FILE_EXIT_ID)
                //{
                //    mainData->game_state = GAME_STATE_FINISH;
                //}
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                //mainData->mouse_x = allegroObj->events.mouse.x;
                //mainData->mouse_y = allegroObj->events.mouse.y;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                //if(!(allegroObj->events.mouse.button&1)) break; //不是按下左鍵就忽略
                //mainData->mouse_click = 1;
                //CheckMouseClick(mainData, allegroObj, layoutParm);
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                //if(!(allegroObj->events.mouse.button&1)) break; //不是按下左鍵就忽略
                //mainData->mouse_click = 0;
                //CheckMouseClick(mainData, allegroObj, layoutParm);
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                //CheckKeyboardDown(mainData, allegroObj);
                break;
            case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
                al_flip_display();
                break;
            case ALLEGRO_EVENT_TIMER:
                //PlaySoundEffect(mainData, allegroObj);
                CheckGameState(mainData, allegroObj);
                break;
            default:
                break;
            }
        }
    }
}

void CheckGameState(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int state = mainData->game_state;
    //printf("state:%d\n", state);
    switch(state){
        case GAME_STATE_BKG_DRAW:
            DrawDisplayAndFlip(mainData, allegroObj);
            break;
        case GAME_STATE_TEST: //test
            //printf("Final Score: %d\n", mainData->tolScore); // After there is no elem. to eleimate, print the final score (each eleimate get 10 points)
            mainData->game_state = GAME_STATE_NULL;
            break;
        case GAME_STATE_NULL:
            //DrawDisplayAndFlip(mainData, allegroObj, layoutParm);
            break;
        default:
            break;
    }
}

void DrawDisplayAndFlip(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int state = mainData->game_state;
    //int calculate = 0;
    al_clear_to_color(al_map_rgb(0, 0, 0));  // Clear display
    switch(state){
        case GAME_STATE_BKG_DRAW:
            al_draw_bitmap(allegroObj->bkgImg, mainData->bkg_x, 0, 0); // Draw bitmap
            al_flip_display(); // Flip display to show the drawing result
            //al_rest(0.01); // Delay
            mainData->bkg_x -= 1;
        case GAME_STATE_NULL:

            break;
    }
    al_flip_display();
}
