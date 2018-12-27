#include <stdio.h>
#include "stuview.h"

void main_menu(void)//主菜单
{
	printf("1.管理员登录\n");
	printf("2.学生登录\n");
	printf("0.退出\n");
}

void admin_menu(void)//管理员菜单
{
	printf("1.添加学生\n");
	printf("2.删除学生\n");
	printf("3.查看所有学生\n");
	printf("4.排序学生\n");
	printf("0.返回上一级\n");
}

void student_menu(void)//学生菜单
{
	printf("1.查看自己成绩\n");
	printf("2.查看自己排名\n");
	printf("3.修改自己密码\n");
	printf("0.返回上一级\n");
}
