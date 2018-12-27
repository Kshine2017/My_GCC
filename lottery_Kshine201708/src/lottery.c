#include "lottery.h"
#include "lotcontrol.h"
#include "fun.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

int bonus_select[5]={20,100,500,2000,10000};
int userhistorycount=0; //需要文件初始化

void print_all_issue(Ilink* iss_head)
{
	system("clear");
        printf("~~~~~~~~历史发行信息查询~~~~~~~~\n");

	if(iss_head==NULL)
	{
		printf("输出发行信息时，头节点为空！\n");
		return;
	}
	iss_head=iss_head->next;
	int i=1;
	printf("\n------------发行信息-----------\n\n");
	while(iss_head)
	{
		printf("第%d期\n",i++);
		printf("发行期号：%s\n",iss_head->data.issue);	
		printf("彩票单价：%d\n",iss_head->data.price);
		printf("售出总数：%d\n",iss_head->data.sellcount);
		printf("销售额  ：%d\n",iss_head->data.price*iss_head->data.sellcount);
		printf("奖池奖金：%d\n",iss_head->data.totalmoney);
		if(iss_head->data.state==0)
		{
			printf("开奖状态：未开奖\n");
			printf("中奖号码：\n\t无");
		}
		else
		{
			printf("开奖状态：已开奖\n");
			printf("中奖号码：\n");
			printf("%d\t%d\t%d\t%d\t%d\n",\
						iss_head->data.num[0],\
						iss_head->data.num[1],\
						iss_head->data.num[2],\
						iss_head->data.num[3],\
						iss_head->data.num[4]);
		}
		
		

		iss_head=iss_head->next;

		
	}


	stop();
	return;
	
}



void delete_node(Ulink* user_head,char* name)//删除逻辑
{
        if(user_head == NULL)
        {
                printf("删除时，用户头节点为空!\n");
                return;
        }
        Ulink* user_pre = select_front_node(user_head,name);
        if(user_pre == NULL)
        {
                printf("该用户不存在!\n");
                return;
        }
        Ulink* user_del = user_pre->next;//要删除的节点
        user_pre->next = user_del->next;//断开重新链接

        free(user_del);
        user_del = NULL;
	userhistorycount++;//用户删除计数，用于用户ID的防重复
        printf("删除成功!\n");
}
void delete_user(Ulink* user_head)//删除函数
{
	system("clear");
        printf("~~~~~~~~删除用户信息~~~~~~~~\n");
        char name[20] = "";
        printf("请输入要删除的用户姓名:");
        scanf("%s",name);
        delete_node(user_head,name);
}

void manage_totalmoney(Ilink* iss_head)
{
	system("clear");
        printf("~~~~~~~~奖池信息查看~~~~~~~~\n");
	if(iss_head==NULL)
	{
		printf("管理奖池时，发行链表头结点为空！\n");
		return;
	}
	//iss_head=iss_head->next;//站在第一个节点上
	while(iss_head->next)//一直走到尾节点
	{
		iss_head=iss_head->next;
	}
	printf("当前奖池剩余金额：%d\n",iss_head->data.totalmoney);
	char ch=0;
	while(1)
	{
		printf("是否进行奖池充值？（y or n）\n");
		scanf("%c",&ch);
		if(ch=='n'||ch=='N')
		{
			break;
		}
		if(ch=='y'||ch=='Y')
		{	
			printf("请输入充值得金额：");
			int tem=0;
			scanf("%d",&tem);
			iss_head->data.totalmoney += tem;
			printf("充值后，奖池剩余金额：%d\n",iss_head->data.totalmoney);
			break;
		}
	}






}

void sort_all_user_by_name(Ulink* user_head,int mode)//通过姓名排序,//mode 控制正序逆序
{
	system("clear");
        printf("~~~~~~~~按照姓名排序~~~~~~~~\n");
        if(user_head == NULL)
        {
                printf("排序时，用户头节点为空!\n");
                return ;
        }
	if(mode!=1&&mode!=-1)
	{
		printf("排序模式选择错误\n");
		return;
	}
        int length = 0;
        int i = 0,j = 0;
        Ulink* user_save = user_head;
        user_head = user_head->next;
	//测量出用户链表的节点个数
        while(user_head != NULL)
        {
                length++;
                user_head = user_head->next;
        }
	//使用冒泡排序法
        for(i = 0; i < length - 1; ++i)
        {
                user_head = user_save->next;//每次外循环都是从第一个节点开始
                for(j = 0; j < length - 1 - i; ++j)
                {
			//用于调试，监督交换数据的过程
			printf("%s %s  %d\n",   user_head->data.name,\
						user_head->next->data.name,\
						strcmp(user_head->data.name,user_head->next->data.name));


			if(mode==1)//正序abcdefg。。。。
			{
                        	if(strcmp(user_head->data.name,user_head->next->data.name)>0)//比较姓名字符串
                        	{
					printf("交换数据\n");
                                	User temp = user_head->data;			//只需要交换节点的数据就行
                                	user_head->data = user_head->next->data;
                                	user_head->next->data = temp;
                        	}
			}
			if(mode==-1)//逆序
			{
				if(strcmp(user_head->data.name,user_head->next->data.name)<0)//比较姓名字符串
                                {
                                        printf("交换数据\n");
                                        User temp = user_head->data;                    //只需要交换节点的数据就行
                                        user_head->data = user_head->next->data;
                                        user_head->next->data = temp;
                                }


			}

			printf("下一组\n");
                        user_head = user_head->next;	//向后移动，下一组
                }
        }
        printf("按照姓名排序成功!\n");
        return ;
}

void sort_all_user_by_id(Ulink* user_head,int mode)//通过id排序
{
	system("clear");
        printf("~~~~~~~~按照ID排序~~~~~~~~\n");
        if(user_head == NULL)
        {
                printf("排序时，用户头节点为空!\n");
                return ;
        }

	if(mode!=1&&mode!=-1)
        {
                printf("排序模式选择错误\n");
                return;
        }

        int length = 0;
        int i = 0,j = 0;
        Ulink* user_save = user_head;
        user_head = user_head->next;
        //测量出用户链表的节点个数
        while(user_head != NULL)
        {
                length++;
                user_head = user_head->next;
        }
        //使用冒泡排序法
        for(i = 0; i < length - 1; ++i)
        {
                user_head = user_save->next;//每次外循环都是从第一个节点开始
                for(j = 0; j < length - 1 - i; ++j)
                {	
			char str_pre[10];
			strcpy(str_pre,user_head->data.id);
			str_pre[0]='0';
			str_pre[1]='0';

			char str_bac[10];
			strcpy(str_pre,user_head->next->data.id);
			str_bac[0]='0';
			str_bac[1]='0';
			if(mode==1)//正序
			{
                        	if(strcmp(str_pre,str_bac)>0)//比较id
                        	{
                                	User temp = user_head->data;                    //只需要交换节点的数据就行
                                	user_head->data = user_head->next->data;
                               		user_head->next->data = temp;
                        	}
			}
			if(mode==-1)
			{
				if(strcmp(str_pre,str_bac)<0)//比较id
                                {
                                        User temp = user_head->data;                    //只需要交换节点的数据就行
                                        user_head->data = user_head->next->data;
                                        user_head->next->data = temp;
                                }


			}
                        user_head = user_head->next;    //向后移动，下一组
                }
        }
        printf("按照 ID 排序成功!\n");
        return ;
}


void notery_login(Ulink* user_head,Tlink* tic_head,Ilink* iss_head)
//管理员登录(顺便传入有数据的链表)
{
	system("clear");
	printf("~~~~~~~~公证员登录~~~~~~~~\n");
	

        if(user_head == NULL)
        {
                printf("头节点为空!\n");
                return;
        }

        char notery_name[20] = "";
        char notery_pass[20] = "";
        printf("请输入公证员账户名:");
        scanf("%s",notery_name);
        printf("请输入公证员密码:");
       // scanf("%s",notery_pass);
	secret_num(notery_pass);
	
        if(0 == strcmp(notery_name,"notery") && 0 == strcmp(notery_pass,"notery"))
        {      
		int flag=identifying_code();
		if(flag==0)
		{
                	printf("公证员登录成功!\n");
               	 	notery_menu_control(user_head,tic_head,iss_head);
			return;
		}
		printf("验证码错误\n");
                return;
        }
        printf("账号密码错误，登录失败!\n");
	stop();
        return;
}







void admin_login(Ulink* head,Tlink* tic_head,Ilink* iss_head)
//管理员登录(顺便传入有数据的链表)
{
	system("clear");
        printf("~~~~~~~~管理员登录~~~~~~~~\n");

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
	//scanf("%s",admin_pass);
	secret_num(admin_pass);

	if(0 == strcmp(admin_name,"admin") && 0 == strcmp(admin_pass,"admin"))
	{
	
		int flag=identifying_code();
		if(flag==0)
		{
			printf("管理员登录成功!\n");
			admin_menu_control(head,tic_head,iss_head);
			return;
		}
		printf("验证码错误!\n");
		return;
		
	}
	printf("管理员账户密码错误,登录失败!\n");
	stop();
	return;
}





void user_login(Ulink* head,Tlink* tic_head,Ilink* iss_head)
//用户登录(顺便传入有数据的链表)
{
	system("clear");
        printf("~~~~~~~~用户  登录~~~~~~~~\n");
        if(head == NULL)
        {
                printf("头节点为空!\n");
                return;
        }

        char user_name[20] = "";
        char user_pass[20] = "";
        printf("请输入账户名:");
        scanf("%s",user_name);
        	
	//找到当前节点的前一个节点
	Ulink* pre=select_front_node(head,user_name);
	if(pre==NULL)	
	{
		printf("不存在该用户！\n");
		return;
	}
	else
	
	printf("通关密码：");
	//printf("请输入密码:");
        //scanf("%s",user_pass);
	secret_num(user_pass);
	
       	if( strcmp(user_pass,pre->next->data.password)==0 )
        {
		int flag=identifying_code();
		if(flag==0)
		{
                	printf("您已成功登录!\n");
                	user_menu_control(head,pre,tic_head,iss_head);
                	return;	//成功登录之后，进行完用户操作，可以返回主界面了
		}
		printf("验证码错误\n");
		return;
	}
	//--------------------------------------//
        printf("账户或者密码错误,登录失败!\n");
	stop();
        return;
	
}



void user_regist(Ulink* user_head)
//用户注册(顺便传入有数据的链表)，（需要自动生成ID号，需要输入自己的姓名和密码）
{
	system("clear");
        printf("~~~~~~~~新用户注册~~~~~~~~\n");
	printf("欢迎使用本系统！\n");

        if(user_head == NULL)
        {
                printf("头节点为空!\n");
                return;
        }
	
	User data;//定义结构体变量，接受输入的值。
	memset(&data,0,sizeof(User));

        printf("请输入申请的账户名:");
        scanf("%s",data.name);
	
	Ulink* pre = select_front_node(user_head,data.name); //传入数据链，传入需要查找的用户名
        if(pre != NULL)  //如果找到，会返回同名节点的前一个节点的地址。
        {
                printf("该用户名已经存在!\n");
                return;  
        }
	
	printf("请输入初始密码:");
        scanf("%s",data.password);	

	//自动生成 char id[10]
	get_userid(user_head,&data);	


	insert_after(user_head,data);    //插入新注册的数据节点到链表最后
        printf("注册成功!\n");
	stop();
	return;
}
int count_user(Ulink* user_head)
{
	int num=0;
	while(user_head->next)
	{
		num++;
		user_head=user_head->next;
	}
	return num;
}
void get_userid(Ulink* user_head,User *data)
{
	int num=0;
	num=count_user(user_head)+1+userhistorycount;//注册的顺序号，外加已经删除的用户
//	char str[4]="";
//	itoa(num,str,16);

	data->id[0]=data->name[0];
	data->id[1]='-';
	data->id[5]='0'+num%10;
	num/=10;
	data->id[4]='0'+num%10;
	num/=10;
	data->id[3]='0'+num%10;
	num/=10;
	data->id[2]='0'+num%10;
	data->id[6]='\0';	
}

void print_all_user(Ulink* head)
{
	system("clear");
        printf("~~~~~~~~查看全部用户~~~~~~~~\n");
	if(head==NULL)
	{
		printf("（显示全部用户时）发现头结点为空！\n");
		return ;
	}

	head=head->next;//从第一个节点开始
	int i=1;
	while(head!=NULL)
	{
		printf("%d.  ID:%s\t姓名:%s\t余额:%d\n",i,head->data.id,head->data.name,head->data.balance);
		head=head->next;
		i++;
	}
	stop();

}


//传入数据链和需要查找的账户名称,
//查找函数，返回当前节点前一个节点
Ulink* select_front_node(Ulink* head,char* name)
{
	if(head==NULL)
	{
		printf("（向前检索时）发现头结点为空!\n");
		return NULL;
	}
	
	Ulink* pre = head;//双指针，pre 始终在head前一个

	head=head->next; //从第一个有效数据节点开始，（此时pre成了头指针）
	while(head!=NULL)
	{
		if(strcmp(head->data.name,name)==0)//找到同名的节点head
		{
			return pre;  //返回上一个节点，方便对当前节点进行操作。
		}
		pre=head;
		head=head->next;

	}
	return NULL;   //未找到，返回空
	
}
Ulink* create_node(User data)
{
	Ulink* newnode=(Ulink*)calloc(1,sizeof(Ulink));//calloc不需要初始化
	newnode->data=data;//数据域赋值
	newnode->next=NULL;//地址域置空
	return newnode;
}

void insert_after(Ulink* head,User data)    //插入新注册的数据节点到链表最后
{
	if(head==NULL)
	{
		printf("（后插数据时）发现头结点为空\n");
	}

	Ulink* newnode=create_node(data);
	
	//找到尾节点（尾节点不为空，它所指向的下一个为空）
	while(head->next!=NULL)
	//当发现节点的下一个为空，则结束循环，当前即为尾节点
	{
		head=head->next;	
	}
	head->next=newnode;
}


void print_personal_info(Ulink* pre)
{
	system("clear");
        printf("~~~~~~~~查看个人信息~~~~~~~~\n");
	printf("--- 编号\t用户名\t密码\t余额\n");
	printf("--> %s\t%s\t%s\t￥%d\n",pre->next->data.id,\
					 pre->next->data.name,\
					 pre->next->data.password,\
					 pre->next->data.balance);
	printf("---------------------\n");

	stop();
}






void change_personal_password(Ulink* head,Ulink* pre)//修改自己密码
{
	system("clear");
        printf("~~~~~~~~修改个人密码~~~~~~~~\n");
        if(head == NULL)
        {
                printf("（修改密码时）发现头节点为空!\n");
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

        if(0 == strcmp(newPass,newPassAgain)) //如果两次密码一样
        {
                strcpy(pre->next->data.password,newPass);  //使用拷贝函数修改密码
                printf("密码修改成功,请重新登录!\n");
                return;//返回学生界面
        }

        printf("两次密码不一致，修改失败!\n");
        return;
}


void recharge_balance(Ulink* head,Ulink* pre)//充值
{
	system("clear");
        printf("~~~~~~~~个人余额充值~~~~~~~~\n");
        if(head == NULL)
        {
                printf("（修改密码时）发现头节点为空!\n");
                return;
        }

        int add_balance=0;

	printf("当前余额；%d\n",pre->next->data.balance);

        printf("请输入您要充入得金额:");
        scanf("%d",&add_balance);


	printf("确定要向账户冲入%d吗?(y/n)\n",add_balance);

	getchar();	
	char ch=0;
	scanf("%c",&ch);
        if(ch=='n'|| ch=='N')
        {
                printf("放弃充值！\n");
                return;
        }

	pre->next->data.balance  = pre->next->data.balance + add_balance;

        printf("充值成功\n");

	printf("当前金额：%d\n",pre->next->data.balance);

	stop();
        return;
}


void print_one_info(Ulink* head)
//管理员查询(顺便传入有数据的链表)
{
	system("clear");
        printf("~~~~~~~~查看单个用户信息~~~~~~~~\n");
        if(head == NULL)
        {
                printf("头节点为空!\n");
                return;
        }

        char user_name[20] = "";
        printf("请输入账户名:");
        scanf("%s",user_name);

        //找到当前节点的前一个节点
        Ulink* pre=select_front_node(head,user_name);
        if(pre==NULL)   
        {
                printf("不存在该用户！\n");
                return;
        }


	printf("---------------------------------------\n");
	printf("\tID\t姓名\t余额\n");
	printf("\t%s\t%s\t%d\n",pre->next->data.id,pre->next->data.name,pre->next->data.balance);	

	getchar();
	stop();

        return;

}

char* get_issue()
{
	time_t timep;
	time (&timep);
	//printf(“%s”,ctime(&timep));
	return ctime(&timep);

}
void print_personal_ticket(Tlink* tic_head,Ulink* user_pre)
{
	system("clear");
        printf("~~~~~~~~自己历史购买记录~~~~~~~~\n");
	if(tic_head==NULL || user_pre==NULL)
        {
                printf("打印全部彩票时，头节点为空！\n");
                return;
        }
        if(count_ticket(tic_head)==0)
        {
                printf("无彩票信息\n");
                stop();
                return;
        }


        tic_head=tic_head->next;//站在第一个数据节点上
        while(tic_head)
        {
		if(strcmp(tic_head->data.userid,user_pre->next->data.id) == 0)
		{
                	printf("############  超级大乐透  ############\n");
                	printf("彩票期号：%s\n",tic_head->data.issue);
               		printf("彩票标识码：%d\n",tic_head->data.ticid);
                	printf("注数：%d\n",tic_head->data.multiple);
                	printf("号码：---------------------------------\n");
                	int i=0;
                	while(i<tic_head->data.multiple)
                	{

                	        printf("第%d注:\t%d\t%d\t%d\t%d\t%d\n",\
                        	                              i+1,\
                                	                      tic_head->data.num[0+i*5],\
                                        	              tic_head->data.num[1+i*5],\
                                        	              tic_head->data.num[2+i*5],\
                        	                              tic_head->data.num[3+i*5],\
                                                      	      tic_head->data.num[4+i*5]);
                        	printf("---------------------------------------\n");
                        	//...
                        	i++;
                	}
                	printf("\n\n");
		}
                tic_head=tic_head->next;
        }
        stop();
        return;
}


void print_all_ticket(Tlink* tic_head)
{
	system("clear");
        printf("~~~~~~~~查看全部彩票信息~~~~~~~~\n");
	if(tic_head==NULL)
	{
		printf("打印全部彩票时，头节点为空！\n");
		return;
	}
	if(count_ticket(tic_head)==0)
	{
		printf("无彩票信息\n");
		stop();
		return;
	}


	tic_head=tic_head->next;//站在第一个数据节点上
	while(tic_head)
	{
		printf("############  超级大乐透  ############\n");
	        printf("彩票期号：%s\n",tic_head->data.issue);
	        printf("彩票标识码：%d\n",tic_head->data.ticid);
		printf("注数：%d\n",tic_head->data.multiple);
	        printf("号码：---------------------------------\n");
		int i=0;
		while(i<tic_head->data.multiple)
		{
			
	        	printf("第%d注:\t%d\t%d\t%d\t%d\t%d\n",\
						      i+1,\
						      tic_head->data.num[0+i*5],\
						      tic_head->data.num[1+i*5],\
						      tic_head->data.num[2+i*5],\
						      tic_head->data.num[3+i*5],\
					     	      tic_head->data.num[4+i*5]);
	        	printf("---------------------------------------\n");
 	       		//...
			i++;
		}
		printf("\n\n");
		tic_head=tic_head->next;
	}
	stop();
	return;
}


//这个函数在调用的时候，总是爆 段错误！！！
int count_ticket(Tlink* tic_head)
{

	if(tic_head ==NULL)
	{
		printf("(彩票链表长度)头文件为空！\n");
		return 0;
	}

	
//	Tlink *save=tic_head;
	tic_head=tic_head->next;//站在第一个节点的位置
	int num=0;
	
	//if(tic_head)	printf("%d\t%d",num++,tic_head->next);//
	//printf("NULL=%d\n",NULL);

	while(tic_head!=NULL) 
	{
		
		num++;
		tic_head=tic_head->next;   //就是这个地方！！！段错误
	}

	return num;	
}

void print_one_ticket(Tlink* tic_head,int ticid)
{
	system("clear");
        printf("~~~~~~~~查看单张彩票信息~~~~~~~~\n");
	if(tic_head==NULL)
	{
		printf("（显示单张彩票）发现头指针为空！\n");
	}
	
	Tlink* tic_pre=select_front_node_T(tic_head,ticid);
	if(tic_pre==NULL)
	{
		printf("无该彩票\n");
		return;
	}


	printf("########  超级大乐透  ########\n");
	printf("彩票期号：%s\n",tic_pre->next->data.issue);
	printf("彩票标识码：%d\n",tic_pre->next->data.ticid);
	printf("号码：------------------------\n");

	int i=0;
	for(; i < tic_pre->next->data.multiple; i++)
	{
		printf("第%d注\t%d\t%d\t%d\t%d\t%d\n", i+1,\
						tic_pre->next->data.num[0+i*5],\
						tic_pre->next->data.num[1+i*5],\
						tic_pre->next->data.num[2+i*5],\
						tic_pre->next->data.num[3+i*5],\
						tic_pre->next->data.num[4+i*5]);
		printf("------------------------\n");
		//...
	}

}

Tlink*  select_front_node_T(Tlink* tic_head,int ticid)
{
	if(tic_head==NULL)
	{
		printf("（彩票链表，查找前节点），发现头指针为空！\n");
		return NULL;
	}
	
	Tlink *tic_pre=tic_head;
	tic_head=tic_head->next;
	
	while(tic_head)
	{
		if(tic_head->data.ticid==ticid)
		{
			return tic_pre;
		}
		tic_pre=tic_head;
		tic_head=tic_head->next;
	}
	return NULL;
}




void buy_ticket(Ulink* pre,Tlink* tic_head,Ilink* iss_head) //ticket_regist
{
	system("clear");
        printf("~~~~~~~~购买彩票~~~~~~~~\n");
	if(tic_head==NULL||pre==NULL||iss_head==NULL)
	{
		printf("（买票时）发现头指针或者用户前指针或者发行链表为空！\n");
		stop();
		return;
	}
	
	printf("-------------------------------\n");


	Tic data;
	memset(&data,0,sizeof(Tic));



	if(iss_head->next==NULL)
	{
		printf("首次进入系统，请等待管理员发行彩票！\n");
		stop();
		return;
	}


	
	//先找到 发行节点
	while(iss_head->next)
	{
		iss_head=iss_head->next;
	}

	//判断最后一个节点是否正在发行的彩票
	if(iss_head->data.state ==1)
	{
		printf("无正在发行的彩票！\n");
		return;
	}

	
	//期号

	strcpy(data.issue,iss_head->data.issue);
	
	printf("彩票期号：%s",data.issue);
	
	//彩票识别号，按照彩票在链表中的次序

	int temp=0;
	temp=count_ticket(tic_head);  //这个函数写的有问题！！！

	data.ticid=20170800+temp+1;//返回的是当前的彩票数量,这个地方导致了段错误
	printf("彩票识别号：%d\n",data.ticid);


	//购买人id //跨表传值
	strcpy(data.userid , pre->next->data.id);

	printf("购买人ID：%s\n",data.userid);



	//彩票号码
	get_ticket_num(&data);//传入数据的地址，直接

	//注数
	//printf("您要买几注");
	//scanf("%d",&data.multiple);


	//扣除费用
	printf("单注价格：%d\n",iss_head->data.price);
	printf("单张注数：%d\n",data.multiple);
	printf("扣除费用：%d\n",iss_head->data.price * data.multiple);
	pre->next->data.balance -=iss_head->data.price * data.multiple;	
	printf("我的当前余额：%d\n",pre->next->data.balance);
	
	//插入Tlink	
	insert_after_T(tic_head,data); //段错误
	
	printf("成功购买！\n");
	
	//其他链表操作

	//iss_head->data.sellcount++;
	iss_head->data.sellcount += data.multiple;
	print_one_ticket(tic_head,data.ticid);
	getchar();
	stop();
	return;

}

void get_ticket_num(Tic* data)
{
	
	printf("您要买几注彩票号码？\n");
	scanf("%d",&data->multiple);	

	if(data->multiple>5)
	{
		printf("单张彩票，最多可以购买5注!\n");
		data->multiple=5;
		printf("已强制改成5注！\n");
	}
	int i=0;
	while(i<data->multiple)
	{
		printf("随机1 / 手写2\n");
		int choose=0;
		while(1)
		{
			scanf("%d",&choose);
			if(choose==1||choose==2)
			{
				break;
			}
			//getchar();
		}
		if(choose==1)
		{
			printf("正在随机生成！\n");//随机获取
			srand(time(NULL)); //时间作为时间原
			data->num[0+i*5]=rand()%10;//0~9
			data->num[1+i*5]=rand()%10;
			data->num[2+i*5]=rand()%10;
			data->num[3+i*5]=rand()%10;//第（i+1）注
			data->num[4+i*5]=rand()%10;
		}
		else if(choose==2)
		{
			printf("请输入你希望的五个数字（0~9）:");//手动输入
			scanf("%d%d%d%d%d",data->num+0+i*5,\
				       	   data->num+1+i*5,\
					   data->num+2+i*5,\
					   data->num+3+i*5,\
					   data->num+4+i*5);
		}	
		printf("%d\t%d\t%d\t%d\t%d\n",\
                                        data->num[0+i*5],\
                                        data->num[1+i*5],\
                                        data->num[2+i*5],\
                                        data->num[3+i*5],\
                                        data->num[4+i*5]);

		i++;
	}

	/*
	i=0;
	printf("---------------------------------------------\n");
	while(i<data->multiple)
	{
		printf("%d\t%d\t%d\t%d\t%d\n",\
					data->num[0+i*5],\
					data->num[1+i*5],\
					data->num[2+i*5],\
					data->num[3+i*5],\
					data->num[4+i*5]);
		i++;
	}*/

	return ;

}

Tlink* create_node_T(Tic data)
{
	Tlink* p=(Tlink*)calloc(1,sizeof(Tlink));
	p->data=data;
	p->next=NULL;
	return p;
}

void insert_after_T(Tlink* tic_head,Tic data)    //插入新注册的数据节点到链表最后
{
        if(tic_head==NULL)
        {
                printf("（后插数据时）发现头结点为空\n");
        }

        Tlink* newnode=create_node_T(data);

        //找到尾节点（尾节点不为空，它所指向的下一个为空）
        while(tic_head->next != NULL)
        //当发现节点的下一个为空，则结束循环，当前即为尾节点
        {
                tic_head=tic_head->next;
        }
        tic_head->next=newnode;
}



void publish_ticket(Ilink* iss_head)
{
	system("clear");
        printf("~~~~~~~~发行彩票~~~~~~~~\n");
	//检查头结点
	if(iss_head==NULL)
	{
		printf("（发行）头结点为空！\n");
		return;
	}
	Ilink* save=iss_head;

	//检查上一期是否已开奖
		//走到尾巴
	int num=0;
	while(iss_head->next)
	{
		num++;
		iss_head=iss_head->next;
	}

		//已经在尾巴上了（但是，第一次是头结点）
	if( num!=0 && iss_head->data.state==0 )
	//如果不是头节点  且  上一期未开奖，则本次不可以发行
	{
		printf("上一期未开奖!\n");
		return;
	}	
	
	//准备发行
	//创建数据块
	Iss data;

	//填入数据
		//发行期号 
	strcpy(data.issue,get_issue());
	printf("本次发行期号：%s\n",data.issue);

		//彩票单价
	printf("请输入彩票单价：");
	scanf("%d",&data.price);

		//开奖状态
	data.state=0;//未开奖
	printf("开奖状态：未开奖\n");

		//中奖号码清为-1
	data.num[0]=-1;
	data.num[1]=-1;
	data.num[2]=-1;
	data.num[3]=-1;
	data.num[4]=-1;
	printf("中奖号码： -1\t-1\t-1\t-1\t-1\n");
		//int sellcount售出总数为0
	data.sellcount=0;
	printf("售出总数：%d\n",data.sellcount);
		//
	data.totalmoney=iss_head->data.totalmoney;       //奖池奖金=尾巴节点的奖池金额
	printf("奖池金额：%d\n",data.totalmoney);
	//插入链表
	iss_head=save;
	insert_after_I(iss_head,data);
	printf("成功发行！\n\n");
	//显示发行信息

	getchar();	
	stop();
	return;

}


Ilink* create_node_I(Iss data)
{
	Ilink* newnode=(Ilink*)calloc(1,sizeof(Ilink));
	newnode->data=data;
	newnode->next=NULL;
	return newnode;
}


void insert_after_I(Ilink* iss_head,Iss data)
{
	if(iss_head==NULL)
	{
		printf("（插入发行链表时）发现头结点为空！\n");
		return;

	}

	Ilink* newnode=create_node_I(data);
	
	while(iss_head->next)
	{
		iss_head=iss_head->next;
	}
	iss_head->next=newnode;

}

void run_the_lottery(Ulink* user_head,Tlink* tic_head,Ilink* iss_head)
//开奖(发行链表)
{
	system("clear");
        printf("~~~~~~~~开奖 见证奇迹~~~~~~~~\n");
	if(user_head==NULL)
	{
		printf("（开奖时）用户链表头节点为空！\n");
		return ;
	}
	if(tic_head==NULL)
        {
                printf("（开奖时）彩票链表头节点为空！\n");
                return ;
        }
	if(iss_head==NULL)
        {
                printf("（开奖时）发行链表头节点为空！\n");
                return ;
        }

	//询问是否确定要开奖
        if(tic_head->next==NULL)
        {
                printf("\n彩票尚无人购买！\n");
        }
	char ch=0;
	while(1)
	{
		printf("是否要开奖？（y/n）\n");
		scanf("%c",&ch);
		if(ch=='n'||ch=='N')
		{
			return;
		}
		if(ch=='y'||ch=='Y')
		{
			break;
		}
	}

	//准备开奖
		//保存彩票头结点，用于发奖
	Tlink* tic_save=tic_head;
			
		//找到发行链表最后一个节点
	if(iss_head->next==NULL)
	{
		printf("首次登陆，无发行彩票，不可以开奖！\n");
		return;
	}

	while(iss_head->next)//找到发行链表的最后一个节点
	{
		iss_head=iss_head->next;
	}
	if(iss_head->data.state==1)//保证只开一次奖
	{
		printf("无奖可开！\n");
		return;
	}
	
		//开始摇奖，传入中奖数组，得到5位中奖数字
	run_number(iss_head->data.num,5);
		//设置状态为已开奖（限制不可以继续购买）
	iss_head->data.state=1;
		//遍历彩票链表，改变开奖状态


	//遍历每一张彩票
	tic_head=tic_head->next;//第一张彩票
	while(tic_head)
	{
		if(strcmp(tic_head->data.issue , iss_head->data.issue)==0)//期号一样
		{
			//判断号码相同情况,返回1,则有中奖号码
			tic_head->data.is_flag=judge_awards(
							iss_head->data.num,\
							tic_head->data.num,\
							tic_head->data.multiple,\
							tic_head->data.sta\
							);
			//修改彩票的中奖状态
				//上方已经修改了tic_head->data.sta   sta[5]
			//相关的用户，增加奖金
				//兑换奖金，奖池减少,这个功能写在别的地方。				

		}
		tic_head=tic_head->next;//下一张彩票
	}
	
	
	ch =0;//上面已经定义过了
	getchar();
	while(1)
	{
		printf("是否现在进行奖金发放？(y or n)\n");
		scanf("%c",&ch);
		if(ch=='Y'||ch=='y')
		{
			break;
		}
		if(ch=='N'||ch=='n')
		{
			return;
		}
	}

	distribute_money(user_head,tic_save,iss_head);
	getchar();
	stop();
	return;
}





void distribute_money(Ulink* user_head,Tlink* tic_head,Ilink* iss_head)
{

//这里传入的  用户链表 是头结点，彩票 是 头结点，发行链表是尾节点

	system("clear");
        printf("~~~~~~~~发放奖金~~~~~~~~\n");
	if(user_head==NULL)
	{
		printf("头节点为空！\n");
		return ;
	}
	//确保发行节点是 最后一个节点
	while(iss_head->next)    
	{
		iss_head=iss_head->next;
	}

	Ulink* user_pre=user_head;

	tic_head=tic_head->next;
	while(tic_head)//遍历每一张彩票，准备发奖
	{
		if(tic_head->data.is_flag && !tic_head->data.is_exc)
		//中奖且未兑换
		{
			//输出中奖信息
				//根据彩票找到中奖人,userid==id
			user_pre=select_front_node_id(user_head,tic_head->data.userid);
			if(user_pre==NULL)
			{
				printf("中奖人员信息丢失，该张彩票无人认领！\n");
				
			}
			else//找到中奖的用户
			{
				//显示用户信息
				printf("中奖id是:%s\n",user_pre->next->data.id);
				printf("中奖人是:%s\n",user_pre->next->data.name);
				//根据彩票 中奖情况，减少奖池，增加个人余额（三链表操作）
				printf("共购买了%d注\n",tic_head->data.multiple);

				int i=0;
				while(i<5)
				{
					if(tic_head->data.sta[i]>0)
					{
						printf("\n\n￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥\n");
						printf("第%d注中了%d个数字，奖金为%d元!\n",\
											i+1,\
											tic_head->data.sta[i],\
											bonus_select[tic_head->data.sta[i] - 1]);
						printf("正在从奖池(%d)中扣除金额(%d)。。。\n",\
											iss_head->data.totalmoney,\
											bonus_select[tic_head->data.sta[i] - 1]);
						iss_head->data.totalmoney -=bonus_select[tic_head->data.sta[i]-1];
						printf("奖池当前剩余:%d\n",iss_head->data.totalmoney);
						//------------------------------------------------------------------
						printf("正在向用户(%d)中增加金额(%d)。。。\n",\
											user_pre->next->data.balance,\
											bonus_select[tic_head->data.sta[i] - 1]);	
						user_pre->next->data.balance +=bonus_select[tic_head->data.sta[i] - 1];
						printf("用户当前余额:%d\n",user_pre->next->data.balance);
					}
					i++;//用于彩票注数循环
				}
			}
			tic_head->data.is_exc=1;

		}
		

		tic_head=tic_head->next;//下一张彩票
	}
	printf("奖金已经全部发放！\n");

}


//传入数据链和需要查找的账户名称,
//查找函数，返回当前节点前一个节点
Ulink* select_front_node_id(Ulink* user_head,char* userid)
{
        if(user_head==NULL)
        {
                printf("（发钱,向前检索时）发现头结点为空!\n");
                return NULL;
        }

        Ulink* user_pre = user_head;//双指针，pre 始终在head前一个

        user_head=user_head->next; //从第一个有效数据节点开始，（此时pre成了头指针）
        while(user_head!=NULL)
        {
                if(strcmp(user_head->data.id,userid)==0)//找到同id的节点head
                {
                        return user_pre;  //返回上一个节点，方便对当前节点进行操作。
                }
                user_pre=user_head;
                user_head=user_head->next;

        }
        return NULL;   //未找到，返回空

}



//判断号码相同情况，涉及到 中奖数组5  买奖数组25 注数x
int judge_awards(int* num,int* buynum,int multiple,int* sta)
{
	//num[5] 
	//buynum[25],multiple
	//sta[5]
	int flag=0;
	int i=0;
	int j=0;
	while(i<multiple)//i代表第i+1注
	{
		j=0;
		while(j<5)
		{
			if(buynum[j+i*5]==num[j])
			{
				sta[i]++;	
				flag=1;
			}
			j++;
		}
		i++;//注数
	}
	if(flag==0)
	{
		return 0;
	}	
	return 1;
}



//得到5位中奖号码
void run_number(int* num ,int len)
{
	int i=0;
	while(i<len)  //#####
	{
		//滚动动画
		system("clear");
		printf("第%d个中奖号码是:",i+1);
		srand(time(NULL)); //时间作为时间原
                num[i]=rand()%10;//0~9
		printf("%d\n",num[i]);

		sleep(1);
		i++;
	}
}


