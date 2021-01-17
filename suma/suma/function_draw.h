#ifndef _FUNCTION_DRAW_H_
#define _FUNCTION_DRAW_H_

#include "resource.h"

/* 主要呼叫 */
void DrawDisplayAndFlip(MainDataStut *mainData, AllegroObjStut *allegroObj);

/* 選單畫面相關 */
void DrawMenu(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawModeButton(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawHomeButton(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawModeSelect(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawRank(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawRankScore(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawAbout(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawRule(MainDataStut *mainData, AllegroObjStut *allegroObj);

/* 遊戲畫面相關(背景、記分板、進度條、暫停畫面、遊戲難度) */
void DrawScoreboard(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawBackground(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawPause(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawPlayMode(MainDataStut *mainData, AllegroObjStut *allegroObj);

/* 遊戲角色相關(角色、金幣、跟班、障礙、地板、隕石) */
void DrawRole(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawSubRole(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawFloor(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawCoin(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawMeteor(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawAttackx(MainDataStut *mainData, AllegroObjStut *allegroObj);
void DrawBoss(MainDataStut *mainData, AllegroObjStut *allegroObj);
/* 物件邊界相關 */
void DrawObjBoundary(float x1, float y1, float x2, float y2);
void DrawObjBoundary_meteor(MeteorStut meteor);
void DrawObjBoundary_object(ObjectStut *obj);

#endif //_FUNCTION_DRAW_H_

