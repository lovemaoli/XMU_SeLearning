#ifndef   __MGraph_H__
#define   __MGraph_H__
typedef int VRType;    // 顶点关系类型
typedef char VertexType[20]; // 顶点类型
// 图的数组(邻接矩阵)存储表示
#define INFINITY 4270000 // 用整型最大值代替∞ 
#define MAX_VERTEX_NUM 20 // 最大顶点个数 
typedef enum {DG,DN,UDG,UDN} GraphKind; // {有向图,有向网,无向图,无向网}

typedef struct {
	VRType adj; // 顶点关系类型。对无权图，用1(是)或0(否)表示相邻否；对带权图，则为权值
} ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 二维数组

typedef struct {    // 图的数组(邻接矩阵)存储
	VertexType vexs[MAX_VERTEX_NUM]; // 顶点矢量
	AdjMatrix arcs; // 邻接矩阵
	int vexnum,arcnum; // 图的当前顶点数和弧数
	GraphKind kind; // 图的种类标志
} MGraph;

/*邻接矩阵的8个基本操作函数声明*/
int LocateVex(MGraph G,VertexType u);//若图G中存在顶点u，则返回该顶点在图中位置；否则返回-1
VertexType* GetVex(MGraph G,int v);// 根据图G中某个顶点的序号v，返回该顶点的值
void visit(VertexType i);// 访问输出顶点的值
int FirstAdjVex(MGraph G,VertexType v);// v是图G中某个顶点，返回v的第一个邻接顶点的序号。若顶点v在G中没有邻接顶点，则返回-1
int NextAdjVex(MGraph G,VertexType v,VertexType w);//v是图G中某个顶点，w是v的邻接顶点，返回v的(相对于w的)下一个邻接顶点的序号，若w是v的最后一个邻接顶点，则返回-1
void CreateGraphF(MGraph &G);//采用数组(邻接矩阵)表示法，由文档构造无向网G
void DestroyGraph(MGraph &G);//销毁图G
void Display(MGraph G);//输出邻接矩阵存储表示的图G
#endif

