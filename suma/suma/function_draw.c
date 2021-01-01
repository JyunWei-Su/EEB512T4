#include "defineHeader.h"
#include "resource.h"

void DrawMenu(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int i;
    float x, y;
    al_draw_bitmap(allegroObj->background.img, 0, 0, 0); // Draw bitmap
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
    al_draw_textf(allegroObj->font_a.font64, COLOR_SCORE, allegroObj->coins.end_x, allegroObj->coins.start_y, ALLEGRO_ALIGN_RIGHT, "%05d", mainData->score.coins);
    al_draw_textf(allegroObj->font_a.font64, COLOR_SCORE, allegroObj->chars.end_x, allegroObj->chars.start_y, ALLEGRO_ALIGN_RIGHT, "%05d", mainData->score.chars);
    DrawObjBoundary(allegroObj->coins.start_x, allegroObj->coins.start_y, allegroObj->coins.end_x, allegroObj->coins.end_y);
    DrawObjBoundary(allegroObj->chars.start_x, allegroObj->chars.start_y, allegroObj->chars.end_x, allegroObj->chars.end_y);
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
    al_draw_bitmap(allegroObj->background.img, 0, 0, 0); // Draw bitmap
    al_draw_textf(allegroObj->font_a.font90, COLOR_SCORE, DISPLAY_WIDTH/2, 0, ALLEGRO_ALIGN_CENTER, "mode select");
    DrawModeButton(mainData, allegroObj);
    DrawHomeButton(mainData, allegroObj);
}

void DrawRule(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    al_draw_bitmap(allegroObj->background.img, 0, 0, 0); // Draw bitmap
    al_draw_textf(allegroObj->font_a.font90, COLOR_SCORE, DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "rule");
    DrawHomeButton(mainData, allegroObj);
}

void DrawRank(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    al_draw_bitmap(allegroObj->background.img, 0, 0, 0); // Draw bitmap
    al_draw_textf(allegroObj->font_a.font90, COLOR_SCORE, DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "rank");
    DrawHomeButton(mainData, allegroObj);
}

void DrawAbout(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    al_draw_bitmap(allegroObj->background.img, 0, 0, 0); // Draw bitmap
    al_draw_textf(allegroObj->font_a.font90, COLOR_SCORE, DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "about");
    DrawHomeButton(mainData, allegroObj);
}

void DrawRole(MainDataStut *mainData, AllegroObjStut *allegroObj)
//Role動畫
{
    switch(allegroObj->role.state)
    {
    case ROLE_NULL:
        if(allegroObj->role.imgCount % (int)(FPS*TIME_PER_IMG) == 0)
        {
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
    DrawObjBoundary(allegroObj->role.start_x, allegroObj->role.start_y, allegroObj->role.end_x, allegroObj->role.end_y);
}
void DrawMeteorAnimation(MainDataStut *mainData, AllegroObjStut *allegroObj)
//隕石動畫，沒有邊界?
{
    int i;
    int state = mainData->game_state;
    switch(state)
    {
    case GAME_PLAYING_FINAL_BOSS:
        for (i = 0; i < allegroObj->meteor_n; i++)
        {
            if(allegroObj->meteors_right_drop[i].imgCount % (int)(FPS*TIME_PER_IMG) == 0)
            {
                allegroObj->meteors_right_drop[i].imgCount = 0;
                allegroObj->meteors_right_drop[i].nowImg += 1;
                if(allegroObj->meteors_right_drop[i].nowImg % NUM_IMG_METEOR_SEQUENCE == 0) allegroObj->meteors_right_drop[i].nowImg = 0;
            }
            al_draw_bitmap_region(allegroObj->meteors_right_drop[i].imgs_runing, SIZE_IMG_METEOR_BIG_WIDTH*allegroObj->meteors_right_drop[i].nowImg, 0, SIZE_IMG_METEOR_BIG_WIDTH, SIZE_IMG_METEOR_BIG_HEIGHT
                                  , allegroObj->meteors_right_drop[i].start_x, allegroObj->meteors_right_drop[i].start_y, 0);
            allegroObj->meteor.imgCount += 1;
            //DrawObjBoundary_meteor(allegroObj->meteors_right_drop[i]);
            DrawObjBoundary(allegroObj->meteors_right_drop[i].start_x, allegroObj->meteors_right_drop[i].start_y, allegroObj->meteors_right_drop[i].end_x, allegroObj->meteors_right_drop[i].end_y);
        }
        break;
    }

}
void DrawMeteor(MainDataStut *mainData, AllegroObjStut *allegroObj)
//隕石
{
    int i;
    int state = mainData->game_state;
    //al_draw_bitmap(allegroObj->meteor.img, allegroObj->meteor.start_x, allegroObj->meteor.start_y, 0);
    //DrawObjBoundary(allegroObj->meteor.start_x, allegroObj->meteor.start_y, allegroObj->meteor.end_x, allegroObj->meteor.end_y);
    switch(state)
    {
    case GAME_PLAYING_MID_BOSS:
        for (i = 0; i < allegroObj->meteor_n; i++)
        {
            //««ª½±¼¸¨
            al_draw_bitmap(allegroObj->meteors[i].img, allegroObj->meteors[i].start_x, allegroObj->meteors[i].start_y, 0);
            DrawObjBoundary_meteor(allegroObj->meteors[i]);
            //¥ª±×¤U±¼¸¨
            al_draw_bitmap(allegroObj->meteors_right_drop[i].img, allegroObj->meteors_right_drop[i].start_x, allegroObj->meteors_right_drop[i].start_y, 0);
            DrawObjBoundary_meteor(allegroObj->meteors_right_drop[i]);
            //¥k±×¤U±¼¸¨
            al_draw_bitmap(allegroObj->meteors_left_drop[i].img, allegroObj->meteors_left_drop[i].start_x, allegroObj->meteors_left_drop[i].start_y, 0);
            DrawObjBoundary_meteor(allegroObj->meteors_left_drop[i]);

        }
        break;
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
    case GAME_PLAYING_NORMAL:
        if(allegroObj->background.x < DISPLAY_WIDTH - SIZE_IMG_BKG_WIDTH)
        {
            al_draw_bitmap(allegroObj->background.img, allegroObj->background.x + SIZE_IMG_BKG_WIDTH, 0, 0); // Draw bitmap
        }
        al_draw_bitmap(allegroObj->background.img, allegroObj->background.x, 0, 0); // Draw bitmap
        DrawRole(mainData, allegroObj);
        al_draw_bitmap(allegroObj->floor.img, allegroObj->floor.start_x, allegroObj->floor.start_y, 0); // Draw bitmap
        DrawObjBoundary(allegroObj->floor.start_x, allegroObj->floor.start_y, allegroObj->floor.end_x, allegroObj->floor.end_y);
        DrawScoreboard(mainData, allegroObj);
        al_draw_textf(allegroObj->font_a.font90, COLOR_SCORE, DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "Play Mode : %d", mainData->game_mode);

    case GAME_NONE:
        break;
    case GAME_PLAYING_MID_BOSS:
        if(allegroObj->background.x < DISPLAY_WIDTH - SIZE_IMG_BKG_WIDTH)
        {
            al_draw_bitmap(allegroObj->background.img, allegroObj->background.x + SIZE_IMG_BKG_WIDTH, 0, 0); // Draw bitmap
        }
        al_draw_bitmap(allegroObj->background.img, allegroObj->background.x, 0, 0); // Draw bitmap
        DrawRole(mainData, allegroObj);
        al_draw_bitmap(allegroObj->floor.img, allegroObj->floor.start_x, allegroObj->floor.start_y, 0); // Draw bitmap
        DrawObjBoundary(allegroObj->floor.start_x, allegroObj->floor.start_y, allegroObj->floor.end_x, allegroObj->floor.end_y);
        DrawScoreboard(mainData, allegroObj);
        al_draw_textf(allegroObj->font_a.font90, COLOR_SCORE, DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "Play Mode : %d", mainData->game_mode);
        DrawMeteor(mainData, allegroObj);
        break;
    case GAME_PLAYING_FINAL_BOSS:
        if(allegroObj->background.x < DISPLAY_WIDTH - SIZE_IMG_BKG_WIDTH)
        {
            al_draw_bitmap(allegroObj->background.img, allegroObj->background.x + SIZE_IMG_BKG_WIDTH, 0, 0); // Draw bitmap
        }
        al_draw_bitmap(allegroObj->background.img, allegroObj->background.x, 0, 0); // Draw bitmap
        DrawRole(mainData, allegroObj);
        al_draw_bitmap(allegroObj->floor.img, allegroObj->floor.start_x, allegroObj->floor.start_y, 0); // Draw bitmap
        DrawObjBoundary(allegroObj->floor.start_x, allegroObj->floor.start_y, allegroObj->floor.end_x, allegroObj->floor.end_y);
        DrawScoreboard(mainData, allegroObj);
        al_draw_textf(allegroObj->font_a.font90, COLOR_SCORE, DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "Play Mode : %d", mainData->game_mode);
        DrawMeteorAnimation(mainData, allegroObj);
        break;
    }
    //al_draw_textf(allegroObj->font_a.font48, COLOR_SCORE, 0, 0, ALLEGRO_ALIGN_LEFT, "This is a text test.");
    al_flip_display();
}

void DrawObjBoundary(float x1, float y1, float x2, float y2)
//畫長方形邊界
{
    //printf("x1: %f, y1: %f\nx2: %f, y2: %f\n", x1, x2, y1, y2);
    al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(255, 0, 0), 0);
}

void DrawObjBoundary_meteor(MeteorStut meteor)
//畫隕石邊界
{
    DrawObjBoundary(meteor.start_x, meteor.start_y, meteor.end_x, meteor.end_y);
}
