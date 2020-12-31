#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "defineHeader.h"

int CountARowIntArray2d(int **src, int row, int col, int rowelect, int countTarget)
// 功能  : 計算2d Array 中第rowSelect Row 出現countTarget幾次
// input : A row * col 2d Array pointer
// output: return the result
{
    int i, count = 0;
    for(i = 0 ; i < col; i++){
        if(src[rowelect][i] == countTarget) count += 1;
    }
    return count;
}

int CountAColIntArray2d(int **src ,int row, int col, int colelect, int countTarget)
// 功能  : 計算2d Array 中第colSelect Col 出現countTarget幾次
// input : A row * col 2d Array pointer
// output: return the result
{
    int i, count = 0;
    for(i = 0 ; i < row; i++){
        if(src[i][colelect] == countTarget) count += 1;
    }
    return count;
}



void CountColDetial(int **src, int row, int col, int **dst)
// 功能  : 計算2d Array 中每col中，每一個數出現的次數
// input : A row * col 2d Array pointer
// output: store the result to a 2d Array dst (pointer)
{
    int i, j;
    for(i = 0; i < col; i++){
        for(j = 0; j < 5; j++){
            dst[j][i] = CountAColIntArray2d(src, row, col, i, j+1);
        }
    }
}

int CountArowRptCount(int **src, int row, int col, int rowSelect)
// 功能  : 計算2d Array 中第rowSelect Row 連續出現數字的總量(連續2個以上才計入)
// input : A row * col 2d Array pointer, rowSelect
// output: return the result
{
    int i, j, score = 0;
    for(i = 0; i < col-1; i++){ // 針對row 中每一個col當標定開始往後檢查
        j = i+1;
        //printf("\tscoreFor i:%d, j:%d\n", i, j);
        while(src[rowSelect][i] == src[rowSelect][j]){
            //printf("\trowRptCountAdd i:%d, j:%d\n", i, j);
            if(j == i+1) score += 2;
            else score += 1;
            if(j == col-1) break; //避免到底了還在檢查
            j += 1;
        }
        i = j-1; //跳出while前多的+1要扣掉
    }
    return score;
}

int CountAcolRptCount(int **src, int row, int col, int colSelect)
// 功能  : 計算2d Array 中第colSelect Col 連續出現數字的總量(連續2個以上才計入)
// input : A row * col 2d Array pointer, rowSelect
// output: return the result
{
    int i, j, score = 0;
    for(i = 0; i < row-1; i++){
        j = i+1;
        //printf("\tscoreFor i:%d, j:%d\n", i, j);
        while(src[i][colSelect] == src[j][colSelect]){
            //printf("\trowRptCountAdd i:%d, j:%d\n", i, j);
            if(j == i+1) score += 2;
            else score += 1;
            if(j == row-1) break; //避免到底了還在檢查
            j += 1;
        }
        i = j-1;//跳出while前多的+1要扣掉
    }
    return score;
}

void CountArrayRepeated(int **src, int row, int col, int *dstrowRptCount, int *dstcolRptCount)
// 功能  : 計算2d Array 中 每一Row每一Col 連續出現數字的總量(連續2個以上才計入)
// input : A row * col 2d Array pointer, rowSelect
// output: store the result to 2 1d Array dstrowRptCount, dstcolRptCount
{
    //printf("CountArrayRepeated: row:%d, col:%d\n", row, col);
    int i;
    for(i = 0; i < row; i++){
        //printf("countScore %d\n", i);
        dstrowRptCount[i] = CountArowRptCount(src, row, col, i);
    }
    for(i = 0; i < col; i++){
        //printf("countScore %d\n", i);
        dstcolRptCount[i] = CountAcolRptCount(src, row, col, i);
    }
}
