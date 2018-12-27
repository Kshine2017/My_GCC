#include "student.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stucontrol.h"
void admin_login(StuLink* head)//管理员登录
{
	if(head == NULL)
	{
		printf("头节点为空!\n");
		return;
	}
	char admin_name[20] = "";
	char admin_pass[20] = "";
	printf("请输入管理员账户名:");
	scanf("%s",admin_name);
	printf("请输入管理员密码:");
	scanf("%s",admin_pass);
	if(0 == strcmp(admin_name,"admin") && 0 == strcmp(admin_pass,"admin"))
	{
		printf("管理员登录成功!\n");
		admin_menu_control(head);
		return;
	}
	printf("管理员账户密码错误,登录失败!\n");
	return;
}
StuLink* create_node(Stu data)//创建新节点
{
	StuLink* newNode = (StuLink*)calloc(1,sizeof(StuLink));
	newNode->data = data;//数据域赋值
	newNode->next = NULL;
	return newNode;
}
void insert_after(StuLink* head,Stu data)//后插
{
	if(NULL == head)
	{
		printf("头节点为空!\n");
		return;
	}
	StuLink* newNode = create_node(data);
	while(head->next != NULL)//找到尾节点
	{
		head = head->next;
	}
	head->next = newNode;
}
StuLink* select_front_node(StuLink* head,char* name)//查找函数，返回当前节点前一个节点
{
	if(NULL == head)
	{
		printf("头节点为空!\n");
		return NULL;
	}
	StuLink* pre = head;
	head = head->next;
	while(head != NULL)
	{
		if(0 == strcmp(head->data.name,name))
		{
			return pre;
		}
		pre = head;
		head = head->next;
	}
	return NULL;
}
void init_student_message(StuLink* head)//添加学生
{
	if(head == NULL)
	{
		printf("头节点为空!\n");
		return;
	}
	Stu data;//定义结构体变量接受输入信息
	memset(&data,0,sizeof(data));//初始化
	printf("请输入学生id:");
	scanf("%d",&data.id);
	printf("请输入学生姓名:");
	scanf("%s",data.name);
	StuLink* pre = select_front_node(head,data.name);
	if(pre != NULL)
	{
		printf("该学生已经存在!\n");
		return;
	}
	printf("请输入学生密码:");
	scanf("%s",data.password);
	printf("请输入学生语文，数学成绩:");
	scanf("%f%f",&data.score[0],&data.score[1]);
	data.score[2] = data.score[0] + data.score[1];
	insert_after(head,data);
	printf("注册成功!\n");
	return;
}
void print_all_student_message(StuLink* head)//查看所有成员
{
	if(head == NULL)
	{
		printf("头节点为空\n");
		return;
	}
	head = head->next;
	printf("id\t姓名\t语文\t数学\t总分\n");
	while(head != NULL)
	{
		printf("%d\t%s\t%.2f\t%.2f\t%.2f\n",head->data.id,head->data.name,\
			head->data.score[0],head->data.score[1],head->data.score[2]);
		head = head->next;
	}
}
void delete_node(StuLink* head,char* name)//删除逻辑
{
	if(head == NULL)
	{
		printf("头节点为空!\n");
		return;
	}
	StuLink* pre = select_front_node(head,name);
	if(pre == NULL)
	{
		printf("该用户不存在!\n");
		return;
	}
	StuLink* del = pre->next;//要删除的节点
	pre->next = del->next;//断开重新链接
	free(del);
	del = NULL;
	printf("删除成功!\n");
}
void delete_stduent_message(StuLink* head)//删除函数
{
	char name[20] = "";
	printf("请输入要删除的学生姓名:");
	scanf("%s",name);
	delete_node(head,name);
}
void free_all_node(StuLink* head)//释放
{
	if(head == NULL)
	{
		printf("头节点为空!\n");
		return;
	}
	StuLink* pre = NULL;
	while(NULL != head)
	{
		pre = head->next;
		free(head);
		head = pre;
	}
}
void sort_all_student_message(StuLink* head)//排序
{
	if(head == NULL)
	{
		printf("头节点为空!\n");
		return ;
	}
	int length = 0;
	int i = 0,j = 0;
	StuLink* save = head;
	head = head->next;
	while(head != NULL)
	{
		length++;
		head = head->next;
	}
	for(i = 0; i < length - 1; ++i)
	{
		head = save->next;
		for(j = 0; j < length - 1 - i; ++j)
		{
			if(head->data.score[2] < head->next->data.score[2])
			{
				Stu temp = head->data;
				head->data = head->next->data;
				head->next->data = temp;
			}
			head = head->next;
		}
	}
	printf("排序成功，请前往查看!\n");
	return ;
}
void f_load_student_message(StuLink* head)//加载函数
{
	if(head == NULL)
	{
		printf("头节点为空!\n");
		return;
	}
	FILE* fp = fopen("stu.bin","rb");
	if(fp == NULL)
	{
		system("touch stu.bin");
		return;
	}
	Stu data;//
	memset(&data,0,sizeof(data));
	while(1)
	{
		int res = fread(&data,sizeof(Stu),1,fp);		
		if(res < 1)
		{
			break;
		}
		insert_after(head,data);
	}
	printf("文件加载成功!\n");
	fclose(fp);
	fp = NULL;
}
void f_save_student_message(StuLink* head)//保存函数
{
	if(head == NULL)
	{
		printf("头节点为空!\n");
		return;
	}
	FILE* fp = fopen("stu.bin","wb");
	if(fp == NULL)
	{
		printf("打开文件失败!\n");
		return;
	}
	head = head->next;
	while(head != NULL)
	{
		fwrite(&head->data,sizeof(Stu),1,fp);
		head = head->next;
	}
	printf("文件保存成功!\n");
	fclose(fp);
	fp = NULL;
}
void student_login(StuLink* head)//学生登录 
{
	if(head == NULL)
	{
		printf("头节点为空!\n");
		return;
	}
	Stu data;
	memset(&data,0,sizeof(data));
	printf("请输入用户名:");
	scanf("%s",data.name);
	StuLink* pre = select_front_node(head,data.name);
	if(pre == NULL)
	{
		printf("无该用户信息!\n");
		return;
	}
	printf("请输入密码:");
	scanf("%s",data.password);
	if(0 == strcmp(data.password,pre->next->data.password))
	{
		printf("登录成功!\n");
		student_menu_control(head,pre);
	}else{
		printf("用户名密码错误，登录失败!\n");
		return;
	}
}
void select_mine_message(StuLink* head,StuLink* pre)//查看个人信息
{
	printf("id\t姓名\t语文\t数学\t总分\n");
	printf("%d\t%s\t%.2f\t%.2f\t%.2f\n",pre->next->data.id,\
		pre->next->data.name,pre->next->data.score[0],\
		pre->next->data.score[1],pre->next->data.score[2]);
}
void change_mine_password(StuLink* head,StuLink* pre)//修改自己密码
{
	if(head == NULL)
	{
		printf("头节点为空!\n");
		return;
	}
	char newPass[20] = "";
	char newPassAgain[20] = "";
	printf("请输入新密码:");
	scanf("%s",newPass);
	if(0 == strcmp(pre->next->data.password,newPass))
	{
		printf("旧密码与新密码不能一致，修改失败!\n");
		return;
	}
	printf("请再次输入新密码:");
	scanf("%s",newPassAgain);
	if(0 == strcmp(newPass,newPassAgain))
	{
		strcpy(pre->next->data.password,newPass);
		printf("密码修改成功,请重新登录!\n");
	//	main_menu_control(head);
		return;
	}
	printf("两次密码不一致，修改失败!\n");
	return;
}
void select_mine_rank(StuLink* head,StuLink* pre)//查看自己排名
{
	if(head == NULL)
	{
		printf("头节点为空!\n");
		return;
	}
	int rank = 1;
	head = head->next;
	while(head != NULL)
	{
		if(head-> data.score[2] > pre->next->data.score[2])
		{
			rank++;
		}
		head = head->next;
	}	
	printf("您的班级排名为:%d\n",rank);
}
