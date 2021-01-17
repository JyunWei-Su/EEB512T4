#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "defineHeader.h"

int main(){
   // HideWindow();

    MainDataStut *mainData;
    AllegroObjStut *allegroObj;

    mainData = ClocMainData();
    allegroObj = ClocAlgObj();

    /* Initialize */
    srand(time(0));
    AllegroDriverInit();
    AllegroObjectInit(allegroObj);
    MainDataInit(mainData);

    /* Main processing */
    while (mainData->game_state != GAME_FINISH){
        CheckEvent(mainData, allegroObj);
    }

    /* Cleanup, Free Dynamic Memory */
    free(mainData);
    free(allegroObj);
    return 0;
}
