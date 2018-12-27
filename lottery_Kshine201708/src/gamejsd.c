#include<stdio.h>  
#include<stdlib.h>  
#include<time.h>  
  
/*************\  
* 剪刀 石头 布 *  
* 最简单小游戏 *  
\*************/  
  
int gamejsb(void)
{  
        char gesture[3][10] = {"scissor","stone","cloth"};  
        int man, computer, result, ret;  
        /*随机数初始化函数*/  
        srand(time(NULL));  
        while(1)
	{
		system("clear");  
                computer = rand()%3;  
                printf("\nInput your gesture 0-scissor 1-stone 2-cloth:\n");  
		printf("q to quit!\n");

                ret = scanf("%d", &man);  
		if(ret=='q')
		{
			return 1;
		}
                if(ret !=1 || man<0 || man>2)
		{  
                        printf("Invalid input!\n");  
                        return 1;  
                }  
                printf("Your gesture:%s\tComputer's gesture: %s\n",  
                gesture[man], gesture[computer]  
                );  
                result =  (man - computer + 4) %3 -1;  
                if(result > 0)  
                        printf("YOU WIN!\n");  
                else if(result == 0)  
                        printf("Draw!\n");  
                else  
                        printf("You lose!\n");

		printf("按Enter继续!\n"); 
		getchar();
		getchar();
 
        }  

        return 0;  
}  
