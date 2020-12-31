#include "../own/header_BYK.h"
#include "../defineHeader.h"


void initPaddle(Paddle* paddlePtr, ALLEGRO_BITMAP* img)//
{
    // give left paddle its initial y-coordinate
    paddlePtr->yLeft = 800;
    paddlePtr->xLeft = 0;
    paddlePtr->img = img;
    // give right paddle its initial y-coordinate
//    paddlePtr->yRight = SCREEN_H / 2;

}

void JumpPaddle(Paddle* paddlePtr, ALLEGRO_KEYBOARD_STATE* KBstatePtr,ALLEGRO_BITMAP* img,ALLEGRO_BITMAP *bkgImg)
{
    int vely=0;
    const int Gravity=1;
    bool jump =true;
    if(paddlePtr->yLeft < 650)
    {
        paddlePtr->yLeft = 650;
        jump =false;
        while(paddlePtr->yLeft<800)
        {
            //al_draw_bitmap(bkgImg, 0, 0, 0);
            paddlePtr->yLeft += 3;
            if(al_key_down(KBstatePtr, ALLEGRO_KEY_D))
                paddlePtr->xLeft += 3;
            if(al_key_down(KBstatePtr, ALLEGRO_KEY_A))
                paddlePtr->xLeft -=3;
            al_draw_bitmap(img, paddlePtr->xLeft, paddlePtr->yLeft, 0);
            al_rest(0.01);
            al_flip_display(); //顯示在視窗上
            al_clear_to_color(al_map_rgb(0, 0, 0)); //避免殘影
            al_draw_bitmap(bkgImg, 0, 0, 0);
        }
        //al_rest(1);
    }
    if(jump)
    {
        if(al_key_down(KBstatePtr, ALLEGRO_KEY_W))
        {
            paddlePtr->yLeft -= 15;
            al_rest(0.01);
        }
    }
    if(paddlePtr->yLeft > 800)
        paddlePtr->yLeft = 800;
    if(paddlePtr->xLeft < 0)
        paddlePtr->xLeft = 0;
    if(paddlePtr->xLeft > 1500)
        paddlePtr->xLeft = 1500;

//    vely+=Gravity;
//   paddlePtr->yLeft +=vely;

    if(al_key_down(KBstatePtr, ALLEGRO_KEY_D))
        paddlePtr->xLeft += 3;
    if(al_key_down(KBstatePtr, ALLEGRO_KEY_A))
        paddlePtr->xLeft -=3;


}
void DropFromMaxPoint(Paddle* paddlePtr, ALLEGRO_KEYBOARD_STATE* KBstatePtr,ALLEGRO_BITMAP* img,ALLEGRO_BITMAP *bkgImg,int game_state)
{
    while(paddlePtr->yLeft<800)
    {
        //al_draw_bitmap(bkgImg, 0, 0, 0);
        paddlePtr->yLeft += 3;
        if(al_key_down(KBstatePtr, ALLEGRO_KEY_D))
            paddlePtr->xLeft += 3;
        if(al_key_down(KBstatePtr, ALLEGRO_KEY_A))
            paddlePtr->xLeft -=3;
        al_draw_bitmap(img, paddlePtr->xLeft, paddlePtr->yLeft, 0);
        al_rest(0.01);
        al_flip_display(); //顯示在視窗上
        al_clear_to_color(al_map_rgb(0, 0, 0)); //避免殘影
        al_draw_bitmap(bkgImg, 0, 0, 0);
    }
    // game_state =  GameStateMove;
BeyondPoint( paddlePtr);
}
void MoveItem(Paddle* paddlePtr, ALLEGRO_KEYBOARD_STATE* KBstatePtr,int game_state)
{

    if(al_key_down(KBstatePtr, ALLEGRO_KEY_W))
    {
        paddlePtr->yLeft -= 15;
        al_rest(0.01);
    }
    if(al_key_down(KBstatePtr, ALLEGRO_KEY_D))
        paddlePtr->xLeft += 3;
    if(al_key_down(KBstatePtr, ALLEGRO_KEY_A))
        paddlePtr->xLeft -=3;
    if(paddlePtr->yLeft < 650)
        paddlePtr->yLeft = 650;
    game_state = GameStateMaxPoint;
    //printf("%d",game_state);
    if(paddlePtr->yLeft > 800)
        paddlePtr->yLeft = 800;
    if(paddlePtr->xLeft < 0)
        paddlePtr->xLeft = 0;
    if(paddlePtr->xLeft > 1500)
        paddlePtr->xLeft = 1500;
}
void BeyondPoint(Paddle* paddlePtr)
{
    if(paddlePtr->yLeft < 650)
        paddlePtr->yLeft = 650;
    if(paddlePtr->yLeft > 800)
        paddlePtr->yLeft = 800;
    if(paddlePtr->xLeft < 0)
        paddlePtr->xLeft = 0;
    if(paddlePtr->xLeft > 1500)
        paddlePtr->xLeft = 1500;


}
void JumpCheck(Paddle* paddlePtr, ALLEGRO_KEYBOARD_STATE* KBstatePtr,ALLEGRO_BITMAP* img,ALLEGRO_BITMAP *bkgImg)
{

    int game_state=GameStateMove;
    switch(game_state)
    {
    case GameStateMove:
        MoveItem( paddlePtr,  KBstatePtr, game_state);
Gravity0(0,3,paddlePtr);
        if(paddlePtr->yLeft == 650)
        {
            game_state = GameStateMaxPoint;
            printf("%d",game_state);
        }
        break;
    case GameStateMaxPoint:
        DropFromMaxPoint(paddlePtr,  KBstatePtr, img,bkgImg, game_state);

        break;


    }

}
void Gravity0(int vely,const int gravity,Paddle* paddlePtr)
{
    vely+=gravity;
    paddlePtr->yLeft +=vely;
}

