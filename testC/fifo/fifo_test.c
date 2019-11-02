#include <stdio.h>
#include <windows.h>
#include "fifo.h"
int dataForPush=0;
int dataForPop={0};
int buff[10]={0};
fifoCtrl_t fifo;
int main(void)
{
    fifoCtrl_t fifo;
    fifo_init(&fifo,buff,sizeof(int),10);
    int buffPrintFlag=0;
    while(1)
    {
        dataForPush++;
        if(0==dataForPush%3)//当dataForPush的值为3的整数倍时,push
        {
            if(FIFO_OK==fifo_push(&fifo,&dataForPush))//if push ok
            {
                printf("push:%d\n",dataForPush);
            }
            else
            {
                dataForPush--;
                printf("push err!!!\n");
            }
            buffPrintFlag=1;
        }
        if((0==dataForPush%6) || fifo_isFull(&fifo))//当dataForPush的值为6的整数倍或fifo满时，pop一个数
        {
            if(FIFO_OK==fifo_pop(&fifo,&dataForPop))//if pop ok
            {
                printf("pop:%d\n",dataForPop);
            }
            else
            {
                printf("pop err!!!\n");
            }
            buffPrintFlag=1;
         }
        if(buffPrintFlag==1)
        {
            buffPrintFlag=0;
            printf("buff:");
            {
                int j=0;
                for(j=0;j<10;j++)//print buff
                    printf("%d, ",buff[j]);
                printf("\n");
            }
            getchar();
        }

        //Sleep(1000);
    }
    return 0;

}
