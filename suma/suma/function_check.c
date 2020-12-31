//#include "function_check.h"
#include "defineHeader.h"
#include "resource.h"


void CheckEvent(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm)
{
    int result = 0;
    if(!al_is_event_queue_empty(allegroObj->event_queue))
    {
        while(al_get_next_event(allegroObj->event_queue, &allegroObj->events))
        {
            if(mainData->game_state == GAME_FINISH) break;
            switch(allegroObj->events.type)//用->還是.
            {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                //result = MY_ALGO_Y_N_Msg("Notice", "Shutdown This Game?\nYou can press Q or Esc to return to MENU.");
                //if(result == 1) mainData->game_state = GAME_STATE_FINISH;
                mainData->game_state = GAME_FINISH;
                break;
            case ALLEGRO_EVENT_MENU_CLICK:
                //if (allegroObj->events.user.data1 == FILE_EXIT_ID)
                //{
                //    mainData->game_state = FINISH;
                //}
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                CheckMouseMove(mainData, allegroObj, layoutParm);
                mainData->mouse.x = allegroObj->events.mouse.x;
                mainData->mouse.y = allegroObj->events.mouse.y;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if(!(allegroObj->events.mouse.button&1)) break; //不是按下左鍵就忽略
                mainData->mouse.isClick = 1;
                CheckMouseClick(mainData, allegroObj, layoutParm);
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if(!(allegroObj->events.mouse.button&1)) break; //不是按下左鍵就忽略
                mainData->mouse.isClick = 0;
                CheckMouseClick(mainData, allegroObj, layoutParm);
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                //CheckKeyboardDown(mainData, allegroObj);
                break;
            case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
                al_flip_display();
                break;
            case ALLEGRO_EVENT_TIMER:
                printf("%d\n", mainData->game_state);
                PlaySoundEffect(mainData, allegroObj);
                ParameterOperate(mainData, allegroObj, layoutParm);
                //CheckGameState(mainData, allegroObj, layoutParm);
                DrawDisplayAndFlip(mainData, allegroObj, layoutParm);
                break;
            default:
                break;
            }
        }
    }
}

void CheckStateMenuSwitchTo(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm)
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
                        break;
                    case 3:
                        mainData->game_state = GAME_ABOUT;
                        break;
                    }
                    allegroObj->menuButton[i].isSelected = 0; //切換狀態後要重設
                }
            }
}

void CheckStateModeSwitchTo(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm)
{
    int i;
    for(i = 0; i < NUM_MODE_BUTTON; i++)
            {
                if(allegroObj->modeButton[i].isSelected)
                {
                    mainData->game_state = GAME_PLAYING;
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

void CheckMouseClick(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm)
{
    int state = mainData->game_state;
    int i;
    if(mainData->mouse.isClick == 1)  //按下
    {

    }
    else if(mainData->mouse.isClick == 0)
    {
        switch(state)
        {
        case GAME_MENU:
            CheckStateMenuSwitchTo(mainData, allegroObj, layoutParm);
            break;
        case GAME_MODE_SELECT:
            CheckStateModeSwitchTo(mainData, allegroObj, layoutParm);
            if(allegroObj->homeButton.isSelected){
                mainData->game_state = GAME_MENU;
                allegroObj->homeButton.isSelected = 0; //切換狀態後要重設
            }
            break;
        case GAME_RULE:
            if(allegroObj->homeButton.isSelected){
                mainData->game_state = GAME_MENU;
                allegroObj->homeButton.isSelected = 0; //切換狀態後要重設
            }
            break;
        case GAME_RANK:
            if(allegroObj->homeButton.isSelected){
                mainData->game_state = GAME_MENU;
                allegroObj->homeButton.isSelected = 0; //切換狀態後要重設
            }
            break;
        case GAME_ABOUT:
            if(allegroObj->homeButton.isSelected){
                mainData->game_state = GAME_MENU;
                allegroObj->homeButton.isSelected = 0; //切換狀態後要重設
            }
            break;
        default:
            break;
        }
    }

}

void CheckMouseMove(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm)
{
    int state = mainData->game_state;
    switch(state)
    {
    case GAME_MENU:
        CheckMouseMoveOnMenuButton(mainData, allegroObj, layoutParm);
        break;
    case GAME_MODE_SELECT:
        CheckMouseMoveOnModeButton(mainData, allegroObj, layoutParm);
        CheckMouseMoveOnHomeButton(mainData, allegroObj, layoutParm);
        break;
    case GAME_RULE:
        CheckMouseMoveOnHomeButton(mainData, allegroObj, layoutParm);
        break;
    case GAME_RANK:
        CheckMouseMoveOnHomeButton(mainData, allegroObj, layoutParm);
        break;
    case GAME_ABOUT:
        CheckMouseMoveOnHomeButton(mainData, allegroObj, layoutParm);
        break;
    default:
        break;
    }
}

void CheckMouseMoveOnHomeButton(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm)
{
    if(allegroObj->homeButton.start_x <= mainData->mouse.x && mainData->mouse.x <= allegroObj->homeButton.end_x
            && allegroObj->homeButton.start_y <= mainData->mouse.y && mainData->mouse.y <= allegroObj->homeButton.end_y)
        allegroObj->homeButton.isSelected = 1;
    else
        allegroObj->homeButton.isSelected = 0;
}

void CheckMouseMoveOnMenuButton(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm)
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

void CheckMouseMoveOnModeButton(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm)
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

void CheckGameState(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm)
{
    int state = mainData->game_state;
    //printf("state:%d\n", state);
    switch(state)
    {
    case GAME_DRAW:
        DrawDisplayAndFlip(mainData, allegroObj, layoutParm);
        break;
    case GAME_TEST: //test
        //printf("Final Score: %d\n", mainData->tolScore); // After there is no elem. to eleimate, print the final score (each eleimate get 10 points)
        mainData->game_state = GAME_NONE;
        break;
    case GAME_NONE:
        //DrawDisplayAndFlip(mainData, allegroObj, layoutParm);
        break;
    default:
        break;
    }
}
