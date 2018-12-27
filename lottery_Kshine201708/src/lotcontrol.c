#include "lottery.h"
#include "lotview.h"
#include "unistd.h"
#include "udrl.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "gamejsb.h"
#include "pic.h"
#include "fun.h"
void others_control()//info
{
        int choose = 1;
        while(1)
        {
                sleep(1);
                //system("clear");
           
		choose=key_udrl(choose,4,3);//按键控制，以及及时刷新
                switch(choose)
                {
                        case 1://开发人员信息
                                printf("2017年，海同培训班！\n");

				printf("按Enter继续!\n");
				getchar();
                                break;
			
                        case 2://开机动画图标
				display_welcome(gImage);
				printf("按Enter继续!\n");
				getchar();
                                break;
                        case 3://二维码
			        display_erweima(gImage_erweima);
				printf("按Enter继续!\n");
				getchar();
                                break;

                        case 0:
                                return;
                        default:
                                printf("输入错误!\n");
                                break;
                }
        }
}


void game_control()//game
{
        int choose = 1;
        while(1)
        {
                sleep(1);
                //system("clear");
                
		choose=key_udrl(choose,4,2);//按键控制，以及及时刷新
		
                switch(choose)
                {
                        case 1://简单石头布
                                gamejsb();
				getchar();
                                break;
                        case 2://贪吃是
                               
                                break;
                        case 3://坦克
                               
                                break;
                    
                        case 0:
                                return;
                        default:
                                printf("输入错误!\n");
                                break;
                }
        }
}

void sort_control(Ulink* user_head)//sort
{
        int choose = 1;
        while(1)
        {
                sleep(1);
                //system("clear");
                


		choose=key_udrl(choose,3,4);                


                switch(choose)
                {
                        case 1://按照姓名排序
                                printf("按照姓名排序\n\n");
				printf("请决定正序（1）还是逆序（-1）");
				int mode=0;
				scanf("%d",&mode);
				sort_all_user_by_name(user_head,mode);//通过姓名排序
				printf("按Enter继续！\n");
				getchar();
				
                                break;
                        case 2://按照id排序
				printf("按照ID排序\n\n");
                                printf("请决定正序（1）还是逆序（-1）");
                                mode=0;
                                scanf("%d",&mode);
                                sort_all_user_by_id(user_head,mode);//通过ID排序           
                                printf("按Enter继续！\n");
                                getchar();
                                break;

                        case 0:
                                return;
                        default:
                                printf("输入错误!\n");
                                break;
                }
        }
}



void main_menu_control(Ulink* user_head,Tlink* tic_head,Ilink* iss_head)//主菜单控制层
{
	int choose = 1;
	if(user_head == NULL)
	{
		printf("头节点为空\n");
		return;
	}
	
	
		sleep(1);
//+++++++++++++++++++ 开机 欢迎界面 ++++++++++++++++++++++//
        display_welcome(gImage);
//      display_erweima(gImage_erweima);

//++++++++++++++++++  程序正常运行  ++++++++++++++++++++++//
	while(1)
	{
		//轻微延时
		sleep(1);
		//用户控制（死循环），可跳出
		choose=key_udrl(choose,6,1);//按键控制，以及及时刷新		

		//程序响应
		switch(choose)
		{
			case 1://用户登录,需要对彩票进行操作，这个地方必须传入tic_head(否则会导致段错误)
				user_login(user_head,tic_head,iss_head);  

				break; //跳出switch，继续循环
			case 2://用户注册
				user_regist(user_head);

				break;//跳出switch，继续循环
			case 3://公证员登录
				notery_login(user_head,tic_head,iss_head);

				break;//跳出switch，继续循环

			case 4://管理员登录
				admin_login(user_head,tic_head,iss_head); //输入账号和密码

				break;//跳出switch，继续循环
			case 5://其他信息
				others_control();			
				break;
			case 0://退出系统
				system("clear");
				return;  //程序结束
			default:
				printf("input error!\n");
				break;
		}
	}
}

void admin_menu_control(Ulink* user_head,Tlink* tic_head,Ilink* iss_head)//管理员控制层
{
	if(user_head == NULL)
	{
		printf("头节点为空!\n");
		return;
	}
	int choose = 1;
	while(1)
	{
		sleep(1);

		choose=key_udrl(choose,9,5);//按键控制，以及及时刷新

		switch(choose)
		{
			case 1://c查看所有用户
				print_all_user(user_head);
				break;
			case 2://查找彩民
				print_one_info(user_head);
				break;
			case 3://发行彩票
				publish_ticket(iss_head);
				break;
			case 4://排序
				sort_control(user_head);//sort
			//	f_save_student_message(user_head);
				break;
			case 5://
        			printf("开始发放奖金！！！\n");
              			sleep(1);
        			distribute_money(user_head,tic_head,iss_head);
        			stop();
				break;
			case 6://
				manage_totalmoney(iss_head);			

				break;
			case 7://
				delete_user(user_head);//删除函数
				break;
			case 8://查看所有的彩票购买信息
				print_all_ticket(tic_head);
				break;
		
			case 0:
				return;
			default:
				printf("输入错误!\n");
				break;
		}
	}
}

void user_menu_control(Ulink* user_head,Ulink* user_pre,Tlink* tic_head,Ilink* iss_head)//学生菜单控制层
{
	int choose = 1;
	while(1)
	{
		sleep(1);


		choose=key_udrl(choose,6,6);
 

		switch(choose)
		{
			case 1://查看个人信息
				print_personal_info(user_pre);
				break;
			case 2://修改密码
				change_personal_password(user_head,user_pre);//修改自己密码
				break;
			case 3://账户充值
				recharge_balance(user_head,user_pre);//充值
				break;
			case 4://购买彩票
				buy_ticket(user_pre,tic_head,iss_head);
				break;
				
			case 5://查看历史购买记录
				print_personal_ticket(tic_head,user_pre);
				break;		
			case 0:
				return;
			default:
				printf("error!\n");
				break;
		}
	}
}

void notery_menu_control(Ulink* user_head,Tlink* tic_head,Ilink* iss_head)//管理员控制层
{
        if(user_head == NULL)
        {
                printf("头节点为空!\n");
                return;
        }
        int choose = 1;
        while(1)
        {
                sleep(1);
                
		choose=key_udrl(choose,4,7);
		
                switch(choose)
                {  
                        case 1://开奖
			run_the_lottery(user_head,tic_head,iss_head);

                                break;
                        case 2://查看历史发行记录
				print_all_issue(iss_head);
				
                                break;
                        case 3://休闲
				game_control();
                                break;
                        case 0:
                                return;
                        default:
                                printf("输入错误!\n");
                                break;
                }
        }
}


