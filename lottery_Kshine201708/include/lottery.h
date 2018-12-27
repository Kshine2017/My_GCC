#ifndef _LOT_H_
#define _LOT_H_

//奖金金额控制，数组存储5种金额
int bonus_select[5];
//记录被删除的人数，用于用户ID的准确生成，防重复
extern int userhistorycount;


/*--------------- 结构体 定义------------------*/

//用户结构体
typedef struct lottery_user{
        char id[10];       //账号
        int id_flag;  //区分身份的标志
        char name[20];
        char password[20];
        int balance;   //账户余额
}User;

//彩票信息结构体
typedef struct lottery_ticket{
        char issue[30];       //期号 170809
        int ticid;       //彩票标识码
        int num[25];     //5位数的彩票 最多5注
        char userid[10];     //购买者账号
        int multiple;    //注数，倍数（不能大于5注）
        
	int is_flag;	  //是否中奖
	int sta[5];       //中奖状态  1 一等奖，2，二等奖，3，三等奖，0 未中奖
	
	int is_exc;	//是否已兑换成现金（是否存入用户余额中）
        int bonus;       //奖金
}Tic;

//发行信息结构体
typedef struct lottery_issue{
        char issue[30];       //期号
        int price;            //彩票单价
        int state;            //开奖状态
        int num[5];          //中奖号码
        int sellcount;       //售出总数
        int totalmoney;       //奖池奖金
}Iss;

/*----------------  链表  ------------------*/

//在结构体的基础上，定义信息链表
//用户链表
typedef struct Userlink{
        User data;//数据
        struct Userlink* next;//指针空间
}Ulink;
//彩票链表
typedef struct Ticketlink{
	Tic data;
	struct Ticketlink* next;
}Tlink;
//发行链表
typedef struct Issuelink{
	Iss data;
	struct Issuelink* next;
}Ilink;

/*---------------函数原型声明----------------*/

//公证员登录
void notery_login(Ulink* user_head,Tlink* tic_head,Ilink* iss_head);
//管理员登录
void admin_login(Ulink* head,Tlink* tic_head,Ilink* iss_head);
//用户登录
void user_login(Ulink* head,Tlink* tic_head,Ilink* iss_head);
//用户注册
void user_regist(Ulink* user_head);

//生成用户的ID，w-0001,首字符-所在序号
void get_userid(Ulink* user_head,User *data);

//计算用户的个数
int count_user(Ulink* user_head);

//根据姓名找到前一个节点
Ulink* select_front_node(Ulink* head,char* name);
//传入数据，创建新的节点
Ulink* create_node(User data);
//用户的后插函数
void insert_after(Ulink* head,User data);
//显示全部用户信息
void print_all_user(Ulink* head);
//显示个人信息
void print_personal_info(Ulink* pre);
//显示全部发行信息
void print_all_issue(Ilink* iss_head);

//用户修改自己的密码
void change_personal_password(Ulink* head,Ulink* pre);//修改自己密码
//用户充值
void recharge_balance(Ulink* head,Ulink* pre);//充值
//管理员查找显示用户
void print_one_info(Ulink* head);//管理员查找彩民

//------买彩票--------------------------
//根据时间获取彩票的期号
char* get_issue();
//数出彩票数量
int  count_ticket(Tlink* tic_head);
//买彩票，总控制
void buy_ticket(Ulink* pre,Tlink* tic_head,Ilink* iss_head);
//获取彩票的号码
void get_ticket_num(Tic* data);
//创建彩票节点
Tlink* create_node_T(Tic data);
//彩票节点后插
void insert_after_T(Tlink* tic_head,Tic data);
//根据彩票的标识号，返回前一个节点
Tlink*  select_front_node_T(Tlink* tic_head,int ticid);
//输出指定的彩票信息
void print_one_ticket(Tlink* tic_head,int ticid);
//输出全部彩票信息
void print_all_ticket(Tlink* tic_head);
//输出自己的彩票信息
void print_personal_ticket(Tlink* tic_head,Ulink* user_pre);
//-----发行彩票---------------------------
//创建发行链表的新节点
Ilink* create_node_I(Iss data);
//传入新的数据块，在发行链表后，插入新节点
void insert_after_I(Ilink* iss_head,Iss data);
//发行彩票
void publish_ticket(Ilink* iss_head);

//-----开奖-------------------------------
void run_the_lottery(Ulink* user_head,Tlink* tic_head,Ilink* iss_head);
//获取中奖号码
void run_number(int* num ,int len);
//判定奖项
int judge_awards(int* num,int* buynum,int multiple,int* sta);
//根据用户id返回前一个节点
Ulink* select_front_node_id(Ulink* user_head,char* userid);
//根据中奖状态，发放奖金
void distribute_money(Ulink* user_head,Tlink* tic_head,Ilink* iss_head);

//排序
void sort_all_user_by_name(Ulink* user_head,int mode);//通过姓名排序
void sort_all_user_by_id(Ulink* user_head,int mode);//通过id排序
//管理奖池
void manage_totalmoney(Ilink* iss_head);
//删除
void delete_node(Ulink* user_head,char* name);//删除逻辑
void delete_user(Ulink* user_head);//删除函数


#endif

