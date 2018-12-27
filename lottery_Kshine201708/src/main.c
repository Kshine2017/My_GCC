#include <stdio.h>
#include <stdlib.h>
#include "lottery.h"
#include "lotcontrol.h"
#include "loadsave.h"

#include "freelink.h"

int main(void)
{
	//为本次程序的运行，创建头结点
	Ulink* user_head = (Ulink*)calloc(1,sizeof(Ulink));
	Tlink* tic_head=(Tlink*)calloc(1,sizeof(Tlink));
	Ilink* iss_head=(Ilink*)calloc(1,sizeof(Ilink));


	tic_head->next=NULL; //特殊处理:


	//读取历史数据
	f_load_others();//加载函数
	f_load_user(user_head);//加载函数
	f_load_tic(tic_head);//加载函数
	f_load_iss(iss_head);//加载函数

	//将有数据的链表传入总程序
	main_menu_control(user_head,tic_head,iss_head);
	

	//保存
	f_save_others();//保存函数
	f_save_user(user_head);//保存函数
	f_save_iss(iss_head);//保存函数
	f_save_tic(tic_head);//保存函数

	//释放
	printf("正在释放链表空间！\n");
	free_all_node_user(user_head);
	free_all_node_tic(tic_head);
	free_all_node_iss(iss_head);
	printf("释放成功！\n");
	
	return 0;
}

