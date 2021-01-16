#ifndef _HYH_H_
#define _HYH_H_

#include "../resource.h"
void PrintTest_HYH();

typedef enum Crash_State {
    _NoDoCrash, _DoCrash ,_Crash
} Crash_State;

//====================
void CreateObscales(MainDataStut *mainData,ObscaleStut *obscale);
void DestoryObscales(ObscaleStut *obscale);
void ObscaleCheck_Boundary(ObscaleStut *obscale);
void CrashCheck_role_obscale(MainDataStut *mainData, AllegroObjStut *allegroObj);
void RandObscaleXY(MainDataStut *mainData,ObjectStut *obscale );
void move_obscale(MainDataStut *mainData, AllegroObjStut *allegroObj);
void end_xy_update_Obscale(ObscaleStut *obscale);
void DrawObscale(MainDataStut *mainData, AllegroObjStut *allegroObj);
void SetObscale(MainDataStut *mainData,AllegroObjStut *allegroObj);
bool FloorObscale(FloorStut floor);

#endif //_HYH_H_


