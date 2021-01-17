#include "defineHeader.h"
#include "resource.h"

/**
  * 此區為各式遊戲物件(使用linked LIst)，通常包含：
  * Create, destory, randXY, elseFuncton
**/

/* Coins */
void CreateCoins(CoinStut *coin)
{
    int count = 0, n = 9; //產生n個物件
    ObjectStut *nowPtr = NULL, *prePtr = NULL, *newPtr = NULL;
    nowPtr = coin->objs; //第一筆資料
    while(count < n)
    {
        if(nowPtr == NULL) //如果為空(沒有新物件)就創新的
        {
            newPtr = (ObjectStut *)calloc(1, sizeof(ObjectStut)); //配一個新的
            nowPtr = newPtr; //把new指派給now(此時now就是新物件), 和pre.next(應當要是now)
            count == 0 ? coin->objs = newPtr : prePtr->nextObj = newPtr;
        }
        RandCoinXY(nowPtr); //設定參數
        prePtr = nowPtr; //轉往下一物件
        nowPtr = nowPtr->nextObj;
        count += 1;
    }
}

int ScoreAdd_Coins(CoinStut *coin)
{
    int count = 0; //nowCoin前方有幾筆coin
    ObjectStut *nowCoin = NULL;
    nowCoin = coin->objs;

    while(nowCoin != NULL)
    {
        if (nowCoin->state == COIN_DESTORY) count += 1;
        nowCoin = nowCoin->nextObj;
    }
    return count;
}

void DestoryCoins(CoinStut *coin)
{
    int count = 0;//nowCoin前方有幾筆coin
    ObjectStut *nowCoin = NULL, *preCoin = NULL;
    nowCoin = coin->objs;

    while(nowCoin != NULL)
    {
        if (nowCoin->state == COIN_DESTORY)
        {
            count == 0 ? coin->objs = nowCoin->nextObj : preCoin->nextObj = nowCoin->nextObj;
            free(nowCoin);
        }
        else
        {
            preCoin = nowCoin;
            count += 1;
        }
        nowCoin = nowCoin->nextObj;
    }
}

void RandCoinXY(ObjectStut *coin)
{
    coin->start_x = (rand() % (DISPLAY_WIDTH/SIZE_IMG_COIN_WIDTH)) * SIZE_IMG_COIN_WIDTH + DISPLAY_WIDTH;
    coin->start_y = 500;
}

void CoinDebugPrint(ObjectStut *nowPtr, ObjectStut *prePtr, ObjectStut *newPtr)
{
    /*
    printf("--now : %x\n", nowPtr);
    printf("--pre : %x\n", prePtr);
    printf("--new : %x\n", newPtr);*/
}

/* Roles */
void AppendSubRole(MainDataStut *mainData, SubRoleStut *subRole, RoleStut *role)
{
    ObjectStut *nowPtr = NULL, *prePtr = NULL, *newPtr = NULL;
    nowPtr = subRole->objs; //第一筆資料
    while(nowPtr != NULL)//找到目前的最後一個
    {
        prePtr = nowPtr;
        nowPtr = nowPtr->nextObj;
    }
    newPtr = (ObjectStut *)calloc(1, sizeof(ObjectStut)); //配一個新的
    nowPtr = newPtr; //把new指派給now(此時now就是新物件)
    nowPtr->state = NULL;
    prePtr == NULL ? nowPtr->id = 1 : nowPtr->id = prePtr->id+1;
    nowPtr->id == 1 ? subRole->objs = nowPtr : prePtr->nextObj = nowPtr;
    SubRoleXY(nowPtr, role);
    mainData->score.chars += 1;
    //printf("NEW:%d\n", nowPtr->id);
}

void SubRoleXY(ObjectStut *subRole, RoleStut *role)
{
    subRole->start_x = role->start_x - SIZE_IMG_ROLE_WIDTH * subRole->id;
    subRole->start_y = role->start_y;
}

void DestorySubRole(SubRoleStut *subRole, RoleStut *role)
{
    int count = 0;//nowSubRle前方有幾筆
    ObjectStut *nowSubRole = NULL, *preSubRole = NULL;
    nowSubRole = subRole->objs;

    while(nowSubRole != NULL)
    {
        if (nowSubRole->state == ROLE_DESTORY)
        {
            count == 0 ? subRole->objs = nowSubRole->nextObj : preSubRole->nextObj = nowSubRole->nextObj;
            free(nowSubRole);
            printf("free\n");
        }
        else
        {
            preSubRole = nowSubRole;
            count += 1;
            preSubRole->id = count;
            //SubRoleXY(preSubRole, role);
        }
        nowSubRole = nowSubRole->nextObj;
    }
}

void FreeSubRole(SubRoleStut *sub_role)
{
    ObjectStut *nowPtr = NULL, *prePtr = NULL;
    nowPtr = sub_role->objs; //第一筆資料
    while(nowPtr != NULL)
    {
        prePtr = nowPtr;
        nowPtr = nowPtr->nextObj;
        free(prePtr);
    }
    sub_role->objs = NULL;
}

/*
void CreateRoles(SubRoleStut *role)
{
    int count = 0, n = 5; //產生n個物件
    ObjectStut *nowPtr = NULL, *prePtr = NULL, *newPtr = NULL;
    nowPtr = role->objs; //第一筆資料
    while(count < n) //舊資料可能要destroy
    {
        if(nowPtr == NULL) //如果為空(沒有新物件)就創新的
        {
            newPtr = (ObjectStut *)calloc(1, sizeof(ObjectStut)); //配一個新的
            nowPtr = newPtr; //把new指派給now(此時now就是新物件), 和pre.next(應當要是now)
            count == 0 ? role->objs = newPtr : prePtr->nextObj = newPtr;
        }
        if(count == 0)
        {
            FirstRoleXY(nowPtr);
        }
        else
        {
            RandRoleXY(nowPtr,count+1);    //設定參數
        }
        prePtr = nowPtr; //轉往下一物件
        nowPtr = nowPtr->nextObj;
        count += 1;
    }
}*/

//修正
void DestoryRoles(SubRoleStut *role, AllegroObjStut *allegroObj)
{

    int count = 0, n=1;
    ObjectStut *nowRole = NULL, *preRole = NULL;
    nowRole = role->objs;

    while(nowRole != NULL)
    {

        nowRole = nowRole->nextObj;
        n+=1;
    }
}

void RandRoleXY(ObjectStut *role,int n)
{
    role->start_x = 200*n;
    role->start_y = 300;
}

/*
void CrashRoleXY(ObjectStut *role,AllegroObjStut *allegroObj,int n)
{
    role->start_x = allegroObj->role.start_x-150*n;
    role->start_y = allegroObj->role.start_y;
    if(allegroObj->role.state == ROLE_JUMP)
    {
        role->start_y = allegroObj->role.start_y+15*n;
    }
    if(allegroObj->role.state == ROLE_MUST_DROP)
    {
        role->start_y = allegroObj->role.start_y-15*n;
    }
}*/
/*
void FirstRoleXY(ObjectStut *role)
{
    role->start_x = 1300;
    role->start_y = 600;
}
*/

/* Meteors */
void CreateMeteors(MeteorStut *meteor)
{
    int count = 0, n = rand()%10+10; //產生n個物件
    ObjectStut *nowPtr = NULL, *prePtr = NULL, *newPtr = NULL;
    nowPtr = meteor->objs; //第一筆資料
    while(count < n) //舊資料可能要destroy
    {
        if(nowPtr == NULL) //如果為空(沒有新物件)就創新的
        {
            newPtr = (ObjectStut *)calloc(1, sizeof(ObjectStut)); //配一個新的
            nowPtr = newPtr; //把new指派給now(此時now就是新物件), 和pre.next(應當要是now)
            count == 0 ? meteor->objs = newPtr : prePtr->nextObj = newPtr;
        }
        RandMeteorXY(nowPtr); //設定參數
        prePtr = nowPtr; //轉往下一物件
        nowPtr = nowPtr->nextObj;
        count += 1;
    }
}

void RandMeteorXY(ObjectStut *meteor)
{
    meteor->start_x = rand() % 2000;
    meteor->start_y = -rand() % 1000;
    meteor->speed_x = (float)(rand()%500-200)/100;
    meteor->speed_y = (float)(rand()%500+500)/100;
}

/*Attackx*/
void CreateAttackX(AttackXStut *attackx)
{
    int count = 0, n = 5; //產生n個物件
    ObjectStut *nowPtr = NULL, *prePtr = NULL, *newPtr = NULL;
    nowPtr = attackx->objs; //第一筆資料
    while(count < n) //舊資料可能要destroy
    {
        if(nowPtr == NULL) //如果為空(沒有新物件)就創新的
        {
            newPtr = (ObjectStut *)calloc(1, sizeof(ObjectStut)); //配一個新的
            nowPtr = newPtr; //把new指派給now(此時now就是新物件), 和pre.next(應當要是now)
            count == 0 ? attackx->objs = newPtr : prePtr->nextObj = newPtr;
        }
        AttackxXY(nowPtr); //設定參數
        prePtr = nowPtr; //轉往下一物件
        nowPtr = nowPtr->nextObj;
        count += 1;
    }
}
void AttackxXY(ObjectStut *attackx)
{
    attackx->id =  rand()%5+1;
    attackx->start_x =  2000;
    attackx->start_y = rand()%300;
    attackx->speed_x = (float)(rand()%300+200)/100;
    attackx->speed_y = (float)(rand()%500+500)/100;
}


/* Floor */

void ReSetFullFloor(ObjectStut *full_floor)
{
    full_floor->start_x = DISPLAY_WIDTH;
    full_floor->end_x = DISPLAY_WIDTH*2;
}

void SetFullFloor(ObjectStut *full_floor)
{
    full_floor->start_x = 0;
    full_floor->end_x = DISPLAY_WIDTH;
}

void SetFloor(FloorStut *floor)
{
    if(floor->objs == NULL) CreateFloorOnce(floor);
    else while(floor->objs->end_x < DISPLAY_WIDTH)CreateFloorOnce(floor);
}

void CreateFloorOnce(FloorStut *floor) //floor的新增邏輯與其他物件不同，是向前新增
{
    int pre_x = 0;
    ObjectStut *nowPtr = NULL, *prePtr = NULL, *newPtr = NULL;
    nowPtr = floor->objs; //第一筆資料
    if(nowPtr == NULL) //如果為空(沒有新物件)就創新的
    {
        newPtr = (ObjectStut *)calloc(1, sizeof(ObjectStut)); //配一個新的
        floor->objs = newPtr;
        nowPtr = newPtr;
        FirstFloorXY(nowPtr);
    }
    else//不為空(已有地板運作中)，在現有地板前面新增新地板(但實際會顯示在後面)
    {
        newPtr = (ObjectStut *)calloc(1, sizeof(ObjectStut)); //配一個新的
        newPtr->nextObj = nowPtr;
        floor->objs = newPtr;
        nowPtr = newPtr; //把new指派給now(此時now就是新物件:floor->objs)
        if(nowPtr->nextObj != NULL) pre_x = nowPtr->nextObj->end_x; //下一個物件就是前一個地板
        RandFloorXY(nowPtr, pre_x); //設定參數
    }

    nowPtr->state = FLOOR_ACTIVE;
}

void DestoryFloorOnce(FloorStut *floor) //floor的新增邏輯與其他物件不同，是向前新增
{
    ObjectStut *nowPtr = NULL, *prePtr = NULL;
    nowPtr = floor->objs; //第一筆資料
    while(nowPtr != NULL)
    {
        if(nowPtr->nextObj == NULL && nowPtr->state == FLOOR_STANDBY)
        {
            free(nowPtr);
            nowPtr == floor->objs ? floor->objs = NULL : prePtr->nextObj = NULL;
        }
        prePtr = nowPtr;
        nowPtr = nowPtr->nextObj;
    }
}

void FreeAllFloor(FloorStut *floor)
{
    ObjectStut *nowPtr = NULL, *prePtr = NULL;
    nowPtr = floor->objs; //第一筆資料
    while(nowPtr != NULL)
    {
        prePtr = nowPtr;
        nowPtr = nowPtr->nextObj;
        free(prePtr);
    }
    floor->objs = NULL;
}

void FirstFloorXY(ObjectStut *floor)
{
    floor->start_x = 0;
    floor->end_x = floor->start_x + (float)((rand()%51+160)*10);
    floor->start_y = DISPLAY_HEIGHT - SIZE_IMG_FLOOR_HEIGHT;
    floor->end_y = DISPLAY_HEIGHT;
}

void RandFloorXY(ObjectStut *floor, int pre_x)
{
    floor->start_x = pre_x + (float)((rand()%16+10)*10);
    floor->end_x = floor->start_x + (float)((rand()%21+70)*10);
    floor->start_y = DISPLAY_HEIGHT - SIZE_IMG_FLOOR_HEIGHT;
    floor->end_y = DISPLAY_HEIGHT;
}

/* Standby Role */
void CreateStandbyRole(MainDataStut *mainData,StandbyRoleStut *strole)
{
    ObjectStut *nowPtr = NULL, *newPtr = NULL;
    nowPtr = strole->objs; //第一筆資料
    if(nowPtr == NULL) //如果為空(沒有新物件)就創新的
    {
        newPtr = (ObjectStut *)calloc(1, sizeof(ObjectStut)); //配一個新的
        nowPtr = newPtr; //把new指派給now(此時now就是新物件), 和pre.next(應當要是now)
        strole->objs = newPtr;
    }
    else
    {
        while(nowPtr->nextObj != NULL) nowPtr = nowPtr->nextObj;
        newPtr = (ObjectStut *)calloc(1, sizeof(ObjectStut)); //配一個新的
        nowPtr->nextObj = newPtr;
        nowPtr = nowPtr->nextObj;
    }
    StandbyRoleXY(nowPtr); //設定參數
}

void StandbyRoleXY(ObjectStut *strole )
{
    strole->start_x = DISPLAY_WIDTH ;
    strole->start_y = (DISPLAY_HEIGHT-OFFSET_FLOOR)-SIZE_IMG_ROLE_HEIGHT;
}

void DestoryStandbyRole(StandbyRoleStut *stbRole)
{
    int count = 0;
    ObjectStut *nowSTB = NULL, *preSTB = NULL;
    nowSTB = stbRole->objs;

    while(nowSTB != NULL)
    {
        if (nowSTB->state == STB_ROLE_DESTORY || nowSTB->state == STB_ROLE_CRASH)
        {
            count == 0 ? stbRole->objs = nowSTB->nextObj : preSTB->nextObj = nowSTB->nextObj;
            free(nowSTB);
        }
        else
        {
            preSTB = nowSTB;
            count += 1;
        }
        nowSTB = nowSTB->nextObj;
    }
}

void StandbyRoleCheck_Boundary(StandbyRoleStut *strole)
{
    float end_x = strole->objs->end_x;
    if(end_x <= 0) strole->objs->state = STB_ROLE_DESTORY;
}

/* Obscals */
void CreateObscales(MainDataStut *mainData,ObscaleStut *obscale)
{
    ObjectStut *nowPtr = NULL, *newPtr = NULL;
    nowPtr = obscale->objs; //第一筆資料
    if(nowPtr == NULL) //如果為空(沒有新物件)就創新的
    {
        newPtr = (ObjectStut *)calloc(1, sizeof(ObjectStut)); //配一個新的
        nowPtr = newPtr; //把new指派給now(此時now就是新物件), 和pre.next(應當要是now)
        obscale->objs = newPtr;
    }
    else
    {
        while(nowPtr->nextObj != NULL) nowPtr = nowPtr->nextObj;
        newPtr = (ObjectStut *)calloc(1, sizeof(ObjectStut)); //配一個新的
        nowPtr->nextObj = newPtr;
        nowPtr = nowPtr->nextObj;
    }
    ObscaleXY(mainData,nowPtr); //設定參數
}

void DestoryObscales(ObscaleStut *obscale)
{
    int count = 0;
    ObjectStut *nowObscale = NULL, *preObscale = NULL;
    nowObscale = obscale->objs;

    while(nowObscale != NULL)
    {
        if (nowObscale->state == OBSCALE_DESTORY || nowObscale->state == OBSCALE_CRASH_MAIN
                || nowObscale->state == OBSCALE_CRASH_FOLLOWER)
        {
            count == 0 ? obscale->objs = nowObscale->nextObj : preObscale->nextObj = nowObscale->nextObj;
            free(nowObscale);
        }
        else
        {
            preObscale = nowObscale;
            count += 1;
        }
        nowObscale = nowObscale->nextObj;
    }
}

void ObscaleXY(MainDataStut *mainData,ObjectStut *obscale )
{
    int persent=0;
    switch(mainData->game_mode)
    {
    case MODE_EASY:
        obscale->start_x = DISPLAY_WIDTH ;
        obscale->start_y = (DISPLAY_HEIGHT-OFFSET_FLOOR)-SIZE_IMG_OBSCALE_HEIGHT;
        break;
    case MODE_MEDIUM:
        obscale->start_x = DISPLAY_WIDTH ;
        obscale->start_y = (DISPLAY_HEIGHT-OFFSET_FLOOR)-SIZE_IMG_OBSCALE_HEIGHT;
        break;
    case MODE_HARD:
        /*obscale->start_x = DISPLAY_WIDTH ;
        persent =rand()%5;
        persent == 0 ? obscale->start_y = obscale->start_y = 5.7*SIZE_IMG_SCOREBOARD_ICON_HEIGHT :
                                          obscale->start_y = (DISPLAY_HEIGHT-SIZE_IMG_FLOOR_HEIGHT)-SIZE_IMG_OBSCALE_HEIGHT;*/
                obscale->start_x = DISPLAY_WIDTH ;
     obscale->start_y = (DISPLAY_HEIGHT-OFFSET_FLOOR)-SIZE_IMG_OBSCALE_HEIGHT;
        break;
    }
}

void SetObscale(MainDataStut *mainData,AllegroObjStut *allegroObj)
{
    switch (mainData->game_mode)
    {
    case MODE_EASY:
        if(rand()%3 == 0 && FloorObscale(allegroObj->floor))
        {
            CreateObscales(mainData,&(allegroObj->obscale));
        }
        break;
    case MODE_MEDIUM:
        if(rand()%2 == 0 && FloorObscale(allegroObj->floor))
        {
            CreateObscales(mainData,&(allegroObj->obscale));
        }
        break;
    case MODE_HARD:
        /*if(FloorObscale(allegroObj->floor))
        {
            CreateObscales(mainData,&(allegroObj->obscale));
        }*/
        break;
    }
}

void ObscaleCheck_Boundary(ObscaleStut *obscale)
{
    float end_x = obscale->objs->end_x;
    if(end_x <= 0) obscale->objs->state = OBSCALE_DESTORY;
}

