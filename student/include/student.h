#ifndef _STUDENT_H_
#define _STUDENT_H_

typedef struct student{
	int id;
	char name[20];
	char password[20];
	float score[3];
}Stu;

typedef struct studentLink{
	Stu data;//数据域
	struct studentLink* next;
}StuLink;

void admin_login(StuLink* head);//管理员登录
StuLink* create_node(Stu data);//创建新节点
void insert_after(StuLink* head,Stu data);//后插
StuLink* select_front_node(StuLink* head,char* name);//查找函数，返回当前节点前一个节点
void init_student_message(StuLink* head);//添加学生
void print_all_student_message(StuLink* head);//查看所有成员
void delete_node(StuLink* head,char* name);//删除逻辑
void delete_stduent_message(StuLink* head);//删除函数
void free_all_node(StuLink* head);//释放
void sort_all_student_message(StuLink* head);//排序

void student_login(StuLink* head);//学生登录 
void select_mine_message(StuLink* head,StuLink* pre);//查看个人信息
void change_mine_password(StuLink* head,StuLink* pre);//修改密码
void select_mine_rank(StuLink* head,StuLink* pre);//查看自己排名
void f_load_student_message(StuLink* head);//加载函数
void f_save_student_message(StuLink* head);//保存函数
#endif
