#include "defineHeader.h"
#include "resource.h"

void ParameterOperate(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    bool statecrash;
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
        statecrash = ObjCrashCheck(allegroObj->role.start_x, allegroObj->role.start_y, allegroObj->role.end_x, allegroObj->role.end_y ,
                                allegroObj->floor.start_x, allegroObj->floor.start_y, allegroObj->floor.end_x, allegroObj->floor.end_y);
        statecrash ? printf("\tCrash\n") : printf("\tNo crash.\n");
        //if(statecrash) printf("\tCrash\n");
        //else printf("\tNo crash.\n");
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

        //炸彈邊界運算
        meteor_end_xy_update(&allegroObj->meteors[i]);
        meteor_end_xy_update(&allegroObj->meteors_right_drop[i]);
        meteor_end_xy_update(&allegroObj->meteors_left_drop[i]);
    }
}

void meteor_end_xy_update(MeteorStut *meteor){
    meteor->end_x = meteor->start_x + SIZE_IMG_METEOR_WIDTH;
    meteor->end_y = meteor->start_y + SIZE_IMG_METEOR_HEIGHT;
}

void start_end_change(float *start,float *end)
{
    float temp;
    //確認start與end大小
    if(*start > *end)
    {
        temp = *start;
        *start = *end;
        *end = temp;
    }
}

bool ObjCrashCheck(float start_x1,float start_y1,float end_x1,float end_y1,float start_x2,float start_y2,float end_x2,float end_y2)
{
    float Length_x,Length_y;
    start_end_change(&start_x1,&end_x1);
    start_end_change(&start_y1,&end_y1);
    start_end_change(&start_x2,&end_x2);
    start_end_change(&start_y2,&end_y2);
    Length_x = end_x1 - start_x1;
    Length_y = end_y1 - start_y1;
    //printf("start_x2=%f\n",start_x2);
    //printf("end_x1=%f\n",end_x1);
    //printf("start_x2 - end_x1=%f\n",start_x2 - end_x1);
    if(start_x2 - end_x1 >= Length_x && start_y2 - end_y1 >= Length_y)
        return ObjCrashCheck_sub(start_x1, start_y1, end_x1, end_y1,start_x2, start_y2, end_x2, end_y2);
    else
        return ObjCrashCheck_sub(start_x1, start_y1, end_x1, end_y1,start_x2, start_y2, end_x2, end_y2);
}

bool ObjCrashCheck_sub(float start_x1,float start_y1,float end_x1,float end_y1,float start_x2,float start_y2,float end_x2,float end_y2)
{
    if((start_x1 <= start_x2 && start_x2 <=end_x1) && (start_y2 >=start_y1 && start_y2 <= end_y1)) return 0;
    else if
       ( (start_x2 <=end_x1 && start_x2>=start_x1) && (end_y2 >=start_y1 && end_y2 <= end_y1))
       ( (start_x2 <=end_x1 && start_x2>=start_x1) && (start_y2 >=start_y1 && start_y2 <= end_y1)) ||
       ( (start_x2 <=end_x1 && start_x2>=start_x1) && (end_y2 >=start_y1 && end_y2 <= end_y1))
    /*
    if(((start_x2 <=end_x1 && start_x2>=start_x1) && (start_y2 >=start_y1 && start_y2 <= end_y1)) ||
       ((start_x2 <=end_x1 && start_x2>=start_x1) && (end_y2 >=start_y1 && end_y2 <= end_y1))
       ((start_x2 <=end_x1 && start_x2>=start_x1) && (start_y2 >=start_y1 && start_y2 <= end_y1)) ||
       ((start_x2 <=end_x1 && start_x2>=start_x1) && (end_y2 >=start_y1 && end_y2 <= end_y1))
       return 1;*/
    else return 0;
}
