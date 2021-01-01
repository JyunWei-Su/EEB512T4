#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h> //for utf
#include <inttypes.h> /* strtoimax */

#define SCREEN_W 640
#define SCREEN_H 480

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> //圖形
#include <allegro5/allegro_native_dialog.h> //對話視窗
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define nl printf("\n")
#define EURO "\xe2\x82\xac"

/* Definition of display size */
#define DISPLAY_WIDTH   900
#define DISPLAY_HEIGHT  900

/* function prototypes */
void MyAlgc_init();
void MyAlgc_waitToClose(ALLEGRO_KEYBOARD_STATE KBstate);

