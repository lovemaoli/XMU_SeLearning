#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define MAX_VERTEX_NUM 30

typedef struct ArcNode {
	int adjvex;
	struct ArcNode *nextarc;
} ArcNode;

typedef struct VNode {
	int data;
	ArcNode *firstarc;
} VNode,AdjList[MAX_VERTEX_NUM];

typedef struct {
	AdjList vertices;
	int vexnum,arcnum;
} ALGraph;

void creat_DG_ALGraph(ALGraph *G) {
	int i,j,k;
	ArcNode *p,*q;
	p=q=NULL;
	printf("Please input vexnum,arcnum=:\n");
	scanf("%d %d",&G->vexnum,&G->arcnum);
	printf("Please input VNode:\n");
	for(i=0; i<G->vexnum; i++) {
		scanf("%d",&G->vertices[i].data);
		G->vertices[i].firstarc=NULL;
	}
//	for(i=0; i<G->vexnum; i++)
//		printf("%d ",G->vertices[i].data);
	printf("\n");
	for(k=0; k<G->arcnum; k++) {
		p=(ArcNode*)malloc(sizeof(ArcNode));
		q=(ArcNode*)malloc(sizeof(ArcNode));
		printf("please input edge <i,j>: \n");
		scanf("%d %d", &i, &j);
//		ÎÞÏòÍ¼
		p->adjvex = j;
		p->nextarc = G->vertices[i].firstarc;
		G->vertices[i].firstarc=p;
		q->adjvex = i;
		q->nextarc = G->vertices[j].firstarc;
		G->vertices[j].firstarc=q;
	}
}
int visited[MAX_VERTEX_NUM]={0},length;
int exist_path_DFS(ALGraph G,int i,int j,int k) {
	ArcNode *p;
	int tmp;
	p=NULL;
	if(i==j&&k==length) return 1;
	else {
		visited[i]=1;
		for(p=G.vertices[i].firstarc; p; p=p->nextarc) {
			tmp=p->adjvex;
			if(!visited[tmp]&&exist_path_DFS(G,tmp,j,k+1)) {
				return 1;
			}
		}
		visited[i]=0;
	}
	return 0;
}

int main() {
	ALGraph *G;
	int i,j;
	G=(ALGraph*)malloc(sizeof(ALGraph));
	creat_DG_ALGraph(G);
	while(1) {
		memset(visited,0,sizeof(visited));
		printf("Please input i->j and length k you want to find:\n");
		scanf("%d %d %d",&i,&j,&length);
		if(i==j&&i==0)return 0;
		if(exist_path_DFS(*G,i,j,0)) printf("Exist the path!\n");
		else printf("Not exist the path!\n");
	}
	return 0;
}
/*
9 7
0 1 2 3 4 5 6 7 8
0 1
1 2
2 4
2 5
4 8
3 6
6 7

0 1 2
1 3 3
1 8 3
3 7 2
0 0 0
*/
