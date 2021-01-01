#ifndef _FUNCTION_DRAW_H_
#define _FUNCTION_DRAW_H_

#include "resource.h"

void DrawDisplayAndFlip(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawMenu(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawHomeButton(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawModeSelect(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawRule(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawRank(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawAbout(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawScoreboard(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawRole(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawMeteor(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawObjBoundary(float x1, float y1, float x2, float y2);

#endif //_FUNCTION_DRAW_H_
