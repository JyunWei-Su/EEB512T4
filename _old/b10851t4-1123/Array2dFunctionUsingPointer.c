#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Array2d 相關 Function(此區暫未更新)
 *
 * IntArray    : 輸出(print)、隨機填入、複製、最大最小值
 *               加總、平方加總、算數平均、幾何平均、標準差、開根號乘以10、轉double、轉char
 * DoubleArray : 輸出(print)、隨機填入、複製、最大最小值
 *               加總、平方加總、算數平均、幾何平均、標準差、開根號乘以10、陣列除以某數
 * CharArray   : 輸出(print)、轉大寫、轉小寫、大小寫互換、複製
 *
 * Version: jws6.27a , 內容來源:b1085151, 整理.除錯.註解:b1085151、b1085114
 */

/*===== int array function =====*/
int *CreateIntArray1d(int col)
// input col
// output a pointer to 2D mat[row][col]
{
    int *addr = (int *) calloc(col, sizeof(int));
    return addr;
}

int **CreateIntArray2d(int row, int col)
// input row and col
// output a pointer to 2D mat[row][col]
{
    int **addr = (int **) calloc(row, sizeof(int *));
    int i=0;
    for(i=0; i<row; i++){
        // Allocate array, store pointer
        addr[i] = (int *) calloc(col, sizeof(int));
    }
    return addr;
}

int **CreateAndFillIntArray2d(int row, int col, int fill)
// input row and col
// return a 2D mat[row][col] with all elements =X
{
    int **addr = CreateIntArray2d(row,col);
    int i=0, j=0;
    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            addr[i][j] = fill;
       }
    }
    return addr;
}

int **CreateAndRandIntArray2d(int row, int col, int fillStart, int fillInterval)
// input row and col
// return a 2D mat[row][col] with all elements =X
{
    int **addr = CreateIntArray2d(row,col);
    int i=0, j=0;
    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            addr[i][j] = (int)(rand()%fillInterval + fillStart);
       }
    }
    return addr;
}

void FreeArray2d(int **addr, int row)
{
    int i=0;
    for(i=0; i<row; i++)
        free(addr[i]);
    free(addr);
}

void FreeArray1d(int *addr)
{
    free(addr);
}

void PrintIntArray2d(int **src, int row, int col, char const *delimiter)
//print a 2d array
{
    int i=0,j=0;
    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            printf("%d%s", src[i][j], delimiter);
        }
        printf("\n");
    }
}

void PrintfIntArray2d(int **src, int row, int col, char *message, char const *delimiter)
//printf a 2d array
{
    int i=0,j=0;
    printf("%s", message);
    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            printf("%d%s", src[i][j], delimiter);
        }
        printf("\n");
    }
}

void PrintIntArray1d(int *src, int col, char *delimiter)
//print a 1d array
{
    int i=0;
    for(i=0; i<col; i++){
        printf("%d%s", src[i], delimiter);
    }
    printf("\n");
}

void PrintfIntArray1d(int *src, int col, char *message, char *delimiter)
//printf a 1d array
{
    int i=0;
    printf("%s", message);
    for(i=0; i<col; i++){
        printf("%d%s", src[i], delimiter);
    }
    printf("\n");
}

/*//此區待整理

int  **mat_add(int **a, int **b, int m, int n) //相加
// input matrix: a(m*n), b(m*n),
// output mat=a+b(m*n)
{
  int **mat=create_matrix2(m,n);

  int i,j;

  for (i=0; i<m; i++)
    for (j=0; j<n; j++){
      mat[i][j] = a[i][j]+b[i][j];
    }
  return mat;
}

int  **mat_minus(int **a, int **b, int m, int n) //相減
// input matrix: a(m*n), b(m*n),
// output mat=a-b(m*n)
{
  int **mat=create_matrix2(m,n);

  int i,j;

  for (i=0; i<m; i++)
    for (j=0; j<n; j++){
      mat[i][j] = a[i][j]-b[i][j];
    }
  return mat;
}

int  **mat_trans(int **a, int m, int n) // 轉置
// input matrix: a(m*n)
// output mat=a(n*m)
{
  int **mat=create_matrix2(n,m);
  int i,j;
  for (i=0; i<n; i++){
    for (j=0; j<m; j++){
      mat[i][j] = a[j][i];
    }
  }
  return mat;
}

int  **mat_mult(int **a, int m, int n, int magnification) //乘以A倍
// input matrix: a(m*n)
// output mat=xA(m*n)
{
    int **mat=create_matrix2(m,n);
    int i,j;
    for (i=0; i<m; i++){
        for (j=0; j<n; j++){
            mat[i][j] =magnification*a[i][j];
        }
    }
    return mat;
}

int  **mat_multAB(int **a, int **b, int m, int n) //相乘
// input matrix: a(m*n), b(m*n), m must as same as n
// output mat=a*b(m*n)
{
    int **mat=create_matrix2(m,n);
    int i,j,k,sum;
    for (i=0; i<m; i++){
        for (j=0; j<n; j++){
            sum=0;
            for (k=0; k<m; k++){
                sum += a[i][k]*b[k][j];
            }
            mat[i][j] = sum;
        }
    }
    return mat;
}
*/


/* //以下尚未轉為pointer形式
void CopyIntArray2d(int row, int col, int src[][col], int dst[][col])
// 功能  : 將 int array src 複製到 char array dst
// input : src:來源array ; dst:目的地array ; size:array大小 ; 建議src和dst大小要一樣
// output: No Ouput, No Return, 只將src複製到dst
{
    int i, j;
    for(i = 0; i < row; i++){
        for(j = 0; i < col; j++){
            dst[i][j] = src[i][j];
        }
    }
}

int MaxMinIntArray2d(int row, int col, int src[][col], int select)
// 功能  : 找出一整數陣列最大值
// input : 一整數陣列、元素個數、選擇最大(1)或最小(-1)
// output: x中最大最小的數
{
    int i, j, ans = src[0][0];
    if(select == 1){ //select=1 時執行選最大
        for(i = 0; i < row; i++){
            for(j = 0; j < col; j++){
                if (src[i][j] >= ans) ans = src[i][j];
            }
        }
    }
    else if(select == -1){ //select=-1 時執行選最小
        for(i = 0; i < row; i++){
            for(j = 0; j < col; j++){
                if (src[i][j] <= ans) ans = src[i][j];
            }
        }
    }
    else ans = 0;
    return ans;
}

int SumIntArray2d(int row, int col, int src[][col])
// 功能  : 將二維陣列元素(整數)相加起來
// input : 大小row * col 的二維整數陣列
// output: 總和(整數)
{
    int i, j, sum = 0;
    for(i = 0 ; i < row ; i++){
        for(j = 0; j < col; j++){
            sum += src[i][j];
        }
    }
    return sum;
}
*/

int CountIntArray2d(int **src, int row, int col, int countTarget)
// 功能  :
// input :
// output:
{
    int i, j, count = 0;
    for(i = 0 ; i < row ; i++){
        for(j = 0; j < col; j++){
            if(src[i][j] == countTarget) count += 1;
        }
    }
    return count;
}

void CopyIntArray2d(int **src, int row, int col, int **dst)
// 功能  : 將 int array src 複製到 char array dst
// input : src:來源array ; dst:目的地array ; size:array大小 ; 建議src和dst大小要一樣
// output: No Ouput, No Return, 只將src複製到dst
{
    int i, j;

    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            dst[i][j] = src[i][j];
        }
    }
}

/*
int SquareSumIntArray2d(int row, int col, int src[][col])
// 功能  : 求平方和
// input : 整數陣列、元素個數
// output: 陣列平方和
{
    int i, j, squaresum = 0;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            squaresum += pow(src[i][j],2);
        }
    }
    return squaresum;
}

double AverageIntArray2d(int row, int col, int src[][col])
// 功能  : 求陣列算數平均
// input : 整數陣列，元素個數
// output: 陣列平均
{
    int sum;
    double average;
    sum = SumIntArray2d(row, col, src);
    average= (double)sum / (row*col);
    return average;
}

double GeometricAverageIntArray2d(int row, int col, int src[][col])
// 功能  : 算幾何平均數
// input : 整數正數陣列，元素個數
// output: 陣列平均
{
    int product=1 , i, j;
    double geometricAverage;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            product *= abs(src[i][j]); //加絕對值避免負號出問題
        }
    }
    geometricAverage = pow(product, (1/(double)(row*col))); //將積開(row*col)倍根號
    return geometricAverage;
}

double StddevIntArray2d(int row, int col, int src[][col])
// 功能  : 算一浮點數陣列標準差
// input : 浮點數陣列、元素個數
// output: 浮點數表示的標準差
{
    int i, j;
    double average, stddev, sum = 0;
    average = AverageIntArray2d(row, col, src);
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            sum += pow(src[i][j] - average, 2);
        }
    }
    stddev = sqrt((double)sum / (row*col));
    return stddev;
}

void Sqrt10IntArray2d(int row, int col, int src[][col], double dst[][col])
// 功能  : 將元素開根號乘上10
// input : 整數陣列，元素個數
// output: 更新開根號乘上10的陣列 注意仍為int(避免使用本函式)
{
    int i, j;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            dst[i][j] = sqrt(fabs((double)src[i][j]))*10; //為了不要讓負數出錯
        }
    }
}

void ConvertIntArrayToDouble2d(int row, int col, int src[][col], double dst[][col])
// 功能  : int array 轉 double array
// input : array
// output: no return, 改變dst為src(型態改為double)
{
    int i, j;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            dst[i][j] = (double)src[i][j];
        }
    }
}

void ConvertIntArrayToChar2d(int row, int col, int src[][col], char dst[][col])
// 功能  : int array 轉 char array
// input : array
// output: no return, 改變dst為src(型態改為char)
{
    int i, j;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            dst[i][j] = (char)src[i][j];
        }
    }
}
*/

/*===== double array function =====*/
/*
void PrintDoubleArray2d(int row, int col, double src[][col], char delimiter[])
// 功能  : 印出陣列x
// input : 浮點數陣列x與其元素個數
// output: print x內元素
{
    int i, j;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            printf("%2.2lf%s", src[i][j], delimiter);
        }
        printf("\n");
    }
}

void RandomDoubleArray2d(int row, int col, double src[][col], int start, int interval)
// 功能  : 在start到interval隨機填size個整數到src[]陣列中
// input : (浮點數)要隨機填入的陣列src[]，填入的個數，與其開始與區間
// output: 沒回傳值，僅更改src[]
{
    int i, j, integer;
    double decimal;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            decimal = (double)rand() / RAND_MAX ; //先取出一個必為小數的數
            integer = rand()%interval + start; //再從範圍中取出整數
            src[i][j] = (double)integer + decimal; //將小數與整數相加
        }
    }
}

void CopyDoubleArray2d(int row, int col, double src[][col], double dst[][col])
// 功能  : 將 int array src 複製到 char array dst
// input : src:來源array ; dst:目的地array ; size:array大小 ; 建議src和dst大小要一樣
// output: No Ouput, No Return, 只將src複製到dst
{
    int i, j;
    for(i = 0; i < row; i++){
        for(j = 0; i < col; j++){
            dst[i][j] = src[i][j];
        }
    }
}

double MaxMinDoubleArray2d(int row, int col, double src[][col], int select)
// 功能  : 找出一浮點數陣列最大值
// input : 一浮點數陣列、元素個數、選擇最大(1)或最小(-1)
// output: x中最大的數
{
    int i, j;
    double ans = src[0][0];
    if(select == 1){ //select=1 時執行選最大
        for(i = 0; i < row; i++){
            for(j = 0; j < col; j++){
                if (src[i][j] >= ans) ans = src[i][j];
            }
        }
    }
    else if(select == -1){ //select=-1 時執行選最小
        for(i = 0; i < row; i++){
            for(j = 0; j < col; j++){
                if (src[i][j] <= ans) ans = src[i][j];
            }
        }
    }
    else ans = 0;
    return ans;
}

double SumDoubleArray2d(int row, int col, double src[][col])
// 功能  : 將一陣列元素(浮點數)相加起來
// input : 一浮點數陣列,要相加的元素量
// output: 總和(浮點數)
{
    int i, j;
    double sum = 0;
    for(i = 0 ; i < row ; i++){
        for(j = 0; j < col; j++){
            sum += src[i][j];
        }
    }
    return sum;
}

double SquareSumDoubleArray2d(int row, int col, double src[][col])
// 功能  : 求平方和
// input : 浮點數陣列、元素個數
// output: 陣列平方和
{
    int i, j;
    double squaresum = 0;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            squaresum += pow(src[i][j],2);
        }
    }
    return squaresum;
}

double AverageDoubleArray2d(int row, int col, double src[][col])
// 功能  : 求陣列算數平均
// input : 浮點數陣列，元素個數
// output: 陣列平均
{
    double sum , average;
    sum = SumDoubleArray2d(row, col, src);
    average = sum / (row*col);
    return average;
}

double GeometricAverageDoubleArray2d(int row, int col, double src[][col])
// 功能  : 算幾何平均數
// input : 浮點數正數陣列，元素個數
// output: 陣列平均
{
    double product = 1, geometricAverage = 0;
    int i, j;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            product *= fabs(src[i][j]);//為了不要讓負數出錯
        }
    }
    geometricAverage = pow(product,(1 / (double)(row*col))); //將積開size倍根號
    return geometricAverage;
}

double StddevDoubleArray2d(int row, int col, double src[][col])
// 功能  : 算一浮點數陣列標準差
// input : 浮點數陣列、元素個數
// output: 浮點數表示的標準差
{
    double average, stddev, sum = 0;
    int i, j;
    average = AverageDoubleArray2d(row, col, src);
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            sum += (src[i][j] - average) * (src[i][j] - average);
        }
    }
    stddev = sqrt(sum / (row*col));
    return stddev;
}

void Sqrt10DoubleArray2d(int row, int col, double src[][col], double dst[][col])
// 功能  : 將元素開根號乘上10
// input : 浮點數陣列，元素個數
// output: 更新開根號乘上10的陣列
{
    int i, j;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            dst[i][j] = sqrt(fabs(src[i][j]))*10; //為了不要讓負數出錯
        }
    }
}

void CutDoubleArray2d(int row, int col, double src[][col], int cut, double dst[][col])
// 功能  : bouble array除以某數
// input : 愈被除array
// output: no return, 改變dst為結果
{
    int i, j;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            dst[i][j] = src[i][j]/cut;
        }
    }
}
*/

/*===== char array function =====*/
/*
void PrintCharArray2d(int row, int col, char src[][col], char delimiter[])
// 功能  : 輸出 char array src (src: source縮寫)
// input : char array src of size elements
// output: print contents of src, No Return
{
    int i, j;
    for(i = 0; i < row; i ++){
        for(j = 0; j < col; j++){
            printf("%c%s", src[i][j], delimiter);
        }
        printf("\n");
    }

}

void ConvertCharArrayToUpper2d(int row, int col, char src[][col])
// 功能  : 將 char array src 所有字母元素轉為大寫
// input : char array src of size elements
// output: No Ouput, No Return, 只改變原array
{
    int i, j;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            if((97 <= (int)src[i][j]) && ((int)src[i][j] <= 122)) src[i][j] -= 32;
        }
    }
}

void ConvertCharArrayToLower2d(int row, int col, char src[][col])
// 功能  : 將 char array src 所有字母元素轉為小寫
// input : char array src of size elements
// output: No Ouput, No Return, 只改變原array
{
    int i, j;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            if((65 <= (int)src[i][j]) && ((int)src[i][j] <= 90)) src[i][j] += 32;
        }
    }
}

void ChangeCharArrayUpperLower2d(int row, int col, char src[][col])
// 功能  : 將 char array src 所有字母元素大小寫互換
// input : char array src of size elements
// output: No Ouput, No Return, 只改變原array
{
    int i, j;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            if((97 <= (int)src[i][j]) && ((int)src[i][j] <= 122)) src[i][j] -= 32;
            else if((65 <= (int)src[i][j]) && ((int)src[i][j] <= 90)) src[i][j] += 32;
        }
    }

}


void CopyCharArray2d(int row, int col, char src[][col], char dst[][col])
// 功能  : 將 int array src 複製到 char array dst
// input : src:來源array ; dst:目的地array ; size:array大小 ; 建議src和dst大小要一樣
// output: No Ouput, No Return, 只將src複製到dst
{
    int i, j;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            dst[i][j] = src[i][j];
        }
    }
}

*/

