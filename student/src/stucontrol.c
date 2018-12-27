#include "stucontrol.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "stuview.h"
void main_menu_control(StuLink* head)//主菜单控制层
{
	int choose = 0;
	if(head == NULL)
	{
		printf("头节点为空\n");
		return;
	}
	while(1)
	{
		sleep(1);
		system("clear");
		main_menu();
		printf("请输入选择:");
		scanf("%d",&choose);
		if(getchar() != '\n')
		{
			printf("输入格式错误!\n");
			continue;
		}
		switch(choose)
		{
			case 1://管理员登录
				admin_login(head);
				break;
			case 2://学生登录
				student_login(head);
				break;
			case 0:
				f_save_student_message(head);
				free_all_node(head);
				return;
			default:
				printf("input error!\n");
				break;
		}
	}
}

void admin_menu_control(StuLink* head)//管理员控制层
{
	if(head == NULL)
	{
		printf("头节点为空!\n");
		return;
	}
	int choose = 0;
	while(1)
	{
		sleep(1);
		system("clear");
		admin_menu();
		printf("请输入选择:");
		scanf("%d",&choose);
		if(getchar() != '\n')
		{
			printf("输入格式错误!\n");
			continue;
		}
		switch(choose)
		{
			case 1://添加学生
				init_student_message(head);
				f_save_student_message(head);
				break;
			case 2://删除学生
				delete_stduent_message(head);
				f_save_student_message(head);
				break;
			case 3://查看所有学生
				print_all_student_message(head);
				break;
			case 4://排序学生
				sort_all_student_message(head);
				f_save_student_message(head);
				break;
			case 0:
				return;
			default:
				printf("输入错误!\n");
				break;
		}
	}
}

void student_menu_control(StuLink* head,StuLink* pre)//学生菜单控制层
{
	int choose = 0;
	while(1)
	{
		sleep(1);
		system("clear");
		student_menu();
		printf("请输入选择:");
		scanf("%d",&choose);
		if(getchar() != '\n')
		{
			printf("输入错误!\n");
			continue;
		}
		switch(choose)
		{
			case 1://查看成绩
				select_mine_message(head,pre);
				break;
			case 2://查看自己排名
				select_mine_rank(head,pre);
				break;
			case 3://修改密码
				change_mine_password(head,pre);
			//	break;
				return;
			case 0:
				return;
			default:
				printf("error!\n");
				break;
		}
	}
}
