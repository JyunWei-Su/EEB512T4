#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

void allegro_init();
void voice_init(ALLEGRO_SAMPLE_INSTANCE *instance, ALLEGRO_MIXER **mixer, ALLEGRO_VOICE **voice);
void layout_init();
void playing(ALLEGRO_MOUSE_STATE *mouse, ALLEGRO_SAMPLE_INSTANCE *instance, int *state);
