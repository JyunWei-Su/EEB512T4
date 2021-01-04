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

#endif //_GAMING_H_

