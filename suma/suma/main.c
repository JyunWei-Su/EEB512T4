#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "defineHeader.h"

int main(){
    printf("%-*.*s=\n", 10, 3, "||||||||||"); //第一個*是總長度, 第二個*是要輸出後面字串幾個
    printf("%-*.*s=\n", 10, 5, "||||||||||");
    printf("%-*.*s=\n", 10, 7, "||||||||||");
    printf("%-*.*s=\n", 10, 9, "||||||||||");
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
