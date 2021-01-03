#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "defineHeader.h"

void MY_ALGO_ErrMsg(char const *title, char const *text)
//錯誤對話框
{
    al_show_native_message_box(NULL, title, "", text, NULL, ALLEGRO_MESSAGEBOX_ERROR);
}

void MY_ALGO_QuaMsg(char const *title, char const *text)
//提示對話框
{
    al_show_native_message_box(NULL, title, "", text, NULL, ALLEGRO_MESSAGEBOX_QUESTION);
}

int  MY_ALGO_Y_N_Msg(char const *title, char const *text)
//提示對話框
{
    int result;
    result = al_show_native_message_box(NULL, title, "", text, NULL, ALLEGRO_MESSAGEBOX_YES_NO);
    return result;
}

void CopyCharArray1d(char src[], char dst[], int size)
// 功能  : 將 char array src 複製到 char array dst
{
    int i;
    for(i = 0; i < size; i++){
        dst[i] = src[i];
    }
}

void SortIntArray1d(int src[], int size, int sequence)
// 功能  : 將 int array src 排序 ; sequence大於1時小排到大, 反之大排到小
{
    int i, j, t;
    for(i = 0; i < size-1; i++){
        for(j = 0; j < size-i-1; j++){
            if((sequence > 0) && (src[j+1] < src[j])){
                t  = src[j];
                src[j] = src[j+1];
                src[j+1] = t;
            }else if((sequence <= 0) && (src[j+1] > src[j])){
                t  = src[j];
                src[j] = src[j+1];
                src[j+1] = t;
            }
        }
    }
}

//=================================================

void GetTime(struct tm *tm)
{
    time_t t = time(NULL);
    tm = localtime(&t);
    //printf("%d-%02d-%02d_%02d:%02d:%02d\n", mainData->tm->tm_year + 1900, mainData->tm->tm_mon + 1, mainData->tm->tm_mday, mainData->tm->tm_hour, mainData->tm->tm_min, mainData->tm->tm_sec);
}

int ScoreFileRead(const char *fileName, RankScoreDataStut *scoreData)
{
    dbp;
    char line[1024];
    int i = 0;
    FILE *fileStream = fopen(fileName, "r");
    while(fgets(line, 1024, fileStream) != NULL)
    {
        sscanf(line, "id:%d,score:%d,name:%[^,],time:%[^;];", &scoreData->data[i].id, &scoreData->data[i].score, scoreData->data[i].name, scoreData->data[i].time);
        //printf("| %d\t| %d\t| %s\t| %s\t|\n", scoreData->data[i].id, scoreData->data[i].score, scoreData->data[i].name, scoreData->data[i].time);
        i++;
        if(i == NUM_SCORE_DATA) break;
    }
    if(fileStream != NULL) fclose(fileStream);
    return 1;
}

void ScoreFileAppend(const char *fileName, MainDataStut *mainData)
{
    char line[1024];
    int i = 0, j = 0, n = 0;
    FILE *fileStream = NULL;
    fileStream = fopen(fileName, "r+");
    RankScoreDataStut *scoreData = (RankScoreDataStut *)calloc(sizeof(RankScoreDataStut), 1);
    scoreData->data = (RankRowStut *)calloc(sizeof(RankRowStut), NUM_SCORE_DATA+1);
    while(fgets(line, 1024, fileStream) != NULL)
    {
        sscanf(line, "id:%d,score:%d,name:%[^,],time:%[^;];", &scoreData->data[i].id, &scoreData->data[i].score, scoreData->data[i].name, scoreData->data[i].time);
        //printf("| %d\t| %d\t| %s\t| %s\t|\n", scoreData->data[i].id, scoreData->data[i].score, scoreData->data[i].name, scoreData->data[i].time);
        i++;
    }
    n = i;
    scoreData->data[n].id = n+1;
    scoreData->data[n].score = mainData->score.score;
    CopyCharArray1d(mainData->usrName.name, scoreData->data[n].name, 20);
    memset(scoreData->data[n].time, 0, 20);
    sprintf(scoreData->data[n].time, "%d/%02d/%02d_%02d:%02d:%02d%c", //format char array
            mainData->tm->tm_year + 1900, mainData->tm->tm_mon + 1, mainData->tm->tm_mday, mainData->tm->tm_hour, mainData->tm->tm_min, mainData->tm->tm_sec, '\0');
    //printf("N:%d\nSORT\n", n);
    if(fileStream != NULL) fclose(fileStream);
    /*sort*/
    for(i = 0; i < n; i++){
        for(j = 0; j < n-i; j++){
            if(scoreData->data[j+1].score > scoreData->data[j].score){
                scoreData->temp.id  = scoreData->data[j].id;
                scoreData->temp.score  = scoreData->data[j].score;
                CopyCharArray1d(scoreData->data[j].name, scoreData->temp.name, 20);
                CopyCharArray1d(scoreData->data[j].time, scoreData->temp.time, 20);

                scoreData->data[j].id = scoreData->data[j+1].id;
                scoreData->data[j].score = scoreData->data[j+1].score;
                CopyCharArray1d(scoreData->data[j+1].name, scoreData->data[j].name, 20);
                CopyCharArray1d(scoreData->data[j+1].time, scoreData->data[j].time, 20);

                scoreData->data[j+1].id = scoreData->temp.id;
                scoreData->data[j+1].score = scoreData->temp.score;
                CopyCharArray1d(scoreData->temp.name, scoreData->data[j+1].name, 20);
                CopyCharArray1d(scoreData->temp.time, scoreData->data[j+1].time, 20);
            }
        }
    }
    /*writefile*/
    fileStream = fopen(fileName, "w");
    for(i = 0; i < NUM_SCORE_DATA; i++){
        fprintf(fileStream, "id:%d,score:%d,name:%s,time:%s;\n", i+1, scoreData->data[i].score, scoreData->data[i].name, scoreData->data[i].time);
    }
    if(fileStream != NULL) fclose(fileStream);
    free(scoreData);
}
