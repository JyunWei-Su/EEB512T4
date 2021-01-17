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
    int count = 0;
    float role_start_y_ref;
    int time_during; //從按下按鈕到現在過幾偵
    int role_state;
    ObjectStut *nowSubRole = NULL;

    role_start_y_ref = DISPLAY_HEIGHT-OFFSET_FLOOR-SIZE_IMG_ROLE_HEIGHT;
    time_during = mainData->timerCount - allegroObj->role.keyDownRecord;
    nowSubRole = allegroObj->subRole.objs;

    while(nowSubRole != NULL)
    {
        if(nowSubRole->state != ROLE_DROP_FLOOR & nowSubRole->state != ROLE_DESTORY)
            nowSubRole->start_x = allegroObj->role.start_x - SIZE_IMG_ROLE_WIDTH * nowSubRole->id;
        role_state = nowSubRole->state;
        //printf("\t%d: %d\n", nowSubRole->id, nowSubRole->state);
        switch(role_state) //以role 的為基準複製修改
        {
        case ROLE_NULL:
            OnFloorCheck_subRole(nowSubRole, &allegroObj->floor);//一定要先
            if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_W) && time_during > OFFSET_SUB_ROLE_DELAY * nowSubRole->id)
                nowSubRole->state = ROLE_JUMP;
            else nowSubRole->start_y = role_start_y_ref;
            break;
        case ROLE_JUMP:
            //printf("---%d\n", count);
            if(!al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_W))
            {
                nowSubRole->state = ROLE_DROP;
                break;
            }
            if(time_during > OFFSET_SUB_ROLE_DELAY * nowSubRole->id)
                nowSubRole->start_y = role_start_y_ref - SPEED_ROLE_JUMP*(time_during - (OFFSET_SUB_ROLE_DELAY*nowSubRole->id));
            if(time_during > TIME_ROLE_JUMP_MAINTAIN + OFFSET_SUB_ROLE_DELAY*nowSubRole->id)
                nowSubRole->state = ROLE_MUST_DROP;
            break;
        case ROLE_DROP:
            Gravity(&nowSubRole->start_y);
            if(nowSubRole->start_y >= role_start_y_ref) OnFloorCheck_subRole(nowSubRole, &allegroObj->floor);
            break;
        case ROLE_MUST_DROP:
            Gravity(&nowSubRole->start_y);
            if(nowSubRole->start_y >= role_start_y_ref) OnFloorCheck_subRole(nowSubRole, &allegroObj->floor);
            break;
        case ROLE_DROP_FLOOR:
            Gravity(&nowSubRole->start_y);
            nowSubRole->start_x -= mainData->speed.object;
            break;
        default:
            break;
        }
        end_xy_update_object(nowSubRole, SIZE_IMG_ROLE_WIDTH, SIZE_IMG_ROLE_HEIGHT);
        nowSubRole = nowSubRole->nextObj;
    }
}
void move_boss(AllegroObjStut *allegroObj)
{
    int distance=0,dx=0,dy=0;
    dx = abs(allegroObj->role.start_x - allegroObj->boss.start_x ) ;
    dy = abs(allegroObj->role.start_y - allegroObj->boss.start_y ) ;
    distance = sqrt(dx*dx+dy*dy);
    switch(allegroObj->boss.state)
    {
    case BOSS_NULL:
        allegroObj->boss.start_x -=rand()%10+3;
        allegroObj->boss.start_y +=rand()%5+3;
        if(allegroObj->boss.start_y>=600) allegroObj->boss.state = BOSS_BEYOND_Y;
        if(allegroObj->boss.start_x<=0) allegroObj->boss.state = BOSS_BEYOND_X;
        break;
    case BOSS_BEYOND_X:
        allegroObj->boss.start_x +=rand()%10+7;
        allegroObj->boss.start_y -=1;
        if(allegroObj->boss.start_x>=1800) allegroObj->boss.state = BOSS_NULL;
        if(allegroObj->boss.start_y<=-400) allegroObj->boss.state = BOSS_NULL;
        break;
    case BOSS_BEYOND_Y:
        allegroObj->boss.start_y -=5;
        allegroObj->boss.start_x -=10;
        if(allegroObj->boss.start_y<=0) allegroObj->boss.state = BOSS_NULL;
        break;
    }
    /*allegroObj->boss.start_x -=rand()%10+3;
    allegroObj->boss.start_y +=rand()%10+3;
    if(allegroObj->boss.start_y>=700)allegroObj->boss.start_y -=rand()%10+7;
    if(allegroObj->boss.start_x<=100)allegroObj->boss.start_x +=rand()%10+7;*/
}

void move_role(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    float role_start_y_ref;
    int time_during; //從按下按鈕到現在過幾偵
    int role_state;
    role_start_y_ref = DISPLAY_HEIGHT-OFFSET_FLOOR-SIZE_IMG_ROLE_HEIGHT;
    time_during = mainData->timerCount - allegroObj->role.keyDownRecord;
    role_state = allegroObj->role.state;
    switch(role_state)
    {
    case ROLE_NULL:
        OnFloorCheck_role(mainData, allegroObj);//一定要先
        if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_W))
        {
            allegroObj->role.keyDownRecord = mainData->timerCount;
            allegroObj->role.state = ROLE_JUMP;
        }
        else allegroObj->role.start_y = role_start_y_ref;
        //printf("td: %d\n", time_during);
        break;
    case ROLE_JUMP:
        if(!al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_W))
        {
            allegroObj->role.state = ROLE_DROP;
            break;
        }
        allegroObj->role.start_y = role_start_y_ref - SPEED_ROLE_JUMP*time_during;
        if(time_during > TIME_ROLE_JUMP_MAINTAIN) allegroObj->role.state = ROLE_MUST_DROP; //0.8秒
        break;
    case ROLE_DROP:
        Gravity(&allegroObj->role.start_y);
        if(allegroObj->role.start_y >= role_start_y_ref) OnFloorCheck_role(mainData, allegroObj);
        break;
    case ROLE_MUST_DROP:
        Gravity(&allegroObj->role.start_y);
        if(allegroObj->role.start_y >= role_start_y_ref) OnFloorCheck_role(mainData, allegroObj);
        break;
    case ROLE_DROP_FLOOR:
        Gravity(&allegroObj->role.start_y);
        allegroObj->role.start_x -= mainData->speed.object;
        break;
    default:
        /*
        if(!al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_W))
        {
            if(allegroObj->role.state == ROLE_JUMP) allegroObj->role.state = ROLE_NULL;
        }*/
        break;
    }

    end_xy_update_role(&allegroObj->role);

}

/*
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

    //Gravity(allegroObj);

    //角色邊界運算
    end_xy_update_role(&allegroObj->role);
}*/

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

    CrashCheck_role_obscale(mainData, allegroObj);
    CrashCheck_role_standbyRole(mainData, allegroObj);
    CrachCheck_subrole_nothing(mainData, allegroObj);

    //CrachCheck_subrole_coin(mainData, allegroObj);
    //CrachCheck_role_role(mainData, allegroObj);
}

void DoCrashOrDestorys(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    mainData->score.coins += ScoreAdd_Coins(&allegroObj->coin)*50;
    DestoryCoins(&allegroObj->coin);
    DestorySubRloe(&allegroObj->subRole, &allegroObj->role);
    //DestoryRoles(&allegroObj->subRole,allegroObj);
}

void OnFloorCheck_role(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    bool onFloor = 0;
    ObjectStut *nowFloor = NULL;
    RoleStut *role = NULL;
    role = &allegroObj->role;
    nowFloor = allegroObj->floor.objs;
    while(nowFloor != NULL)
    {

        onFloor += FloorCrashCheck(role->start_x, role->start_y, role->end_x, role->end_y,
                                   nowFloor->start_x, nowFloor->start_y, nowFloor->end_x, nowFloor->end_y);
        nowFloor = nowFloor->nextObj;
    }
    if(!onFloor) role->state = ROLE_DROP_FLOOR;
    else role->state = ROLE_NULL;
}

void OnFloorCheck_subRole_old(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    bool onFloor ;
    ObjectStut *nowFloor = NULL;
    ObjectStut *nowSubRole = NULL;
    nowSubRole = allegroObj->subRole.objs;
    while(nowSubRole != NULL)
    {
        onFloor = 0;
        nowFloor = allegroObj->floor.objs;
        while(nowFloor != NULL)
        {
            onFloor += FloorCrashCheck(nowSubRole->start_x, nowSubRole->start_y, nowSubRole->end_x, nowSubRole->end_y,
                                       nowFloor->start_x, nowFloor->start_y, nowFloor->end_x, nowFloor->end_y);
            nowFloor = nowFloor->nextObj;
        }
        if(!onFloor) nowSubRole->state = ROLE_DROP_FLOOR;
        else nowSubRole->state = ROLE_NULL;
        nowSubRole = nowSubRole->nextObj;
    }
}

void OnFloorCheck_subRole(ObjectStut *subRole, FloorStut *floor)
{
    bool onFloor = 0;
    ObjectStut *nowFloor;
    nowFloor = floor->objs;
    while(nowFloor != NULL)
    {
        onFloor += FloorCrashCheck(subRole->start_x, subRole->start_y, subRole->end_x, subRole->end_y,
                                   nowFloor->start_x, nowFloor->start_y, nowFloor->end_x, nowFloor->end_y);
        nowFloor = nowFloor->nextObj;
    }
    if(!onFloor) subRole->state = ROLE_DROP_FLOOR;
    else subRole->state = ROLE_NULL;
}

void CrashCheck_role_standbyRole(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    bool crash;
    ObjectStut *nowStdRole = NULL;
    RoleStut *nowRole = NULL;
    nowStdRole = allegroObj->stbRole.objs;
    nowRole = &allegroObj->role;
    while(nowStdRole != NULL)
    {
        crash = ObjCrashCheck(nowStdRole->start_x, nowStdRole->start_y, nowStdRole->end_x, nowStdRole->end_y,
                              nowRole->start_x, nowRole->start_y, nowRole->end_x, nowRole->end_y);
        if(crash)
        {
            nowStdRole->state = STB_ROLE_DESTORY;
            AppendSubRole(&allegroObj->subRole, &allegroObj->role);
            DestoryStandByRole(&allegroObj->stbRole);//放置位置有誤
        }
        nowStdRole = nowStdRole->nextObj;
    }
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
        if(crash)
        {
            nowCoin->state = COIN_DESTORY;
            allegroObj->sound.coinCrash.readyToPlay = 1; //傳遞播放音效的參數
        }

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

    while(nowCoin != NULL)
    {
        nowSubRole = allegroObj->subRole.objs;
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

void CrachCheck_subrole_nothing(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    //確認subrow是否死亡
    ObjectStut *nowSubRole = NULL;
    nowSubRole = allegroObj->subRole.objs;

    while(nowSubRole != NULL)
    {
        if(nowSubRole->state == ROLE_DROP_FLOOR)
        {
            if(nowSubRole->end_x < 0 || nowSubRole->start_y > DISPLAY_HEIGHT)
            {
                nowSubRole->state = ROLE_DESTORY;
                //printf("ddd\n");
            }
        }
        nowSubRole = nowSubRole->nextObj;
    }
}

/*
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
}*/

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
        SetStandbyRole(mainData,allegroObj);
        move_coin(mainData, allegroObj);
        //順序異常
        move_sub_role(mainData, allegroObj);
        move_meteor(mainData, allegroObj);
        move_attackx(mainData, allegroObj);
        move_obscale(mainData,allegroObj);
        move_standbyrole(mainData,allegroObj);
        move_floor(mainData, allegroObj); //FTT
        SetFloor(&allegroObj->floor); //確認是否需要新增地板or釋放地板��
        /* 進度條 */
        if(mainData->game_percent <= GAME_PERSEND_100 )
        {
            if (mainData->game_percent == GAME_PERSEND_99)
            {
                mainData->game_state= GAME_PLAYING_FINAL_BOSS;
                mainData->game_percent += 1;
            }
            else if (mainData->game_percent == GAME_PERSEND_50)
            {
                mainData->game_percent += 1;
                mainData->game_state= GAME_PLAYING_MID_BOSS;
            }
                        mainData->game_percent += GAME_PERSEND_APPEND;
            printf("time=%d,game_percent=%d\n",mainData->timerCount,mainData->game_percent);
        }
        /* Role */
        move_boss(allegroObj);
        //role_jump(allegroObj);
        move_role(mainData, allegroObj);
        //meteor_drop(allegroObj);
        /* Check Crash */
        CrachCheck(mainData, allegroObj);
        //CrachCheckForFloor(mainData, allegroObj); //FTT
        DoCrashOrDestorys(mainData, allegroObj);
        break;
    case GAME_PLAYING_MID_BOSS:
        move_floor(mainData, allegroObj); //FTT
        move_role(mainData, allegroObj);
        move_background(mainData, allegroObj);
        //move_coin_old(mainData, allegroObj);
        printf("MIDtime=%d\n",mainData->timerCount);
        if(mainData->timerCount>=GAME_PERSEND_MID_TIME)  mainData->game_state= GAME_PLAYING_NORMAL;
        /* Role*/
        //role_jump(allegroObj);
        //meteor_drop(allegroObj);
        break;

    case GAME_PLAYING_FINAL_BOSS:
        move_floor(mainData, allegroObj); //FTT
        move_boss(allegroObj);
        move_role(mainData, allegroObj);
        move_background(mainData, allegroObj);
        printf("BOSStime=%d\n",mainData->timerCount);
        if(mainData->timerCount>=GAME_PERSEND_FINAL_TIME)  mainData->game_state= GAME_PLAYING_NORMAL;
        //move_coin_old(mainData, allegroObj);
        //role_jump(allegroObj);
        //meteor_drop(allegroObj);
        break;
    }
}


void Gravity(float *y) //重力
{
    //const float gravity =GRAVITY;
    *y += GRAVITY;
}


void end_xy_update_role(RoleStut *role)
//計算主角色邊界
{
    role->end_x = role->start_x + SIZE_IMG_ROLE_WIDTH;
    role->end_y = role->start_y + SIZE_IMG_ROLE_HEIGHT;
}


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

