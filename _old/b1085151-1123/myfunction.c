#include "myheader.h"


void MyAlgc_init(){
    /* first, set up Allegro and the graphics mode */
    al_init(); /* initialize Allegro */
    al_install_keyboard(); /* install the keyboard for Allegro to use */
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
}

void MyAlgc_waitToClose(ALLEGRO_KEYBOARD_STATE KBstate){
    while(!al_key_down(&KBstate, ALLEGRO_KEY_ESCAPE)){
        al_rest(0.01);
        al_flip_display();
        al_get_keyboard_state(&KBstate);
    }

}


