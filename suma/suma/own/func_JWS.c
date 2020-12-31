#include "../own/header_JWS.h"
#include "../defineHeader.h"

void PrintTest_JWS()
{
    printf("This is a print test by JWS.\n");
}



void ParameterOperate(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm)
{
    int state = mainData->game_state;
    al_get_keyboard_state(&allegroObj->keyboard_state);
    switch(state)
    {
    case GAME_PLAYING:
        allegroObj->background.x -= 3;
        if(allegroObj->background.x <= -SIZE_IMG_BKG_WIDTH) allegroObj->background.x += SIZE_IMG_BKG_WIDTH;
        /* Role*/
        if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_W)){
            if(allegroObj->role.state != ROLE_MUST_DROP) allegroObj->role.start_y -= 10;
            if(allegroObj->role.state == ROLE_NULL) allegroObj->role.state = ROLE_JUMP;
        }
        if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_S)){ //帶與重力修正
            allegroObj->role.start_y += 10;
            if(allegroObj->role.state == ROLE_JUMP) allegroObj->role.state = ROLE_DROP;
        }
        if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_D))
            allegroObj->role.start_x += 10;
        if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_A))
            allegroObj->role.start_x -=10;
        //邊界
        if(allegroObj->role.start_y <= 550) allegroObj->role.state = ROLE_MUST_DROP;
        if(allegroObj->role.state == ROLE_MUST_DROP) Gravity(allegroObj);

        if(allegroObj->role.start_y >= 700){
            allegroObj->role.start_y = 700;
            allegroObj->role.state = ROLE_NULL;
        }
        if(allegroObj->role.start_x < 0)
            allegroObj->role.start_x = 0;
        if(allegroObj->role.start_x > 1500)
            allegroObj->role.start_x = 1500;

        Gravity(allegroObj); //?
        break;
    case GAME_MENU:
        break;
    }


}


