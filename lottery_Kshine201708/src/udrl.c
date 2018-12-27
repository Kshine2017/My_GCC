#include <stdio.h>
#include <stdlib.h>
#include "lotview.h"


int key_udrl(int choose,int menu_num,int mode)
{
	printf("\n\033[47;31m\t\t\t敲击Enter继续！\033[0m\n");
	getchar();


        while (1)
        {
		
                char c =0;

		if(mode==1)
		{
			V_main_menu_move(choose);
		}
		else if(mode==2)
		{
			V_game_move(choose);
		}
		else if(mode==3)
		{
			V_other_move(choose);
		}
		else if(mode==4)
		{
			V_sort_move(choose);
		}
		else if(mode==5)
		{
			V_admin_menu_move(choose);
		}
		else if(mode==6)
		{
			V_user_menu_move(choose);
		}
		else if(mode==7)
		{
			V_notery_menu_move(choose);
		}
                while(1) //自动清掉奇怪的符号
		{
			system("stty -icanon");//关闭缓冲区，输入字符无需回车直接接受
			
                	c=getchar();  
			if(c=='\n')
			{
				
				return choose;
			}
                	if((c>='a'&&c<='z')
			&& (c>='A'&&c<='Z') 
			&& (c>='9'&&c<='0')) 
			{
				printf("\b");
				continue;
			}
			else  //是字母或者数字
			{
				break;
			}
                }
		//得到上下左右或者字母数字

		if(c<='9'&&c>='0')//返回数值，直接控制
		{
			choose = (int)(c-'0');//不要急着返回
		}
		else
		{
			if(c=='A')//up
			{
				choose--;
			}
			if(c=='B')//down
			{
				choose++;
			}
			if(c=='D')//left
			{
				choose=0;
				
			}
			if(c=='C')//right
			{
				//进入当前的choose菜单
				break;
				
			}
		}
		//--------------------
		if(choose<0)
		{
			choose += menu_num;
		}
		if(choose>menu_num-1)
		{
			choose -=(menu_num);	
		}
                //-----动态显示
		//V_main_menu_move(choose);
		//----
		
        }
	return choose;
}
