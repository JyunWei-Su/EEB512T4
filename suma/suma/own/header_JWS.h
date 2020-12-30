#ifndef _JWS_H_
#define _JWS_H_

#include "../resource.h"
void PrintTest_JWS();

void CheckEvent(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm);
void CheckGameState(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm);

void ParameterOperate(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm);
void CheckMouseMove(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm);
void CheckMouseClick(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm);
void CheckMouseMoveOnHomeButton(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm);
void CheckMouseMoveOnModeButton(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm);
void CheckMouseMoveOnMenuButton(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm);

void CheckStateModeSwitchTo(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm);
void CheckStateMenuSwitchTo(MainDataStut *mainData, AllegroObjStut *allegroObj, LayoutParmStut *layoutParm);
#endif //_JWS_H_
