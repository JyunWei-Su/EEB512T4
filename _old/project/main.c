#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "defineHeader.h"


int main(){
    //int finish = 0;
    PrintTest_JWS();

    MainDataStut *mainData;
    AllegroObjStut *allegroObj;

    mainData = ClocMainData();
    allegroObj = ClocAlgObj();

    /* Initialize Allegro */
    AllegroDriverInit();

    AllegroObjectInit(allegroObj);
    InitMainData(mainData);


    /*執行主要function*/
    srand(time(0));

    while (mainData->game_state != GAME_STATE_FINISH){
        CheckEvent(mainData, allegroObj);
    }

    /* Cleanup, Free Dynamic Memory */
    free(mainData);
    free(allegroObj);
    return 0;
}
