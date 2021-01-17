#ifndef _FUNCTION_ELSE_H_
#define _FUNCTION_ELSE_H_

#include "resource.h"


void MY_ALGO_ErrMsg(char const *title, char const *text);
void MY_ALGO_QuaMsg(char const *title, char const *text);
int MY_ALGO_Y_N_Msg(char const *title, char const *text);
void CopyCharArray1d(char src[], char dst[], int size);
void SortIntArray1d(int src[], int size, int sequence);
void GetTime(struct tm *tm);
int ScoreFileRead(const char *fileName, RankScoreDataStut *scoreData);
void ScoreFileAppend(const char *fileName, MainDataStut *mainData);
#endif //_FUNCTION_ELSE_H_

