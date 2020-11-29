#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
// Definition of display size
#define ROW 9
#define COL 9
#define DISPLAY_WIDTH   900
#define DISPLAY_HEIGHT  900

void Random_Picture( int row,int col,int a[][COL],ALLEGRO_BITMAP* bitmap1,ALLEGRO_BITMAP* bitmap2,ALLEGRO_BITMAP* bitmap3,ALLEGRO_BITMAP* bitmap4,ALLEGRO_BITMAP* bitmap5,ALLEGRO_BITMAP* bitmap6);
void Close_By_Space(int select);
void Close_Event(int select);
