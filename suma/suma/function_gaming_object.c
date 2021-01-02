#include "defineHeader.h"
#include "resource.h"

void CreateCoins(newCoinStut *coin)
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

void RandCoinXY(ObjectStut *coin)
{
    coin->start_x = (rand() % (DISPLAY_WIDTH/SIZE_IMG_COIN_WIDTH)) * SIZE_IMG_COIN_WIDTH;
    coin->start_y = 500;
}

void CoinDebugPrint(ObjectStut *nowPtr, ObjectStut *prePtr, ObjectStut *newPtr)
{
    printf("--now : %x\n", nowPtr);
    printf("--pre : %x\n", prePtr);
    printf("--new : %x\n", newPtr);
}
