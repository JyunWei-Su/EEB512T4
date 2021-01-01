#ifndef _HYH_H_
#define _HYH_H_

#include "../resource.h"
void PrintTest_HYH();

typedef enum Crash_State {
    NoDoCrash, DoCrash ,Crash
} Crash_State;

//====================
void DrawCoin(MainDataStut *mainData, AllegroObjStut *allegroObj);

#endif //_HYH_H_


