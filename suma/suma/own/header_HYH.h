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
void ObscaleXY(MainDataStut *mainData,ObjectStut *obscale );
void move_obscale(MainDataStut *mainData, AllegroObjStut *allegroObj);
void end_xy_update_Obscale(ObscaleStut *obscale);
void DrawObscale(MainDataStut *mainData, AllegroObjStut *allegroObj);
void SetObscale(MainDataStut *mainData,AllegroObjStut *allegroObj);
bool FloorObscale(FloorStut floor);
void CrashCheck_subrole_obscale(MainDataStut *mainData, AllegroObjStut *allegroObj);
//=======================
void CreateStandbyRole(MainDataStut *mainData,StandbyRoleStut *strole);
void StandbyRoleXY(ObjectStut *strole );
void DestoryStandbyRole(StandbyRoleStut *strole);
//void CrashCheck_role_StandbyRole(MainDataStut *mainData, AllegroObjStut *allegroObj);
void StandbyRoleCheck_Boundary(StandbyRoleStut *strole);
void move_stb_role(MainDataStut *mainData, AllegroObjStut *allegroObj);
void end_xy_update_StandbyRole(StandbyRoleStut *strole);
void SetStandbyRole(MainDataStut *mainData,AllegroObjStut *allegroObj);
void DrawSTBRole(MainDataStut *mainData, AllegroObjStut *allegroObj);
void SetChoose(MainDataStut *mainData,AllegroObjStut *allegroObj);

void ReSetFullFloor(ObjectStut *full_floor);
void SetFullFloor(ObjectStut *full_floor);
void move_full_floor(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawFullFloor(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawNormalObj(MainDataStut *mainData, AllegroObjStut *allegroObj);
void full_floor_init(AllegroObjStut *allegroObj);
void CheckForCoin(AllegroObjStut *allegroObj);
#endif //_HYH_H_


