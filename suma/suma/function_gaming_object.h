#ifndef _GAMING_H_
#define _GAMING_H_

#include "resource.h"

void CreateCoins(CoinStut *coin);
void CreateMeteors(newMeteorStut *meteor);
void CreateRoles(newRoleStut *role);

void DestoryCoins(CoinStut *coin);
//void DestoryRoles(newRoleStut *role);
void DestoryRoles(newRoleStut *role,AllegroObjStut *allegroObj);

int ScoreAdd_Coins(CoinStut *coin);

void RandCoinXY(ObjectStut *coin);
void RandMeteorXY(ObjectStut *meteor);
void RandRoleXY(ObjectStut *role,int n);
void FirstRoleXY(ObjectStut *role);
void CrashRoleXY(ObjectStut *role,AllegroObjStut *allegroObj,int n);

void CoinDebugPrint(ObjectStut *nowPtr, ObjectStut *prePtr, ObjectStut *newPtr);


void SetFloor(FloorStut *floor);
void CreateFloorOnce(FloorStut *floor);
void RandFloorXY(ObjectStut *floor, int pre_x);
void DestoryFloorOnce(FloorStut *floor);


#endif //_GAMING_H_

