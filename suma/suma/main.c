#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "defineHeader.h"

int main(){
    /*-------------*/
    //PrintTest_JWS();
    //PrintTest_IRL();
    //PrintTest_BYK();
    /*-------------*/

    MainDataStut *mainData;
    AllegroObjStut *allegroObj;
    LayoutParmStut *layoutParm;

    mainData = ClocMainData();
    allegroObj = ClocAlgObj();
    layoutParm = ClocLayoutParm();

    /* Initialize */
    AllegroDriverInit();
    AllegroObjectInit(allegroObj);
    MainDataInit(mainData);
    LayoutParmInit(layoutParm);

    /*執行主要function*/
    srand(time(0));
    printf("aaaa\n");
    while (mainData->game_state != GAME_FINISH){
        CheckEvent(mainData, allegroObj, layoutParm);
    }

    /* Cleanup, Free Dynamic Memory */
    free(mainData);
    free(allegroObj);
    return 0;
}
