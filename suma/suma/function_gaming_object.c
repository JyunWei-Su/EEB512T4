#include "defineHeader.h"
#include "resource.h"

/**
  * ���Ϭ��U���C������(�ϥ�linked LIst)�A�q�`�]�t�G
  * Create, destory, randXY, elseFuncton
**/

/* Coins */
void CreateCoins(CoinStut *coin)
{
    int count = 0, n = 9; //����n�Ӫ���
    ObjectStut *nowPtr = NULL, *prePtr = NULL, *newPtr = NULL;
    nowPtr = coin->objs; //�Ĥ@�����
    while(count < n)
    {
        if(nowPtr == NULL) //�p�G����(�S���s����)�N�зs��
        {
            newPtr = (ObjectStut *)calloc(1, sizeof(ObjectStut)); //�t�@�ӷs��
            nowPtr = newPtr; //��new������now(����now�N�O�s����), �Mpre.next(����n�Onow)
            count == 0 ? coin->objs = newPtr : prePtr->nextObj = newPtr;
        }
        RandCoinXY(nowPtr); //�]�w�Ѽ�
        prePtr = nowPtr; //�੹�U�@����
        nowPtr = nowPtr->nextObj;
        count += 1;
    }
}

int ScoreAdd_Coins(CoinStut *coin)
{
    int count = 0; //nowCoin�e�観�X��coin
    ObjectStut *nowCoin = NULL;
    nowCoin = coin->objs;

    while(nowCoin != NULL)
    {
        if (nowCoin->state == COIN_DESTORY) count += 1;
        nowCoin = nowCoin->nextObj;
    }
    return count;
}

void DestoryCoins(CoinStut *coin)
{
    int count = 0;//nowCoin�e�観�X��coin
    ObjectStut *nowCoin = NULL, *preCoin = NULL;
    nowCoin = coin->objs;

    while(nowCoin != NULL)
    {
        if (nowCoin->state == COIN_DESTORY)
        {
            count == 0 ? coin->objs = nowCoin->nextObj : preCoin->nextObj = nowCoin->nextObj;
            free(nowCoin);
        }
        else
        {
            preCoin = nowCoin;
            count += 1;
        }
        nowCoin = nowCoin->nextObj;
    }
}

void RandCoinXY(ObjectStut *coin)
{
    coin->start_x = (rand() % (DISPLAY_WIDTH/SIZE_IMG_COIN_WIDTH)) * SIZE_IMG_COIN_WIDTH + DISPLAY_WIDTH;
    coin->start_y = 500;
}

void CoinDebugPrint(ObjectStut *nowPtr, ObjectStut *prePtr, ObjectStut *newPtr)
{
    printf("--now : %x\n", nowPtr);
    printf("--pre : %x\n", prePtr);
    printf("--new : %x\n", newPtr);
}


/* Roles */
void CreateRoles(SubRoleStut *role)
{
    int count = 0, n = 5; //����n�Ӫ���
    ObjectStut *nowPtr = NULL, *prePtr = NULL, *newPtr = NULL;
    nowPtr = role->objs; //�Ĥ@�����
    while(count < n) //�¸�ƥi��ndestroy
    {
        if(nowPtr == NULL) //�p�G����(�S���s����)�N�зs��
        {
            newPtr = (ObjectStut *)calloc(1, sizeof(ObjectStut)); //�t�@�ӷs��
            nowPtr = newPtr; //��new������now(����now�N�O�s����), �Mpre.next(����n�Onow)
            count == 0 ? role->objs = newPtr : prePtr->nextObj = newPtr;
        }
        if(count == 0)
        {
            FirstRoleXY(nowPtr);
        }
        else
        {
            RandRoleXY(nowPtr,count+1);    //�]�w�Ѽ�
        }
        prePtr = nowPtr; //�੹�U�@����
        nowPtr = nowPtr->nextObj;
        count += 1;
    }
}

void DestoryRoles(SubRoleStut *role, AllegroObjStut *allegroObj)
{

    int count = 0,n=1;//nowCoin�e�観�X��coin
    ObjectStut *nowRole = NULL, *preRole = NULL;
    nowRole = role->objs;

    while(nowRole != NULL)
    {
        if (nowRole->state == SUPROLE_CRASH)
        {
            CrashRoleXY(nowRole,allegroObj,n);
            //printf("n=%d\n",n);
            //nowRole->state = SUBROLE_MOVE;
            // count == 0 ? role->objs = nowRole->nextObj : preRole->nextObj = nowRole->nextObj;
            // free(nowRole);
        }
        else
        {
            preRole = nowRole;
            count += 1;
        }
        nowRole = nowRole->nextObj;
        n+=1;
    }
}

void RandRoleXY(ObjectStut *role,int n)
{
    role->start_x = 200*n;
    role->start_y = 300;
}

void CrashRoleXY(ObjectStut *role,AllegroObjStut *allegroObj,int n)
{
    role->start_x = allegroObj->role.start_x-150*n;
    role->start_y = allegroObj->role.start_y;
    if(allegroObj->role.state == ROLE_JUMP)
    {
        role->start_y = allegroObj->role.start_y+15*n;
    }
    if(allegroObj->role.state == ROLE_MUST_DROP)
    {
        role->start_y = allegroObj->role.start_y-15*n;
    }
}

void FirstRoleXY(ObjectStut *role)
{
    role->start_x = 1300;
    role->start_y = 600;
}


/* Meteors */
void CreateMeteors(MeteorStut *meteor)
{
    int count = 0, n = rand()%10+10; //����n�Ӫ���
    ObjectStut *nowPtr = NULL, *prePtr = NULL, *newPtr = NULL;
    nowPtr = meteor->objs; //�Ĥ@�����
    while(count < n) //�¸�ƥi��ndestroy
    {
        if(nowPtr == NULL) //�p�G����(�S���s����)�N�зs��
        {
            newPtr = (ObjectStut *)calloc(1, sizeof(ObjectStut)); //�t�@�ӷs��
            nowPtr = newPtr; //��new������now(����now�N�O�s����), �Mpre.next(����n�Onow)
            count == 0 ? meteor->objs = newPtr : prePtr->nextObj = newPtr;
        }
        RandMeteorXY(nowPtr); //�]�w�Ѽ�
        prePtr = nowPtr; //�੹�U�@����
        nowPtr = nowPtr->nextObj;
        count += 1;
    }
}

void RandMeteorXY(ObjectStut *meteor)
{
    meteor->start_x = rand() % 2000;
    meteor->start_y = -rand() % 1000;
    meteor->speed_x = (float)(rand()%500-200)/100;
    meteor->speed_y = (float)(rand()%500+500)/100;
}
/*Attackx*/
void CreateAttackX(AttackXStut *attackx)
{
    int count = 0, n = 5; //����n�Ӫ���
    ObjectStut *nowPtr = NULL, *prePtr = NULL, *newPtr = NULL;
    nowPtr = attackx->objs; //�Ĥ@�����
    while(count < n) //�¸�ƥi��ndestroy
    {
        if(nowPtr == NULL) //�p�G����(�S���s����)�N�зs��
        {
            newPtr = (ObjectStut *)calloc(1, sizeof(ObjectStut)); //�t�@�ӷs��
            nowPtr = newPtr; //��new������now(����now�N�O�s����), �Mpre.next(����n�Onow)
            count == 0 ? attackx->objs = newPtr : prePtr->nextObj = newPtr;
        }
        AttackxXY(nowPtr); //�]�w�Ѽ�
        prePtr = nowPtr; //�੹�U�@����
        nowPtr = nowPtr->nextObj;
        count += 1;
    }
}
void AttackxXY(ObjectStut *attackx)
{
    attackx->start_x =  2000;
    attackx->start_y = rand()%800;
    attackx->speed_x = (float)(rand()%500+200)/100;
    attackx->speed_y = (float)(rand()%500+500)/100;
}
/* Floor */


void SetFloor(FloorStut *floor)
{
    if(floor->objs == NULL) CreateFloorOnce(floor);
    else while(floor->objs->end_x < DISPLAY_WIDTH)CreateFloorOnce(floor);
}

void CreateFloorOnce(FloorStut *floor) //floor���s�W�޿�P��L���󤣦P�A�O�V�e�s�W
{
    int pre_x = 0;
    ObjectStut *nowPtr = NULL, *prePtr = NULL, *newPtr = NULL;
    nowPtr = floor->objs; //�Ĥ@�����
    if(nowPtr == NULL) //�p�G����(�S���s����)�N�зs��
    {
        newPtr = (ObjectStut *)calloc(1, sizeof(ObjectStut)); //�t�@�ӷs��
        floor->objs = newPtr;
    }
    else//������(�w���a�O�B�@��)�A�b�{���a�O�e���s�W�s�a�O(����ڷ|��ܦb�᭱)
    {
        newPtr = (ObjectStut *)calloc(1, sizeof(ObjectStut)); //�t�@�ӷs��
        newPtr->nextObj = nowPtr;
        floor->objs = newPtr;
    }
    nowPtr = newPtr; //��new������now(����now�N�O�s����:floor->objs)
    printf("new:%x\n", nowPtr);
    if(nowPtr->nextObj != NULL) pre_x = nowPtr->nextObj->end_x; //�U�@�Ӫ���N�O�e�@�Ӧa�O
    RandFloorXY(nowPtr, pre_x); //�]�w�Ѽ�
    nowPtr->state = FLOOR_ACTIVE;
}

void DestoryFloorOnce(FloorStut *floor) //floor���s�W�޿�P��L���󤣦P�A�O�V�e�s�W
{
    ObjectStut *nowPtr = NULL, *prePtr = NULL;
    nowPtr = floor->objs; //�Ĥ@�����
    while(nowPtr != NULL)
    {
        if(nowPtr->nextObj == NULL && nowPtr->state == FLOOR_STANDBY)
        {
            printf("free:%x\n", nowPtr);
            free(nowPtr);
            nowPtr == floor->objs ? floor->objs = NULL : prePtr->nextObj = NULL;
        }
        prePtr = nowPtr;
        nowPtr = nowPtr->nextObj;
    }
}

void RandFloorXY(ObjectStut *floor, int pre_x)
{
    floor->start_x = pre_x + (float)((rand()%11+5)*10);
    floor->end_x = floor->start_x + (float)((rand()%21+50)*10);
    floor->start_y = DISPLAY_HEIGHT - SIZE_IMG_FLOOR_HEIGHT;
    floor->end_y = DISPLAY_HEIGHT;
}
