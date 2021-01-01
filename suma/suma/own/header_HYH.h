#ifndef _HYH_H_
#define _HYH_H_

#include "../resource.h"
void PrintTest_HYH();

typedef enum Crash_State {
    NoDoCrash, DoCrash ,Crash
} Crash_State;

//====================
void Change(float *start_1,float *end_1);
bool CrashCheck(float start_x1,float start_y1,float end_x1,float end_y1,float start_x2,float start_y2,float end_x2,float end_y2);
bool DefineCrash(float start_x1,float start_y1,float end_x1,float end_y1,float start_x2,float start_y2,float end_x2,float end_y2);

#endif //_HYH_H_


