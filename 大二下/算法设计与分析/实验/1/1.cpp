#include <bits/stdc++.h>
using namespace std;
int ans[11]= {0};
int main() {
	string a;
	cin >> a;
	for(int i=0; i<a[0]-'0'; i++) {
		int cheng=1;
		for(int k=3; k<=a.length(); k++)cheng*=10;
		for(int j=0; j<=9; j++) {
			ans[j]+=cheng;
		}
		if(i!=0) {
			ans[i]+=cheng;
		}
	}
	int flag=1;
	for(int i=0; i<a.length(); i++) {
		if(a[i]!='9')flag=0;
	}
	if(flag==1) {
		ans[0]-=1;
		for(int i=0; i<=9; i++) {
			cout << ans[i] <<endl;
		}
		return 0;
	}
	int b=0;
	for(int i=1; i<a.length(); i++) {
		b*=10;
		b+=(a[i]-'0');
	}
//	cout <<(a[0]-'0')*(10^(a.length())/10)<<endl;
	for(int i=(a[0]-'0')*(10^(a.length())/10); i<=(a[0]-'0')*(10^(a.length())/10)+b; i++) {
		int tmp=i;
		while(tmp) {
			ans[tmp%10]++;
			tmp/=10;
		}
	}
	ans[0]-=1;
	for(int i=0; i<=9; i++) {
		cout << ans[i]<<endl;
	}


}
