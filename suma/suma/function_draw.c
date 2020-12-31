#include "defineHeader.h"
#include "resource.h"

void DrawMenu(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int i;
    float x, y;
    al_draw_bitmap(allegroObj->background.Img, 0, 0, 0); // Draw bitmap
    for(i = 0; i < NUM_MENU_BUTTON; i++)
    {
        x = (allegroObj->menuButton[i].start_x + allegroObj->menuButton[i].end_x)/2;
        y = allegroObj->menuButton[i].start_y;
        if(allegroObj->menuButton[i].isSelected)
        {
            al_draw_scaled_bitmap(allegroObj->menuButton[i].img, 0, 0, SIZE_IMG_MENU_BUTTON_WIDTH, SIZE_IMG_MENU_BUTTON_HEIGHT,
                                  allegroObj->menuButton[i].start_x, allegroObj->menuButton[i].start_y, SIZE_IMG_MENU_BUTTON_WIDTH, SIZE_IMG_MENU_BUTTON_HEIGHT*SCALE_MENU_BUTTON, 0);
            al_draw_textf(allegroObj->font_a.font90, COLOR_MENU_BUTTON_A, x, y, ALLEGRO_ALIGN_CENTER, allegroObj->menuButton[i].text);
        }
        else
        {
            al_draw_bitmap(allegroObj->menuButton[i].img, allegroObj->menuButton[i].start_x, allegroObj->menuButton[i].start_y, 0);
            al_draw_textf(allegroObj->font_a.font90, COLOR_MENU_BUTTON_B, x, y, ALLEGRO_ALIGN_CENTER, allegroObj->menuButton[i].text);
        }
    }
    al_draw_textf(allegroObj->font_a.font120, COLOR_SCORE, DISPLAY_WIDTH/2, 0, ALLEGRO_ALIGN_CENTER, "S U M A");
    al_draw_textf(allegroObj->font_a.font24, COLOR_SCORE, DISPLAY_WIDTH, DISPLAY_HEIGHT-al_get_font_line_height(allegroObj->font_a.font24), ALLEGRO_ALIGN_RIGHT, "Ver:000");
}

void DrawScoreboard(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    al_draw_bitmap(allegroObj->coins.img, allegroObj->coins.start_x, allegroObj->coins.start_y, 0);
    al_draw_bitmap(allegroObj->chars.img, allegroObj->chars.start_x, allegroObj->chars.start_y, 0);
    al_draw_textf(allegroObj->font_a.font64, COLOR_SCORE, allegroObj->coins.end_x, allegroObj->coins.end_y, ALLEGRO_ALIGN_RIGHT, "%05d", mainData->score.chars);
    al_draw_textf(allegroObj->font_a.font64, COLOR_SCORE, allegroObj->chars.end_x, allegroObj->chars.end_y, ALLEGRO_ALIGN_RIGHT, "%05d", mainData->score.chars);
}

void DrawModeButton(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int i;
    float x, y;

    for(i = 0; i < NUM_MODE_BUTTON; i++)
    {
        x = (allegroObj->modeButton[i].start_x + allegroObj->modeButton[i].end_x)/2;
        y = allegroObj->modeButton[i].start_y;
        if(allegroObj->modeButton[i].isSelected)
        {
            al_draw_scaled_bitmap(allegroObj->modeButton[i].img, 0, 0, SIZE_IMG_MODE_BUTTON_WIDTH, SIZE_IMG_MODE_BUTTON_HEIGHT,
                                  allegroObj->modeButton[i].start_x, allegroObj->modeButton[i].start_y, SIZE_IMG_MODE_BUTTON_WIDTH, SIZE_IMG_MODE_BUTTON_HEIGHT*SCALE_MODE_BUTTON, 0);
            al_draw_textf(allegroObj->font_a.font90, COLOR_MODE_BUTTON_A, x, y, ALLEGRO_ALIGN_CENTER, allegroObj->modeButton[i].text);
        }
        else
        {
            al_draw_bitmap(allegroObj->modeButton[i].img, allegroObj->modeButton[i].start_x, allegroObj->modeButton[i].start_y, 0);
            al_draw_textf(allegroObj->font_a.font90, COLOR_MODE_BUTTON_B, x, y, ALLEGRO_ALIGN_CENTER, allegroObj->modeButton[i].text);
        }
    }
}

void DrawHomeButton(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    if(allegroObj->homeButton.isSelected)
    {
        al_draw_bitmap(allegroObj->homeButton.img, allegroObj->homeButton.start_x, allegroObj->homeButton.start_y, 0);
    }
    else
    {
        al_draw_bitmap(allegroObj->homeButton.img2, allegroObj->homeButton.start_x, allegroObj->homeButton.start_y, 0);
    }
}

void DrawModeSelect(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    al_draw_bitmap(allegroObj->background.Img, 0, 0, 0); // Draw bitmap
    al_draw_textf(allegroObj->font_a.font90, COLOR_SCORE, DISPLAY_WIDTH/2, 0, ALLEGRO_ALIGN_CENTER, "mode select");
    DrawModeButton(mainData, allegroObj);
    DrawHomeButton(mainData, allegroObj);
}

void DrawRule(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    al_draw_bitmap(allegroObj->background.Img, 0, 0, 0); // Draw bitmap
    al_draw_textf(allegroObj->font_a.font90, COLOR_SCORE, DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "rule");
    DrawHomeButton(mainData, allegroObj);
}

void DrawRank(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    al_draw_bitmap(allegroObj->background.Img, 0, 0, 0); // Draw bitmap
    al_draw_textf(allegroObj->font_a.font90, COLOR_SCORE, DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "rank");
    DrawHomeButton(mainData, allegroObj);
}

void DrawAbout(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    al_draw_bitmap(allegroObj->background.Img, 0, 0, 0); // Draw bitmap
    al_draw_textf(allegroObj->font_a.font90, COLOR_SCORE, DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "about");
    DrawHomeButton(mainData, allegroObj);
}

void DrawRole(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    switch(allegroObj->role.state)
    {
    case ROLE_NULL:
        if(allegroObj->role.imgCount % (int)(FPS*TIME_PER_IMG) == 0){
            allegroObj->role.imgCount = 0;
            allegroObj->role.nowImg += 1;
            if(allegroObj->role.nowImg % NUM_IMG_ROLE_SEQUENCE == 0) allegroObj->role.nowImg = 0;
        }
        al_draw_bitmap_region(allegroObj->role.imgs_runing, SIZE_IMG_ROLE_WIDTH*allegroObj->role.nowImg, 0, SIZE_IMG_ROLE_WIDTH, SIZE_IMG_ROLE_HEIGHT
                              , allegroObj->role.start_x, allegroObj->role.start_y, 0);
        allegroObj->role.imgCount += 1;
        break;
    default:
        al_draw_bitmap(allegroObj->role.img, allegroObj->role.start_x, allegroObj->role.start_y, 0); // Draw bitmap
        break;
    }

}
void DrawMeteor(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int i;
    dbp;
    al_draw_bitmap(allegroObj->meteor.img, allegroObj->meteor.start_x, allegroObj->meteor.start_y, 0); // Draw bitmap
    for (i = 0; i < allegroObj->meteor_n; i++)
    {
        al_draw_bitmap(allegroObj->meteors[i].img, allegroObj->meteors[i].start_x, allegroObj->meteors[i].start_y, 0);
    }
}
void DrawDisplayAndFlip(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int state = mainData->game_state;
    //int calculate = 0;
    al_clear_to_color( COLOR_CLEAR );

    switch(state)
    {
    case GAME_MENU:
        DrawMenu(mainData, allegroObj);
        break;
    case GAME_MODE_SELECT:
        DrawModeSelect(mainData, allegroObj);
        break;
    case GAME_RULE:
        DrawRule(mainData, allegroObj);
        break;
    case GAME_RANK:
        DrawRank(mainData, allegroObj);
        break;
    case GAME_ABOUT:
        DrawAbout(mainData, allegroObj);
        break;
    case GAME_PLAYING:

        if(allegroObj->background.x < DISPLAY_WIDTH - SIZE_IMG_BKG_WIDTH)
        {
            al_draw_bitmap(allegroObj->background.Img, allegroObj->background.x + SIZE_IMG_BKG_WIDTH, 0, 0); // Draw bitmap
        }
        al_draw_bitmap(allegroObj->background.Img, allegroObj->background.x, 0, 0); // Draw bitmap
        DrawRole(mainData, allegroObj);
        DrawMeteor(mainData, allegroObj);
        DrawScoreboard(mainData, allegroObj);
        al_draw_textf(allegroObj->font_a.font90, COLOR_SCORE, DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "Play Mode : %d", mainData->game_mode);
    case GAME_NONE:
        break;
    }
    //al_draw_textf(allegroObj->font_a.font48, COLOR_SCORE, 0, 0, ALLEGRO_ALIGN_LEFT, "This is a text test.");
    al_flip_display();
}
