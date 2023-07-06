#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MGraph.h"
/*邻接矩阵的8个基本操作函数定义*/
int LocateVex(MGraph G,VertexType u) {
	//初始条件：图G存在，u和G中顶点有相同特征
	// 操作结果：若G中存在顶点u，则返回该顶点在图中位置；否则返回-1
	int i;
	for(i=0; i<G.vexnum; ++i)
		if(strcmp(u,G.vexs[i]) == 0)
			return i;   // VertexType是char [16]类型
	return -1;
}

VertexType* GetVex(MGraph G,int v) {
	// 初始条件：图G存在，v是G中某个顶点的序号。操作结果：返回v的值
	if( v>=G.vexnum || v<0 )
		exit(0);
	return &(G.vexs[v]);
}

void visit(VertexType i) {
	printf("%s ",i);
}

int FirstAdjVex(MGraph G,VertexType v) {
	// 初始条件：图G存在，v是G中某个顶点
	// 操作结果：返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点，则返回-1
	int i,j=0,k;
	k=LocateVex(G,v); // k为顶点v在图G中的序号
	if(G.kind%2) // 网
		j=INFINITY;
	for(i=0; i<G.vexnum; i++)
		if(G.arcs[k][i].adj!=j)
			return i;
	return -1;
}

int NextAdjVex(MGraph G,VertexType v,VertexType w) {
	// 初始条件：图G存在，v是G中某个顶点，w是v的邻接顶点
	// 操作结果：返回v的(相对于w的)下一个邻接顶点的序号，若w是v的最后一个邻接顶点，则返回-1
	int i,j=0,k1,k2;
	k1=LocateVex(G,v); // k1为顶点v在图G中的序号
	k2=LocateVex(G,w); // k2为顶点w在图G中的序号
	if(G.kind%2) // 网
		j=INFINITY;
	for(i=k2+1; i<G.vexnum; i++)
		if(G.arcs[k1][i].adj!=j)
			return i;
	return -1;
}

void CreateGraphF(MGraph &G) {
	// 采用数组(邻接矩阵)表示法，由文档构造无向网G
	int i,j,k,w;
	VertexType va,vb;
	printf("请输入图的类型(有向图:0,有向网:1,无向图:2,带权连通图:3): \n");
	scanf("%d",&G.kind);
	printf("图的顶点的个数n:\n");
	scanf("%d",&G.vexnum);
	printf("图的边的条数m:\n");
	scanf("%d",&G.arcnum);
	printf("n个顶点的数据:\n");
	for(i=0; i<G.vexnum; ++i)            // 构造顶点矢量
		scanf("%s",G.vexs[i]);
	printf("m条边的数据:\n");
	for(i=0; i<G.vexnum; ++i)            // 初始化邻接矩阵
		for(j=0; j<G.vexnum; ++j) {
			if(G.kind%2)                 // 网
				G.arcs[i][j].adj=INFINITY;
			else                         // 图
				G.arcs[i][j].adj=0;
		}
	for(k=0; k<G.arcnum; ++k) {
		if(G.kind%2)                 // 网
			scanf("%s%s%d",va,vb,&w);
		else                         // 图
			scanf("%s%s",va,vb);

		i=LocateVex(G,va);
		j=LocateVex(G,vb);
		if(G.kind == 0)              // 有向图
			G.arcs[i][j].adj =1;
		else if(G.kind == 1)
			G.arcs[i][j].adj=w;      // 有向网
		else   if(G.kind == 2)       // 无向图
			G.arcs[i][j].adj =  G.arcs[j][i].adj=1;
		else
			G.arcs[i][j].adj =  G.arcs[j][i].adj = w;
	}
}

void DestroyGraph(MGraph &G) {
	// 初始条件：图G存在。操作结果：销毁图G
	int i,j,k=0;
	if(G.kind%2) // 网
		k=INFINITY; // k为两顶点之间无边或弧时邻接矩阵元素的值
	G.vexnum=0; // 顶点数为0
	G.arcnum=0; // 边数为0
}

void Display(MGraph G) {
	// 输出邻接矩阵存储表示的图G
	int i,j;
	switch(G.kind) {
		case DG:
			printf("有向图\n");
			break;
		case DN:
			printf("有向网\n");
			break;
		case UDG:
			printf("无向图\n");
			break;
		case UDN:
			printf("带权连通图\n");
	}
	printf("%d个顶点%d条边。顶点依次是: ",G.vexnum,G.arcnum);
	for(i=0; i<G.vexnum; ++i)       // 输出G.vexs
		printf("%s ",G.vexs[i]);
	printf("\n图的邻接矩阵:\n");     // 输出G.arcs.adj

	for(i=0; i<G.vexnum; i++) {
		for(j=0; j<G.vexnum; j++)
			if(G.kind%2) {
				if(G.arcs[i][j].adj==INFINITY)
					printf("%s\t","∞");
				else
					printf("%d\t",G.arcs[i][j].adj);
			} else
				printf("%d\t",G.arcs[i][j].adj);
		printf("\n");
	}
}

