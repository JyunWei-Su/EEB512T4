#include "../own/header_HYH.h"
#include "../defineHeader.h"

void PrintTest_HYH()
{
    printf("This is a print test by HYH.\n");
}

void CreateObscales(MainDataStut *mainData,ObscaleStut *obscale)
{
    int count = 0, n = 2; //產生n個物件
    ObjectStut *nowPtr = NULL, *prePtr = NULL, *newPtr = NULL;
    nowPtr = obscale->objs; //第一筆資料
    while(count < n)
    {
        if(nowPtr == NULL) //如果為空(沒有新物件)就創新的
        {
            newPtr = (ObjectStut *)calloc(1, sizeof(ObjectStut)); //配一個新的
            nowPtr = newPtr; //把new指派給now(此時now就是新物件), 和pre.next(應當要是now)
            count == 0 ? obscale->objs = newPtr : prePtr->nextObj = newPtr;
        }
        RandObscaleXY(mainData,nowPtr); //設定參數
        prePtr = nowPtr; //轉往下一物件
        nowPtr = nowPtr->nextObj;
        count += 1;
}
}

void DestoryObscales(ObscaleStut *obscale)
{
    int count = 0;//nowCoin前方有幾筆coin
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
        if(crash) nowObscale->state = OBSCALE_CRASH_MAIN;
        if(nowObscale->state == OBSCALE_CRASH_MAIN) DestoryObscales(&(allegroObj->obscale));
        //crash ? printf("\tCrash\n") : printf("\tNoCrash\n") ;
        nowObscale = nowObscale->nextObj;
    }

}
void ObscaleCheck_Boundary(ObscaleStut *obscale)
{
  float end_x = obscale->objs->end_x;
  if(end_x <= 0) obscale->objs->state = OBSCALE_DESTORY;
}

void RandObscaleXY(MainDataStut *mainData,ObjectStut *obscale )
{
   int difficulty = mainData->game_mode ;
   int persent=0;
   switch(difficulty)
   {
    case 0:
        obscale->start_x = DISPLAY_WIDTH +(rand()%5)*SIZE_IMG_OBSCALE_WIDTH;
        obscale->start_y = (DISPLAY_HEIGHT-SIZE_IMG_FLOOR_HEIGHT)-SIZE_IMG_OBSCALE_HEIGHT;
        break;
    case 1:
        obscale->start_x = DISPLAY_WIDTH +(rand()%4)*SIZE_IMG_OBSCALE_WIDTH;
        obscale->start_y = (DISPLAY_HEIGHT-SIZE_IMG_FLOOR_HEIGHT)-SIZE_IMG_OBSCALE_HEIGHT;
        break;
    case 2:
           obscale->start_x = DISPLAY_WIDTH +(rand()%3)*SIZE_IMG_OBSCALE_WIDTH;
           persent =rand()%3;
           persent==0 ? obscale->start_y = (DISPLAY_HEIGHT-SIZE_IMG_FLOOR_HEIGHT)-SIZE_IMG_OBSCALE_HEIGHT :
                        obscale->start_y = 5.7*SIZE_IMG_SCOREBOARD_ICON_HEIGHT;
           break;
   }
}

void move_obscale(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    ObjectStut *nowObscale = NULL;
    nowObscale = allegroObj->obscale.objs;

    while(nowObscale != NULL)
    {
        nowObscale->start_x -= 2;
        end_xy_update_object(nowObscale, SIZE_IMG_OBSCALE_WIDTH, SIZE_IMG_OBSCALE_HEIGHT);
        ObscaleCheck_Boundary(&(allegroObj->obscale));
        if(nowObscale->state == OBSCALE_DESTORY) DestoryObscales(&(allegroObj->obscale));
        nowObscale = nowObscale->nextObj;
    }
}
void end_xy_update_Obscale(ObscaleStut *obscale)
//計算障礙物邊界
{
    obscale->objs->end_x = obscale->objs->start_x + SIZE_IMG_OBSCALE_WIDTH;
    obscale->objs->end_y = obscale->objs->start_y + SIZE_IMG_OBSCALE_HEIGHT;
}

void DrawObscale(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    ObjectStut *nowObscale = NULL;
    nowObscale = allegroObj->obscale.objs;

    while(nowObscale != NULL)
    {
        switch(nowObscale->state)
        {
        case OBSCALE_NULL:
            /*if(nowCoin->imgCount % (int)(FPS*TIME_PER_IMG_COIN) == 0)
            {
                nowCoin->imgCount = 0;
                nowCoin->imgNow += 1;
                if(nowCoin->imgNow % NUM_IMG_COIN_SEQUENCE == 0) nowCoin->imgNow = 0;
            }*/
            al_draw_bitmap_region(allegroObj->obscale.imgs_shining, 0, 0, SIZE_IMG_OBSCALE_WIDTH, SIZE_IMG_OBSCALE_HEIGHT
                                  , nowObscale->start_x, nowObscale->start_y, 0);
            //DrawObjBoundary_object(nowCoin);
            //nowCoin->imgCount += 1;
            nowObscale = nowObscale->nextObj;
            break;
        }

    }
}
/** 觸碰扣分、隨機產生**/
