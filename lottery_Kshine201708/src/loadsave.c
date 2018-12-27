#include "lottery.h"
#include "loadsave.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void f_load_others()//加载函数
{

        //打开文件，读取二进制文件
        FILE* fp = fopen("common.bin","rb");
        if(fp == NULL)
        {
                system("touch common.bin");
                return;
        }

        //------------------------------------------
        printf("--->读取用户计数信息---\n");
        fread(&userhistorycount,sizeof(int),1,fp);
        printf("--->读取奖金设置信息---\n");
        fread(bonus_select,sizeof(int),5,fp);




        printf("基本信息加载成功!\n");
        //------------------------------------------
        fclose(fp);
        fp = NULL;
}



void f_load_user(Ulink* head)//加载函数
{
        if(head == NULL)
        {
                printf("加载数据时，头节点为空!\n");
                return;
        }
        //打开文件，读取二进制文件
        FILE* fp = fopen("user.bin","rb");
        if(fp == NULL)
        {
                system("touch user.bin");
                return;
        }
        //定义中转数据块
        User data;//
        memset(&data,0,sizeof(data));
        while(1)
        {
                printf("--->读取用户链表信息---\n");
                int res = fread(&data,sizeof(User),1,fp);
                if(res < 1)
                {
                        break;
                }
                insert_after(head,data); //一个节点一个节点的读取插后
        }
        printf("用户文件加载成功!\n");
        fclose(fp);
        fp = NULL;
}



void f_load_tic(Tlink* head)//加载函数
{
        if(head == NULL)
        {
                printf("加载数据时，头节点为空!\n");
                return;
        }
        //打开文件，读取二进制文件
        FILE* fp = fopen("tic.bin","rb");
        if(fp == NULL)
        {
                system("touch tic.bin");
                return;
        }
        //定义中转数据块
        Tic data;//
        memset(&data,0,sizeof(data));
        while(1)
        {
                printf("--->读取彩票链表信息---\n");
                int res = fread(&data,sizeof(Tic),1,fp);
                if(res < 1)
                {
                        break;
                }
                insert_after_T(head,data); //一个节点一个节点的读取插后
        }
        printf("彩票文件加载成功!\n");
        fclose(fp);
        fp = NULL;
}

void f_load_iss(Ilink* head)//加载函数
{
        if(head == NULL)
        {
                printf("加载数据时，头节点为空!\n");
                return;
        }
        //打开文件，读取二进制文件
        FILE* fp = fopen("iss.bin","rb");
        if(fp == NULL)
        {
                system("touch iss.bin");
                return;
        }
        //定义中转数据块
        Iss data;//
        memset(&data,0,sizeof(data));
        while(1)
        {
                printf("--->读取发行链表信息---\n");
                int res = fread(&data,sizeof(Iss),1,fp);
                if(res < 1)
                {
                        break;
                }
                insert_after_I(head,data); //一个节点一个节点的读取插后
        }
        printf("发行文件加载成功!\n");
        fclose(fp);
        fp = NULL;
}



void f_save_others()//保存函数
{
        FILE* fp = fopen("user.bin","wb");
        if(fp == NULL)
        {
                printf("打开文件失败!\n");
                return;
        }
        //------------------------------------------
        printf("--->写入用户计数信息---\n");
        fwrite(&userhistorycount,sizeof(int),1,fp);
        printf("--->写入奖金设置信息---\n");
        fwrite(bonus_select,sizeof(int),5,fp);


        //-----------------------------------------
        printf("文件保存成功!\n");
        fclose(fp);
        fp = NULL;
}


void f_save_user(Ulink* head)//保存函数
{
        if(head == NULL)
        {
                printf("头节点为空!\n");
                return;
        }
        FILE* fp = fopen("user.bin","wb");
        if(fp == NULL)
        {
                printf("打开文件失败!\n");
                return;
        }
        head = head->next;
        while(head != NULL)
        {
                fwrite(&head->data,sizeof(User),1,fp);
                head = head->next;
        }
        printf("文件保存成功!\n");
        fclose(fp);
        fp = NULL;
}

void f_save_tic(Tlink* head)//保存函数
{
        if(head == NULL)
        {
                printf("头节点为空!\n");
                return;
        }
        FILE* fp = fopen("tic.bin","wb");
        if(fp == NULL)
        {
                printf("打开文件失败!\n");
                return;
        }
        head = head->next;
        while(head != NULL)
        {
                fwrite(&head->data,sizeof(Tic),1,fp);
                head = head->next;
        }
        printf("文件保存成功!\n");
        fclose(fp);
        fp = NULL;
}


void f_save_iss(Ilink* head)//保存函数
{
        if(head == NULL)
        {
                printf("头节点为空!\n");
                return;
        }
        FILE* fp = fopen("iss.bin","wb");
        if(fp == NULL)
        {
                printf("打开文件失败!\n");
                return;
        }
        head = head->next;
        while(head != NULL)
        {
                fwrite(&head->data,sizeof(Iss),1,fp);
                head = head->next;
        }
        printf("文件保存成功!\n");
        fclose(fp);
        fp = NULL;
}


