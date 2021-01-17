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
                mainData->mouse.x = allegroObj->events.mouse.x;
                mainData->mouse.y = allegroObj->events.mouse.y;
                CheckMouseMove(mainData, allegroObj);
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
            case ALLEGRO_EVENT_KEY_DOWN:
                CheckKeyboardDown(mainData, allegroObj);
                break;
            case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
                al_flip_display();
                break;
            case ALLEGRO_EVENT_TIMER:
                mainData->timerCount += 1;
                //printf("%d\n", mainData->game_state);
                PlaySoundEffect(mainData, allegroObj);
                ParameterOperate(mainData, allegroObj);
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
        case ALLEGRO_KEY_C:
            if(mainData->game_state == GAME_PLAYING_NORMAL) CreateCoins(&allegroObj->coin);
            break;
        case ALLEGRO_KEY_B:
            if(mainData->game_state == GAME_PLAYING_NORMAL) CreateAttackX(&allegroObj->attackx);
        default:
            break;
        }
        break;
    case GAME_PLAYING_END://單次遊戲結束
        switch(allegroObj->events.keyboard.keycode)
        {
        case ALLEGRO_KEY_ENTER:
            GetTime(mainData->tm);
            ScoreFileAppend(PATH_FILE_SCORE, mainData);
            mainData->game_state = GAME_MENU;
            mainData->score.coins = 0;
            mainData->score.probar = 0;
            mainData->score.score = 0;
            mainData->game_percent = 0;
            memset(mainData->usrName.name, 0, 20);
            mainData->usrName.len = 0;
            FreeSubRole(&allegroObj->subRole);
            FreeAllFloor(&allegroObj->floor);
            role_reset(allegroObj);
            break;
        case ALLEGRO_KEY_BACKSPACE:
            if(mainData->usrName.len == 0) break;
            mainData->usrName.len -= 1;
            mainData->usrName.name[mainData->usrName.len] = 0;
            break;
        case ALLEGRO_KEY_A:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'A';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_B:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'B';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_C:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'C';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_D:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'D';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_E:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'E';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_F:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'F';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_G:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'G';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_H:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'H';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_I:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'I';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_J:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'J';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_K:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'K';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_L:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'L';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_M:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'M';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_N:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'N';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_O:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'O';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_P:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'P';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_Q:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'Q';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_R:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'R';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_S:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'S';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_T:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'T';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_U:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'U';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_V:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'V';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_W:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'W';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_X:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'X';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_Y:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'Y';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_Z:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = 'Z';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_0:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = '0';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_1:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = '1';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_2:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = '2';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_3:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = '3';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_4:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = '4';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_5:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = '5';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_6:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = '6';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_7:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = '7';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_8:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = '8';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_9:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = '9';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_COMMA:
            if(mainData->usrName.len >= 20) break;
            //必免與格式重複
            //mainData->usrName.name[mainData->usrName.len] = ',';
            //mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_FULLSTOP:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = '.';
            mainData->usrName.len += 1;
            break;
        case ALLEGRO_KEY_MINUS:
            if(mainData->usrName.len >= 20) break;
            mainData->usrName.name[mainData->usrName.len] = '-';
            mainData->usrName.len += 1;
            break;

        }
        break;
    }
}

void CheckStateModeSwitchTo(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int i;
    for(i = 0; i < NUM_MODE_BUTTON; i++)
    {
        if(allegroObj->modeButton[i].isSelected)
        {

            switch(i)
            {
            case 0:
                mainData->game_mode = MODE_EASY;
                mainData->speed.background = 2.5;
                mainData->speed.object = 3.5;
                break;
            case 1:
                mainData->game_mode = MODE_MEDIUM;
                mainData->speed.background = 3.5;
                mainData->speed.object = 4.5;
                break;
            case 2:
                mainData->game_mode = MODE_HARD;
                mainData->speed.background = 4.5;
                mainData->speed.object = 5.5;
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
            mainData->timerCount = 0;
            mainData->game_state = GAME_PLAYING_NORMAL;
            mainData->score.chars = 1;
            role_reset(allegroObj);

            SetFloor(&allegroObj->floor);
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
    {
        if(allegroObj->homeButton.isSelected == 0) allegroObj->sound.buttonMoveIn.readyToPlay = 1; //傳遞播放音效的參數
        allegroObj->homeButton.isSelected = 1;
    }
    else
        allegroObj->homeButton.isSelected = 0;
    //allegroObj->sound.buttonMoveIn.readyToPlay = 0;
}

void CheckMouseMoveOnMenuButton(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int i;
    for(i = 0; i < NUM_MENU_BUTTON; i++)
    {
        if(allegroObj->menuButton[i].start_x <= mainData->mouse.x && mainData->mouse.x <= allegroObj->menuButton[i].end_x
                && allegroObj->menuButton[i].start_y <= mainData->mouse.y && mainData->mouse.y <= allegroObj->menuButton[i].end_y)
        {
            if(allegroObj->menuButton[i].isSelected == 0) allegroObj->sound.buttonMoveIn.readyToPlay = 1; //傳遞播放音效的參數
            allegroObj->menuButton[i].isSelected = 1;
        }
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
        {
            if(allegroObj->modeButton[i].isSelected == 0) allegroObj->sound.buttonMoveIn.readyToPlay = 1; //傳遞播放音效的參數
            allegroObj->modeButton[i].isSelected = 1;
        }
        else
            allegroObj->modeButton[i].isSelected = 0;
    }
}
