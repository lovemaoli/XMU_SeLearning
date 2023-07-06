#include<stdio.h>
#include<stdlib.h>
#define MAXVEX 100   //最大定点顶点数 
#define INFINITF 65535  //用 65535来表示无穷 
#define	MAX 100
#define MAXSIZE 100
#define TRUE 1
#define FALSE 0 
#define OK 1 
#define ERROR 0
typedef int Boolean;	//Boolean是布尔类型，其值是TRUE或FALSE 
Boolean visited[MAX];
typedef struct{
	char vexs[MAXVEX];  //顶点表 
	int arc[MAXVEX][MAXVEX];  //邻接矩阵，可看作边表
	int numVertexes,numEdges;  //图中当前的顶点数 
	int GraphType; //图的类型 
}MGraph;
typedef struct{
	int data[MAXSIZE];
	int front;     //头指针 
	int rear; //尾指针，若队列不空，指向队列尾元素的下一个位置 
}SqQueue;
//初始化一个空队列
int InitQueue(SqQueue *Q)
{
	Q->front=0;
	Q->rear=0;
	return OK;
}
int QueueEmpty(SqQueue Q)
{
	if(Q.rear==Q.front)
		return TRUE;
	else
		return FALSE;
}
//循环队列入队列操作 
int EnQueue(SqQueue *Q,int e) 
{
	if ((Q->rear+1)%MAXSIZE == Q->front);  //队列满的判断
		return ERROR;
	Q->data[Q->rear]=e;  //将元素e赋值给队尾
	Q->rear=(Q->rear+1)%MAXSIZE; //rear指针向后移一位置,若到最后则转到数组头部
	return OK; 
}
// 循环队列出队列操作
int DeQueue(SqQueue *Q,int *e)
{
	if (Q->front == Q->rear)
		return ERROR; //队列空的判断
	*e = Q->data[Q->front];  //将队头元素赋值给e 
	Q->front=(Q->front+1)%MAXSIZE; //front指针向后移一位置
	return OK; 
} 
void CreateMGraph (MGraph *G)
{
	int i,j,k,w;
	printf("输入顶点数和边数：\n");
	scanf("%d %d",&G->numVertexes,&G->numEdges); //输入顶点数和边数
	fflush(stdin);
	for(i=0;i<G->numVertexes;i++)
	{
		printf("第%d个顶点：",i+1);
		scanf("%c",&G->vexs[i]);
		getchar(); 
	}
	for(i=0;i<G->numVertexes;i++)
		for(j=0;j<G->numVertexes;j++)
			G->arc[i][j]=INFINITF ; //邻接矩阵初始化 
	for(k=0;k<G->numEdges;k++)
	{
		printf("输入边(vi,vj)上的上标i,下标j和权W:");
		scanf("%d %d %d",&i,&j,&w); //输入边(vi,vj)上的权W
		G->arc[i][j]=w;
		if(G->GraphType==0)
		G->arc[j][i]=G->arc[i][j];  //因为是无向图，矩阵对称 
	}
}
  //输出邻接矩阵
void output(MGraph *G) 
{
	int i,j,count=0;
	for (i=0;i<G->numVertexes;i++)
		printf("\t%c",G->vexs[i]);	
	printf("\n");
	for(i=0;i<G->numVertexes;i++)
	{
		printf("%4c",G->vexs[i]);
		for(j=0;j<G->numVertexes;j++)
		{
			printf("\t%d",G->arc[i][j]);
			count++;
			if(count%G->numVertexes==0)
			printf("\n");
		}
	}
}
//邻接矩阵的深度优先递归算法 
void DFS (MGraph G,int i)
{
	int j;
	visited[i]=TRUE;
	printf("%c ",G.vexs[i]);  //打印顶点
	for(j=0;j<G.numVertexes;j++)
	{
		if(G.arc[i][j]==1&&!visited[j])
		DFS(G,j);  //对未访问的邻接顶点递归调用 
	}	 
} 
//邻接矩阵的深度遍历操作
void DFSTraverse(MGraph G)
{
	int i;
	for(i=0;i<G.numVertexes;i++)
		visited[i]=FALSE;  //初始化所有顶点状态都是未访问过状态 
	for(i=0;i<G.numVertexes;i++)
		if(!visited[i])   //对未访问过的顶点调用DFS，若是连通图，只会执行一次 
		DFS(G,i); 
} 
void BFSTraverse(MGraph G)
{
	int i,j;
	SqQueue Q;
	for(i=0;i<G.numVertexes;i++)
		visited[i]=FALSE;
	InitQueue(&Q);  //初始化一辅助用的队列
	for(i=0;i<G.numVertexes;i++)  //对每个顶点做循环 
	{
		if(!visited[i])  //若是未访问过就处理 
		{
			visited[i]=TRUE;  //设置当前顶点访问过 
			printf("%c ",G.vexs[i]);  //打印顶点
			EnQueue(&Q,i);	 //将此顶点入队列 
			while(!QueueEmpty(Q)) //若当前队列不为空 
			{
				DeQueue(&Q,&i); //将队中元素出队列，赋值给i 
				for(j=0;j<G.numVertexes;j++)
				{
					//判断其他结点若与当前顶点存在且未访问过 
					if(G.arc[i][j] == 1&& !visited[j])
					{
						visited[j]=TRUE;  //将找到的此顶点标记为已访问 
						printf("%c ",G.vexs[j]);  //打印顶点 
						EnQueue(&Q,j); //将找到的此顶点入队列 
					}
				}
			} 
		} 
	} 
}
int main()
{
	MGraph G;
	int i,j;
	printf("输入图的类型（无向图0/有向图1）：");
	scanf("%d",&G.GraphType); 
	CreateMGraph (&G);
	printf("邻接矩阵数据如下：\n");
	output(&G); 
	printf("\n");
	printf("图的深度优先遍历如下:\n");
	DFSTraverse(G);
	printf("\n图的广度优先遍历如下：\n");
	BFSTraverse(G);
	return 0;
}
