#ifndef _DEF_HEADER_H_
#define _DEF_HEADER_H_

#include "own/header_BYK.h"
#include "own/header_HYH.h"
#include "own/header_IRL.h"
#include "own/header_JWS.h"
#include "resource.h"
#include "function_draw.h"
#include "function_sound.h"
#include "function_check.h"
#include "function_operate.h"

/* Definition of display size */
#define FPS 60
#define DISPLAY_WIDTH   1600
#define DISPLAY_HEIGHT  900
#define nl printf("\n")
#define dbp printf("...///...///\n")

//====================
void MY_ALGO_DestroyCandyImgs(ALLEGRO_BITMAP **candyImgsAddr, int num);
ALLEGRO_BITMAP **MY_ALGO_CreateCandyImgs(int num);
void MY_ALGO_LoadCandyImgs(ALLEGRO_BITMAP **candyImgsAddr, int num);
void MY_ALGO_DrawCandyImgs(int **mainArray, int row, int col, ALLEGRO_BITMAP **candyImgsAddr);
void MY_ALGO_ErrMsg(char const *title, char const *text);
//====================
int *CreateIntArray1d(int col);
int **CreateIntArray2d(int row, int col);
int **CreateAndFillIntArray2d(int row, int col, int fill);
int **CreateAndRandIntArray2d(int row, int col, int fillStart, int fillInterval);
void FreeArray2d(int **addr, int row);
void FreeArray1d(int *addr);
void PrintIntArray2d(int **src, int row, int col, char *delimiter);
void PrintfIntArray2d(int **src, int row, int col, char *message, char *delimiter);
void PrintIntArray1d(int *src, int col, char *delimiter);
void PrintfIntArray1d(int *src, int col, char *message, char *delimiter);
int CountIntArray2d(int **src, int row, int col, int countTarget);
void CopyIntArray2d(int **src, int row, int col, int **dst);

//====================

void CountNumberIntArray2d(int **src, int row, int col, int *dst);
int CountARowIntArray2d(int **src, int row, int col, int rowelect, int countTarget);
int CountAColIntArray2d(int **src,int row, int col, int colelect, int countTarget);
void CountRowDetial(int **src, int row, int col, int **dst);
void CountColDetial(int **src, int row, int col, int **dst);
int CountArowRptCount(int **src, int row, int col, int rowSelect);
int CountAcolRptCount(int **src, int row, int col, int colSelect);
void CountArrayRepeated(int **src, int row, int col, int *dstrowRptCount, int *dstcolRptCount);
//void PrintArrayCountAndScore_1005(int row, int col, int mainArray[][col], int rowCount[][FillRange], int colCount[][col], int rowRptCount[], int colRptCount[]);
void CheckElementAndMark(int **mainArray, int row, int col, int rowSelect, int colSelect);
void CheckArrayAndMarkAll(int **mainArray, int row, int col);
int EliminateAndCountScore(int **mainArray, int row, int col);
void ReComposeAndFill(int **mainArray, int row, int col, int fillStart, int fillInterval);
int DoAllProcessAndPrint(int **mainArray, int row, int col);
int DoOnceProcessAndPrint(int **mainArray, int row, int col, int round, int score);
void PrintArrayCountAndScore_1102(int row, int col, int **mainArray, int *rowRptCount, int *colRptCount, int **elmtArray, int **reFillArray, int round, int score);
void PrintfIntArray2dAddAValue(int **src, int row, int col, char const *message, char const *delimiter, int addValue);


#endif  //_DEF_HEADER_H_
