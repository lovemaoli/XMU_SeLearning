#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CHAR  20  // 最大字符
#include<time.h>
#define MAX_NUM  200  // 单词的最大个数
struct word

//单词的结构体
{
	char  en[MAX_CHAR]; // 英文形式
	char  ch[MAX_CHAR];   //中文形式
}
s[MAX_NUM]; //单词数组
int   num;           //单词个数
int select=1;//select 为是否退出系统的标记
int d=0,c=0;
int in;

//帮助
void help() {
	printf("\n本系统主要实现英语单词学习的功能。用户可对词典文件中的单词进行预览，增删改查。");
	printf("\n同时还可进行中英、英中测试。本系统还提供了测试成绩的显示功能。");
}

//从文件中读取单词的信息
void  readfile() {
	FILE *fp;
	int i=0;
	fp=fopen("data.txt","r");
	if(!fp) {
		printf("\n打开文件data.txt失败!");
	}
	while(fscanf(fp,"%s %s ",s[i].en,s[i].ch)==2) {
		i++;
	}
	num=i;
	if(0==i)
		printf("\n文件为空，请选择词典维护增加词条！");
	else
		printf("\n");
	fclose(fp);
}

//从文件中读取单词的信息
void  writefile() {
	FILE *fp;
	int i=0;
	fp=fopen("data.txt","w");
	if(!fp) {
		printf("\n打开文件data.txt失败!");
	}
	for(i=0; i<num; i++) {
		fprintf(fp,"\n%s %s ",s[i].en,s[i].ch);
	}
	printf("\n");
	fclose(fp);
}

//从增强记忆文件中读取单词
void  readRemeberfile() {
	FILE *fp;
	int i=0;
	fp=fopen("Remeberdata.txt","r");
	if(!fp) {
		printf("\n打开文件Remeberdata.txt失败!");
	}
	while(fscanf(fp,"%s %s ",s[i].en,s[i].ch)==2) {
		i++;
	}
	num=i;
	if(0==i)
		printf("\n你还没有错题哦！");
	else
		printf("\n");
	fclose(fp);
}

void sort() { /*按字典排序*/
	int i,j;
	char temp[MAX_CHAR];
	for(i=0; i<num-1; i++) {
		for(j=num-1; j>i; j--) {
			if(strcmp(s[j-1].en,s[j].en)>0) {
				strcpy(temp,s[j-1].en);
				strcpy(s[j-1].en,s[j].en);
				strcpy(s[j].en,temp);
				strcpy(temp,s[j-1].ch);
				strcpy(s[j-1].ch,s[j].ch);
				strcpy(s[j].ch,temp);
			}
		}
	}
}

//添加单词信息
void add() {
	int i=num,j,flag=1;
	while(flag) {
		flag=0;
		printf("\n请输入单词的英文形式:");
		scanf("%s",s[i].en);
		for(j=0; j<i; j++)
			if(strcmp(s[i].en,s[j].en)==0) {
				printf("已有该单词,请检查后重新录入!\n");
				flag=1;
				break; /*如有重复立即退出该层循环,提高判断速度*/
			}
	}
	printf("\n请输入单词的中文形式:");
	scanf("%s",s[i].ch);
	num++;
	printf("\n您输入的信息为: 英文: %s 中文: %s  ",s[i].en,s[i].ch);
	sort();
}

//删除单词信息
void del() {
	int i=0,j=0;
	char  en[MAX_CHAR];   //英文形式
	printf("\n请输入你要删除的单词英文形式:");
	scanf("%s",en);
	for(i=0; i<num; i++) //先找到该英文形式对应的序号
		if(strcmp(s[i].en,en)==0) {
			for(j=i; j<num-1; j++)
				s[j]=s[j+1];
			num--; //数量减少 1
			return;
		}
	printf("\n没有这个单词!");
}

//修改单词信息
void modify() {
	int i=0,choose=0,flag=1;//chooses代表选项标识，flag代表是否找到单词
	char  en[MAX_CHAR];   //英文形式
	while(flag||choose) {
		printf("\n请输入你要修改的单词英文形式:");
		scanf("%s",en);
		for(i=0; i<num; i++) //先找到该英文形式对应的序号
			if(strcmp(s[i].en,en)==0) {
				printf("\n请输入单词正确的英文形式:");
				scanf("%s",s[i].en);
				printf("\n请输入此单词正确的的中文形式:");
				scanf("%s",s[i].ch);
				printf("\n继续修改请选1，返回上一级请选0:");
				scanf("%d",&choose);
				if(choose==0) return;
			}
		flag=0;
	}
	if(!flag)  printf("\n没有这个单词!");
}

//单词预览
void show() {
	int  i=0;
	printf("\n单词：     英文        中文         ");
	for(i=0; i<num; i++)
		printf("\n          %-12s%-12s",s[i].en,s[i].ch);
}

//查询单词
void search() {
	int i=0,choose=0,flag=1;
	char  ch[MAX_CHAR];   //中文形式
	char  en[MAX_CHAR];   //英文形式
	while(choose||flag) {
		printf("请选择中文查询或英文查询。\n");
		printf("1.按照单词中文形式查询\n");
		printf("2.按照单词英文形式查询\n");
		scanf("%d",&in);
		switch(in) {
			case 1: {
				while(flag) {
					printf("\n请输入你要查询的单词的英文形式：");
					scanf("%s",en);
					for(i=0; i<num; i++) { //先找到该英文形式对应的序号
						if(strcmp(s[i].en,en)==0) {
							printf("\n英文形式          中文形式            ");
							printf("\n    %-12s%12%",s[i].en,s[i].ch);
						}
					}
					printf("\n继续查询选1，返回上一级选0：");
					scanf("%d",&choose);
					if(choose==0)
						return;
					flag=0;
				}
				if(!flag)
					printf("\n没有这个单词!");
			}
			break;
			case 2: {
				while(flag) {
					printf("\n请输入你要查询的单词的中文形式：");
					scanf("%s",ch);
					for(i=0; i<num; i++) { //先找到该中文形式对应的序号
						if(strcmp(s[i].ch,ch)==0) {
							printf("\n英文形式          中文形式          ");
							printf("\n   %-12s%12s",s[i].en,s[i].ch);
						}
					}
					printf("\n继续查询请选1，返回上一级请选0:");
					scanf("%d",&choose);
					if(choose==0) return;

					flag=0;
				}
				if(!flag)
					printf("\n没有这个单词!");
			}
			break;
			default:
				printf("输入的选项不合适，请重新输入！");
				break;
		}
	}
}

//中译英测试
void zytest() {
	char b1[20];
	int z;
	int choose=1;
	int   i;
	while(choose) {
		i = rand()%num;
		printf("\n【%s】请输入英文单词:\n\n",s[i].ch);
		gets(b1);
		printf("\n【%s】\n\n",s[i].en);
// 	scanf("%s",b1);
		if(strcmp(b1,s[i].en)!=0) {

			printf("\n输入错误!你好傻!\n");

		} else {
			printf("\n恭喜你，回答正确\n\n");

		}

	}
}

//英译中测试
void yztest() {
	char b1[20];
	int z,x=41;
	int choose=1;
	int   i;
	i = rand()%num;
	while(choose) {
		i = rand()%num;
		printf("\n【%s】请输入中文意思:\n\n",s[i].en);
		gets(b1);
		printf("\n【%s】\n\n",s[i].ch);
		if(strcmp(b1,s[i].ch)!=0) {

			printf("\n输入错误！你好傻！\n");
		} else {
			printf("\n恭喜你，回答正确!\n\n");
		}
	}
}

//成绩列表
void list() {
	printf("\n 共计输入错误:%d次 **每次扣10分**\n",c);
	printf(" 共计输入正确:%d次 **每次加10分**\n",d);
	printf(" 你的总得分为:%d分\n\n",10*d-10*c);
}

//词典维护
void maintain() {
	int choose;//维护功能选择
	printf("   ------------------\n");
	printf("   1.增加单词\n");
	printf("   2.修改单词\n");
	printf("   3.删除单词\n");
	printf("   4.查询单词\n");
	printf("   5.退出本菜单\n");
	printf("   ------------------\n");
	while(1) {
		printf(" \n请输入维护功能编号:");
		scanf("%d",&choose);
		switch(choose) {
			case 1:
				add();
				writefile();
				break;
			case 2:
				modify();
				writefile();
				break;
			case 3:
				del();
				writefile();
				break;
			case 4:
				search();
				break;
			case 5:
				return;
			default:
				printf("\n请在1-5之间选择");
		}
	}
}

//用户界面
void menu() {
	int item;
	srand((int)time(0));
	printf("\n");
	printf("***************************************************************\n");
	printf("#                                                             #\n");
	printf("#                         英语单词小助手                      #\n");
	printf("#                                                             #\n");
	printf("#                        版本 ： v1.0   by maoli              #\n");
	printf("#                                                             #\n");
	printf("***************************************************************\n");
	printf("#                                                             #\n");
	printf("#       0.词库维护          1.单词预览                        #\n");
	printf("#                                                             #\n");
	printf("#       2.单词背诵(中英)    3.单词背诵(英中)                  #\n");
	printf("#                                                             #\n");
	printf("#       4.查询成绩          5.帮助                            #\n");
	printf("#                                                             #\n");
	printf("#       6.退出系统                                            #\n");
	printf("#                                                             #\n");
	printf(" **************************************************************\n");
	printf("\n");
	printf("       请选择您需要的操作序号(0-5)按回车确认:");
	scanf("%d",&item);
	printf("\n");
	readfile();
	switch(item) {
		case 0:
			maintain();
			break;
		case 1:
			show();
			break;
		case 2:
			zytest();
			break;
		case 3:
			yztest();
			break;
		case 4:
			list();
			break;
		case 5:
			help();
			break;
		case 6:
			select =0;
			break;
		default:
			printf("请在0-6之间选择\n");
	}
}
int main() {
	while(select) {
		menu();
	}
	system("pause");
	return 0;
}

