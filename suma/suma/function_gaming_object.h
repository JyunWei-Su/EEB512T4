#ifndef _GAMING_H_
#define _GAMING_H_

#include "resource.h"

void CreateCoins(newCoinStut *coin);

void RandCoinXY(ObjectStut *coin);
void CoinDebugPrint(ObjectStut *nowPtr, ObjectStut *prePtr, ObjectStut *newPtr);

#endif //_GAMING_H_

