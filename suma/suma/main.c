#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "defineHeader.h"

int main(){
    MainDataStut *mainData;
    AllegroObjStut *allegroObj;

    mainData = ClocMainData();
    allegroObj = ClocAlgObj();

    /* Initialize */
    AllegroDriverInit();
    AllegroObjectInit(allegroObj);
    MainDataInit(mainData);

    /*執行主要function*/
    srand(time(0));
    while (mainData->game_state != GAME_FINISH){
        CheckEvent(mainData, allegroObj);
    }

    /* Cleanup, Free Dynamic Memory */
    free(mainData);
    free(allegroObj);
    return 0;
}
