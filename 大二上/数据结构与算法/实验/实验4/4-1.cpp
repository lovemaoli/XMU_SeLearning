#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "MGraph.cpp"
#include "MGraph.h"

typedef struct min { //记录从顶点集U到V-U的代价最小的边的辅助数组定义
	VertexType adjvex;
	VRType lowcost;
} minside[MAX_VERTEX_NUM];

int minimum(minside SZ,MGraph G) { //求SZ.lowcost的最小正值，并返回其在SZ中的序号
	int i=0,j,k,min;
	while(!SZ[i].lowcost)
		i++;
	min=SZ[i].lowcost;                         // 第一个不为0的值
	k=i;
	for(j=i+1; j<G.vexnum; j++)
		if(SZ[j].lowcost>0&&min>SZ[j].lowcost) { // 找到新的大于0的最小值
			min=SZ[j].lowcost;
			k=j;
		}
	return k;
}

void MiniSpanTree_PRIM(MGraph G,VertexType u) {	// 用Prim算法从第u个顶点出发构造网G的最小生成树T，输出T的各条边
	int i,j,k;
	minside closedge;
	k=LocateVex(G,u);
	for(j=0; j<G.vexnum; ++j) {
		strcpy(closedge[j].adjvex,u);
		closedge[j].lowcost=G.arcs[k][j].adj;
	}
	closedge[k].lowcost=0;
	printf("最小代价生成树的各条边为:\n");
	for(i=1; i<G.vexnum; ++i) {
		k=minimum(closedge,G);
		printf("边(%s,%s),权值为%d\n",closedge[k].adjvex,G.vexs[k],closedge[k].lowcost);
		closedge[k].lowcost=0;
		for(j=0; j<G.vexnum; ++j)
			if(G.arcs[k][j].adj<closedge[j].lowcost) {
				strcpy(closedge[j].adjvex,G.vexs[k]);
				closedge[j].lowcost=G.arcs[k][j].adj;
			}
	}
}

int main() {
	MGraph g;
	int n;
	CreateGraphF(g);  // 利用数据文档创建无向图
	Display(g);      // 输出无向图
	printf("请输入构造最小生成树的起点：\n");
	scanf("%d",&n);
	printf("用普里姆算法从g的第%d个顶点出发输出最小生成树的各条边:\n",n);
	MiniSpanTree_PRIM(g,g.vexs[n]);  // Prim算法从第1个顶点构造最小生成树
	return 0;
}

/*
3
5
8
0
1
2
3
4
0 1 1
0 2 3
0 3 4
0 4 7
1 2 2
2 3 5
2 4 8
3 4 6
0
*/
