#include "lottery.h"
#include "freelink.h"

#include <stdio.h>
#include <stdlib.h>


void free_all_node_user(Ulink* head)//释放
{
        if(head == NULL)
        {
                printf("释放用户链表，头节点为空!\n");
                return;
        }
        Ulink* pre = NULL;
        while(NULL != head)
        {
                pre = head->next;
                free(head);
                head = pre;
        }
}
void free_all_node_tic(Tlink* head)//释放
{
        if(head == NULL)
        {
                printf("释放彩票链表，头节点为空!\n");
                return;
        }
        Tlink* pre = NULL;
        while(NULL != head)
        {
                pre = head->next;
                free(head);
                head = pre;
        }
}

void free_all_node_iss(Ilink* head)//释放
{
        if(head == NULL)
        {
                printf("释放发行链表，头节点为空!\n");
                return;
        }
        Ilink* pre = NULL;
        while(NULL != head)
        {
                pre = head->next;
                free(head);
                head = pre;
        }
}



