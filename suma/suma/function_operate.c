#include "defineHeader.h"
#include "resource.h"

void ParameterOperate(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int state = mainData->game_state;
    al_get_keyboard_state(&allegroObj->keyboard_state);
    switch(state)
    {
    case GAME_PLAYING:
        allegroObj->background.x -= OFFSET_ROLE_WALK;
        if(allegroObj->background.x <= -SIZE_IMG_BKG_WIDTH) allegroObj->background.x += SIZE_IMG_BKG_WIDTH;
        /* Role*/

        if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_W))
        {
            if(allegroObj->role.state != ROLE_MUST_DROP) allegroObj->role.start_y -= OFFSET_ROLE_JUMP;
            if(allegroObj->role.state == ROLE_NULL) allegroObj->role.state = ROLE_JUMP;
        }
        if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_S))  //帶與重力修正
        {
            allegroObj->role.start_y += OFFSET_ROLE_JUMP;
            if(allegroObj->role.state == ROLE_JUMP) allegroObj->role.state = ROLE_DROP;
        }
        if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_D))
            allegroObj->role.start_x += OFFSET_ROLE_JUMP;
        if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_A))
            allegroObj->role.start_x -=OFFSET_ROLE_JUMP;
        //邊界
        if(allegroObj->role.start_y <= MAX_ROLE_Y ) allegroObj->role.state = ROLE_MUST_DROP;
        //if(allegroObj->role.state == ROLE_MUST_DROP) Gravity(allegroObj);

        if(allegroObj->role.start_y >= MIN_ROLE_Y)
        {
            allegroObj->role.start_y = MIN_ROLE_Y;
            allegroObj->role.state = ROLE_NULL;
        }
        if(allegroObj->role.start_x < MIN_ROLE_X)
            allegroObj->role.start_x = MIN_ROLE_X;
        if(allegroObj->role.start_x > MAX_ROLE_X)
            allegroObj->role.start_x = MAX_ROLE_X;

        Gravity(allegroObj); //?
        break;
    case GAME_MENU:
        break;
    }
}

void Gravity(AllegroObjStut *allegroObj) //重力
{
    //const float gravity =GRAVITY;
    allegroObj->role.start_y += GRAVITY;
}

void role_init(AllegroObjStut *allegroObj)
{
    allegroObj->role.img = al_load_bitmap(PATH_IMG_ROLE_1);
    allegroObj->role.start_x=200;
    allegroObj->role.start_y=700;
    allegroObj->role.state = ROLE_NULL;
}

void role_jump(AllegroObjStut *allegroObj)
{
    //int vely=0;
    //const int Gravity=1;
    //bool jump =true;
    if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_W))
    {
        allegroObj->role.start_y -= OFFSET_ROLE_JUMP ;
    }
    if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_D))
        allegroObj->role.start_x += OFFSET_ROLE_WALK ;
    if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_A))
        allegroObj->role.start_x -=OFFSET_ROLE_WALK ;

    if(allegroObj->role.start_y> 800)
        allegroObj->role.start_y = 800;
    if(allegroObj->role.start_x < 0)
        allegroObj->role.start_x = 0;
    if(allegroObj->role.start_x > 1500)
        allegroObj->role.start_x = 1500;
}
