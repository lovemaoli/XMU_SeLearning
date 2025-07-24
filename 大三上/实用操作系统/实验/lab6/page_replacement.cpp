#include <iostream>  
#include<map>
#include<set>
#include <algorithm>
#include<cstdio>
#include<cstring> 
#include<cmath>
#define N 200
using namespace std;  
 
int page[N];//页面引用号 
int block[N];//物理块，内存 
int dist[N][N];//第i次访问内存的时候，内存中的页面j 在以后被访问的最小时间 

int n;//页面引用号个数 
int m;//物理块数目 
int page_max;//最大页面号 

int pre[N];//page[i]在page中的索引
int opt(){
    int page_lack = 0;
    memset(pre, 0, sizeof(pre));
    memset(dist, 0x3f, sizeof(dist));
    memset(block, -1, sizeof(block));
    for(int i=n; i>=1; --i){
         for(int j=0; j<=page_max; ++j) 
             if(pre[j])
                dist[i][j] = pre[j] - i;
         pre[page[i]] = i; 
    }
    
    for(int i=1; i<=n; ++i){
        int j;
        int max_dist = 0, p; 
        for(j=1; j<=m; ++j){
            if(block[j] == -1){
                block[j] = page[i]; 
                page_lack++;
                break;
            } else if(block[j] == page[i])
                break;
            
            if(max_dist < dist[i][block[j]]){
                max_dist = dist[i][block[j]];
                p = j;
            }
        }
        if(j > m){
             block[p] = page[i];
             page_lack++; 
        }
    }
    return page_lack;
} 

int lru(){
    int page_lack = 0;
    memset(pre, 0, sizeof(pre));
    memset(dist, 0x3f, sizeof(dist));
    memset(block, -1, sizeof(block));
    for(int i=1; i<=n; ++i){
         for(int j=0; j<=page_max; ++j) 
             if(pre[j])
                dist[i][j] = i - pre[j];
         pre[page[i]] = i; 
    }
    
    for(int i=1; i<=n; ++i){
        int j;
        int max_dist = 0, p; 
        for(j=1; j<=m; ++j){
            if(block[j] == -1){
                block[j] = page[i]; 
                page_lack++;
                break;
            } else if(block[j] == page[i])
                break;
            
            if(max_dist < dist[i][block[j]]){
                max_dist = dist[i][block[j]];
                p = j;
            }
        }
        if(j > m){
             block[p] = page[i];
             page_lack++; 
        }
    }
    return page_lack;
} 

set<int>page_set;
int fifo(){
    int page_lack = 0; 
    memset(block, -1, sizeof(block));
    int index = 1;
    for(int i=1; i<=n; ++i){
        if(index > m) index = 1;
        set<int>::iterator it;
        it = page_set.find(page[i]);  
        if(it == page_set.end()){
            if(block[index] != -1)
                page_set.erase(block[index]);
            page_set.insert(page[i]);
            block[index++] = page[i];
            ++page_lack;
        } 
    } 
    return page_lack;
}

int main(){
    cin>>n>>m;
    for(int i=1; i<=n; ++i){ 
        cin>>page[i];
        page_max = max(page_max, page[i]) ;
    }
    double page_fault_rate = 0;
    int page_fault_count= 0;
    page_fault_count = opt();
    page_fault_rate = (double) page_fault_count / n;
    printf("opt缺页中断次数:%d, 缺页率：%lf, 命中率：%lf\n",page_fault_count, page_fault_rate, 1.0 - page_fault_rate);
    page_fault_count = fifo();
    page_fault_rate = (double) page_fault_count / n;
    printf("fifo缺页中断次数:%d, 缺页率：%lf, 命中率：%lf\n",page_fault_count, page_fault_rate, 1.0 - page_fault_rate);
    page_fault_count = lru();
    page_fault_rate = (double) page_fault_count / n;
    printf("lru缺页中断次数:%d, 缺页率：%lf, 命中率：%lf\n",page_fault_count, page_fault_rate, 1.0 - page_fault_rate);
    return 0;
} 