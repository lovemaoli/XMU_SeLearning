#include <bits/stdc++.h> 
using namespace std;
#define N 20
int a[N][N],times[N][N];//a是临接矩阵，times用于记录每条边被走过的次数  
int len=1000000,rec[N*N],res[N*N];//len用于记录总路长,rec用于记录走过点的顺序 ,res用于记录可行的结果 
int n_v=0,n_e=0;//分别是点数和边数 

void display()//展示矩阵 
{
	for(int i=0;i<n_v;i++)
	{
		for(int j=0;j<n_v;j++)
		{
			if(a[i][j]>0)
			    cout<<a[i][j]<<' ';
			else if(a[i][j]==-1)
			    cout<<"* ";
		}
		cout<<endl;
	}
}

bool judge(int des[],int n)//判断是否走完了全部目标 
{
	bool *flags=new bool[n_v];
	memset(flags, false,n_v);//初始化
	for(int i=0;rec[i]!=-1;i++)
		flags[rec[i]]=true;
    for(int i=0;i<n;i++)
    	if(flags[des[i]]==false)
    	    return false;
	return true;
}

void find_way(int des[],int n,int x,int cou=0)//n是目标个数，x是起点，cou是已经走过点的数量 
{
	if(judge(des,n))//如果达成一种结果 
	{
		int sum=0;//用于记录该结果的总长度 
		for(int i=1;rec[i]!=-1;i++)
		    sum+=a[rec[i-1]][rec[i]];
		if(sum<len)
		{
			cout<<"恭喜！找到了一条路:";
			len=sum;
			for(int i=0;rec[i]!=-1;i++)
			{
			    res[i]=rec[i];//储存当前最优解 
			    cout<<res[i]+1<<' ';
		    }
		    cout<<"这条路的长度是:"<<len<<endl;
	    }
	    return;
	}
	
	
	for(int y=0;y<n_v;y++)
	{
		if(a[x][y]>0 && times[x][y]<2)//如果可以走 
		    {
		    	//cout<<"One step forward"<<y+1<<endl;
		    	times[x][y]++;
		    	times[y][x]++;
		    	rec[cou]=x;
		    	cou++;//留痕 
		    	
		    	find_way(des,n,y,cou);
		    	
		    	times[x][y]--;
		    	times[y][x]--;
                rec[cou]=-1;
                cou--;//恢复现场
                //cout<<"One step back"<<x+1<<endl;
			}
	}
}

int main()
{
	cout<<"请输入景点个数(20以内)：";
	cin>>n_v;
	cout<<"请输入景点关系个数：";
	cin>>n_e;
	for(int i=0;i<N*N;i++)
	rec[i]=res[i]=-1;
	
	for(int i=0;i<n_v;i++)//初始化 
	{
	    for(int j=0;j<n_v;j++)
	    {
	        a[i][j]=-1;
	        times[i][j]=0;
	    }
	}
	
	cout<<"请成对输入两个景点的序号以及权值："<<endl; 
	for(int i=0;i<n_e;i++)
	{
		int t1,t2,weight;
		cin>>t1>>t2>>weight;	
		a[t1-1][t2-1]=a[t2-1][t1-1]=weight;
	}
	cout<<"邻接矩阵："<<endl; 
	display(); 
	cout<<"请输入起点"<<endl;
	int ori;
	cin>>ori;
	ori--; 
	cout<<"请输入要经历的点的个数"<<endl;
	int n;
	cin>>n; 
	cout<<"请输入要经历的点的序号"<<endl;
	int *des=new int[n];
	for(int i=0;i<n;i++)
	{
		cin>>des[i];
		des[i]--;
	}
	
	cout<<"查询中"<<endl;
	find_way(des,n,ori);
	cout<<"最短的路程是:"<<endl;
	for(int i=0;res[i]!=-1;i++)
	cout<<res[i]+1<<' ';
	cout<<"最短的路程为:"<<len<<endl;
	return 0;
}

/*
9
9
1 2 1
2 3 1
3 4 1
4 5 1
5 6 1
6 2 1
6 7 2
6 8 3
8 9 4
2
4
1 4 7 9
*/

