#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "windows.h"
#define SIZE sizeof(struct student)



struct student {
	long long int number;//学号
	char name[20];//姓名
	int sex;//M:男生 F:女生
	char class_name[50];//班级名称
	char birthday[20];//出生日期 2018-1-1
	long long int phone_number;//联系方式
	char home_address[100];//家庭住址
	char subject[20][20];//学科名称
	int  score[20];//学科成绩
	struct student *next;//指向下一个节点的指针
};

//初始化函数

struct student *create_node();
void print(struct student *head, int mode);
int count_repeat_number(long long int number, struct student *list);
int count_node(struct student *list);
struct student *del_node(struct student *list, int mode, long long int number, char str[]);
struct student *insert_node(struct student *list);
struct student *modify_list(struct student *list, long long int number, char str[]);
struct student *search_node(struct student *list, int mode, char str[], long long int number);
void export_data(struct student *list);
struct student *import_data();


/*
 * 创建新的节点
 @ return struct student * 链表地址
 */
struct student *create_node(){
	struct student *head,*curnode=NULL,*newnode;
	long long int number;
	int mode;
	head = NULL;
	while (true) {
		while (true) {
			printf("请输入学生的学号(输入0返回首页):");
			scanf_s("%lld", &number, 20);
			//遍历函数,检查是否有重复的学号
			if (count_repeat_number(number, head) != 0) {
				printf("学号已存在,请重新输入学号!\n");
				continue;
			}
			else {
				break;
			}
		}
		if (number == 0) { break; }
		newnode = (struct student *)malloc(SIZE);//这里的(struct student *)是为了定义malloc返回的指针类型为struct student
		if (newnode == NULL) {
			printf("Error.\n");
			exit(1);
		}
		newnode->next = NULL;//把新节点的指针指向NULL
		newnode->number = number;
		printf("请输入该同学的名称:");
		scanf_s("%s", newnode->name, 20);//scanf_s的第三参数会视作为字符串可以写的内存大小,如果超出了数组定义的位数,将会越界报错
		//getchar();//处理上一个回车遗留的\n,防止gets获取到\n就直接跳过了
		//gets_s(newnode->name);
		printf("请输入该同学的性别(0:男|1:女):");
		scanf_s("%d", &newnode->sex, 1);
		getchar();
		printf("请输入该同学的班级名称:");
		scanf_s("%s", newnode->class_name, 50);
		printf("请输入该同学的出生日期(格式:2018-1-1):");
		scanf_s("%s", newnode->birthday, 20);
		printf("请输入该同学的手机号码\\固定电话:");
		scanf_s("%lld",&newnode->phone_number, 100);
		printf("请输入该同学的家庭住址:");
		scanf_s("%s", newnode->home_address, 100);
		//初始化成绩数组
		for (int i = 0; i < 20; i++) {
			sprintf_s(newnode->subject[i],"NULL");
		}
		memset(newnode->score,-1,sizeof(newnode->score));
		//显示将要插入的数据,如果要修改则直接跳过head的重定向
		system("cls");
		printf("+------------------+\n");
		printf("学号:%lld\n", newnode->number);
		printf("姓名:%s\n", newnode->name);
		if (newnode->sex == 0) { printf("性别:男性\n"); }
		else if (newnode->sex == 1 ) { printf("性别:女性\n"); }else{
			printf("性别:中性\n");
		}
		printf("班级名称:%s\n", newnode->class_name);
		printf("出生日期:%s\n", newnode->birthday);
		printf("电话号码:%lld\n", newnode->phone_number);
		printf("家庭住址:%s\n", newnode->home_address);
		printf("+------------------+\n");
		printf("信息是否正确?(正确请输入1|不正确请输入0)");
		scanf_s("%d", &mode, 2);
		if (mode == 1) {
			if (head == NULL) {
				head = newnode;
				curnode = head;
				continue;
			}
			curnode->next = newnode;
			curnode = curnode->next;
		}
	}
	return (head);
}

/*
 * 打印链表
 @ param struct student * 链表
 @ param int 模式[0:正常输出|1:显示插入符(插入模式下使用)|2:只输出一次]
 */
void print(struct student *head,int mode=0) {
	struct student *curnode=NULL;
	int count = 1;
	if (head != NULL) {
		curnode = head;
		do {
			printf("+------------------+\n");
			printf("学号:%lld\n",curnode->number);
			printf("姓名:%s\n",curnode->name);
			if (curnode->sex == 0) { printf("性别:男性\n"); }
			else if (curnode->sex == 1) { printf("性别:女性\n"); }
			else { printf("性别:中性\n"); }
			printf("班级名称:%s\n",curnode->class_name);
			printf("出生日期:%s\n",curnode->birthday);
			printf("电话号码:%lld\n",curnode->phone_number);
			printf("家庭住址:%s\n",curnode->home_address);
			printf("+------------------+\n");
			if (mode == 1) { printf("%d->\n", count); count++; }
			if (mode == 2)break;
			curnode = curnode->next;
		} while (curnode != NULL);
	} else {
		printf("无数据记录.\n");
	}
}

/*
 * 检查是否已存在相同学号
 @ param long long int 目标学号
 @ param struct student * 待检查的链表
 @ return int 重复的个数
 */
int count_repeat_number(long long int number,struct student *list) {
	int count=0;
	struct student *curnode;
	curnode = list;
	if (curnode == NULL){
		//printf("NULL\n");
		return count;//用于过滤掉create_node传入的NULL指针 
	}
	if (number == curnode->number) { count++; }//用于处理只有一个节点的情况
	while (curnode->next!=NULL) {
		if (number == curnode->number) { count++; }
		curnode = curnode->next;
	}
	return count;
}

/*
 * 统计节点个数
 @ param struct student * 待统计链表
 @ return int 节点个数
 */
int count_node(struct student *list) {
	int count = 1;
	if (list == NULL) { return 0; }
	struct student *curnode;
	curnode = list;
	while (curnode->next!= NULL) {
		curnode = curnode->next;
		count++;
	}
	return count;
}
/*
 * 删除节点数据
 @ param struct student * 链表地址 
 @ param int 模式[0:学号模式|1:名字模式]
 @ param long long int 学号
 @ param char [] 名字
 @ rerurn struct student * 返回修改好的链表的地址
 */
struct student *del_node(struct student *list,int mode,long long int number,char str[]) {
	int count=0,tongji=0;
	struct student *curnode= (struct student *)malloc(SIZE), *prinode= (struct student *)malloc(SIZE);
	do {
		if (count == 0) { 
			curnode = list; 
		} else {
			prinode = curnode;
			curnode = prinode->next;
		}
		//删除第一个节点只需要把指针指向NULL即可
		if (count==0) {
			if (mode == 0&&curnode->number==number) {
				//定位到了待删除的节点
				list = curnode->next;
				tongji++;
				break;
			}
			else if (mode == 1 && !strcmp(curnode->name, str)) {
				//定位到了待删除的节点
				list = curnode->next;
				tongji++;
				break;
			}
		} else {
			if (mode == 0 && curnode->number == number) {
				//删除2至n号节点
				prinode->next = curnode->next;
				tongji++;
				//curnode->next = NULL;
				break;
			}
			else if (mode == 1 && !strcmp(curnode->name, str)) {
				//删除2至n号节点
				prinode->next = curnode->next;
				tongji++;
				//curnode->next = NULL;
				break;
			}
		}
		count++;
	}while(curnode->next!=NULL);
	if (tongji == 0) {
		printf("找不到目标学号/目标姓名,请重新输入!\n");
		system("pause");
	}
	return list;
}

/*
 * 插入新节点
 @ param struct student * 待插入节点的链表
 @ return struct student * 已插入节点的链表
 */
struct student *insert_node(struct student *list) {
	long long int number;
	int count = 0;
	struct student *curnode,*newnode,*nextnode;
	printf("-----插入数据-----\n");
	print(list,1);
	printf("------------------\n");
	printf("0:返回首页\n");
	printf("------------------\n");
	printf("输入插入位置的序号:");
	scanf_s("%lld", &number,20);
	if (number == 0) { return list; }
	curnode = list;
	nextnode = curnode ->next;
	while (count<=count_node(list)) {
		count++;
		if (count == number) {
			while (true) {
				printf("请输入学生的学号(输入0返回首页):");
				scanf_s("%lld", &number, 20);
				//遍历函数,检查是否有重复的学号
				if (count_repeat_number(number, list) != 0) {
					printf("学号已存在,请重新输入学号!\n");
					continue;
				}
				else {
					break;
				}
			}
			if (number == 0) { break; }
			newnode = (struct student *)malloc(SIZE);
			if (newnode == NULL) {
				printf("Error.\n");
				exit(1);
			}
			newnode->next = nextnode;//把新节点的指针指向NULL
			newnode->number = number;
			printf("请输入该同学的名称:");
			scanf_s("%s", newnode->name, 20);//scan f_s的第三参数会视作为字符串可以写的内存大小,如果超出了数组定义的位数,将会越界报错
			printf("请输入该同学的性别(0:男|1:女):");
			scanf_s("%d", &newnode->sex, 2);
			printf("请输入该同学的班级名称:");
			scanf_s("%s", newnode->class_name, 50);
			printf("请输入该同学的出生日期(格式:2018-1-1):");
			scanf_s("%s", newnode->birthday, 20);
			printf("请输入该同学的手机号码\\固定电话:");
			scanf_s("%lld",&newnode->phone_number, 100);
			printf("请输入该同学的家庭住址:");
			scanf_s("%s", newnode->home_address, 100);
			for (int i = 0; i < 20; i++) {
				sprintf_s(newnode->subject[i], "NULL");
			}//初始化成绩数组
			memset(newnode->score,-1, sizeof(newnode->score));
			curnode->next = newnode;
			break;
		}
		else {
			printf("找不到插入点,请重新输入!\n");
		}
		curnode = nextnode;
	}
	system("cls");
	printf("-----成绩总览-----\n");
	printf("已有数据:%d\n", count_node(list));
	printf("------------------\n");
	print(list,0);
	printf("------------------\n");
	printf("回车返回首页\n");
	printf("------------------\n");
	system("pause");
	return list;
}
/*
  * 修改指定学生的数据
  @ sturct student * 待修改的链表
  @ return struct student * 返回已修改的链表
 */
struct student *modify_list(struct student *list,long long int number,char str[]) {
	int count = 0,mode;
	struct student *curnode, *nextnode;
	curnode = list;
	nextnode = curnode->next;
	while (count < count_node(list)) {
		count++;
		if (curnode->number == number || !strcmp(curnode->name,str)) {
			while(true){
				system("cls");
				printf("-----修改数据-----\n");
				printf("1-学号\n");
				printf("2-姓名\n");
				printf("3-性别\n");
				printf("4-班级名称\n");
				printf("5-出生日期\n");
				printf("6-联系方式\n");
				printf("7-家庭住址\n");
				printf("------------------\n");
				printf("0-返回首页\n");
				printf("------------------\n");
				printf("请输入该要修改的信息对应的序号:");
				scanf_s("%d", &mode, 2);
				if (mode == 0) { break; }
				if (mode == 1) {
					printf("请输入学生的序号:");
					scanf_s("%lld", &number, 20);
					//遍历函数,检查是否有重复的学号
					if (count_repeat_number(number, list) != 0) {
						printf("学号已存在,请重新输入学号!\n");
						continue;
					}
					curnode->number = number;
				}
				if (mode == 2) {
					printf("请输入该同学的名称:");
					scanf_s("%s", curnode->name, 20);//scanf_s的第三参数会视作为字符串可以写的内存大小,如果超出了数组定义的位数,将会越界报错
				}
				if (mode == 3) {
					printf("请输入该同学的性别(M:男|F:女):");
					scanf_s("%d", &curnode->sex, 2);
				}
				if (mode == 4) {
					printf("请输入该同学的班级名称:");
					scanf_s("%s", &curnode->class_name, 50);
				}
				if (mode == 5) {
					printf("请输入该同学的出生日期(格式:2018-1-1):");
					scanf_s("%s", &curnode->birthday, 20);
				}
				if (mode == 6) {
					printf("请输入该同学的手机号码\\固定电话:");
					scanf_s("%lld", &curnode->phone_number, 100);
				}
				if (mode == 7) {
					printf("请输入该同学的家庭住址:");
					scanf_s("%s", &curnode->home_address, 100);
				}
		}
			break;
		}
		else {
			printf("找不到目标学号/目标姓名,请重新输入!\n");
		}
		curnode = nextnode;
	}
	return list;
}

/*
 * 检索与操作链表节点
 @ param struct student *
 @ param int 模式[0:检索char类型的数据|1:检索学号数据|2:检索性别数据]
 @ param char [] 目标字符值
 @ param long long int 目标数值
 @ return struct student * 修改完成的链表
 */
struct student *search_node(struct student *list, int mode, char str[], long long int number) {
	struct student *curnode = list, *tmpnode;
	int count = count_node(list), c, tongji = 0;
	system("cls");
	printf("+-----搜索结果-----+\n");
	if (count == 1) {
		if (mode == 0) {
			if (!strcmp(curnode->name, str) || !strcmp(curnode->birthday, str) || !strcmp(curnode->class_name, str) || !strcmp(curnode->home_address, str)) {
				tongji++;
				print(curnode, 2);
			}
		}
		else if (mode == 1) {
			if (curnode->number == number && number != 0) {
				tongji++;
				print(curnode, 2);
			}
			if (number == 0) {
				tongji++;
				print(list,0);

			}
		}
		else if (mode == 2) {
			if (curnode->sex == number) {
				tongji++;
				print(curnode, 2);
			}
		}
		else if (mode == 3) {
			if (curnode->phone_number == number) {
				tongji++;
				print(curnode, 2);
			}
		}
		if (tongji == 0) { printf("无搜索结果.\n"); printf("------------------\n");  system("pause"); return list; }
	}
	else {
		c = 0;
		while (c < count) {
			if (mode == 0) {
				if (!strcmp(curnode->name, str) || !strcmp(curnode->birthday, str) || !strcmp(curnode->class_name, str) || !strcmp(curnode->home_address, str)) {
					tongji++;
					print(curnode, 2);
				}
			}
			else if (mode == 1) {
				if (curnode->number == number && number != 0) {
					tongji++;
					print(curnode, 2);
				}
				if (number == 0) {
					tongji++;
					print(list,0);
					c = count;
				}
			}
			else if (mode == 2) {
				if (curnode->sex == number) {
					tongji++;
					print(curnode, 2);
				}
			}
			else if (mode == 3) {
				if (curnode->phone_number == number) {
					tongji++;
					print(curnode, 2);
				}
			}
			curnode = curnode->next;
			c++;
		}
		if (tongji == 0) { printf("无搜索结果.\n"); printf("------------------\n"); system("pause"); return list; }
	}

	//跳出数据遍历
	//开始操作数据
	printf("请输入选定模式(0:返回首页|1:按照学号选定|2:按照名字选定):");
	scanf_s("%d", &mode);
	while(true){
	if (mode == 0) {
		return list;
	}
	else if (mode == 1) {
		printf("请输入想要操作(删除/修改)的数据的学号:");
		scanf_s("%lld", &number, 20);
		printf("请输入希望执行的操作(0:返回首页|1:删除数据|2:修改数据):");
		scanf_s("%d", &mode, 2);
		if (mode == 0) {
			return list;
		}
		else if (mode == 1) {
			list = del_node(list, 0, number, str);
			break;
		}
		else if (mode == 2) {
			list = modify_list(list,number,str);
			break;
		}
	}
	else if (mode == 2) {
		printf("请输入想要操作(删除/修改)的数据的名字:");
		scanf_s("%s", str, 50);
		printf("请输入希望执行的操作(0:返回首页|1:删除数据|2:修改数据):");
		scanf_s("%d", &mode, 2);
		if (mode == 0) {
			return list;
		}
		else if (mode == 1) {
			list = del_node(list, 1, number, str);
			break;
		}
		else if (mode == 2) {
			list = modify_list(list,number, str);
			break;
		}
	}
	else {
		printf("无法识别序号,请重新输入正确的序号.\n");
		system("pause");
		break;
	}
}
	return list;
}

/*
 * 导出数据
 @ struct student * 待导出的链表
 */
void export_data(struct student *list) {
	struct student *curnode = list;
	FILE *fw1,*fw2;
	char filename[50];
	errno_t err;
	err = fopen_s(&fw1,"user.lb","w+");
	if (err) {
		printf("无法打开缓存文件\n");
		return;
	}
	if (curnode == NULL) {
		printf("无数据可导出\n");
		return;
	}
	do{
		printf("保存用户数据中.\n");
		fprintf(fw1,"%lld %s %d %s %s %lld %s\n",curnode->number,curnode->name,curnode->sex,curnode->class_name,curnode->birthday,curnode->phone_number,curnode->home_address);
		//保存用户成绩数据
		sprintf_s(filename,"%lld_subject.lb",curnode->number);
		err = fopen_s(&fw2, filename , "w+");
		if (err) {
			printf("无法打开缓存文件\n");
			return;
		}
		if (curnode == NULL) {
			printf("无学科数据可导出\n");
			return;
		}
		//遍历保存学科成绩
		for (int i = 0; i < 20;i++) {
			printf("保存学科数据中.\n");
			fprintf(fw2, "%s\n", curnode->subject[i]);
		}
		fclose(fw2);
		sprintf_s(filename, "%lld_score.lb", curnode->number);
		err = fopen_s(&fw2, filename, "w+");
		if (err) {
			printf("无法打开缓存文件\n");
			return;
		}
		if (curnode == NULL) {
			printf("无成绩数据可导出\n");
			return;
		}
		//遍历保存学科成绩
		for (int i = 0; i < 20; i++) {
			printf("保存成绩数据中.\n");
			fprintf(fw2, "%d\n", curnode->score[i]);
		}
		fclose(fw2);
			curnode = curnode->next;
	}while (curnode!=NULL);

	fclose(fw1);
	printf("导出完毕\n");
}

/*
 * 导入数据
 @ return struct student * 导入的链表数据
 */
struct student *import_data() {
	FILE *fr,*fr2,*fr3;
	errno_t err;
	char filename[50];
	struct student *head=NULL, *curnode = NULL, *newnode;
	err = fopen_s(&fr, "user.lb", "r");
	if (err) {
		printf("无法打开缓存文件\n");
		return head;
	}
	while (!feof(fr)) {
		newnode = (struct student *)malloc(SIZE);//这里的(struct student *)是为了定义malloc返回的指针类型为struct student
		if (newnode == NULL) {
			printf("Error.\n");
			return head;
		}
		fscanf_s(fr,"%lld ",&newnode->number);
		fscanf_s(fr,"%s ",newnode->name,sizeof(curnode->name));
		fscanf_s(fr,"%d ",&newnode->sex,2);
		fscanf_s(fr,"%s ",newnode->class_name,sizeof(curnode->class_name));
		fscanf_s(fr,"%s ",newnode->birthday,sizeof(curnode->birthday));
		fscanf_s(fr,"%lld ",&newnode->phone_number);
		fscanf_s(fr,"%s\n",newnode->home_address,100);
		newnode->next = NULL;//把新节点的指针指向NULL
		sprintf_s(filename, "%lld_subject.lb", newnode->number);
		err = fopen_s(&fr2, filename, "r");
		//编写遍历数据 
		for (int i = 0; i < 20; i++) {
			fscanf_s(fr2, "%s\n", &newnode->subject[i], sizeof(newnode->subject[i]));
		}
		fclose(fr2);
		sprintf_s(filename, "%lld_score.lb", newnode->number);
		//
		err = fopen_s(&fr3, filename, "r");
		//编写遍历数据 
		for (int i = 0; i < 20; i++) {
			fscanf_s(fr3, "%d\n", &newnode->score[i], sizeof(newnode->score[i]));
		}
		fclose(fr3);
			if (head == NULL) {
				head = newnode;
				curnode = head;
				continue;
			}
			
			curnode->next = newnode;
			curnode = curnode->next;
	}
	fclose(fr);
	printf("导入完成\n");
	return head;
}

/*
 * 排列链表
 @ param struct student 待排列的链表
 @ param int 模式[1:学号2:姓名3:班级名称4:总成绩] 
 @ return struct student * 已排列的链表
 */
struct student *rank_node(struct student *list,int mode) {
	struct student *pre, *cur, *next, *head, *temp, *new_head, *new_cur, *new_next;
	long long int arr_1[1000] = { '\0' },tmp_1;
	char arr_2[1000][100] = { '\0' },arr_3[1000][100] = { '\0' };
	char tmp_2[100],tmp_3[100];
	int count = 0, a, b, c, arr_c, e = count_node(list);
	cur = list;
	new_head = NULL;
	new_cur = NULL;
	if (mode == 1) {
		//提取链表的数值到数组中
		while (cur != NULL) {
			arr_1[count] = cur->number;
			cur = cur->next;
			count++;
		}
		//计算数组含有有效值的个数
		for (arr_c = 0; arr_1[arr_c] != '\0'; arr_c++);
		for (a = 0; a < count_node(list); a++)
		{
			for (b = 0; b < count_node(list) - a; b++)
			{
				if (arr_1[b] > arr_1[b + 1])
				{
					tmp_1 = arr_1[b];
					arr_1[b] = arr_1[b + 1];
					arr_1[b + 1] = tmp_1;
				}
			}
		}
		b = 0;
		//根据已排好的数值,来重新连接链表
		while (b < e + 1) {
			cur = list;
			c = 0;
			while (c < e) {
				if (arr_1[b] == cur->number) {
					if (new_head == NULL) {
						new_head = cur;
						new_cur = cur;
					}
					else {
						new_cur->next = cur;
						new_cur = cur;
					}
				}
				cur = cur->next;
				c++;
			}
			b++;
		}
	}
	else if (mode==2) {
		while (cur != NULL) {
			strcpy_s(arr_2[count],cur->name);
			cur = cur->next;
			count++;
		}
		for (a = 0; a < count_node(list); a++)
		{
			for (b = 0; b < count_node(list) - a; b++)
			{
				if (strcmp(arr_2[b],arr_2[b + 1])>0)
				{
					strcpy_s(tmp_2,arr_2[b]);
					strcpy_s(arr_2[b],arr_2[b + 1]);
					strcpy_s(arr_2[b + 1],tmp_2);
				}
			}
		}
		b = 0;
		while (b < e + 1) {
			cur = list;
			c = 0;
			while (c < e) {
				if (strcmp(arr_2[b],cur->name)==0) {
					if (new_head == NULL) {
						new_head = cur;
						new_cur = cur;
					}
					else {
						new_cur->next = cur;
						new_cur = cur;
					}
				}
				cur = cur->next;
				c++;
			}
			b++;
		}
	}
	else if (mode==3) {
		while (cur != NULL) {
			strcpy_s(arr_3[count], cur->class_name);
			cur = cur->next;
			count++;
		}
		for (a = 0; a < count_node(list); a++)
		{
			for (b = 0; b < count_node(list) - a; b++)
			{
				if (strcmp(arr_3[b], arr_3[b + 1]) > 0)
				{
					strcpy_s(tmp_3, arr_3[b]);
					strcpy_s(arr_3[b], arr_3[b + 1]);
					strcpy_s(arr_3[b + 1], tmp_3);
				}
			}
		}
		b = 0;
		while (b < e + 1) {
			cur = list;
			c = 0;
			while (c < e) {
				if (strcmp(arr_3[b], cur->class_name) == 0) {
					if (new_head == NULL) {
						new_head = cur;
						new_cur = cur;
					}
					else {
						new_cur->next = cur;
						new_cur = cur;
					}
				}
				cur = cur->next;
				c++;
			}
			b++;
		}
	}
	else if (mode == 4) {
	//按照总成绩排序
	count = 0;
	int total;
	cur = list;
	int array_score[1000];
	long long int array_number[1000],array_temp[1000];
	while (cur != NULL) {
		total = 0; 
		for (int i = 0; i < 20; i++) {
			if (cur->score[i] >= 0) { total = total + cur->score[i]; }
		}
		array_score[count] = total;
		array_number[count] = cur->number;
		cur = cur->next;
		count++;
	}

	for (a = 0; a < count_node(list); a++)
	{
		for (b = 0; b < count_node(list) - a; b++)
		{
			if (array_score[b]> array_score[b + 1])
			{
				array_temp[b]=array_number[b];
				array_number[b]=array_number[b + 1];
				array_number[b + 1]=array_temp[b];
			}
		}
	}
	b = 0;
	while (b < e + 1) {
		cur = list;
		c = 0;
		while (c < e) {
			if (array_number[b] == cur->number) {
				if (new_head == NULL) {
					new_head = cur;
					new_cur = cur;
				}
				else {
					new_cur->next = cur;
					new_cur = cur;
				}
			}
			cur = cur->next;
			c++;
		}
		b++;
	}
	}
	else if (mode==5) {
	//按照特定科目成绩排序
	count = 0;
	int total;
	cur = list;
	char search_subject[100];
	int array_score[1000],temp_score=-1;
	long long int array_number[1000], array_temp[1000];
	printf("请输入想要搜索的学科名称(0:返回首页):");
	scanf_s("%s",search_subject,100);
	if (!strcmp(search_subject,"0")) { return list; }
	while (cur != NULL) {
		for (int i = 0; i < 20; i++) {
			if (!strcmp(cur->subject[i], search_subject)) {
				temp_score = cur->score[count];
			}
			if (temp_score == -1) { temp_score = 999; }
		}
		array_score[count] = temp_score;
		array_number[count] = cur->number;
		cur = cur->next;
		count++;
	}

	for (a = 0; a < count_node(list); a++)
	{
		for (b = 0; b < count_node(list) - a; b++)
		{
			if (array_score[b] > array_score[b + 1])
			{
				array_temp[b] = array_number[b];
				array_number[b] = array_number[b + 1];
				array_number[b + 1] = array_temp[b];
			}
		}
	}
	b = 0;
	while (b < e + 1) {
		cur = list;
		c = 0;
		while (c < e) {
			if (array_number[b] == cur->number) {
				if (new_head == NULL) {
					new_head = cur;
					new_cur = cur;
				}
				else {
					new_cur->next = cur;
					new_cur = cur;
				}
			}
			cur = cur->next;
			c++;
		}
		b++;
	}
	}
		//处理最后一个节点,让节点的next指向NULL
		cur = new_head;
		b = 0;
		while (b < e) {
			if (b == (e - 1)) { cur->next = NULL; }
			cur = cur->next;
			b++;
		}
	return (new_head);
}
/*
 * 计算单个节点的已录入成绩的个数
 @ param struct student * 待计数的节点
 @ return int 已录入的个数
 */
int count_score(struct student *list) {
	int count=0;
	for (int a=0; a < 20;a++) {
			if (strcmp(list->subject[a],"NULL") != 0) { count++; }
	}
	return count;
}

/*
 * 查找值为空的键值对
 */
int find_null_keyname(struct student *list) {
	int count=0,key_c=0;
	struct student *cur;
	cur = list;
	while (cur!=NULL) {
		if (strcmp(cur->subject[count],"NULL")==0) {
			key_c = count;
			break;
		}
		count++;
	}
	return key_c;
}
/*
 * 编辑学生成绩
 */
struct student *edit_score(struct student *list) {
	int mode,count,total,max_score;
	float avg;
	long long int number,num,temp,max_number;
	struct student *cur;
	if (list == NULL) { return list; }
	while (true) {
		system("cls");
		printf("-----编辑学生成绩-----\n");
		printf("0-返回首页\n");
		printf("1-录入成绩\n");
		printf("2-修改成绩\n");
		printf("3-打印成绩\n");
		printf("4-删除成绩\n");
		printf("5-概览成绩\n");
		printf("6-最高成绩\n");
		printf("7-成绩前三名\n");
		printf("------------------\n");
		printf("请输入功能对应的序号:");
		scanf_s("%d", &mode, 2);
		//返回首页
		if (mode == 0) { break; }
		//录入成绩
		if (mode == 1) {
			system("cls");
			printf("---可录入成绩的链表---\n");
			print(list);
			printf("----------------------\n");
			printf("0-返回首页\n");
			printf("----------------------\n");
			printf("请输入学生的学号:");
			scanf_s("%lld", &number, 20);
			if (number == 0) { continue; }
			count = 0;
			int score_c,null_key;
			cur = list;
			while (cur!=NULL) {
				if (cur->number == number) {
					score_c=count_score(cur);
					if (score_c < 20) {
						printf("--新增学科成绩--\n");
						printf("请输入学科名称:");
						null_key = find_null_keyname(cur);//找到值为'\0'的可用空间
						scanf_s("%s",cur->subject[null_key],20);
						printf("请输入学科成绩:");
						scanf_s("%d",&cur->score[null_key],20);
						printf("-----------------\n");
						printf("学科名称:%s\n",cur->subject[null_key]);
						printf("学科成绩:%d\n",cur->score[null_key]);
						printf("-----------------\n");
						printf("信息是否正确?(正确:1|不正确:0):");
						scanf_s("%d",&mode,2);
						if (mode == 0)
						{
							
							sprintf_s(cur->subject[null_key], "NULL");
							cur->score[null_key] = -1;
						}
						if (mode == 1)
						{
							printf("学科数据已保存\n");
							system("pause");
							count++;
						}
						break;
					}
					else {
						printf("无位置存储新增学科数据,但您仍可使用修改与删除功能!\n");
						system("pause");
						count++;
						break;
					}
					count++;
				}
				cur = cur->next;
			}
			if (count==0) {
				printf("无法找到目标学生,请重新输入学生学号!\n");
				system("pause");
			}
		}
		//修改成绩
		if (mode == 2) {
			system("cls");
			printf("---可修改成绩的同学---\n");
			print(list);
			printf("----------------------\n");
			printf("0-返回首页\n");
			printf("----------------------\n");
			printf("请输入学生的学号:");
			scanf_s("%lld", &number, 20);
			if (number == 0) { continue; }
			cur = list;
			printf("-----已录入的成绩-----\n");
			while (cur != NULL) {
				if (cur->number == number) {
					for (int c = 0; c < 20; c++) {

						if (cur->score[c] >= 0) {
							printf("%d-%s:%d\n", c,cur->subject[c],cur->score[c]);

						}
					}
					count++;
				}
				cur = cur->next;
			}
			printf("-----------------------\n");
			printf("21-返回首页\n");
			printf("-----------------------\n");
			printf("请输入想要修改成绩的序号:");
			scanf_s("%lld",&num,10);
			if (num == 21) { continue; }
			cur = list;
			while (cur != NULL) {
				if (cur->number == number) {
						printf("请输入想要修改的数据(0:返回首页1:学科名称2:成绩):");
						scanf_s("%lld", &number,10);
						if (number == 0) {
							continue;
						}else
						if (number == 1) {
							printf("请输入学科的新名称:");
							scanf_s("%s", cur->subject[num],sizeof(cur->subject[num]));
						}else
						if (number == 2) {
							printf("请输入学科的新成绩:");
							scanf_s("%d", &cur->score[num],sizeof(cur->score[num]));
						}
						else { 
							printf("找不到目标功能,请重新输入"); 
							system("pause");
							continue;
						}
						printf("数据已修改,请务必使用导出功能,保存本次操作!\n");
						system("pause");
				
			}
				cur = cur->next;
			}

		}
		//打印成绩
		if (mode == 3)
		{
			while(true){
			cur = list;
			count = 0;
			printf("---可打印成绩的学生与学号---\n");
			while (cur != NULL) {
				if (count_score(cur) > 0) {
					printf("%lld:%s\n", cur->number ,cur->name);
					count++;
				}
				cur = cur->next;
			}
			if (count == 0) { printf("无学生数据可打印!\n"); }
			printf("----------------------------\n");
			printf("请输入想要打印成的学生学号(0:返回上一页):");
			scanf_s("%lld", &number);
			if (count == 0) { break; }
			if (number == 0) { break; }
			cur = list;
			count = 0;
			int a=0;
			while (cur != NULL) {
				if (cur->number == number) {
					for (int c = 0; c<20; c++) {
						
						if (cur->score[c] >= 0) {
							printf("%s", cur->subject[c]);
							printf(":");
							printf("%d\n", cur->score[c]);

						}
					}
					count++;
				}
				cur = cur->next;
			}
			if (count == 0) {
				printf("无法找到目标学号的学生,请重新输入!\n");
				system("pause");
			}
			else {
				system("pause");
				break;
			}
		}
		}
		//删除成绩
		if (mode == 4) {
			system("cls");
			count = 0;
			cur = list;
			printf("---可删除成绩的学生与学号---\n");
			while (cur != NULL) {
				if (count_score(cur) > 0) {
					printf("%lld:%s\n", cur->number, cur->name);
					count++;
				}
				cur = cur->next;
			}
			if (count == 0) { printf("无学生数据可打印!\n"); }
			printf("----------------------------\n");
			printf("请输入想要打印成的学生学号(0:返回上一页):");
			scanf_s("%lld", &number);
			if (count == 0) { continue; }
			if (number == 0) { continue; }
			cur = list;
			count = 0;
			printf("-----已录入的成绩-----\n");
			while (cur != NULL) {
				if (cur->number == number) {
					for (int c = 0; c < 20; c++) {

						if (cur->score[c] >= 0) {
							printf("%d-%s:%d\n", c, cur->subject[c], cur->score[c]);

						}
					}
					count++;
				}
				cur = cur->next;
			}
			if (count == 0) { printf("无成绩可删除!\n"); }
			printf("-----------------------\n");
			printf("21-返回首页\n");
			printf("-----------------------\n");
			printf("请输入想要删除成绩的序号:");
			scanf_s("%lld", &num, 10);
			if (count == 0) { continue; }
			if (num == 21) { continue; }
			cur = list;
			while (cur != NULL) {
				if (cur->number == number) {
					memset(cur->subject[num], '\0', sizeof(cur->subject[num]));//初始化学科名称数组
					cur->score[num] = -1;
					printf("数据已修改,请务必使用导出功能,保存本次操作!\n");
					system("pause");
					
				}
				cur = cur->next;
			}

		}
		//概览成绩(成绩总分,平均分)
		if (mode == 5) {
			while (true) {
				cur = list;
				count = 0;
				printf("---可打印成绩的学生与学号---\n");
				while (cur != NULL) {
					if (count_score(cur) > 0) {
						printf("%lld:%s\n", cur->number, cur->name);
						count++;
					}
					cur = cur->next;
				}
				if (count == 0) { printf("无学生数据可打印!\n"); }
				printf("----------------------------\n");
				printf("请输入想要概览的学生学号(0:返回上一页):");
				scanf_s("%lld", &number);
				if (count == 0) { break; }
				if (number == 0) { break; }
				cur = list;
				while(cur!=NULL){
					if (cur->number == number) {
						total = 0;
						for (int i = 0; i < 20; i++) {
							if (cur->score[i] >= 0) { total = total + cur->score[i]; }
						}
						total = 0;
						count = 0;
						for (int i = 0; i < 20; i++) {
							if (cur->score[i] >= 0) { total = total + cur->score[i]; count++; }
						}
						avg = (float)total / count;
						system("cls");
						printf("---学生成绩概览---\n");
						printf("学号:%lld\n", cur->number);
						printf("学生名称:%s\n", cur->name);
						printf("学生总分:%d\n", total);
						printf("学生平均分:%.2f\n", avg);
						printf("------------------\n");
					}
					cur = cur->next;
			}
				system("pause");
			}
		}
		//最高成绩总分的人
		if (mode == 6) {
			count = 0;
			max_score = 0;
			max_number = 0;
			cur = list;
			count = count_node(list);
			if (count == 0) { 
				printf("无学生数据可打印!\n");
				system("pause");
				continue;
			}
			//计算首个学生的成绩
			total = 0;
			for (int i = 0; i < 20; i++) {
				if (cur->score[i] >= 0) { total = total + cur->score[i]; }
			}
			max_score = total;
			max_number = cur->number;
			cur = cur->next;
			while(cur!=NULL) {
			//加入排序代码
				total = 0;
				for (int i = 0; i < 20; i++) {
					if (cur->score[i] >= 0) { total = total + cur->score[i]; }
				}
				if (max_score < total) {
					max_score = total;
					max_number = cur->number;
				}
				cur = cur->next;
			}
			cur = list;
			printf("---最高成绩的学生信息---\n");
			printf("学生学号:%lld\n",max_number);
			while (cur != NULL) {
				if (cur->number==max_number) {
					printf("学生姓名:%s\n",cur->name);
				}
				cur = cur->next;
			}
			printf("学生成绩:%d\n",max_score);
			printf("------------------------\n");
			system("pause");
		}
		//总分排名前三的学生信息
		if(mode==7){
			long long int rank_number_1=0,rank_number_2=0,rank_number_3=0;
			int rank_score_1=0,rank_score_2=0,rank_score_3=0;
			cur = list;
			count = 0;
			
			cur = list;
			while (count < count_node(list)) {
				if (count_node(list) == 1||cur==NULL) { break; }
				//加入排序代码
				total = 0;
				for (int i = 0; i < 20; i++) {
					if (cur->score[i] >= 0) { total = total + cur->score[i]; }
				}
				if (rank_score_1 < total) {
					rank_score_1 = total;
					rank_number_1 = cur->number;
				}
				cur = cur->next;
			}
			cur = list;
			while (count < count_node(list)) {
				if (count_node(list) == 1 || cur == NULL) { break; }
					total = 0;
					for (int i = 0; i < 20; i++) {
						if (cur->score[i] >= 0) { total = total + cur->score[i]; }
					}
					if (rank_score_2 < total&&count_node(list)>1&&total != rank_score_1) {
						rank_score_2 = total;
						rank_number_2 = cur->number;
					}
					cur = cur->next;
			}
			cur = list;
			while (count < count_node(list)) {
				if (count_node(list) == 1 || cur == NULL) { break; }
					total = 0;
					for (int i = 0; i < 20; i++) {
						if (cur->score[i] >= 0) { total = total + cur->score[i]; }
					} 
					if (rank_score_3 < total&& count_node(list)>2 && total != rank_score_1 && total != rank_score_2) {
						rank_score_3 = total;
						rank_number_3 = cur->number;
						count++;
					}
					cur = cur->next;
				}
			printf("---总分前三的学生信息---\n");
			cur = list;
			while (cur != NULL) {
				if (cur->number == rank_number_1) {
					printf("第一名: %s 成绩: %d\n", cur->name,rank_score_1);
				}
				cur = cur->next;
			}
			cur = list;
			while (cur != NULL) {
				if (cur->number == rank_number_2) {
					printf("第二名: %s 成绩: %d\n", cur->name, rank_score_2);
				}
				cur = cur->next;
			}
			cur = list;
			while (cur != NULL) {
				if (cur->number == rank_number_3) {
					printf("第三名: %s 成绩: %d\n", cur->name, rank_score_3);
				}
				cur = cur->next;
			}
			printf("------------------------\n");
			system("pause");
		}
		//最外层循环的结束
	}
	return list;
}

void main()
{
	system("title Score manager");
	int mode, sw = 0;
	struct student *list=NULL;
	while(1){
		if(count_node(list) > 0){sw = 1; } else { sw = 0; }
	system("cls");
	printf("-----成绩登记系统-----\n");
	printf("1-录入/插入数据\n");
	if (list != NULL) {
		printf("2-检索数据\n");
		printf("3-排序数据\n");
		printf("4-编辑成绩数据\n");
	}
	printf("5-导入/导出数据\n");
	printf("6-退出系统\n");
	printf("----------------------\n");
	printf("请输入功能对应的序号:");
	scanf_s("%d", &mode, 5);
	system("cls"); 
	if (mode == 1) {
		if (sw == 0) {
			list = create_node();
		}
		else {
			list = insert_node(list);
		}
	}
	else if (mode == 2&&list!=NULL) {
		//Power by 7gugu
			int mode, sex = 0;
			long long int number = 0;
			char str[100];
			while (true) {
				system("cls");
				printf("-----数据类型-----\n");
				printf("1-学号\n");
				printf("2-姓名\n");
				printf("3-性别\n");
				printf("4-班级名称\n");
				printf("5-出生日期\n");
				printf("6-联系方式\n");
				printf("7-家庭住址\n");
				printf("8-打印所有数据\n");
				printf("------------------\n");
				printf("0-返回首页\n");
				printf("------------------\n");
				printf("请输入你想按何种类型搜索,输入对应类型的序号:");
				scanf_s("%d", &mode, 2);
				if (mode == 0) { break; }
				switch (mode) {
				case 1:
					printf("请输入学号:");
					scanf_s("%lld", &number, 20);
					break;
				case 2:
					printf("请输入学生姓名:");
					scanf_s("%s", str, 50);
					break;
				case 3:
					printf("请输入学生性别(0:男|1:女):");
					scanf_s("%d", &sex, 2);
					break;
				case 4:
					printf("请输入学生班级名称:");
					scanf_s("%s", str, 20);
					break;
				case 5:
					printf("请输入学生出生日期:");
					scanf_s("%s", str, 20);
					break;
				case 6:
					printf("请输入学生联系方式:");
					scanf_s("%lld", &number, 20);
					break;
				case 7:
					printf("请输入学生家庭住址:");
					scanf_s("%s", str, 50);
					break;
				case 8:
					number = 0;
					break;
				}

				if (mode == 1) {
					list = search_node(list, 1, str, number);
				}
				else if (mode == 3) {
					list = search_node(list, 2, str, sex);
				}
				else if (mode == 6) {
					list = search_node(list, 3, str, number);
				}
				else if (mode == 8) {
					list = search_node(list, 1, str, number);
				}
				else {
					list = search_node(list, 0, str, number);
				}

			}
	}
	else if (mode == 3 && list != NULL) {
		printf("-----排列数据-----\n");
		printf("0-返回首页\n");
		printf("1-按学号排序\n");
		printf("2-按名字排序\n");
		printf("3-按班级名字排序\n");
		printf("4-按总成绩排序\n");
		printf("5-按指定学科成绩排序\n");
		printf("***排序从小到大***\n");
		printf("------------------\n");
		printf("请输入对应的功能序号:");
		scanf_s("%d",&mode,2);
		if (mode == 0) { continue; }
		printf("排序前的链表:\n");
		print(list);
		if (mode == 1) {
			list = rank_node(list, 1);
		}
		else if (mode == 2) {
			list = rank_node(list, 2);
		}
		else if(mode==3) {
			list = rank_node(list,3);
		}
		else if (mode==4) {
			list = rank_node(list,4);
		}
		else if (mode==5) {
			list = rank_node(list,5);
		}
		printf("------------------\n");
		printf("排序后的链表:\n");
		print(list);
		system("pause");

	}
	else if (mode==4 && list != NULL) {
	list=edit_score(list);
	}
	else if (mode == 5) {
		while(true){
		printf("-----管理数据-----\n");
		printf("1-导入数据\n");
		printf("2-导出数据\n");
		printf("0-返回首页\n");
		printf("------------------\n");
		printf("Warning:导入数据会覆盖当前的数据!!!\n");
		printf("请输入功能对应的序数:");
		scanf_s("%d", &mode, 2);
		if (mode == 0) {
			break;
		}
		else if (mode == 1) {
			list = import_data();
			system("pause");
			break;
		}
		else if (mode == 2) {
			export_data(list);
			system("pause");
			break;
		}
		else {
			printf("无法识别功能序号,请重新输入!\n");
			continue;
		}
	}
	}
	else if (mode == 6) {
		printf("感谢使用!\n");
		break;
	}
	else {
		printf("无法识别功能序号,请输入正确的功能序号!\n");
		system("pause");
	}
}
}