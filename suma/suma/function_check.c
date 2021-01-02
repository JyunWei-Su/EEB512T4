#include "defineHeader.h"
#include "resource.h"

void CheckEvent(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    if(!al_is_event_queue_empty(allegroObj->event_queue))
    {
        while(al_get_next_event(allegroObj->event_queue, &allegroObj->events))
        {
            if(mainData->game_state == GAME_FINISH) break;
            switch(allegroObj->events.type)
            {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                CheckWantToFinish(mainData, allegroObj);
                break;
            case ALLEGRO_EVENT_MENU_CLICK:
                //if (allegroObj->events.user.data1 == FILE_EXIT_ID)
                //{
                //    mainData->game_state = FINISH;
                //}
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                CheckMouseMove(mainData, allegroObj);
                mainData->mouse.x = allegroObj->events.mouse.x;
                mainData->mouse.y = allegroObj->events.mouse.y;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if(!(allegroObj->events.mouse.button&1)) break; //不是按下左鍵就忽略
                mainData->mouse.isClick = 1;
                CheckMouseClick(mainData, allegroObj);
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if(!(allegroObj->events.mouse.button&1)) break; //不是按下左鍵就忽略
                mainData->mouse.isClick = 0;
                CheckMouseClick(mainData, allegroObj);
                break;
            case ALLEGRO_EVENT_KEY_CHAR:
                CheckKeyboardDown(mainData, allegroObj);
                break;
            case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
                al_flip_display();
                break;
            case ALLEGRO_EVENT_TIMER:
                printf("%d\n", mainData->game_state);
                //PlaySoundEffect(mainData, allegroObj);
                ParameterOperate(mainData, allegroObj);
                //CheckGameState(mainData, allegroObj);
                DrawDisplayAndFlip(mainData, allegroObj);
                break;
            default:
                break;
            }
        }
    }
}

void CheckWantToFinish(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int result;
    mainData->game_state_pause = mainData->game_state;
    mainData->game_state = GAME_PAUSE;
    al_pause_event_queue(allegroObj->event_queue, true);
    al_stop_timer(allegroObj->timer);
    DrawDisplayAndFlip(mainData, allegroObj);
    result = MY_ALGO_Y_N_Msg("Notice", "Shutdown This Game?\nYou can press...");
    if(result == 1) mainData->game_state = GAME_FINISH;
    else
    {
        mainData->game_state = mainData->game_state_pause;
        mainData->game_state_pause = GAME_NONE;
        al_pause_event_queue(allegroObj->event_queue, false);
        al_start_timer(allegroObj->timer);
    }
}

void CheckStateMenuSwitchTo(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int i;
    for(i = 0; i < NUM_MENU_BUTTON; i++)
    {
        if(allegroObj->menuButton[i].isSelected)
        {
            switch(i)
            {
            case 0:
                mainData->game_state = GAME_MODE_SELECT;
                break;
            case 1:
                mainData->game_state = GAME_RULE;
                break;
            case 2:
                mainData->game_state = GAME_RANK;
                if(!mainData->scoreFileData->fileIsRead) mainData->scoreFileData->fileIsRead = ScoreFileRead( PATH_FILE_SCORE, mainData->scoreFileData);
                break;
            case 3:
                mainData->game_state = GAME_ABOUT;
                break;
            }
            allegroObj->menuButton[i].isSelected = 0; //切換狀態後要重設
        }
    }
}

void CheckKeyboardDown(MainDataStut *mainData, AllegroObjStut *allegroObj)
//人物跳動改用TIMER偵測鍵盤，才不會卡頓，其他照常
{
    int state = mainData->game_state;
    switch(state)
    {
    case GAME_PLAYING_NORMAL:
        switch(allegroObj->events.keyboard.keycode)
        {
        case ALLEGRO_KEY_V:
            CreateMeteors(&allegroObj->newMeteor);
            break;
      /*  case ALLEGRO_KEY_B:
            CreateMeteors(&allegroObj->newMeteor);
            break;*/
        case ALLEGRO_KEY_Z:
            mainData->game_state = GAME_PLAYING_MID_BOSS;
            //creat
            break;
        case ALLEGRO_KEY_X:
            mainData->game_state = GAME_PLAYING_FINAL_BOSS;
            break;
        case ALLEGRO_KEY_C:
            if(mainData->game_state == GAME_PLAYING_NORMAL) CreateCoins(&allegroObj->coin);
        default:
            break;
        }

    }
}

void CheckStateModeSwitchTo(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int i;
    for(i = 0; i < NUM_MODE_BUTTON; i++)
    {
        if(allegroObj->modeButton[i].isSelected)
        {
            mainData->game_state = GAME_PLAYING_NORMAL;
            mainData->score.chars = 1;
            //CreateCoins(&allegroObj->Coin);
            switch(i)
            {
            case 0:
                mainData->game_mode = MODE_EASY;
                break;
            case 1:
                mainData->game_mode = MODE_MEDIUM;
                break;
            case 2:
                mainData->game_mode = MODE_HARD;
                break;
            }
            allegroObj->modeButton[i].isSelected = 0; //切換狀態後要重設
        }
    }
}

void CheckMouseClick(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int state = mainData->game_state;
    //int i;
    if(mainData->mouse.isClick == 1)  //按下
    {

    }
    else if(mainData->mouse.isClick == 0)
    {
        switch(state)
        {
        case GAME_MENU:
            CheckStateMenuSwitchTo(mainData, allegroObj);
            break;
        case GAME_MODE_SELECT:
            CheckStateModeSwitchTo(mainData, allegroObj);
            if(allegroObj->homeButton.isSelected)
            {
                mainData->game_state = GAME_MENU;
                allegroObj->homeButton.isSelected = 0; //切換狀態後要重設
            }
            break;
        case GAME_RULE:
            if(allegroObj->homeButton.isSelected)
            {
                mainData->game_state = GAME_MENU;
                allegroObj->homeButton.isSelected = 0; //切換狀態後要重設
            }
            break;
        case GAME_RANK:
            if(allegroObj->homeButton.isSelected)
            {
                mainData->game_state = GAME_MENU;
                mainData->scoreFileData->fileIsRead = 0;
                allegroObj->homeButton.isSelected = 0; //切換狀態後要重設
            }
            break;
        case GAME_ABOUT:
            if(allegroObj->homeButton.isSelected)
            {
                mainData->game_state = GAME_MENU;
                allegroObj->homeButton.isSelected = 0; //切換狀態後要重設
            }
            break;
        default:
            break;
        }
    }

}

void CheckMouseMove(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int state = mainData->game_state;
    switch(state)
    {
    case GAME_MENU:
        CheckMouseMoveOnMenuButton(mainData, allegroObj);
        break;
    case GAME_MODE_SELECT:
        CheckMouseMoveOnModeButton(mainData, allegroObj);
        CheckMouseMoveOnHomeButton(mainData, allegroObj);
        break;
    case GAME_RULE:
        CheckMouseMoveOnHomeButton(mainData, allegroObj);
        break;
    case GAME_RANK:
        CheckMouseMoveOnHomeButton(mainData, allegroObj);
        break;
    case GAME_ABOUT:
        CheckMouseMoveOnHomeButton(mainData, allegroObj);
        break;
    default:
        break;
    }
}

void CheckMouseMoveOnHomeButton(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    if(allegroObj->homeButton.start_x <= mainData->mouse.x && mainData->mouse.x <= allegroObj->homeButton.end_x
            && allegroObj->homeButton.start_y <= mainData->mouse.y && mainData->mouse.y <= allegroObj->homeButton.end_y)
        allegroObj->homeButton.isSelected = 1;
    else
        allegroObj->homeButton.isSelected = 0;
}

void CheckMouseMoveOnMenuButton(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int i;
    for(i = 0; i < NUM_MENU_BUTTON; i++)
    {
        if(allegroObj->menuButton[i].start_x <= mainData->mouse.x && mainData->mouse.x <= allegroObj->menuButton[i].end_x
                && allegroObj->menuButton[i].start_y <= mainData->mouse.y && mainData->mouse.y <= allegroObj->menuButton[i].end_y)
            allegroObj->menuButton[i].isSelected = 1;
        else
            allegroObj->menuButton[i].isSelected = 0;
    }
}

void CheckMouseMoveOnModeButton(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int i;
    for(i = 0; i < NUM_MODE_BUTTON; i++)
    {
        if(allegroObj->modeButton[i].start_x <= mainData->mouse.x && mainData->mouse.x <= allegroObj->modeButton[i].end_x
                && allegroObj->modeButton[i].start_y <= mainData->mouse.y && mainData->mouse.y <= allegroObj->modeButton[i].end_y)
            allegroObj->modeButton[i].isSelected = 1;
        else
            allegroObj->modeButton[i].isSelected = 0;
    }
}

void CheckGameState(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int state = mainData->game_state;
    //printf("state:%d\n", state);
    switch(state)
    {
    case GAME_NONE:
        //DrawDisplayAndFlip(mainData, allegroObj);
        break;
    default:
        break;
    }
}
