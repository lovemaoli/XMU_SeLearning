#include <bits/stdc++.h>
using namespace std;
int fenpei[21][21],n,ans=0x3f3f3f3f;
bool vis[21];
int dfs(int x,int dq){
    if(x==n+1){
        if(dq<ans){
            ans=dq;
        }
    }else{
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                vis[i]=true;
                dfs(x+1,dq+fenpei[x][i]);
                vis[i]=false;
            }
        }
    }
}
int main(){
    cin >> n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin >> fenpei[i][j];
        }
    }
    dfs(1,0);
    cout << ans << endl;
    return 0;
}