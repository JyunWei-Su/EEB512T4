#ifndef _FUNCTION_CHECK_H_
#define _FUNCTION_CHECK_H_

#include "resource.h"

void CheckEvent(MainDataStut *mainData, AllegroObjStut *allegroObj);
void CheckStateMenuSwitchTo(MainDataStut *mainData, AllegroObjStut *allegroObj);
void CheckKeyboardDown(MainDataStut *mainData, AllegroObjStut *allegroObj);
void CheckStateModeSwitchTo(MainDataStut *mainData, AllegroObjStut *allegroObj);
void CheckMouseClick(MainDataStut *mainData, AllegroObjStut *allegroObj);
void CheckMouseMove(MainDataStut *mainData, AllegroObjStut *allegroObj);
void CheckMouseMoveOnHomeButton(MainDataStut *mainData, AllegroObjStut *allegroObj);
void CheckMouseMoveOnMenuButton(MainDataStut *mainData, AllegroObjStut *allegroObj);
void CheckMouseMoveOnModeButton(MainDataStut *mainData, AllegroObjStut *allegroObj);
void CheckGameState(MainDataStut *mainData, AllegroObjStut *allegroObj);
void CheckWantToFinish(MainDataStut *mainData, AllegroObjStut *allegroObj);
#endif //_FUNCTION_CHECK_H_
