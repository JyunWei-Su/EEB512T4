#include "defineHeader.h"

void initPaddle(Paddle* paddlePtr, ALLEGRO_BITMAP* img)
{
    /* give left paddle its initial y-coordinate */
    paddlePtr->yLeft = 800;
    paddlePtr->xLeft = 0;
    paddlePtr->img = img;
    /* give right paddle its initial y-coordinate */
//    paddlePtr->yRight = SCREEN_H / 2;

}

void JumpPaddle(Paddle* paddlePtr, ALLEGRO_KEYBOARD_STATE* KBstatePtr)
{
    int vely=0;
    const int Gravity=2;
    if(al_key_down(KBstatePtr, ALLEGRO_KEY_W))
    {
        paddlePtr->yLeft -= 15;
        al_rest(0.01);
    }
//    vely+=Gravity;
//   paddlePtr->yLeft +=vely;
    if(paddlePtr->yLeft>=800)
    {
        paddlePtr->yLeft=800;
    }
    if(al_key_down(KBstatePtr, ALLEGRO_KEY_D))
        paddlePtr->xLeft += 3;
    if(al_key_down(KBstatePtr, ALLEGRO_KEY_A))
        paddlePtr->xLeft -=3;
    if(paddlePtr->yLeft < 150)
        paddlePtr->yLeft = 150;
    if(paddlePtr->yLeft > 800)
        paddlePtr->yLeft = 800;
    if(paddlePtr->xLeft < 0)
        paddlePtr->xLeft = 0;
    if(paddlePtr->xLeft > 1500)
        paddlePtr->xLeft = 1500;

}

void Gravity0(int vely,const int gravity,Paddle* paddlePtr)
{

    vely+=gravity;
    paddlePtr->yLeft +=vely;
}
