#include "defineHeader.h"
#include "resource.h"


void move_background(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    allegroObj->background.x -= mainData->speed.background;
    if(allegroObj->background.x <= -SIZE_IMG_BKG_WIDTH) allegroObj->background.x += SIZE_IMG_BKG_WIDTH;
}

void move_coin(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    ObjectStut *nowCoin = NULL;
    nowCoin = allegroObj->coin.objs;
    while(nowCoin != NULL)
    {
        nowCoin->start_x -= mainData->speed.object;
        if((nowCoin->start_x) + SIZE_IMG_COIN_WIDTH <= 0) nowCoin->start_x = DISPLAY_WIDTH;
        end_xy_update_object(nowCoin, SIZE_IMG_COIN_WIDTH, SIZE_IMG_COIN_HEIGHT);
        nowCoin = nowCoin->nextObj;
    }
}

void move_sub_role(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    ObjectStut *nowRole = NULL;
    nowRole = allegroObj->subRole.objs;
    while(nowRole != NULL)
    {
        if( nowRole->state == SUBROLE_MOVE)
        {
            /*if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_W))
            {
                if(allegroObj->role.state != ROLE_MUST_DROP) nowRole->start_y-= OFFSET_ROLE_JUMP;
                if(allegroObj->role.state == ROLE_NULL) allegroObj->role.state = ROLE_JUMP;

            }
            if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_D))
                nowRole->start_x += OFFSET_ROLE_JUMP-rand()%5;
            if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_A))
                nowRole->start_x -=OFFSET_ROLE_JUMP-rand()%5;
            if(nowRole->start_y <= MAX_ROLE_Y ) allegroObj->role.state = ROLE_MUST_DROP;
            if(allegroObj->role.state == ROLE_MUST_DROP) Gravity(allegroObj);
            if(nowRole->start_y >= MIN_ROLE_Y)
            {
                nowRole->start_y = MIN_ROLE_Y;
                allegroObj->role.state = ROLE_NULL;
            }
            if(nowRole->start_x < MIN_ROLE_X)
                nowRole->start_x = MIN_ROLE_X;
            if(nowRole->start_x > MAX_ROLE_X)
                nowRole->start_x= MAX_ROLE_X;
            //nowRole->start_x -= 2;
            //nowRole->start_y += 0;
            nowRole->start_y += GRAVITY;*/
        }
        if((nowRole->start_x) + SIZE_IMG_ROLE_WIDTH <= 0) nowRole->start_x = DISPLAY_WIDTH;
        end_xy_update_object(nowRole, SIZE_IMG_ROLE_WIDTH, SIZE_IMG_ROLE_HEIGHT);
        nowRole = nowRole->nextObj;
    }
}

void role_jump(AllegroObjStut *allegroObj)
{
    if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_W))
    {
        if(allegroObj->role.state != ROLE_MUST_DROP) allegroObj->role.start_y -= OFFSET_ROLE_JUMP;
        if(allegroObj->role.state == ROLE_NULL) allegroObj->role.state = ROLE_JUMP;
    }
    if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_S))  //±a»P­«¤O­×¥¿
    {
        allegroObj->role.start_y += OFFSET_ROLE_JUMP;
        if(allegroObj->role.state == ROLE_JUMP) allegroObj->role.state = ROLE_DROP;
    }
    if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_D))
        allegroObj->role.start_x += OFFSET_ROLE_JUMP;
    if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_A))
        allegroObj->role.start_x -=OFFSET_ROLE_JUMP;

    //Ãä¬É
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

    //¨¤¦âÃä¬É¹Bºâ
    end_xy_update_role(&allegroObj->role);
}

void move_meteor(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    ObjectStut *nowMeteor = NULL;
    nowMeteor = allegroObj->meteor.objs;
    while(nowMeteor != NULL)
    {
        nowMeteor->start_x -= nowMeteor->speed_x;
        nowMeteor->start_y += nowMeteor->speed_y;
        if((nowMeteor->start_x) + SIZE_IMG_METEOR_WIDTH <= 0) nowMeteor->start_x = DISPLAY_WIDTH;
        end_xy_update_object(nowMeteor, SIZE_IMG_METEOR_WIDTH, SIZE_IMG_METEOR_HEIGHT);
        nowMeteor = nowMeteor->nextObj;
    }
}
void move_attackx(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    ObjectStut *nowAttackx = NULL;
    nowAttackx = allegroObj->attackx.objs;
    while(nowAttackx != NULL)
    {
        nowAttackx->start_x -= nowAttackx->speed_x;
        //nowAttackx->start_y += nowAttackx->speed_y;
        if((nowAttackx->start_x) + SIZE_IMG_ATTACKX_WIDTH <= 0) nowAttackx->start_x = DISPLAY_WIDTH;
        end_xy_update_object(nowAttackx, SIZE_IMG_ATTACKX_WIDTH, SIZE_IMG_ATTACKX_HEIGHT);
        nowAttackx = nowAttackx->nextObj;
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
            nowFloor->start_x -= mainData->speed.object;
            nowFloor->end_x -= mainData->speed.object;
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
    CrachCheck_subrole_coin(mainData, allegroObj);
    CrachCheck_role_role(mainData, allegroObj);
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
    DestoryRoles(&allegroObj->subRole,allegroObj);
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

void CrachCheck_subrole_coin(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    bool crash;
    ObjectStut *nowCoin = NULL;
    ObjectStut *nowSubRole = NULL;
    nowCoin = allegroObj->coin.objs;
    nowSubRole = allegroObj->subRole.objs;
    while(nowCoin != NULL)
    {
        while(nowSubRole != NULL)
        {
            crash = ObjCrashCheck(nowSubRole->start_x, nowSubRole->start_y, nowSubRole->end_x, nowSubRole->end_y,
                                  nowCoin->start_x, nowCoin->start_y, nowCoin->end_x, nowCoin->end_y);
            if(crash) nowCoin->state = COIN_DESTORY;
            //crash ? printf("\tCrash\n") : NULL ;
            nowSubRole = nowSubRole->nextObj;
        }
        nowCoin = nowCoin->nextObj;
    }
}

void CrachCheck_role_role(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    bool crash;
    ObjectStut *nowSubRole = NULL;
    RoleStut *nowRole = NULL;
    nowSubRole = allegroObj->subRole.objs;
    nowRole = &allegroObj->role;
    while(nowSubRole != NULL)
    {
        crash = ObjCrashCheck(nowRole->start_x, nowRole->start_y, nowRole->end_x, nowRole->end_y,
                              nowSubRole->start_x, nowSubRole->start_y, nowSubRole->end_x, nowSubRole->end_y);
        if(crash) nowSubRole->state = SUPROLE_CRASH;
        // crash ? printf("\tCrash\n") : NULL ;
        nowSubRole = nowSubRole->nextObj;
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
        SetObscale(mainData,allegroObj);
        move_coin(mainData, allegroObj);
    //¶¶§Ç²§±`
        move_sub_role(mainData, allegroObj);
        move_meteor(mainData, allegroObj);
        move_attackx(mainData, allegroObj);
        move_obscale(mainData,allegroObj);
        move_floor(mainData, allegroObj); //FTT
        SetFloor(&allegroObj->floor); //½T»{¬O§_»Ý­n·s¼W¦aªOorÄÀ©ñ¦aªO¿
        /* ¶i«×±ø */

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
        //meteor_drop(allegroObj);
        break;

    case GAME_PLAYING_FINAL_BOSS:
        move_background(mainData, allegroObj);
        move_floor(mainData, allegroObj); //FTT
        //move_coin_old(mainData, allegroObj);

        role_jump(allegroObj);
        //meteor_drop(allegroObj);
        break;
    }
}

void Gravity(AllegroObjStut *allegroObj) //­«¤O
{
    //const float gravity =GRAVITY;
    allegroObj->role.start_y += GRAVITY;
}


void end_xy_update_role(RoleStut *role)
//­pºâ¥D¨¤¦âÃä¬É
{
    role->end_x = role->start_x + SIZE_IMG_ROLE_WIDTH;
    role->end_y = role->start_y + SIZE_IMG_ROLE_HEIGHT;
}


void end_xy_update_object(ObjectStut *obj, int size_w, int size_h)
//­pºâª«¥óÃä¬É(·s)
{
    obj->end_x = obj->start_x + size_w;
    obj->end_y = obj->start_y + size_h;
}

void start_end_change(float *start,float *end)
{
    float temp;
    //½T»{start»Pend¤j¤p
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

