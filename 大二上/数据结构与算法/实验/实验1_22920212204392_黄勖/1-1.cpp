#include<stdio.h> 
#include<stdlib.h>

typedef struct node {
	int data;    //数据域，这里定义为int类型 
	struct node *next; //指针域
}Node,*LinkList;

//创建空链表
LinkList create() {
	LinkList list=(LinkList)malloc(sizeof(Node));//申请空间
	if(list!=NULL) list->next=NULL;
	else printf("Create failed!\n");
	return(list);
}

//判断空链表
int isempty(LinkList list) {
	return(list->next==NULL);
}

//在链表中找某元素的存储位置
int find(LinkList list,int x) {
	Node* p=list->next;
	int i=1; 
	while(p->next!=NULL && p->data!=x){
		p=p->next;
		i++;
	}
	if(p->data!=x)i=0; 
	return i;
}

//单链表的插入（链表末尾插入元素x） 
int insert(LinkList list,int x) {
	Node *p=list,*q=(Node*)malloc(sizeof(Node));
	while(p->next!=NULL){
		p=p->next;
	}
	if(p==NULL) {
		printf("Insert failed!\n");
		return 0;
	} else {
		q->data=x;
		q->next=NULL;
		p->next=q;
		return 1;
	}
}

// 单链表的删除(删除第一个值为x的结点)
int delete_node(LinkList list,int x) {
	Node *p,*q;
	p=list;
	if(p->next==NULL)  return 0;
	while(p->next!=NULL && p->next->data!=x)
		p=p->next;//找值为x的结点的前驱结点的存储位置
	if(p->next==NULL) { //没找到值为x的结点
		printf("Not exist!\n");
		return 0;
	} else {
		q=p->next;
		p->next=q->next;
		free(q);
		return 1;
	}
}

//打印链表 
void show(LinkList list){
	Node *p=list->next;
	while(p!=NULL) {
		if(p->next==NULL)
			printf("%d",p->data);
		else
			printf("%d->",p->data);
		p=p->next;
	}
	printf("\n");
}

int main() {
	int i,x;
	Node *p;
	LinkList list1;
	list1=create();
	if(list1!=NULL)
		printf("创建空表成功！\n");
	for(i=0; i<5; i++) {
		printf("请输入第 %d 个结点的值：",i+1);
		scanf("%d",&x);
		insert(list1,x);
	}
	printf("\n");
	show(list1);
	printf("\n");
	printf("请输入查找结点的值：\n");
	scanf("%d",&x);
	if(!find(list1,x)){
		printf("未查找到！\n");
	}else{
		printf("在第%d个节点找到该元素！\n", find(list1,x));
	}
	printf("请输入删除结点的值：",i+1);
	scanf("%d",&x);
	delete_node(list1,x);
	printf("\n");
	show(list1);
	return 0;
}
