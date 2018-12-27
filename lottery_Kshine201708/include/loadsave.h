#ifndef LOSA_H_
#define LOSA_H_

//将文本中保存的数据，读取，给程序初始化
void f_load_others();//加载函数
void f_load_user(Ulink* head);//加载函数
void f_load_tic(Tlink* head);//加载函数
void f_load_iss(Ilink* head);//加载函数

//保存本次使用做的改变
void f_save_others();//保存函数
void f_save_user(Ulink* head);//保存函数
void f_save_iss(Ilink* head);//保存函数
void f_save_tic(Tlink* head);//保存函数



#endif
