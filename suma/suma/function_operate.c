#include "defineHeader.h"
#include "resource.h"

void ParameterOperate(MainDataStut *mainData, AllegroObjStut *allegroObj)
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
        //if(allegroObj->role.state == ROLE_MUST_DROP) Gravity(allegroObj);

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

void Gravity(AllegroObjStut *allegroObj) //重力
{
    const int gravity =3;
    allegroObj->role.start_y += gravity;
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
        allegroObj->role.start_y -= 15;
    }
    if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_D))
        allegroObj->role.start_x += 3;
    if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_A))
        allegroObj->role.start_x -=3;

    if(allegroObj->role.start_y> 800)
        allegroObj->role.start_y = 800;
    if(allegroObj->role.start_x < 0)
        allegroObj->role.start_x = 0;
    if(allegroObj->role.start_x > 1500)
        allegroObj->role.start_x = 1500;
}
