#include "defineHeader.h"
#include "resource.h"

/**
 * ¹Bºâ¬ÛÃö¨ç¦¡
 * ¥D­n©I¥s¡G
**/

/* ¥D­n°Ñ¼Æ¹Bºâ»Pª¬ºA§P§O */
void ParameterOperate(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int state = mainData->game_state;
    al_get_keyboard_state(&allegroObj->keyboard_state);
    switch(state)
    {
    case GAME_PLAYING_NORMAL:
        /*³]©w·sª«¥ó*/
        CheckForCoin(allegroObj);
        SetChoose(mainData,allegroObj);
        SetFloor(&allegroObj->floor); //½T»{¬O§_»Ý­n·s¼W¦aªOorÄÀ©ñ¦aªO¿
        /*²¾°Êª«¥ó*/
        move_playing_normal(mainData, allegroObj);
        /* Check Crash */
        CrachCheck(mainData, allegroObj);
        DoCrashOrDestorys(mainData, allegroObj);
        /* ¹CÀ¸¶i«×§ó·s*/
        PlayingStateSwitchTo(mainData, allegroObj);
        break;
    case GAME_PLAYING_END:

        break;
    }
}

void PlayingStateSwitchTo(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    switch(mainData->game_state)
    {
    case GAME_PLAYING_NORMAL:
        if(mainData->game_percent <= GAME_PERSEND_100)
        {
            if (mainData->game_percent == GAME_PERSEND_70)
            {
                CreateMeteors(&allegroObj->meteor);

            }
            if (mainData->game_percent == GAME_PERSEND_50)
            {
                CreateMeteors(&allegroObj->meteor);


            }
            if (mainData->game_percent == GAME_PERSEND_25)
            {

                CreateAttackX(&allegroObj->attackx);

            }

            mainData->game_percent += GAME_PERSEND_APPEND;
        }
        else mainData->game_state = GAME_PLAYING_END;
        break;
    }
}
//move_attackx(mainData, allegroObj);

/* move ¦X¶° */
void move_playing_normal(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int state = mainData->game_mode;
    switch(state)
    {
    case MODE_EASY:
        move_background(mainData, allegroObj);
        move_coin(mainData, allegroObj);
        move_obscale(mainData,allegroObj);
        move_floor(mainData, allegroObj);
        //move_meteor(mainData, allegroObj);
        //move_role(mainData, allegroObj);
        move_role_xy(mainData, allegroObj);
        move_sub_role(mainData, allegroObj);
        move_stb_role(mainData,allegroObj);
        break;
    case MODE_MEDIUM:
        move_background(mainData, allegroObj);
        move_coin(mainData, allegroObj);
        move_obscale(mainData,allegroObj);
        move_floor(mainData, allegroObj);
        move_meteor(mainData, allegroObj);
        move_attackx(mainData, allegroObj);
        //move_role(mainData, allegroObj);
        move_role_xy(mainData, allegroObj);
        move_sub_role(mainData, allegroObj);
        move_stb_role(mainData,allegroObj);
        break;
    case MODE_HARD:
        move_background(mainData, allegroObj);
        move_coin(mainData, allegroObj);
        move_obscale(mainData,allegroObj);
        move_floor(mainData, allegroObj);
        //move_meteor(mainData, allegroObj);
        move_boss(allegroObj);
        //move_role(mainData, allegroObj);
        move_role_xy(mainData, allegroObj);
        move_sub_role(mainData, allegroObj);
        move_stb_role(mainData,allegroObj);
        break;
    }
    /* move_background(mainData, allegroObj);
     move_coin(mainData, allegroObj);
     move_obscale(mainData,allegroObj);
     move_floor(mainData, allegroObj);
     move_meteor(mainData, allegroObj);
     //move_role(mainData, allegroObj);
     move_role_xy(mainData, allegroObj);
     move_sub_role(mainData, allegroObj);
     move_stb_role(mainData,allegroObj);*/
}

void move_playing_ready_mid(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    move_background(mainData, allegroObj);
    move_coin(mainData, allegroObj);
    move_obscale(mainData,allegroObj);
    move_floor(mainData, allegroObj);
    move_full_floor(mainData, allegroObj);

    move_role(mainData, allegroObj);
    move_sub_role(mainData, allegroObj);
    move_stb_role(mainData,allegroObj);
}

void move_playing_mid(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    move_floor(mainData, allegroObj);
    move_meteor(mainData, allegroObj);
    //move_role(mainData, allegroObj);
}

void move_playing_ready_final(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    move_background(mainData, allegroObj);
    move_coin(mainData, allegroObj);
    move_obscale(mainData,allegroObj);
    move_floor(mainData, allegroObj);
    move_full_floor(mainData, allegroObj);

    move_role(mainData, allegroObj);
    move_sub_role(mainData, allegroObj);
    move_stb_role(mainData,allegroObj);
}

void move_playing_final(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    //move_full_floor(mainData, allegroObj);
    //move_role(mainData, allegroObj);
    move_boss(allegroObj);
}


/* ª«¥ó move */
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
    int time_during; //±q«ö¤U«ö¶s¨ì²{¦b¹L´X°»
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
        switch(role_state) //¥Hrole ªº¬°°ò·Ç½Æ»s­×§ï
        {
        case ROLE_NULL:
            OnFloorCheck_subRole(mainData, allegroObj, nowSubRole, &allegroObj->floor);//¤@©w­n¥ý
            if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_W) && time_during > OFFSET_SUB_ROLE_DELAY * nowSubRole->id)
                nowSubRole->state = ROLE_JUMP;
            else nowSubRole->start_y = role_start_y_ref;
            printf("ROLE_NULL: %f\n",nowSubRole->start_y);
            break;
        case ROLE_JUMP:
            if(!al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_W))
            {
                nowSubRole->state = ROLE_DROP;
                break;
            }
            if(time_during > OFFSET_SUB_ROLE_DELAY * nowSubRole->id)
                nowSubRole->start_y = role_start_y_ref - SPEED_ROLE_JUMP*(time_during - (OFFSET_SUB_ROLE_DELAY*nowSubRole->id));
            if(time_during > TIME_ROLE_JUMP_MAINTAIN + OFFSET_SUB_ROLE_DELAY*nowSubRole->id)
                nowSubRole->state = ROLE_MUST_DROP;
            printf("ROLE_JUMP: %f\n",nowSubRole->start_y);
            break;
        case ROLE_DROP:
            Gravity(&nowSubRole->start_y);

            if(nowSubRole->start_y >= role_start_y_ref) OnFloorCheck_subRole(mainData, allegroObj, nowSubRole, &allegroObj->floor);
            break;
        case ROLE_MUST_DROP:
            Gravity(&nowSubRole->start_y);
            if(nowSubRole->start_y >= role_start_y_ref) OnFloorCheck_subRole(mainData, allegroObj, nowSubRole, &allegroObj->floor);

            break;
        case ROLE_DROP_FLOOR:
            Gravity(&nowSubRole->start_y);
            nowSubRole->start_x -= mainData->speed.object;
            printf("ROLE_DROP_FLOOR: %f\n",nowSubRole->start_y);
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
        allegroObj->boss.start_x -=5;
        allegroObj->boss.start_y +=3;
        if(allegroObj->boss.start_y>=600) allegroObj->boss.state = BOSS_BEYOND_Y;
        if(allegroObj->boss.start_x<=0) allegroObj->boss.state = BOSS_BEYOND_X;
        break;
    case BOSS_BEYOND_X:
        allegroObj->boss.start_x +=15;
        allegroObj->boss.start_y -=1;
        if(allegroObj->boss.start_x>=1400) allegroObj->boss.state = BOSS_NULL;
        if(allegroObj->boss.start_y<=0) allegroObj->boss.state = BOSS_NULL;
        break;
    case BOSS_BEYOND_Y:
        allegroObj->boss.start_y -=3;
        allegroObj->boss.start_x -=5;
        if(allegroObj->boss.start_y<=0) allegroObj->boss.state = BOSS_NULL;
        if(allegroObj->boss.start_x<=0)  allegroObj->boss.state = BOSS_NULL;
        break;
    }
    allegroObj->boss.end_x = allegroObj->boss.start_x + SIZE_IMG_BOSS_WIDTH;
    allegroObj->boss.end_y = allegroObj->boss.start_y + SIZE_IMG_BOSS_HEIGHT;
    /*allegroObj->boss.start_x -=rand()%10+3;
    allegroObj->boss.start_y +=rand()%10+3;
    if(allegroObj->boss.start_y>=700)allegroObj->boss.start_y -=rand()%10+7;
    if(allegroObj->boss.start_x<=100)allegroObj->boss.start_x +=rand()%10+7;*/
}
void move_boss2(AllegroObjStut *allegroObj)
{
    switch(allegroObj->boss.state)
    {
    case BOSS_NULL:
        allegroObj->boss.start_x -=7;
        //allegroObj->boss.start_y +=rand()%5+3;
        //if(allegroObj->boss.start_y>=600) allegroObj->boss.state = BOSS_BEYOND_Y;
        if(allegroObj->boss.start_x<=0) allegroObj->boss.state = BOSS_BEYOND_X;
        break;
    case BOSS_BEYOND_X:
        allegroObj->boss.start_x +=7;
        //allegroObj->boss.start_y -=1;
        if(allegroObj->boss.start_x>=1400) allegroObj->boss.state = BOSS_NULL;
       // if(allegroObj->boss.start_y<=0) allegroObj->boss.state = BOSS_NULL;
        break;
    case BOSS_BEYOND_Y:
        allegroObj->boss.start_y -=5;
        allegroObj->boss.start_x -=10;
       // if(allegroObj->boss.start_y<=0) allegroObj->boss.state = BOSS_NULL;
        break;
    }
}
void move_boss3(AllegroObjStut *allegroObj)
{
    switch(allegroObj->boss.state)
    {
    case BOSS_NULL:
        allegroObj->boss.start_x -=5;
        allegroObj->boss.start_y +=3;
        if(allegroObj->boss.start_y>=600) allegroObj->boss.state = BOSS_BEYOND_Y;
        if(allegroObj->boss.start_x<=0) allegroObj->boss.state = BOSS_BEYOND_X;
        break;
    case BOSS_BEYOND_X:
        allegroObj->boss.start_x +=5;
        allegroObj->boss.start_y -=3;
        if(allegroObj->boss.start_x>=1400) allegroObj->boss.state = BOSS_NULL;
        if(allegroObj->boss.start_y<=0) allegroObj->boss.state = BOSS_NULL;
        break;
    case BOSS_BEYOND_Y:
        allegroObj->boss.start_y -=3;
        allegroObj->boss.start_x -=5;
        if(allegroObj->boss.start_y<=0) allegroObj->boss.state = BOSS_NULL;
        if(allegroObj->boss.start_x<=0) allegroObj->boss.state = BOSS_NULL;
        break;
    }
}
void move_role(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    float role_start_y_ref;
    int time_during; //±q«ö¤U«ö¶s¨ì²{¦b¹L´X°»
    int role_state;
    role_start_y_ref = DISPLAY_HEIGHT-OFFSET_FLOOR-SIZE_IMG_ROLE_HEIGHT;
    time_during = mainData->timerCount - allegroObj->role.keyDownRecord;
    role_state = allegroObj->role.state;
    switch(role_state)
    {
    case ROLE_NULL:
        OnFloorCheck_role(mainData, allegroObj);//¤@©w­n¥ý
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
        if(time_during > TIME_ROLE_JUMP_MAINTAIN) allegroObj->role.state = ROLE_MUST_DROP; //0.8¬í

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
        break;
    }
    end_xy_update_role(&allegroObj->role);
}
void move_role_xy(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    float role_start_y_ref;
    int time_during; //±q«ö¤U«ö¶s¨ì²{¦b¹L´X°»
    int role_state;
    role_start_y_ref = DISPLAY_HEIGHT-OFFSET_FLOOR-SIZE_IMG_ROLE_HEIGHT;
    time_during = mainData->timerCount - allegroObj->role.keyDownRecord;
    role_state = allegroObj->role.state;
    switch(role_state)
    {
    case ROLE_NULL:
        OnFloorCheck_role(mainData, allegroObj);//¤@©w­n¥ý
        if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_W))
        {
            allegroObj->role.keyDownRecord = mainData->timerCount;
            allegroObj->role.state = ROLE_JUMP;
        }
        if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_A))
        {
            allegroObj->role.start_x -= OFFSET_ROLE_WALK;
        }
        if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_D))
        {
            allegroObj->role.start_x += OFFSET_ROLE_WALK;
        }
        if (allegroObj->role.start_x<=0)
        {
            allegroObj->role.start_x=0;
        }
        if (allegroObj->role.start_x>=DISPLAY_WIDTH-SIZE_IMG_ROLE_WIDTH)
        {
            allegroObj->role.start_x=DISPLAY_WIDTH-SIZE_IMG_ROLE_WIDTH;
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
        if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_D))
        {
            allegroObj->role.start_x += OFFSET_ROLE_JUMP_X;
        }
        if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_A))
        {
            allegroObj->role.start_x -= OFFSET_ROLE_JUMP_X;
        }
        if (allegroObj->role.start_x<=0)
        {
            allegroObj->role.start_x=0;
        }
        if (allegroObj->role.start_x>=DISPLAY_WIDTH-SIZE_IMG_ROLE_WIDTH)
        {
            allegroObj->role.start_x=1516;
        }
        allegroObj->role.start_y = role_start_y_ref - SPEED_ROLE_JUMP*time_during;
        if(time_during > TIME_ROLE_JUMP_MAINTAIN) allegroObj->role.state = ROLE_MUST_DROP; //0.8¬í
        break;
    case ROLE_DROP:
        Gravity(&allegroObj->role.start_y);
        if(allegroObj->role.start_y >= role_start_y_ref) OnFloorCheck_role(mainData, allegroObj);
        break;
    case ROLE_MUST_DROP:
        Gravity(&allegroObj->role.start_y);
        if(allegroObj->role.start_y >= role_start_y_ref) OnFloorCheck_role(mainData, allegroObj);
        if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_D))
        {
            allegroObj->role.start_x += OFFSET_ROLE_JUMP_X;
        }
        if(al_key_down(&allegroObj->keyboard_state, ALLEGRO_KEY_A))
        {
            allegroObj->role.start_x -= OFFSET_ROLE_JUMP_X;
        }
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

void move_full_floor(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    allegroObj->full_floor.start_x -= mainData->speed.object;
    allegroObj->full_floor.end_x -= mainData->speed.object;
}

void move_floor(MainDataStut *mainData, AllegroObjStut *allegroObj)
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

void move_obscale(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    ObjectStut *nowObscale = NULL;
    nowObscale = allegroObj->obscale.objs;

    while(nowObscale != NULL)
    {
        nowObscale->start_x -= mainData->speed.object;
        end_xy_update_object(nowObscale, SIZE_IMG_OBSCALE_WIDTH, SIZE_IMG_OBSCALE_HEIGHT);
        ObscaleCheck_Boundary(&(allegroObj->obscale));
        if(nowObscale->state == OBSCALE_DESTORY) DestoryObscales(&(allegroObj->obscale));
        nowObscale = nowObscale->nextObj;
    }
}

void move_stb_role(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    ObjectStut *nowSTB = NULL;
    nowSTB = allegroObj->stbRole.objs;

    while(nowSTB != NULL)
    {
        nowSTB->start_x -= mainData->speed.object;
        end_xy_update_object(nowSTB, SIZE_IMG_ROLE_WIDTH, SIZE_IMG_ROLE_HEIGHT);
        StandbyRoleCheck_Boundary(&allegroObj->stbRole);
        //if(nowSTB->state == STB_ROLE_DESTORY) DestoryStandbyRole(&allegroObj->stbRole);
        nowSTB = nowSTB->nextObj;
    }
}


/* Crach */

void CrachCheck(MainDataStut *mainData, AllegroObjStut *allegroObj) //FTT
{

    switch(mainData->game_state)
    {
    case GAME_PLAYING_NORMAL:
        CrachCheck_role_coin(mainData, allegroObj);
        CrashCheck_role_obscale(mainData, allegroObj);
        CrachCheck_role_nothing(mainData, allegroObj);
        CrashCheck_role_StandbyRole(mainData, allegroObj);

        CrashCheck_subrole_obscale(mainData, allegroObj);
        CrachCheck_subrole_nothing(mainData, allegroObj);
        CrachCheck_subrole_coin(mainData, allegroObj);
        break;
    }

}

void CrashCheck_role_StandbyRole(MainDataStut *mainData, AllegroObjStut *allegroObj)
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
            AppendSubRole(mainData, &allegroObj->subRole, &allegroObj->role);
            DestoryStandbyRole(&allegroObj->stbRole);//©ñ¸m¦ì¸m¦³»~
        }
        nowStdRole = nowStdRole->nextObj;
    }
}

void CrashCheck_role_obscale(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    bool crash;
    ObjectStut *nowObscale = NULL;
    RoleStut *nowRole = NULL;
    nowObscale = allegroObj->obscale.objs;
    nowRole = &allegroObj->role;
    while(nowObscale != NULL)
    {
        crash = ObjCrashCheck(nowRole->start_x, nowRole->start_y, nowRole->end_x, nowRole->end_y,
                              nowObscale->start_x, nowObscale->start_y, nowObscale->end_x, nowObscale->end_y);
        if(crash)
        {
            nowObscale->state = OBSCALE_CRASH_MAIN;
            allegroObj->sound.damageBook.readyToPlay = 1;
            mainData->score.chars -= 1;
        }
        if(nowObscale->state == OBSCALE_CRASH_MAIN) DestoryObscales(&(allegroObj->obscale));
        //crash ? printf("\tCrash\n") : printf("\tNoCrash\n") ;
        nowObscale = nowObscale->nextObj;
    }
}

void CrashCheck_subrole_obscale(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    bool crash;
    ObjectStut *nowObscale = NULL;
    ObjectStut *nowSubRole = NULL;
    nowObscale = allegroObj->obscale.objs;

    while(nowObscale != NULL)
    {
        nowSubRole = allegroObj->subRole.objs;
        while(nowSubRole)
        {
            crash = ObjCrashCheck(nowSubRole->start_x, nowSubRole->start_y, nowSubRole->end_x, nowSubRole->end_y,
                                  nowObscale->start_x, nowObscale->start_y, nowObscale->end_x, nowObscale->end_y);
            if(crash)
            {
                nowObscale->state = OBSCALE_CRASH_MAIN;
                nowSubRole->state = ROLE_DESTORY;
                allegroObj->sound.damageBook.readyToPlay = 1;
            }
            if(nowObscale->state == OBSCALE_CRASH_MAIN) DestoryObscales(&(allegroObj->obscale));
            //crash ? printf("\tCrash\n") : printf("\tNoCrash\n") ;
            nowSubRole = nowSubRole->nextObj;
        }
        nowObscale = nowObscale->nextObj;
    }

}

void DoCrashOrDestorys(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    mainData->score.coins += ScoreAdd_Coins(&allegroObj->coin)*50;
    DestoryCoins(&allegroObj->coin);
    DestorySubRole(&allegroObj->subRole, &allegroObj->role);
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

void OnFloorCheck_subRole(MainDataStut *mainData, AllegroObjStut *allegroObj, ObjectStut *subRole, FloorStut *floor)
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
            allegroObj->sound.coinCrash.readyToPlay = 1; //¶Ç»¼¼½©ñ­µ®Äªº°Ñ¼Æ
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
            if(crash)
            {
                nowCoin->state = COIN_DESTORY;
                allegroObj->sound.coinCrash.readyToPlay = 1; //¶Ç»¼¼½©ñ­µ®Äªº°Ñ¼Æ
            }
            //crash ? printf("\tCrash\n") : NULL ;
            nowSubRole = nowSubRole->nextObj;
        }
        nowCoin = nowCoin->nextObj;
    }
}

void CrachCheck_subrole_nothing(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    //½T»{subrow¬O§_¦º¤`
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

void CrachCheck_role_nothing(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    //½T»{role¬O§_¦º¤`
    RoleStut *role = &allegroObj->role;
    if(role->state == ROLE_DROP_FLOOR)
    {

        if(role->end_x < 0 || role->start_y > DISPLAY_HEIGHT)
        {
            role->state = ROLE_DESTORY;
        }

    }
}

/* ­«¤O°¾²¾¡BÃä¬É§PÂ_*/

void Gravity(float *y) //­«¤O
{
    //const float gravity =GRAVITY;
    *y += GRAVITY;
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
