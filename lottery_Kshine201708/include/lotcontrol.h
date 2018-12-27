#ifndef _LOT_CONTROL_H_
#define _LOT_CONTROL_H_


#include "lottery.h"

//函数原型声明
//1.主界面控制
void main_menu_control(Ulink* user_head,Tlink* tic_head,Ilink* iss_head);

//1.1管理员
void admin_menu_control(Ulink* user_head,Tlink* tic_head,Ilink* iss_head);//管理员控制层

//1.2用户
void user_menu_control(Ulink* user_head,Ulink* user_pre,Tlink* tic_head,Ilink* iss_head);//学生菜单控制层

//1.3公证员
void notery_menu_control(Ulink* user_head,Tlink* tic_head,Ilink* iss_head);

//1.3.2公证员 休闲游戏
void game_control(void);//game

//1.4信息展示
void others_control(void);//info

//1.1.5管理员排序
void sort_control(Ulink* user_head);//sort
#endif
