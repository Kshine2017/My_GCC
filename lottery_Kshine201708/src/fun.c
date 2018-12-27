#include "fun.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void stop()
{
        printf("<-- 按Enter键退出！-->\n");
        getchar();
}


//遮挡输入的数值
char* secret_num(char* str)
{

        char ch=0;
        int i=0;
        getchar();
        while(1)
        {
                system("stty -icanon");//关闭缓冲区，输入字符无需回车直接接受
                ch=getchar();
                printf("\b@");
                if(ch=='\n')
                {
                        break;
                }
                str[i++]=ch;
        }
        str[i]='\0';
        return str;
}


//验证码
int identifying_code()
{
	char array[100]={"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"};
	char a[5]="";
	char b[5]="";
	srand(time(NULL));
	a[0]=array[rand()%62];
	a[1]=array[rand()%62];
	a[2]=array[rand()%62];
	a[3]=array[rand()%62];
	printf("验证码是:");
	printf("\033[42;31m%s\033[0m\n",a);
	printf("请输入您的验证码:");
	scanf("%s",b);
	if(strcmp(a,b)==0)
	{
		printf("验证成功！\n");
		return 0;
	}
	else
	{
		printf("验证失败！");
		return 1;
	}
	return 0;
}






