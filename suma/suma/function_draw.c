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
    al_draw_bitmap(allegroObj->sb_coins.img, allegroObj->sb_coins.start_x, allegroObj->sb_coins.start_y, 0);
    al_draw_bitmap(allegroObj->sb_chars.img, allegroObj->sb_chars.start_x, allegroObj->sb_chars.start_y, 0);
    al_draw_textf(allegroObj->font_a.font64, COLOR_SCORE, allegroObj->sb_coins.end_x, allegroObj->sb_coins.start_y, ALLEGRO_ALIGN_RIGHT, "%05d", mainData->score.coins);
    al_draw_textf(allegroObj->font_a.font64, COLOR_SCORE, allegroObj->sb_chars.end_x, allegroObj->sb_chars.start_y, ALLEGRO_ALIGN_RIGHT, "%05d", mainData->score.chars);
    DrawObjBoundary(allegroObj->sb_coins.start_x, allegroObj->sb_coins.start_y, allegroObj->sb_coins.end_x, allegroObj->sb_coins.end_y);
    DrawObjBoundary(allegroObj->sb_chars.start_x, allegroObj->sb_chars.start_y, allegroObj->sb_chars.end_x, allegroObj->sb_chars.end_y);
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
    al_draw_textf(allegroObj->font_a.font90, COLOR_SCORE, DISPLAY_WIDTH/2, 0, ALLEGRO_ALIGN_CENTER, "rank");
    DrawRankScore(mainData, allegroObj);
    DrawHomeButton(mainData, allegroObj);
}

void DrawRankScore(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int i;
    int x = DISPLAY_WIDTH/2;
    int y = DISPLAY_HEIGHT/2;
    //al_draw_textf(allegroObj->font_b.font64, COLOR_SCORE, x, y-SIZE_TEXT_RANK_LEADONG*8, ALLEGRO_ALIGN_CENTER, "Rank");
    al_draw_textf(allegroObj->font_b.font36, COLOR_SCORE, x, y-SIZE_TEXT_RANK_LEADONG*5, ALLEGRO_ALIGN_CENTER, "--No act: Press Q or Esc to return to menu.");
    for(i = 0; i < NUM_SCORE_DATA; i++){
        al_draw_textf(allegroObj->font_b.font36, COLOR_SCORE, x/3, y-SIZE_TEXT_RANK_LEADONG*(4-i), ALLEGRO_ALIGN_LEFT, "%2d\t%5d\t%20s\t%s",
                      mainData->scoreFileData->data[i].id, mainData->scoreFileData->data[i].score, mainData->scoreFileData->data[i].name, mainData->scoreFileData->data[i].time);
    }
}

void DrawAbout(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    al_draw_bitmap(allegroObj->background.img, 0, 0, 0); // Draw bitmap
    al_draw_textf(allegroObj->font_a.font90, COLOR_SCORE, DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "about");
    DrawHomeButton(mainData, allegroObj);
}

void DrawRole(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    switch(allegroObj->role.state)
    {
    case ROLE_NULL:
        if(allegroObj->role.imgCount % (int)(FPS*TIME_PER_IMG_ROLE) == 0)
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

void DrawMeteor(MainDataStut *mainData, AllegroObjStut *allegroObj)
{
    int i;
    DrawObjBoundary(allegroObj->meteor.start_x, allegroObj->meteor.start_y, allegroObj->meteor.end_x, allegroObj->meteor.end_y);
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
        DrawCoin(mainData, allegroObj);
        al_draw_bitmap(allegroObj->floor.img, allegroObj->floor.start_x, allegroObj->floor.start_y, 0); // Draw bitmap
        DrawObjBoundary(allegroObj->floor.start_x, allegroObj->floor.start_y, allegroObj->floor.end_x, allegroObj->floor.end_y);
        DrawMeteor(mainData, allegroObj);
        DrawScoreboard(mainData, allegroObj);
        al_draw_textf(allegroObj->font_a.font90, COLOR_SCORE, DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "Play Mode : %d", mainData->game_mode);
    case GAME_NONE:
        break;
    }
    //al_draw_textf(allegroObj->font_a.font48, COLOR_SCORE, 0, 0, ALLEGRO_ALIGN_LEFT, "This is a text test.");
    al_flip_display();
}

void DrawObjBoundary(float x1, float y1, float x2, float y2)
{
    //printf("x1: %f, y1: %f\nx2: %f, y2: %f\n", x1, x2, y1, y2);
    al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(255, 0, 0), 0);
}

void DrawObjBoundary_meteor(MeteorStut meteor)
{
    DrawObjBoundary(meteor.start_x, meteor.start_y, meteor.end_x, meteor.end_y);
}
