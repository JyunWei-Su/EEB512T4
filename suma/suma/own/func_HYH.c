#include "../own/header_HYH.h"
#include "../defineHeader.h"

void PrintTest_BYK(){
    printf("This is a print test by BYK.\n");
}

void Change(float *start,float *end)
{
    float temp;
    //確認start與end大小
    if(*start > *end)
    {
        temp = *start;
        *start = *end;
        *end = temp;
    }
}

bool CrashCheck(float start_x1,float start_y1,float end_x1,float end_y1,float start_x2,float start_y2,float end_x2,float end_y2)
{
    float Length_x,Length_y;
   Change(&start_x1,&end_x1);
   Change(&start_y1,&end_y1);
   Change(&start_x2,&end_x2);
   Change(&start_y2,&end_y2);
    Length_x = end_x1 - start_x1;
    Length_y = end_y1 - start_y1;
    //printf("start_x2=%f\n",start_x2);
    //printf("end_x1=%f\n",end_x1);
    //printf("start_x2 - end_x1=%f\n",start_x2 - end_x1);
    if(start_x2 - end_x1 >= Length_x && start_y2 - end_y1 >= Length_y)
    {
        return 0;
    }
    else
    {
        return DefineCrash(start_x1, start_y1, end_x1, end_y1,start_x2, start_y2, end_x2, end_y2);
    }
}

bool DefineCrash(float start_x1,float start_y1,float end_x1,float end_y1,float start_x2,float start_y2,float end_x2,float end_y2)
{

        if(((start_x2 <=end_x1 && start_x2>=start_x1) && (start_y2 >=start_y1 && start_y2 <= end_y1)) || (start_x2 <=end_x1 && start_x2>=start_x1) && (end_y2 >=start_y1 && end_y2 <= end_y1))
        {
            return 1;
        }
        else
        {
            return 0;
        }


}
