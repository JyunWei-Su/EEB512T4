#include <stdio.h>
#include "defineHeader.h"

void MY_ALGO_DestroyCandyImgs(ALLEGRO_BITMAP **candyImgsAddr, int num)
// free imgs array
{
    int i = 0;
    for(i = 0; i < num; i++){
        al_destroy_bitmap(candyImgsAddr[i]);
    }
    free(candyImgsAddr);
}

ALLEGRO_BITMAP **MY_ALGO_CreateCandyImgs(int num)
// create imgs array
{
    ALLEGRO_BITMAP **addr = (ALLEGRO_BITMAP **) calloc(num, sizeof(ALLEGRO_BITMAP *));
    return addr;
}


void MY_ALGO_LoadCandyImgs(ALLEGRO_BITMAP **candyImgsAddr, int num)
//讀圖片
{
    int i = 0;
    char candyImgPath[20] = "./img/candy0.png";
    for(i = 0; i < num; i++){
        candyImgPath[11] = (char)(i + 48);//圖片編號
        candyImgsAddr[i] = al_load_bitmap(candyImgPath);
        //printf("addr: %s \n", candyImgPath);
    }
}

void MY_ALGO_DrawCandyImgs(int **mainArray, int row, int col, ALLEGRO_BITMAP **candyImgsAddr)
//讀圖片
{
    int x = 0, y = 0, n = 0;
    int i = 0, j = 0;

    y = 144;
    for(i = 0; i < row; i++){
        x = 32;
        for(j = 0; j < col; j++){
            n = mainArray[i][j]; // laod elmt in mainArray
            al_draw_bitmap(candyImgsAddr[n-1], x, y, 0); // Draw bitmap
            x += 80;
        }
        y += 80;
    }
}

void MY_ALGO_ErrMsg(char const *title, char const *text)
//錯誤對話框
{
    al_show_native_message_box(NULL, title, "", text, NULL, ALLEGRO_MESSAGEBOX_ERROR);
}

