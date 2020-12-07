#include "myheader.h"

void moveBall( int *x, int *y, int *dir ) /* moves the ball */
{
   switch ( *dir ) {
      case DOWN_RIGHT:
         *x=*x+1; /* move the ball to the right */
         ++*y; /* move the ball down */
         break;
      case UP_RIGHT:
         ++*x; /* move the ball to the right */
         --*y; /* move the ball up */
         break;
      case DOWN_LEFT:
         --*x; /* move the ball to the left */
         ++*y; /* move the ball down n */
         break;
      case UP_LEFT:
         --*x; /* move the ball to the left */
         --*y; /* move the ball up */
         break;
   } /* end switch */

   /* make sure the ball doesn't go off the screen */

   /* if the ball is going off the top or bottom... */
   if ( *y <= 0 || *y >= (SCREEN_H - BALL_SIZE) )
      reverseVerticaldir(dir); /* make it go the other way */

   /* if the ball is going off the left or right... */
   if ( *x <= 0 || *x >= (SCREEN_W - BALL_SIZE) )
      reverseHorizontaldir(dir); /* make it go the other way */
} /* end function moveBall */

void reverseVerticaldir( int *dir ) /* reverse the ball's up-down dir */
{
   if ( *dir == DOWN_RIGHT ) *dir = UP_RIGHT;
    else if ( *dir == DOWN_LEFT ) *dir = UP_LEFT;
        else if ( *dir == UP_RIGHT ) *dir = DOWN_RIGHT;
            else if ( *dir == UP_LEFT ) *dir = DOWN_LEFT;
} /* end function reverseVerticaldir */

void reverseHorizontaldir( int *dir ) /* reverses the horizontal dir */
{
   switch ( *dir ){
      case DOWN_RIGHT:
          *dir = DOWN_LEFT;
         break;
      case UP_RIGHT:
         *dir = UP_LEFT;
         break;
      case DOWN_LEFT:
         *dir = DOWN_RIGHT;
         break;
      case UP_LEFT:
         *dir = UP_RIGHT;
         break;
   } /* end switch */
} /* end function reverseHorizontaldir */
