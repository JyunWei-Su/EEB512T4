#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "myHeader1116.h"

void CountNumberIntArray2d(int **src, int row, int col, int *dst)
// 功能  :計算0 ~ FillRange-1 分別在array 中出現幾次
// input :
// output: Store the result to a 1d array dst
{
    int i =0;
    for(i = 0; i < FillRange; i++){
        dst[i] = CountIntArray2d(src, row, col, i+1);
    }
}

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

void CountRowDetial(int **src, int row, int col, int **dst)
// 功能  : 計算2d Array 中每一row中，每一個數出現的次數
// input : A row * col 2d Array pointer
// output: store the result to a 2d Array dst (pointer)
{
    int i, j;
    for(i = 0; i < row; i++){
        for(j = 0; j < FillRange; j++){
            dst[i][j] = CountARowIntArray2d(src, row, col, i, j+1);
        }
    }
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

//void PrintArrayCountAndScore_1005(int row, int col, int mainArray[][col], int rowCount[][FillRange], int colCount[][col], int rowRptCount[], int colRptCount[])
//輸出結果(過時)
/*
{
    int i, j;
    printf("\t| mainArray:\t  count:1 2 3 4 5 \tscore:\n"); // print title
    printf("--------|-----------------------------------------------\n");
    for(i = 0; i < row; i++){ //print mainArray, rowCount, rowRptCount row by row
        printf("\t| ");
        for(j = 0; j<col; j++) printf("%d ", mainArray[i][j]); // print mainArray
        printf("\t");
        for(j = 0; j<FillRange; j++) printf("%d ", rowCount[i][j]); // print rowCount
        printf("\t%d\n", rowRptCount[i]); // print rowRptCount
    }
    printf("count:  |\n");
    for(i = 0; i < FillRange; i++){
        printf("      %d | ", i+1);
        for(j = 0; j<col; j++) printf("%d ", colCount[i][j]); // print colCount
        printf("\n");
    }
    printf("\t|\nscore:  | ");
    for(i = 0; i < col; i++) printf("%d ", colRptCount[i]); // print colRptCount
    printf("\n");
}*/

/*
void PrintAddress(char info[], int *address)
{
    printf("%s\t@ %x\n", info , address);
}*/



void CheckElementAndMark(int **mainArray, int row, int col, int rowSelect, int colSelect)
// 功能  : 檢查array中"特定"元素之上下左右連續性，若連續3個以上則標定連續的部分(正數轉為負數)
// input : A row * col 2d Array pointer, rowSelect, colSelect
// output: change the element to its minus value which is continuous (over 3)
{
    int i = 0;
    int cl, cr, cu, cd; //check_left, right, up, down
    int target = mainArray[rowSelect][colSelect];
    cl = colSelect; cr = colSelect; cu = rowSelect; cd = rowSelect;
    //分別向4個方向檢查連續性，先檢查偏移後是否在範圍內，再檢查偏移後是否與標定物相同
    while(cl-1>=0  && abs(mainArray[rowSelect][cl-1])==target) cl--;
    while(cr+1<col && abs(mainArray[rowSelect][cr+1])==target) cr++;
    while(cu-1>=0  && abs(mainArray[cu-1][colSelect])==target) cu--;
    while(cd+1<row && abs(mainArray[cd+1][colSelect])==target) cd++;
    if(cr-cl+1 >= 3){
        for(i=cl; i<=cr; i++) mainArray[rowSelect][i] = (-1)*abs(target);
    }
    if(cd-cu+1 >= 3){
        for(i=cu; i<=cd; i++) mainArray[i][colSelect] = (-1)*abs(target);
    }
}

void CheckArrayAndMarkAll(int **mainArray, int row, int col)
// 功能  : 檢查array中"所有"元素之上下左右連續性，若連續3個以上則標定連續的部分(正數轉為負數)
// input : A row * col 2d Array pointer
// output: change the element to its minus value which is continuous (over 3)
{
    int i=0, j=0;
    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            CheckElementAndMark(mainArray, row, col, i, j);
        }
    }
}

int EliminateAndCountScore(int **mainArray, int row, int col)
// 功能  : 將已標定的部分(負數)轉為零(0)並計數(非計分)
// input : A row * col 2d Array pointer
// output: change the element which has been marked to Zero, return the total count of marks
{
    int i=0, j=0, count=0;
    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            if(mainArray[i][j] < 0){
                mainArray[i][j] = 0;
                count += 1;
            }
        }
    }
    return count*10;
}

void ReComposeAndFill(int **mainArray, int row, int col, int fillStart, int fillInterval)
// 功能  : array中遇到0(被消除掉的元素)就取上方非0數字填入，若上方全為0則隨機填入(一個col一個col執行)
// input : A row * col 2d Array pointer, fillStart, fillInterval
// output: store the reComposed and reFilled array to mainArrray
{
    int i=0, j=0, k=0;
    for(i=0; i<col; i++){ //跑每一個col
        for(j=row-1; j>=0; j--){ //每一個col從尾巴檢查回來
            k = j-1;
            while(mainArray[j][i] == 0){
                if(k < 0){ //沒有東西可以下落
                    mainArray[j][i] = (int)(rand()%fillInterval + fillStart);
                }
                else if(mainArray[k][i] == 0){
                    k--;
                }else{
                    mainArray[j][i] = mainArray[k][i];
                    mainArray[k][i] = 0;
                    k--;
                }
            }
        }
    }
}

int DoAllProcessAndPrint(int **mainArray, int row, int col)
// 持續檢查是否有可以消除的連續，並輸出總消除之計數(非計分)
{
    int score = 0, addScore = 0, round = 0;
    do{
        round += 1;
        addScore = DoOnceProcessAndPrint(mainArray, row, col, round, score);
        score += addScore;
    }while(addScore > 0);
    return score;
}

int DoOnceProcessAndPrint(int **mainArray, int row, int col, int round, int score)
// 檢查一次mainArray消除後並回填，最後print相關資料
{
    int addScore = 0;
    int *rowRptCount, *colRptCount;
    int **elmtArray, **bkupArray;

    rowRptCount = CreateIntArray1d(row); //連續數計數
    colRptCount = CreateIntArray1d(col); //連續數計數
    elmtArray = CreateIntArray2d(row, col); //消除後array
    bkupArray = CreateIntArray2d(row,col); //初始時之mainArray(備份供print用)

    CountArrayRepeated(mainArray, row, col, rowRptCount, colRptCount); //計數各行各列
    CopyIntArray2d(mainArray, row, col, bkupArray); //備份mainArray供輸出用
    CheckArrayAndMarkAll(mainArray, row, col); //探索並標記可消除之元素
    addScore += EliminateAndCountScore(mainArray, row, col); //消除並計分
    if(addScore == 0) return 0;

    CopyIntArray2d(mainArray, row, col, elmtArray); //複製消除後的array
    ReComposeAndFill(mainArray, row, col, 1, FillRange); //下落並回填
    PrintArrayCountAndScore_1102(row, col, bkupArray, rowRptCount, colRptCount, elmtArray, mainArray, round, score+addScore);//輸出

    FreeArray1d(rowRptCount);
    FreeArray1d(colRptCount);
    FreeArray2d(elmtArray, row);
    FreeArray2d(bkupArray, row);

    return addScore;
}

void PrintArrayCountAndScore_1102(int row, int col, int **mainArray, int *rowRptCount, int *colRptCount, int **elmtArray, int **reFillArray, int round, int score)
// 輸出指定要求
{
    //以下輸出時 會扣1 array填入的需求是0~n, 然而因為0在運算中拿來當作要消除之用 因此配置時配置1~n+1 輸出時才在這裡扣1
    int i, j;
    printf("Round:%d\t| mainArray:\t rowCount:\teleimate:\t\treFill:\n", round); // print title
    printf("--------|----------------------------------------------------------------------\n");
    for(i = 0; i < row; i++){ //print mainArray, rowCount, rowRptCount row by row
        printf("\t| ");
        for(j = 0; j<col; j++) printf("%d ", mainArray[i][j]-1); // print mainArray
        printf("\t%d\t", rowRptCount[i]); // print rowRptCount
        for(j = 0; j<col; j++){ //print eleimateArray
            if(elmtArray[i][j] == 0) printf("- ");
            else printf("%d ", elmtArray[i][j]-1);
        }
        printf("\t");
        for(j = 0; j<col; j++) printf("%d ", reFillArray[i][j]-1); // print reFillArray
        printf("\n");
    }
    printf("\t|\nrol_Cnt:| ");
    for(i = 0; i < col; i++) printf("%d ", colRptCount[i]); // print colRptCount
    printf("\t\t=> Currently Score : %d", score);
    printf("\n\n");
}

void PrintfIntArray2dAddAValue(int **src, int row, int col, char const *message, char const *delimiter, int addValue)
//printf a 2d array
{
    int i=0,j=0;
    printf("%s", message);
    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            printf("%d%s", src[i][j] + addValue, delimiter);
        }
        printf("\n");
    }
}
