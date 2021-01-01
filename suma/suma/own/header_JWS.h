#ifndef _JWS_H_
#define _JWS_H_

#include "../resource.h"
void PrintTest_JWS();

void GetTime(struct tm *tm);
int ScoreFileRead(const char *fileName, RankScoreDataStut *scoreData);
void ScoreFileAppend(const char *fileName, MainDataStut *mainData);

void CopyCharArray1d(char src[], char dst[], int size);
void SortIntArray1d(int src[], int size, int sequence);


void MY_ALGO_ErrMsg(char const *title, char const *text);
void MY_ALGO_QuaMsg(char const *title, char const *text);
int  MY_ALGO_Y_N_Msg(char const *title, char const *text);
#endif //_JWS_H_
