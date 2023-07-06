#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#define path "map.txt"
#include <windows.h>
#include <vector>
#include <iostream>
using namespace std;
const int MAX = 105;
const int inf = 0x3f3f3f;
// 景区旅游信息管理系统

typedef struct node {
	char PlaceName[MAX]; // 景点的名字　
	int number; //　景点编号　
	char PlaceNum[MAX]; // 编号;
} Node;
typedef struct Tornode {
	int u;
	int v;
	int weight;
} TorNode; // 起点终点和距离;
typedef struct matGraph {
	int map[MAX][MAX];
	int n , e;
} MatGraph; // 完整的图邻接矩阵类型

typedef struct NODE {
	int key;// 关键字项
	Node infor; // 信息
	struct NODE *lchild;
	struct NODE *rchild;
} BSTNode;

typedef struct ANode {
	int adjvex; // 编号
	struct ANode *nextarc;
	int weight;

} ArcNode; // 边节点的类型
typedef struct Vnode {

	ArcNode *fitstarc;
	int count;
} VNode; // 邻接表的头结点类型
typedef struct {
	VNode adjlist[MAX];
	int n , e; // 边数和顶点数
} AdjGraph;
int vis[MAX];
int dis[MAX];
int state=0; 
int count1;
BSTNode *MapVex[MAX]; // 顶点
void CreatMatGragh(MatGraph &GT  ,int n ,int e , int pot, TorNode Gr[MAX][MAX]) {
	// 创建导游有向图;
	for(int i = 1; i<=n; i++) {
		for(int j = 1; j <=n; j++) {
			if(i == j ) {
				GT.map[i][j] = 0;
			}
			GT.map[i][j] = inf;
		}
	}
	for(int i = 1; i<=e; i++) {
		GT.map[Gr[pot][i].u][Gr[pot][i].v] = Gr[pot][i].weight;
	}
	return;
}
int cmp(const Node &a , const Node &b) {
	return a.number <b.number;
}
int digit(int x ) {
	// 计算位数
	int t = x;
	int k = 0;
	while(t) {
		k++;
		t/=10;
	}
	return k;
}
char *transtr(int n) {
	//转换成字符串
	//char t[MAX];
	char *t;
	t = new char[MAX];
	int i = 0 ,x = n;
	while(x) {
		t[digit(n) - i-1] = (x%10) + '0';
		x/=10;
		i++;
	}
	return t;
}
void Read(Node Place[] ,int n ,int e) {
	// 读取数据
	FILE *fp;
	fp = fopen(path,"r");
	if(fp == NULL) {
		perror("fopen\n");
		exit(-1);
	}
	for(int i = 1; i<=n; i++) {
		fscanf(fp,"%s %d",Place[i].PlaceName,&Place[i].number);
		int d = digit(Place[i].number);
		char Tmp[MAX] = "000";
		if(d==1) {
			strcpy(Place[i].PlaceNum,transtr(Place[i].number));
			strcat(Tmp,Place[i].PlaceNum);
			strcpy(Place[i].PlaceNum,Tmp);
		} else if(d==2) {
			char Tmp[MAX] = "00";
			strcpy(Place[i].PlaceNum,transtr(Place[i].number));
			strcat(Tmp,Place[i].PlaceNum);
			strcpy(Place[i].PlaceNum,Tmp);

		} else if(d==3) {
			char Tmp[MAX] = "0";
			strcpy(Place[i].PlaceNum,transtr(Place[i].number));
			strcat(Tmp,Place[i].PlaceNum);

		}
		Place[i].PlaceNum[4]='\0';
	}

	return;
}

void MAtToList(MatGraph g , AdjGraph *&G) {
	//将邻接矩阵转换成邻接表
	ArcNode *p; // 边节点

	G = (AdjGraph *)malloc(sizeof(AdjGraph));
	for(int i = 1; i<=g.n; i++) {
		G->adjlist[i].fitstarc = NULL;
	}
	for(int i = 1; i<= g.n; i++) {
		for(int j = g.n; j >=1; j--) {
			if(g.map[i][j]!= 0 && g.map[i][j] !=inf ) {
				p = (ArcNode *)malloc(sizeof(ArcNode));
				p->adjvex = j;
				p->weight = g.map[i][j];
				p->nextarc = G->adjlist[i].fitstarc;
				G->adjlist[i].fitstarc = p;
			}
		}
	}
	G->n = g.n;
	G->e = g.e;
	return;
}
int DispAdj(AdjGraph *G ) {
	// 输出邻接表
	ArcNode *p;
	int count = 0;
	for(int i = 1; i <=G->n; i++ ) {
		p = G->adjlist[i].fitstarc;
		printf("%3d: " ,i );
		while(p!=NULL ) {
			printf("%3d[%d]-> ", p->adjvex , p->weight );
			p = p->nextarc;
			count++;
		}
		printf(" ^ \n");
	}

	return count;
}
BSTNode *SearchBST(BSTNode *bt , int k ) {
	// 在二叉搜素树中查找 编号为k 的节点
	// return 节点的地址
	if(bt == NULL || bt->infor.number == k ) {
		return bt;
	}
	if(k < bt->infor.number) {
		return SearchBST(bt->lchild , k);
	} else {
		return SearchBST(bt->rchild , k );
	}

}
void TopSort(AdjGraph *G) {
	// 拓扑排序;
	int St[MAX]  , top = -1;
	ArcNode * p;
	for(int i  = 1;  i<=G->n; i++) {
		G->adjlist[i].count = 0; // 初始化
	}
	for(int i  = 1; i<=G->n; i++) {
		p = G->adjlist[i].fitstarc;
		while(p!=NULL) {
			G->adjlist[p->adjvex].count++;
			p = p->nextarc;

		}
	}

	for(int i = 1;  i <=G->n; i++) {
		if(G->adjlist[i].count == 0 ) {
			top++;
			St[top] = i;

		}
	}
	int i  , j;
	while(top>-1) {
		i = St[top];
		top --;
		cout<<i<<" ";
		p = G->adjlist[i].fitstarc;
		while(p!=NULL) {
			j = p->adjvex;
			G->adjlist[j].count --;
			if(G->adjlist[j].count ==0 ) {
				top++;
				St[top] = j;
			}
			p = p->nextarc;   // 下一个邻接点;
		}
	}


}

void DFS(AdjGraph *G , int v , Node Place[] ,BSTNode *bt  ) {
	// 深度优先搜素
	ArcNode *p;
	BSTNode *Root;
	vis[v] = 1;
	//printf("%d ",v);
	Root = SearchBST(bt,v);// 在二叉排序树中找到

	if(Root!=NULL) { // 小心驶得万年船,不加会异常
//		if(vis[p->adjvex] = 0  )

		cout<<Root->infor.PlaceName <<"-> ";
		MapVex[++count1]= Root;// 将DFS创建的节点依次加入到导游图中
		// 创建导游图,
	}

	p = G->adjlist[v].fitstarc;
	while(p!=NULL) {
		if(vis[p->adjvex] == 0 ) {
			vis[p->adjvex] = 1; //
			DFS(G,p->adjvex,Place,bt);
			//vis[p->adjvex] = 0; //
		}
		p = p->nextarc;
	}

}
void Display(Node Place[] ,int n) {
	// 显示所有景点名字
	cout<<"景点名字\t  编号\n";
	for(int i = 1; i<=n; i++) {
		printf("%8s\t%8s\n",Place[i].PlaceName,Place[i].PlaceNum);
		//	cout<<Place[i].PlaceName<< "\t"<<Place[i].PlaceNum<<endl;
		Sleep(100);
	}

}
void CreadMat(MatGraph &Map , int n , int e) {
	// 创建邻接矩阵
	FILE *fp;
	fp = fopen("edge.txt","r");
	for(int i = 1; i<=n; i++) {
		for(int j = 1; j<=n; j++) {
			Map.map[i][j] = inf;
			if(i == j )
				Map.map[i][j] = 0;
		}

	}
	Map.n = n;
	Map.e = e;
	for(int i = 1; i<=e; i++) {
		int u , v ,w;
		fscanf(fp,"%d %d %d",&u,&v,&w);
		Map.map[u][v] = w;// 无向图
		Map.map[v][u] = w;
	}
	return;
}

bool InsertBST(BSTNode *&bt , Node k ) {
	// 二叉排序树插入节点
	if(bt==NULL) {

		bt = (BSTNode*)malloc(sizeof(BSTNode));
		bt->infor.number = k.number;
		strcpy(bt->infor.PlaceName,k.PlaceName);
		strcpy(bt->infor.PlaceNum,k.PlaceNum);
		bt->lchild = NULL;
		bt->rchild = NULL;
		return true;
	} else if (k.number == bt->infor.number) {
		return false;
	} else if (k.number < bt->infor.number ) {
		return InsertBST(bt->lchild , k);
	} else if (k.number > bt->infor.number ) {
		return InsertBST(bt->rchild , k);
	}

}
BSTNode *CreatBST(Node Place[] , int n) {
	// 创建二叉排序树;
	BSTNode *bt = NULL;
	for(int i =  1; i <=n; i++) {
		InsertBST(bt,Place[i]);
	}

	return bt;
}
void Dijkstra(int cur,MatGraph Map,BSTNode *bt ,int End) {
	// 最短路Dijkstra 实现
	int n , e;
	int Path[MAX];
	n = Map.n;
	e = Map.e;
	memset(vis,0,sizeof(vis));
	memset(Path,0,sizeof(Path));

	for(int i = 1; i<=n; i++) {
		dis[i] = Map.map[cur][i];

		if(Map.map[cur][i] < inf) {
			Path[i] = cur;
		} else {
			Path[i] = 0;
		}
	}
	vis[cur] = 1;
	Path[cur] = 0;
	for(int i = 1; i<n; i++) {
		int minn = inf;
		int u = -1;
		for(int j = 1; j<=n; j++) {
			if(!vis[j] && dis[j]<minn) {
				minn = dis[j];
				u = j;
			}

		}
		if(u !=-1) {
			vis[u] = 1;

			for(int v = 1; v <=n; v++) {
				if(Map.map[u][v]<inf && vis[v]== 0) {

					if(dis[v] > dis[u]+Map.map[u][v]) {
						dis[v] = dis[u] + Map.map[u][v];

						Path[v] = u;

					}

				}
			}

		}
	}
	BSTNode *pfind1 ,*pfind2,*pfind3;
	int pre;
	for(int i=1; i<=n; i++) { //输出结果和最短路径
		pfind1 = SearchBST(bt,cur);
		pfind2 = SearchBST(bt,i);
		if(pfind1 && pfind2) {
			if(End == pfind2->infor.number) {
				printf("%s 到 %s的最短距离为 ",pfind1->infor.PlaceName,pfind2->infor.PlaceName);
				printf("%d m\n",dis[i]);  //打印结果
				pre = Path[i];
				printf("路径：%s",pfind2->infor.PlaceName);
			}

			while(pre!=0) { //继续找前趋顶点
				pfind3 = SearchBST(bt,pre);
				if(pfind1) {
					printf("<——%s",pfind3->infor.PlaceName);
					pre=Path[pre];
				} else {
					printf("\n");
					exit(0);
				}
			}

		} else {
			cout<<"输入错误 "<<endl;
			exit(0);
		}

	}

	return;
}

void Prim(MatGraph Map ,int cur ,BSTNode *bt) {
	// 最小生成树
	int lowcost[MAX];
	int MIN;
	int closet[MAX] , i , j , k;

	cout<<"往返道路规划  : "<<endl;
	for( i  = 1; i<=Map.n; i++) {
		//cout<<Map.map[cur][i]<<"  ";
		lowcost[i] = Map.map[cur][i];
		closet[i] = cur;
	}
	for( i = 1; i<Map.n; i++) {
		MIN = inf;
		for(j = 1; j<=Map.n; j++)

			if(lowcost[j]!=0 && lowcost[j] <MIN) {
				MIN = lowcost[j];
				k = j;
			}
		//printf("(%d ,%d)  : %d \n ",closet[k],k ,MIN);
		BSTNode *s = SearchBST(bt,closet[k]);
		BSTNode *sz = SearchBST(bt,k);
		if( s!=NULL && sz !=NULL) {
			cout<<s->infor.PlaceName <<" - "<<sz->infor.PlaceName <<endl;
		}

		lowcost[k] = 0;
		for(int j = 1; j <=Map.n; j++) {
			if(lowcost[j] !=0 && Map.map[k][j]<lowcost[j]) {
				lowcost[j] = Map.map[k][j];
				closet[j] = k;
			}
		}

	}
}
int Find(char *a, Node M[],int n  ) {
	//查找
	int i;

	bool find = false;
	for( i = 1; i <=n; i++) {
		if(strcmp(a,M[i].PlaceName)==0) {
			find = true;
			break;
		}
	}

	return find?M[i].number:-1;
}
void InOrder(BSTNode *bt ) {
	// 中序
	if(bt!=NULL) {
		InOrder(bt->lchild);
		cout<<bt->infor.number <<"   " <<bt->infor.PlaceName <<"  "<<bt->infor.PlaceNum <<endl;
		InOrder(bt->rchild);
	}
	return;
}
void PageInfor() {
	system("color 5E");
	cout<<"\t\t\t   *********************************************"<<endl;
	cout<<"\t\t\t   *                                           *"<<endl;
	cout<<"\t\t\t   *                                           *"<<endl;
	cout<<"\t\t\t   *\t       景区旅游信息咨询系统            *"<<endl;
	cout<<"\t\t\t   *                厦门市景区                 *"<<endl;
	cout<<"\t\t\t   *                                           *"<<endl;
	cout<<"\t\t\t   *                                           *"<<endl;
	cout<<"\t\t\t   *\t"<<" ☆"<<" 1  创建景区景点分布图        ☆    *"<<endl;
	cout<<"\t\t\t   *                                           *"<<endl;
	cout<<"\t\t\t   *\t"<<" ☆"<<" 2  输出景区景点分布图        ☆    *"<<endl;
	cout<<"\t\t\t   *                                           *"<<endl;
	cout<<"\t\t\t   *\t"<<" ☆"<<" 3  输出导游路线              ☆    *"<<endl;
	cout<<"\t\t\t   *                                           *"<<endl;
	cout<<"\t\t\t   *\t"<<" ☆"<<" 4  输出最佳导游路线          ☆    *"<<endl;
	cout<<"\t\t\t   *                                           *"<<endl;
	cout<<"\t\t\t   *\t"<<" ☆"<<" 5  输出最短路径              ☆    *"<<endl;
	cout<<"\t\t\t   *                                           *"<<endl;
	cout<<"\t\t\t   *\t"<<" ☆"<<" 6  输出往返路线规划图        ☆    *"<<endl;
	cout<<"\t\t\t   *                                           *"<<endl;
	cout<<"\t\t\t   *\t"<<" ☆"<<" 7  退出系统                  ☆    *"<<endl;
	cout<<"\t\t\t   *                                           *"<<endl;
	cout<<"\t\t\t   *                                           *"<<endl;
	cout<<"\t\t\t   *********************************************"<<endl;

	cout<<"功能选择 >>  :    ";

}
void DisplayMenu(int n ,int e ) {
	TorNode Gr[MAX][MAX];
	MatGraph Map ,TMP ,TorMap;
	int TourMap[MAX][MAX];
	AdjGraph *G;// 邻接表
	Node Place[MAX]; // 所有的景点信息
	char start[MAX] ,end[MAX]; // 起点和终点
	BSTNode *bt; // 二叉排序树根节点
	cout<<endl<<endl;
	int num;
	Read(Place,n,e); // 读入数据
	PageInfor(); // 显示页面信息

	while(cin >> num && num!=7) {

		if(num == 1 ) {
			CreadMat(Map,n,e);
			cout<<" 地图创建成功 "<<endl;
			state = 1;
		} else if(num == 2 ) {
			if(state < 1){
				cout << "地图未创建！" << endl;system("pause");PageInfor();
				continue;
			}
			// 显示景点图
			//Display(Place,n);

			cout<<"☆所有景点信息 ☆   \n";
			cout<<" 景点名字\t  编号\n";
			for(int i = 1; i <=n; i++) {
				cout<<Place[i].PlaceName<< "  : "<<Place[i].PlaceNum<<endl;
			}
			cout<<" 景区地图 "<<endl;
			for(int i = 1; i<= n; i++) {
				cout<<"  "<<i;
			}
			cout<<endl;
			int k = 1;

			for(int i = 1; i <=n; i++) {
				cout<<k++ <<"  ";

				for(int j = 1; j<=n; j++) {
					if(Map.map[i][j] == inf ) {
						cout<<"∞"<<" ";

					} else {
						printf("%d ",Map.map[i][j]);

					}
				}
				cout<<endl;
			}
			cout<<endl;

		}

		else if(num == 3 ) {
			// 输出所有的旅游路线;
			if(state < 1){
				cout << "地图未创建！" << endl;system("pause");PageInfor();
				continue;
			}
			state = 3; 
			bt = CreatBST(Place,n); // 创建二叉排序树
			cout<<" 所有景点如下 :  "<<endl;
			InOrder(bt);// 中序遍历二叉树
			cout<<endl;
			MAtToList(Map ,G); // 转化成邻接表
			//DispAdj(G);
			//cout<<"dfs   "<<endl;
			int v = 2;
			printf(" 所有的导游路线  :   \n" );
			cout<<endl;
			int num;
			for(int i = 1; i<=n; i++) {

				cout<< "    方案     "<<i<<"   :  \n  ";
				memset(vis,0,sizeof(vis));
				memset(MapVex,0,sizeof(MapVex) );
				DFS(G,i,Place,bt);
				count1 = 0;
				cout<<endl<<endl;

				for(int j = 1; j<=n; j++) {
					int u = MapVex[j]->infor.number;
					TourMap[i][j] = u;
				}

			}

		} else if (num == 4 ) {
			if(state < 3){
				cout << "未生成导游路线！" << endl;system("pause");PageInfor();
				continue;
			}
			TorMap.e = e;
			TorMap.n = n;
			cout<<endl;
			int StrageWeight[MAX][MAX];
			for(int i = 1; i <=n; i++) {
				for(int j = 1; j <=n; j++) {

					Gr[i][j].u = TourMap[i][j];// 起点,
					Gr[i][j].v = TourMap[i][j+1];
					Gr[i][j].weight = Map.map[TourMap[i][j]][TourMap[i][j+1]];
					//StrageWeight[i][j] = Map.map[TourMap[i][j]][TourMap[i][j+1]];
				}


			}
			// 建图 
			MatGraph GT[20]; // 导游路线图
			for(int i = 1; i<=n; i++)
				CreatMatGragh(GT[i],n,e,i,Gr);
			int number;

			int edgenum[MAX ];
			int ed = 0;
			for(int k = 1; k <=n; k++) {

				for(int i = 1; i <= n; i++) {

					for(int j = 1; j<=n; j++) {

						if(GT[k].map[i][j]!=inf) {
							edgenum[k]++;
						}
					}

				}

			}
			for(int i = 1; i<=n; i ++) {
				if(edgenum[i] == n-1) {
					number = i; // 找到回路图;
					break;
				}
			}
			cout<<" 最佳导游路线 "<<endl;
			for(int i = 1; i <=n; i++) {
				// 二叉搜索树,依次输出景点
				BSTNode *r = SearchBST(bt,TourMap[number][i]); // 查找最佳路线图

				cout<<r->infor.PlaceName;
				if(i!=n)
					cout<<" -> ";

			}
			cout<<endl;

		} else if (num == 5 ) {
			if(state < 1){
				cout << "地图未创建！" << endl;system("pause");PageInfor();
				continue;
			}
			bt = CreatBST(Place,n);
			BSTNode *pfind1 ,*pfind2;
			cout<<endl;
			Display(Place,n);
			cout<<endl;
			printf(" 输入起点景点：\n");
			cin >> start;
			printf(" 输入终点景点：\n");
			cin >>end;

			int Find_Start_Num = Find(start,Place,Map.n);
			int Find_End_Num = Find(end,Place,Map.n);

			pfind1 = SearchBST(bt,Find_Start_Num);//顶点
			pfind2 = SearchBST(bt,Find_End_Num); // 终点
			if(!pfind1 && !pfind2){
				printf(" 输入错误！\n");system("pause");PageInfor();
				continue;
			}
			else
				cout<<pfind1->infor.PlaceName << " - > " <<pfind2->infor.PlaceName <<endl;
			if(Find_Start_Num != -1 && Find_End_Num != -1) {
				Dijkstra(Find_Start_Num,Map,bt,Find_End_Num);
				cout << endl;
			} else {
				printf(" 输入错误！\n");system("pause");PageInfor();
				continue;
			}

		} else if (num == 6 ) {
			if(state < 1){
				cout << "地图未创建！" << endl;system("pause");PageInfor();
				continue;
			}
			bt = CreatBST(Place,n);
			Prim(Map ,1,bt );
		} else if (num == 7 ) {
			// 终止程序

			cout<<" 退出系统成功!"<<endl;
			exit(0);
		}
		system("pause");
		PageInfor();
	}
	return;
}
int main() {
	
	int n = 13;
	int e = 14;
	DisplayMenu(n,e );
	return 0;

}


