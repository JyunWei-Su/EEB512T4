#ifndef _GAMING_H_
#define _GAMING_H_

#include "resource.h"

/* Coins */
void CreateCoins(CoinStut *coin);
int ScoreAdd_Coins(CoinStut *coin);
void DestoryCoins(CoinStut *coin);
void RandCoinXY(ObjectStut *coin);
void CoinDebugPrint(ObjectStut *nowPtr, ObjectStut *prePtr, ObjectStut *newPtr);

/* Roles */
void AppendSubRole(SubRoleStut *subRole, RoleStut *role);
void SubRoleXY(ObjectStut *subRole, RoleStut *role);
void DestorySubRloe(SubRoleStut *subRole, RoleStut *role);
void CreateRoles(SubRoleStut *role);
void DestoryRoles(SubRoleStut *role,AllegroObjStut *allegroObj);
void RandRoleXY(ObjectStut *role,int n);
void CrashRoleXY(ObjectStut *role,AllegroObjStut *allegroObj,int n);
void FirstRoleXY(ObjectStut *role);

/* Meteors */
void CreateMeteors(MeteorStut *meteor);
void RandMeteorXY(ObjectStut *meteor);

/* Floor */
void SetFloor(FloorStut *floor);
void CreateFloorOnce(FloorStut *floor);
void DestoryFloorOnce(FloorStut *floor);
void FirstFloorXY(ObjectStut *floor);
void RandFloorXY(ObjectStut *floor, int pre_x);

/* AttackX */
void CreateAttackX(AttackXStut *attackx);
void AttackxXY(ObjectStut *attackx);

#endif //_GAMING_H_

