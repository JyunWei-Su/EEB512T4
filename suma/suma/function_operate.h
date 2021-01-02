#ifndef _FUNCTION_OPERATE_H_
#define _FUNCTION_OPERATE_H_

#include "resource.h"

void ParameterOperate(MainDataStut *mainData, AllegroObjStut *allegroObj);
void Gravity(AllegroObjStut *allegroObj);
void role_init(AllegroObjStut *allegroObj);
void role_jump(AllegroObjStut *allegroObj);
void meteor_init(AllegroObjStut *allegroObj);
void meteor_drop(AllegroObjStut *allegroObj);

void start_end_change(float *start, float *end);
bool ObjCrashCheck(float start_x1, float start_y1, float end_x1, float end_y1, float start_x2, float start_y2, float end_x2, float end_y2);
bool ObjCrashCheck_sub(float start_x1, float start_y1, float end_x1, float end_y1, float start_x2, float start_y2, float end_x2, float end_y2);

void end_xy_update_meteor(MeteorStut *meteor);
void end_xy_update_role(RoleStut *role);
void end_xy_update_coin(CoinStut *coin);
void end_xy_update_floor(FloorStut *floor);
void end_xy_update_object(ObjectStut *obj, int size_w, int size_h);


void move_background(MainDataStut *mainData, AllegroObjStut *allegroObj);
void move_coin(MainDataStut *mainData, AllegroObjStut *allegroObj);
void move_floor(MainDataStut *mainData, AllegroObjStut *allegroObj);
void move_coin_new(MainDataStut *mainData, AllegroObjStut *allegroObj);

#endif //_FUNCTION_OPERATE_H_
