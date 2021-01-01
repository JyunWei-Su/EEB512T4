#ifndef _FUNCTION_OPERATE_H_
#define _FUNCTION_OPERATE_H_

#include "resource.h"

void ParameterOperate(MainDataStut *mainData, AllegroObjStut *allegroObj);
void Gravity(AllegroObjStut *allegroObj);
void role_init(AllegroObjStut *allegroObj);
void role_jump(AllegroObjStut *allegroObj);
void meteor_init(AllegroObjStut *allegroObj);
void meteor_drop(AllegroObjStut *allegroObj);
void meteor_end_xy_update(MeteorStut *meteor);
void start_end_change(float *start, float *end);
bool ObjCrashCheck(float start_x1, float start_y1, float end_x1, float end_y1, float start_x2, float start_y2, float end_x2, float end_y2);
bool ObjCrashCheck_sub(float start_x1, float start_y1, float end_x1, float end_y1, float start_x2, float start_y2, float end_x2, float end_y2);

#endif //_FUNCTION_OPERATE_H_
