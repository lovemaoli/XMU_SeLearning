#include<iostream>
#include<algorithm>
using namespace std;
struct meeting{
	int begin;
	int end;
};
meeting meet[100000];

int n;

bool cmp(meeting a,meeting b) {
	return a.begin<b.begin;
}

int main(){
	cin>>n;
	int num=n;
	int i=0;
	while(num>0){
		cin>>meet[i].begin>>meet[i].end;
		i++;
		num--;
	}
	sort(meet,meet+n,cmp);
	
	int j=0;
	int count;
	if(n!=0){
		count=1;
	}
	else{
		count=0;
	}
	for(i=j+1;i<n;i++){
		if(meet[i].begin>meet[j].end){
			j=i;
			count++;
		}
	}
	cout<<count;
	return 0;
}
