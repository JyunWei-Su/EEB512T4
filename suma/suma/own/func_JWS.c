#include "../own/header_JWS.h"
#include "../defineHeader.h"

void PrintTest_JWS(){
    printf("This is a print test by JWS.\n");
}



void ParameterOperate(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm)
{
    int state = mainData->game_state;
    switch(state)
    {
    case GAME_PLAYING:
        allegroObj->background.x -= 3;
        if(allegroObj->background.x <= -SIZE_IMG_BKG_WIDTH) allegroObj->background.x += SIZE_IMG_BKG_WIDTH;
        break;
    case GAME_MENU:
        break;
    }


}


