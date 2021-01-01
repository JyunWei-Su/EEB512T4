#include "../own/header_HYH.h"
#include "../defineHeader.h"

void PrintTest_BYK()
{
    printf("This is a print test by BYK.\n");
}

void DrawCoin(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
        if(allegroObj->coin.imgCount % (int)(FPS*TIME_PER_IMG_COIN) == 0)
        {
            allegroObj->coin.imgCount = 0;
            allegroObj->coin.nowImg += 1;
            if(allegroObj->coin.nowImg % NUM_IMG_COIN_SEQUENCE == 0) allegroObj->coin.nowImg = 0;
        }
        al_draw_bitmap_region(allegroObj->coin.imgs_runing, SIZE_IMG_COIN_WIDTH*allegroObj->coin.nowImg, 0, SIZE_IMG_COIN_WIDTH, SIZE_IMG_COIN_HEIGHT
                              , allegroObj->coin.start_x, allegroObj->coin.start_y, 0);
        allegroObj->coin.imgCount += 1;


    DrawObjBoundary(allegroObj->coin.start_x, allegroObj->coin.start_y, allegroObj->coin.start_x+SIZE_IMG_COIN_WIDTH, allegroObj->coin.start_y+SIZE_IMG_COIN_HEIGHT);
}

