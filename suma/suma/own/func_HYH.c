#include "../own/header_HYH.h"
#include "../defineHeader.h"

void PrintTest_HYH()
{
    printf("This is a print test by HYH.\n");
}

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
    RandObscaleXY(mainData,nowPtr); //設定參數
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
    int persent=0;
    switch(mainData->game_mode)
    {
    case MODE_EASY:
        obscale->start_x = DISPLAY_WIDTH ;
        obscale->start_y = (DISPLAY_HEIGHT-SIZE_IMG_FLOOR_HEIGHT)-SIZE_IMG_OBSCALE_HEIGHT;
        break;
    case MODE_MEDIUM:
        obscale->start_x = DISPLAY_WIDTH ;
        obscale->start_y = (DISPLAY_HEIGHT-SIZE_IMG_FLOOR_HEIGHT)-SIZE_IMG_OBSCALE_HEIGHT;
        break;
    case MODE_HARD:
        obscale->start_x = DISPLAY_WIDTH ;
        persent =rand()%5;
        persent == 0 ? obscale->start_y = obscale->start_y = 5.7*SIZE_IMG_SCOREBOARD_ICON_HEIGHT :
                                          obscale->start_y = (DISPLAY_HEIGHT-SIZE_IMG_FLOOR_HEIGHT)-SIZE_IMG_OBSCALE_HEIGHT;
        break;
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
void SetObscale(MainDataStut *mainData,AllegroObjStut *allegroObj)
{
    if(mainData->timerCount%60 == 0 )
    {
        switch (mainData->game_mode)
        {
        case MODE_EASY:
            if(rand()%2 ==1 && FloorObscale(allegroObj->floor))
            {
                CreateObscales(mainData,&(allegroObj->obscale));
            }
            break;
        case MODE_MEDIUM:
            if(rand()%4 ==1)
            {
                CreateObscales(mainData,&(allegroObj->obscale));
            }
            break;
        case MODE_HARD:
            if(rand()% 5==1)
            {
                CreateObscales(mainData,&(allegroObj->obscale));
            }
            break;
        }
    }
}
bool FloorObscale(FloorStut floor)
{
    printf("%f\t",floor.objs->start_x);
     printf("%f\n",floor.objs->end_x);
 if(floor.objs->start_x < DISPLAY_WIDTH && DISPLAY_WIDTH < floor.objs->start_x+SIZE_IMG_FLOOR_WIDTH)
 {
     if(floor.objs->start_x < DISPLAY_WIDTH + SIZE_IMG_OBSCALE_WIDTH && DISPLAY_WIDTH + SIZE_IMG_OBSCALE_WIDTH < floor.objs->start_x+SIZE_IMG_FLOOR_WIDTH)return 1;
 }
}
/** 觸碰扣分**/
