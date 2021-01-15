#ifndef _GAMING_H_
#define _GAMING_H_

#include "resource.h"

void CreateCoins(CoinStut *coin);
void DestoryCoins(CoinStut *coin);
void CreateMeteors(newMeteorStut *meteor);

int ScoreAdd_Coins(CoinStut *coin);
void RandCoinXY(ObjectStut *coin);
void RandMeteorXY(ObjectStut *meteor);
void CoinDebugPrint(ObjectStut *nowPtr, ObjectStut *prePtr, ObjectStut *newPtr);

void SetFloor(FloorStut *floor);
void CreateFloorOnce(FloorStut *floor);
void RandFloorXY(ObjectStut *floor, int pre_x);
void DestoryFloorOnce(FloorStut *floor);

#endif //_GAMING_H_

