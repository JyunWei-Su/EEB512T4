#ifndef _BYK_H_
#define _BYK_H_

#include "../resource.h"

/* 以下待整理 不需要者刪除 12.30 */
void PrintTest_BYK();

#define minpoint 800
#define maxpoint 650
#define GameStateMove 8000
#define GameStateMaxPoint 8001

typedef struct Paddle
{
    int yLeft;
    int xLeft;
    ALLEGRO_BITMAP* img;
} Paddle;

typedef struct Match
{
    Paddle paddle;
} Match;

//void JumpPaddle(Paddle* paddlePtr, ALLEGRO_KEYBOARD_STATE* KBstatePtr);
void JumpPaddle(Paddle* paddlePtr, ALLEGRO_KEYBOARD_STATE* KBstatePtr,ALLEGRO_BITMAP* img,ALLEGRO_BITMAP *bkgImg);
void Gravity0(int vely,const int gravity,Paddle* paddlePtr);
void initPaddle(Paddle* paddlePtr, ALLEGRO_BITMAP* img);

//12/28
void DropFromMaxPoint(Paddle* paddlePtr, ALLEGRO_KEYBOARD_STATE* KBstatePtr,ALLEGRO_BITMAP* img,ALLEGRO_BITMAP *bkgImg,int game_state);
void MoveItem(Paddle* paddlePtr, ALLEGRO_KEYBOARD_STATE* KBstatePtr,int game_state);
void BeyondPoint(Paddle* paddlePtr);
void JumpCheck(Paddle* paddlePtr, ALLEGRO_KEYBOARD_STATE* KBstatePtr,ALLEGRO_BITMAP* img,ALLEGRO_BITMAP *bkgImg);

#endif //_BYK_H_
