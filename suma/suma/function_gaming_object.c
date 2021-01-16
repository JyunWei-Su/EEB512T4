#include "defineHeader.h"
#include "resource.h"

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
void DestoryRoles(newRoleStut *role,AllegroObjStut *allegroObj)
{
    int count = 0,n=1;//nowCoin前方有幾筆coin
    ObjectStut *nowRole = NULL, *preRole = NULL;
    nowRole = role->objs;

    while(nowRole != NULL)
    {
        if (nowRole->state == SUPROLE_CRASH)
        {

            CrashRoleXY(nowRole,allegroObj,n);
            printf("n=%d\n",n);

//nowRole->state = SUBROLE_MOVE;
            // count == 0 ? role->objs = nowRole->nextObj : preRole->nextObj = nowRole->nextObj;
            // free(nowRole);
        }
        else
        {
            preRole = nowRole;
            count += 1;
        }
        nowRole = nowRole->nextObj;
        n+=1;
    }
}
void CreateMeteors(newMeteorStut *meteor)
{
    int count = 0, n = rand()%30+15; //產生n個物件
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
void CreateRoles(newRoleStut *role)
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
}
void RandMeteorXY(ObjectStut *meteor)
{
    meteor->start_x = rand() % 2000;
    meteor->start_y = -rand() % 1000;
    meteor->speed_x = (float)(rand()%300+200)/100;
    meteor->speed_y = (float)(rand()%500+500)/100;
}
void RandRoleXY(ObjectStut *role,int n)
{
    role->start_x = 200*n;
    role->start_y = 300;
}
void CrashRoleXY(ObjectStut *role,AllegroObjStut *allegroObj,int n)
{
    role->start_x = allegroObj->role.start_x-150*n;
    role->start_y = allegroObj->role.start_y;
    if(allegroObj->role.state == ROLE_JUMP){role->start_y = allegroObj->role.start_y+15*n;}
    if(allegroObj->role.state == ROLE_MUST_DROP) {role->start_y = allegroObj->role.start_y-15*n;}
}
void FirstRoleXY(ObjectStut *role)
{
    role->start_x = 1300;
    role->start_y = 600;
}
void RandCoinXY(ObjectStut *coin)
{
    coin->start_x = (rand() % (DISPLAY_WIDTH/SIZE_IMG_COIN_WIDTH)) * SIZE_IMG_COIN_WIDTH + DISPLAY_WIDTH;
    coin->start_y = 500;
}

void CoinDebugPrint(ObjectStut *nowPtr, ObjectStut *prePtr, ObjectStut *newPtr)
{
    printf("--now : %x\n", nowPtr);
    printf("--pre : %x\n", prePtr);
    printf("--new : %x\n", newPtr);
}
