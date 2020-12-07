#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "myHeader1116.h"

#include "myheader.h"


int main( void )
{
    int i, init_base;
    //int x,y,dir;
    struct stut_ball
    {
        ALLEGRO_BITMAP *ballimg = NULL;
        int x;
        int y;
        int dir;
    };

    //ALLEGRO_BITMAP *ballimg = NULL; /* pointer to the ball's image bitmap */
    ALLEGRO_DISPLAY *display = NULL;/* pointer to display */
    ALLEGRO_KEYBOARD_STATE KBstate;

    struct stut_ball ball[10];
    /* first, set up Allegro and the graphics mode */
    al_init(); /* initialize Allegro */
    al_install_keyboard(); /* install the keyboard for Allegro to use */
    al_init_image_addon();
    srand( time( NULL ) ); /* seed the random function */

    display = al_create_display(SCREEN_W, SCREEN_H);
    for(i = 0;i<10;i++){
        ball[i].ballimg = al_load_bitmap( "ball.bmp"); /* load the ball bitmap */
        init_base = rand() % 4 +1;
        ball[i].x = SCREEN_W / init_base; /* give the ball its initial x-coordinate */
        ball[i].y = SCREEN_H / init_base; /* give the ball its initial y-coordinate */
        ball[i].dir = rand() % 4; /* and then make a random initial direction */
    }

    al_get_keyboard_state(&KBstate);

    while(!al_key_down(&KBstate, ALLEGRO_KEY_ESCAPE))
    {
        for(i=0; i<10; i++){
            moveBall(&ball[i].x, &ball[i].y, &ball[i].dir); /* move the ball */
            al_draw_bitmap(ball[i].ballimg, ball[i].x, ball[i].y, 0);/* draw the bitmap */
        }
        //Sleep(10);
        al_rest(0.01);

        /* display */
        al_flip_display(); /* Wait for the beginning of a vertical retrace. */
        al_clear_to_color(al_map_rgb(0,172,172));

        /* Clear the complete target bitmap, but confined by the clipping rectangle. */
        al_get_keyboard_state(&KBstate);
    }

    for(i = 0; i<10; i++){
        al_destroy_bitmap(ball[i].ballimg); /* destroy the ball bitmap */
    }
    al_destroy_display( display); /* destroy the display */

    return 0;
} /* end function main */

