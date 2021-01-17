#include "../own/header_HYH.h"
#include "../defineHeader.h"

void PrintTest_HYH()
{
    printf("This is a print test by HYH.\n");
}

bool FloorObscale(FloorStut floor)
{
    if(floor.objs->start_x+SIZE_IMG_OBSCALE_WIDTH/2 < DISPLAY_WIDTH
            && DISPLAY_WIDTH < floor.objs->end_x-SIZE_IMG_OBSCALE_WIDTH/2
            && floor.objs->start_x+SIZE_IMG_OBSCALE_WIDTH/2 < DISPLAY_WIDTH + SIZE_IMG_OBSCALE_WIDTH
            && DISPLAY_WIDTH + SIZE_IMG_OBSCALE_WIDTH < floor.objs->end_x-SIZE_IMG_OBSCALE_WIDTH/2)
        return 1;
    else return 0;
}

void SetStandbyRole(MainDataStut *mainData,AllegroObjStut *allegroObj)
{
    if(rand()%2 ==0 && FloorObscale(allegroObj->floor))
    {
        CreateStandbyRole(mainData,&allegroObj->stbRole);
    }
}

void SetChoose(MainDataStut *mainData,AllegroObjStut *allegroObj)
{
    int persent=0;
    persent = rand()%2;
    if(mainData->timerCount%(int)(SIZE_IMG_OBSCALE_WIDTH/mainData->speed.object) == 0)
    {
        switch(persent)
        {
        case 0:
            SetObscale(mainData,allegroObj);
            break;
        default:
            SetStandbyRole(mainData,allegroObj);
            break;
        }
    }

}

void CheckForCoin(AllegroObjStut *allegroObj)
{
 if(allegroObj->coin.objs == NULL)
 {
  CreateCoins(&(allegroObj->coin));
 }
}
