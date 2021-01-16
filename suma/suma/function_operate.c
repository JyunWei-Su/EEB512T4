#include "defineHeader.h"
#include "resource.h"

void move_background(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    allegroObj->background.x -= OFFSET_ROLE_WALK;
    if(allegroObj->background.x <= -SIZE_IMG_BKG_WIDTH) allegroObj->background.x += SIZE_IMG_BKG_WIDTH;
}

void move_coin(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    ObjectStut *nowCoin = NULL;
    nowCoin = allegroObj->coin.objs;

    while(nowCoin != NULL)
    {
        nowCoin->start_x -= 2;
        if((nowCoin->start_x) + SIZE_IMG_COIN_WIDTH <= 0) nowCoin->start_x = DISPLAY_WIDTH;
        end_xy_update_object(nowCoin, SIZE_IMG_COIN_WIDTH, SIZE_IMG_COIN_HEIGHT);
        nowCoin = nowCoin->nextObj;
    }
}

void move_meteor_new(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    ObjectStut *nowMeteor = NULL;
    nowMeteor = allegroObj->newMeteor.objs;

    while(nowMeteor != NULL)
    {
        nowMeteor->start_x -= nowMeteor->speed_x;
        nowMeteor->start_y += nowMeteor->speed_y;
        if((nowMeteor->start_x) + SIZE_IMG_METEOR_WIDTH <= 0) nowMeteor->start_x = DISPLAY_WIDTH;
        end_xy_update_object(nowMeteor, SIZE_IMG_METEOR_WIDTH, SIZE_IMG_METEOR_HEIGHT);
        nowMeteor = nowMeteor->nextObj;
    }
}


void move_floor(MainDataStut *mainData, AllegroObjStut *allegroObj) //FTT
{
    ObjectStut *nowFloor = NULL;
    nowFloor = allegroObj->floor.objs;

    while(nowFloor != NULL)
    {
        switch(nowFloor->state)
        {
        case FLOOR_ACTIVE:
            nowFloor->start_x -= OFFSET_ROLE_WALK+1;
            nowFloor->end_x -= OFFSET_ROLE_WALK+1;
            if(nowFloor->end_x < 0) nowFloor->state = FLOOR_STANDBY;
            break;
        case FLOOR_STANDBY:
            DestoryFloorOnce(&allegroObj->floor);
            break;
        }
        nowFloor = nowFloor->nextObj;
    }
}

void CrachCheck(MainDataStut *mainData, AllegroObjStut *allegroObj) //FTT
{
    /*bool crash;
    crash = ObjCrashCheck(allegroObj->role.start_x, allegroObj->role.start_y, allegroObj->role.end_x, allegroObj->role.end_y,
                               allegroObj->floor.start_x, allegroObj->floor.start_y, allegroObj->floor.end_x, allegroObj->floor.end_y);
    crash ? printf("\tCrash\n") : printf("\tNo crash.\n");*/
    CrachCheck_role_coin(mainData, allegroObj);
}

void CrachCheckForFloor(MainDataStut *mainData, AllegroObjStut *allegroObj) //FTT

{
    /*bool crash;
    crash = FloorCrashCheck(allegroObj->role.start_x, allegroObj->role.start_y, allegroObj->role.end_x, allegroObj->role.end_y,
                               allegroObj->floor.start_x, allegroObj->floor.start_y, allegroObj->floor.end_x, allegroObj->floor.end_y);
    crash ? printf("\tFloor\n") : printf("\tNo floor.\n");*/
    //CrachCheck_role_coin(mainData, allegroObj);
}

void DoCrash(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    mainData->score.coins += ScoreAdd_Coins(&allegroObj->coin)*50;
    DestoryCoins(&allegroObj->coin);
}

void CrachCheck_role_coin(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    bool crash;
    ObjectStut *nowCoin = NULL;
    RoleStut *nowRole = NULL;
    nowCoin = allegroObj->coin.objs;
    nowRole = &allegroObj->role;
    while(nowCoin != NULL)
    {
        crash = ObjCrashCheck(nowRole->start_x, nowRole->start_y, nowRole->end_x, nowRole->end_y,
                               nowCoin->start_x, nowCoin->start_y, nowCoin->end_x, nowCoin->end_y);
        if(crash) nowCoin->state = COIN_DESTORY;
        //crash ? printf("\tCrash\n") : NULL ;
        nowCoin = nowCoin->nextObj;
    }

}


void ParameterOperate(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int state = mainData->game_state;
    al_get_keyboard_state(&allegroObj->keyboard_state);
    switch(state)
    {
    case GAME_PLAYING_NORMAL:
        move_background(mainData, allegroObj);
        //move_coin_old(mainData, allegroObj);
        move_coin(mainData, allegroObj);
        move_obscale(mainData,allegroObj);
        move_meteor_new(mainData, allegroObj);
        move_floor(mainData, allegroObj); //FTT
        SetFloor(&allegroObj->floor); //確認是否需要新增地板or釋放地板

        if(mainData->game_percent < 10000) mainData->game_percent += 3;

        /* Role */
        role_jump(allegroObj);
        //meteor_drop(allegroObj);
        /* Check Crash */
        CrachCheck(mainData, allegroObj);
        //CrachCheckForFloor(mainData, allegroObj); //FTT
        DoCrash(mainData, allegroObj);
        CrashCheck_role_obscale(mainData, allegroObj);
        break;

    case GAME_PLAYING_MID_BOSS:
        move_background(mainData, allegroObj);
        move_floor(mainData, allegroObj); //FTT
        //move_coin_old(mainData, allegroObj);

        /* Role*/
        role_jump(allegroObj);
        meteor_drop(allegroObj);
        break;

    case GAME_PLAYING_FINAL_BOSS:
        move_background(mainData, allegroObj);
        move_floor(mainData, allegroObj); //FTT
        //move_coin_old(mainData, allegroObj);

        role_jump(allegroObj);
        meteor_drop(allegroObj);
        break;
    }
}

void Gravity(AllegroObjStut *allegroObj) //重力
{
    //const float gravity =GRAVITY;
    allegroObj->role.start_y += GRAVITY;
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
    end_xy_update_role(&allegroObj->role);
}

void meteor_drop(AllegroObjStut *allegroObj)
{
    int i;
    //allegroObj->meteor.start_y += allegroObj->meteor.speed_y;
    for (i = 0; i < allegroObj->meteor_n; i++)
    {
        allegroObj->meteors[i].start_y += allegroObj->meteors[i].speed_y;
        allegroObj->meteors_right_drop[i].start_x -= allegroObj->meteors_right_drop[i].speed_x;
        allegroObj->meteors_right_drop[i].start_y += allegroObj->meteors_right_drop[i].speed_y;
        allegroObj->meteors_left_drop[i].start_x += allegroObj->meteors_right_drop[i].speed_x;
        allegroObj->meteors_left_drop[i].start_y += allegroObj->meteors_right_drop[i].speed_y;
        //計算隕石邊界
        end_xy_update_meteor(&allegroObj->meteors[i]);
        end_xy_update_meteor(&allegroObj->meteors_right_drop[i]);
        end_xy_update_meteor(&allegroObj->meteors_left_drop[i]);
    }
}


void end_xy_update_meteor(MeteorStut *meteor)
//計算隕石邊界
{
    meteor->end_x = meteor->start_x + SIZE_IMG_METEOR_WIDTH;
    meteor->end_y = meteor->start_y + SIZE_IMG_METEOR_HEIGHT;
}

void end_xy_update_role(RoleStut *role)
//計算角色邊界
{
    role->end_x = role->start_x + SIZE_IMG_ROLE_WIDTH;
    role->end_y = role->start_y + SIZE_IMG_ROLE_HEIGHT;
}

void end_xy_update_coin_old(CoinStut_old *coin_old)
//計算金幣邊界
{
    coin_old->end_x = coin_old->start_x + SIZE_IMG_COIN_WIDTH;
    coin_old->end_y = coin_old->start_y + SIZE_IMG_COIN_HEIGHT;
}


/*
void end_xy_update_floor(FloorStut *floor) //FTT
//計算地板邊界
{
    floor->end_x = floor->start_x + SIZE_IMG_FLOOR_WIDTH;
    floor->end_y = floor->start_y + SIZE_IMG_FLOOR_HEIGHT;
}*/

void end_xy_update_object(ObjectStut *obj, int size_w, int size_h)
//計算物件邊界(新)
{
    obj->end_x = obj->start_x + size_w;
    obj->end_y = obj->start_y + size_h;
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
    if(start_x2 - end_x1 >= 2*Length_x && start_y2 - end_y1 >= 2*Length_y)
        return ObjCrashCheck_sub(start_x1, start_y1, end_x1, end_y1,start_x2, start_y2, end_x2, end_y2);
    else
        return ObjCrashCheck_sub(start_x1, start_y1, end_x1, end_y1,start_x2, start_y2, end_x2, end_y2);;
}

bool ObjCrashCheck_sub(float start_x1,float start_y1,float end_x1,float end_y1,float start_x2,float start_y2,float end_x2,float end_y2)
{
    if((start_x1 <= start_x2 && start_x2 <=end_x1) && (start_y1 <=start_y2 && start_y2 <= end_y1)) return 1;
    else if ( (start_x1 <=start_x2 && start_x2<=end_x1) && (start_y1 <=end_y2 && end_y2 <= end_y1)) return 1;
    else if( (start_x1 <=end_x2 && end_x2<=end_x1) && (start_y1 <=start_y2 && start_y2 <= end_y1))  return 1;
    else if( (start_x1 <=end_x2 && end_x2<=end_x1) && (start_y1 <=end_y2 && end_y2 <= end_y1))    return 1;
    //==================================
    else if((start_x2 <= start_x1 && start_x1 <=end_x2) && (start_y2 <=start_y1 && start_y1 <= end_y2)) return 1;
    else if ( (start_x2 <=start_x1 && start_x1<=end_x2) && (start_y2 <=end_y1 && end_y1 <= end_y2)) return 1;
    else if( (start_x2 <=end_x1 && end_x1<=end_x2) && (start_y2 <=start_y1 && start_y1 <= end_y2))  return 1;
    else if( (start_x2 <=end_x1 && end_x1<=end_x2) && (start_y2 <=end_y1 && end_y1 <= end_y2))    return 1;
    else return 0;
}

//FTT
bool FloorCrashCheck(float start_char_x,float start_char_y,float end_char_x,float end_char_y,float start_floor_x,float start_floor_y,float end_floor_x,float end_floor_y)
{
    start_end_change(&start_char_x,&end_char_x);
    start_end_change(&start_char_y,&end_char_y);
    start_end_change(&start_floor_x,&end_floor_x);
    start_end_change(&start_floor_y,&end_floor_y);
    //printf("start_x2=%f\n",start_x2);
    //printf("end_x1=%f\n",end_x1);
    //printf("start_x2 - end_x1=%f\n",start_x2 - end_x1);
        return FloorCrashCheck_sub(start_char_x, start_char_y, end_char_x, end_char_y,start_floor_x, start_floor_y, end_floor_x, end_floor_y);
}

//FTT
bool FloorCrashCheck_sub(float start_char_x,float start_char_y,float end_char_x,float end_char_y,float start_floor_x,float start_floor_y,float end_floor_x,float end_floor_y)
{
    float Ly = end_char_y - start_floor_y;
    if((start_floor_x <=start_char_x && start_char_x<=end_floor_x) && (start_char_y + Ly <= start_floor_y))return 1;
    else if ( (start_floor_x <=end_char_x && end_char_x <=end_floor_x) && (start_char_y + Ly <= start_floor_y )) return 1;
    else if((start_char_x <= start_floor_x && start_floor_x <=end_char_x) && (start_char_y + Ly <= start_floor_y )) return 1;
    else if ( (start_char_x <=end_floor_x && end_floor_x <=end_char_x) && (start_char_y + Ly<= start_floor_y)) return 1;
    else return 0;
}

