#ifndef _MYHEADER_H_
#define _MYHEADER_H_


/* symbolic constants for the ball¡¦s possible directions */
#define DOWN_RIGHT 0
#define UP_RIGHT 1
#define DOWN_LEFT 2
#define UP_LEFT 3

#define SCREEN_W 640
#define SCREEN_H 480
#define BALL_SIZE 40


/* function prototypes */
void moveBall( int *x, int *y, int *dir ); /* moves the ball */
void reverseVerticaldir( int *dir ); /* reverse the ball's up-down dir */
void reverseHorizontaldir( int *dir ); /* reverses the horizontal dir */

#endif // _MYHEADER_H_
