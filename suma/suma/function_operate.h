#ifndef _FUNCTION_OPERATE_H_
#define _FUNCTION_OPERATE_H_

#include "resource.h"

void ParameterOperate(MainDataStut *mainData, AllegroObjStut *allegroObj);
void Gravity(AllegroObjStut *allegroObj);
void role_init(AllegroObjStut *allegroObj);
void role_jump(AllegroObjStut *allegroObj);
void meteor_init(AllegroObjStut *allegroObj);
void meteor_drop(AllegroObjStut *allegroObj);

//CrashCheck
void start_end_change(float *start, float *end);
bool ObjCrashCheck(float start_x1, float start_y1, float end_x1, float end_y1, float start_x2, float start_y2, float end_x2, float end_y2);
bool ObjCrashCheck_sub(float start_x1, float start_y1, float end_x1, float end_y1, float start_x2, float start_y2, float end_x2, float end_y2);
bool FloorCrashCheck(float start_char_x,float start_char_y,float end_char_x,float end_char_y,float start_floor_x,float start_floor_y,float end_floor_x,float end_floor_y);
bool FloorCrashCheck_sub(float start_char_x,float start_char_y,float end_char_x,float end_char_y,float start_floor_x,float start_floor_y,float end_floor_x,float end_floor_y);

void end_xy_update_meteor(MeteorStut *meteor);
void end_xy_update_role(RoleStut *role);
void end_xy_update_coin_old(CoinStut_old *coin_old);
void end_xy_update_floor(FloorStut *floor);
void end_xy_update_object(ObjectStut *obj, int size_w, int size_h);

void DoCrash(MainDataStut *mainData, AllegroObjStut *allegroObj);

void move_background(MainDataStut *mainData, AllegroObjStut *allegroObj);
void move_coin_old(MainDataStut *mainData, AllegroObjStut *allegroObj);
void move_floor(MainDataStut *mainData, AllegroObjStut *allegroObj);
void move_role_new(MainDataStut *mainData, AllegroObjStut *allegroObj);

void move_coin(MainDataStut *mainData, AllegroObjStut *allegroObj);

void CrachCheck(MainDataStut *mainData, AllegroObjStut *allegroObj);
void CrachCheckForFloor(MainDataStut *mainData, AllegroObjStut *allegroObj);
void CrachCheck_role_coin(MainDataStut *mainData, AllegroObjStut *allegroObj);
void CrachCheck_role_role(MainDataStut *mainData, AllegroObjStut *allegroObj);
void CrachCheck_subrole_coin(MainDataStut *mainData, AllegroObjStut *allegroObj);
void move_meteor_new(MainDataStut *mainData, AllegroObjStut *allegroObj);

#endif //_FUNCTION_OPERATE_H_
