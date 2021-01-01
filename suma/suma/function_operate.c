#include "defineHeader.h"
#include "resource.h"

void ParameterOperate(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    bool statecrash;
    float sx,sy,ex,ey;
    sx = 1000;
    ex = 1500;
    sy = 0;
    ey = 800;
    int state = mainData->game_state;
    al_get_keyboard_state(&allegroObj->keyboard_state);
    switch(state)
    {
    case GAME_PLAYING_NORMAL:
        allegroObj->background.x -= OFFSET_ROLE_WALK;
        if(allegroObj->background.x <= -SIZE_IMG_BKG_WIDTH) allegroObj->background.x += SIZE_IMG_BKG_WIDTH;
        allegroObj->floor.start_x -= 1.5;
        allegroObj->floor.end_x = allegroObj->floor.start_x + SIZE_IMG_FLOOR_WIDTH;
        allegroObj->floor.end_y = allegroObj->floor.start_y + SIZE_IMG_FLOOR_HEIGHT;

        /* Role*/
        role_jump(allegroObj);
        meteor_drop(allegroObj);
        statecrash = CrashCheck(allegroObj->role.start_x,allegroObj->role.start_y, allegroObj->role.end_x, allegroObj->role.end_y ,sx,sy,ex,ey);
        if(statecrash) printf("\tCrash\n");
        else printf("\tNo crash.\n");
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
    allegroObj->role.img = al_load_bitmap( PATH_IMG_ROLE_1 );
    allegroObj->role.imgs_runing = al_load_bitmap( PATH_IMG_ROLE_SEQ_RUNING );
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

    Gravity(allegroObj);
    //角色邊界運算
    allegroObj->role.end_x = allegroObj->role.start_x + SIZE_IMG_ROLE_WIDTH;
    allegroObj->role.end_y = allegroObj->role.start_y + SIZE_IMG_ROLE_HEIGHT;
}

void meteor_init(AllegroObjStut *allegroObj)
{
    int i;
    allegroObj->meteor_n = rand()%NUMBER_METEOR+5; //隕石數量
    allegroObj->meteor.img = al_load_bitmap( PATH_IMG_METEOR);
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
        allegroObj->meteors_right_drop[i].start_x = rand()%2000;
        allegroObj->meteors_right_drop[i].start_y = 0;
        allegroObj->meteors_right_drop[i].speed_x = rand()%SPEED_X_METEOR_RIGHT+1;
        allegroObj->meteors_right_drop[i].speed_y = rand()%SPEED_Y_METEOR_RIGHT+3;
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

void meteor_drop(AllegroObjStut *allegroObj)
{
    int i;
    for (i = 0; i < allegroObj->meteor_n; i++)
    {
        allegroObj->meteors[i].start_y += allegroObj->meteors[i].speed_y;
        allegroObj->meteors_right_drop[i].start_x -=allegroObj->meteors_right_drop[i].speed_x;
        allegroObj->meteors_right_drop[i].start_y +=allegroObj->meteors_right_drop[i].speed_y;
        allegroObj->meteors_left_drop[i].start_x +=allegroObj->meteors_right_drop[i].speed_x;
        allegroObj->meteors_left_drop[i].start_y +=allegroObj->meteors_right_drop[i].speed_y;

        meteor_end_xy_update(&allegroObj->meteors[i]);
        meteor_end_xy_update(&allegroObj->meteors_right_drop[i]);
        meteor_end_xy_update(&allegroObj->meteors_left_drop[i]);

        //allegroObj->meteors[i].end_x = allegroObj->meteors[i].start_x + SIZE_IMG_METEOR_WIDTH;
        //allegroObj->meteors[i].end_y = allegroObj->meteors[i].start_y + SIZE_IMG_METEOR_HEIGHT;

    }
    //allegroObj->meteor.start_y +=20;

    //炸彈邊界運算
    //allegroObj->meteor.end_x = allegroObj->meteor.start_x + SIZE_IMG_METEOR_WIDTH;
    //allegroObj->meteor.end_y = allegroObj->meteor.start_y + SIZE_IMG_METEOR_HEIGHT;
}

void meteor_end_xy_update(MeteorStut *meteor){
    meteor->end_x = meteor->start_x + SIZE_IMG_METEOR_WIDTH;
    meteor->end_y = meteor->start_y + SIZE_IMG_METEOR_HEIGHT;
}
