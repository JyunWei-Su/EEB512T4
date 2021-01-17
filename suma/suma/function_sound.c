#include "defineHeader.h"
#include "resource.h"

void PlaySoundEffect(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int state = mainData->game_state;
    int isPlaying = 0;
    switch(state)
    {
    case GAME_MENU:
        isPlaying = al_get_sample_instance_playing(allegroObj->sound.sfi_background);
        if(!isPlaying)
        {
            al_set_sample_instance_gain(allegroObj->sound.sfi_background, 0.5); //調整聲音大小
            al_set_sample_instance_playmode(allegroObj->sound.sfi_background, ALLEGRO_PLAYMODE_LOOP);
            //al_set_sample_instance_playing(allegroObj->sound.sfi_background, true);
        }
        PlayButtonSfx(mainData, allegroObj);
        break;
    case GAME_MODE_SELECT:
        PlayButtonSfx(mainData, allegroObj);
        break;
    case GAME_RULE:
        PlayButtonSfx(mainData, allegroObj);
        break;
    case GAME_RANK:
        PlayButtonSfx(mainData, allegroObj);
        break;
    case GAME_ABOUT:
        PlayButtonSfx(mainData, allegroObj);
        break;
    case GAME_PLAYING_NORMAL:
        if(allegroObj->sound.coinCrash.readyToPlay)
        {
            al_play_sample(allegroObj->sound.coinCrash.sfx, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &allegroObj->sound.id);
            allegroObj->sound.coinCrash.readyToPlay = 0;
        }
        if(allegroObj->sound.damageBook.readyToPlay)
        {
            al_play_sample(allegroObj->sound.damageBook.sfx, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &allegroObj->sound.id);
            allegroObj->sound.damageBook.readyToPlay = 0;
        }
        if(allegroObj->sound.roleDead.readyToPlay )
        {
            al_play_sample(allegroObj->sound.roleDead.sfx, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &allegroObj->sound.id);
            allegroObj->sound.roleDead.readyToPlay = 0;
        }
    default:
        break;
    }
}

void PlayButtonSfx(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    if(allegroObj->sound.buttonMoveIn.readyToPlay)
    {
        al_play_sample(allegroObj->sound.buttonMoveIn.sfx, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &allegroObj->sound.id);
        allegroObj->sound.buttonMoveIn.readyToPlay = 0;
    }
}
