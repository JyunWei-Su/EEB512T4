#include "defineHeader.h"
#include "resource.h"

void PlaySoundEffect(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int state = mainData->game_state;
    int isPlaying = 0;
    switch(state){
        case GAME_MENU:
            isPlaying = al_get_sample_instance_playing(allegroObj->sound.sfi_background);
            if(!isPlaying){
                al_set_sample_instance_gain(allegroObj->sound.sfi_background, 0.2);
                al_set_sample_instance_playmode(allegroObj->sound.sfi_background, ALLEGRO_PLAYMODE_LOOP);
                al_set_sample_instance_playing(allegroObj->sound.sfi_background, true);
            }
            break;
        default:
            break;
    }
}
