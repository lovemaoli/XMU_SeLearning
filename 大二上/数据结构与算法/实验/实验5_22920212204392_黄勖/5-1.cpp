#include <stdio.h>
#define N 10000 
int main()
{
	int a[N],n;
	scanf("%d",&n);
	for (int i=0; i<n; i++)
		scanf("%d",&a[i]);
	int m;
	scanf("%d",&m);
	while (m--)
	{
		int x;
		scanf("%d",&x);
		int low =0, high =n-1,mid;   // 置区间初值
		while (low<=high)
		{
			mid = (low+high)/2 ;
			if (x == a[mid])   break;           // 找到待查记录
			else if (x<a[mid])  high=mid-1;   // 继续在前半区间进行检索
			else  low=mid+1;                      // 继续在后半区间进行检索
		}
		if (low<=high)       // 找到待查记录
			printf("%d在下标位%d的位置\n",x,mid);
		else
			printf("未找到！\n");
	}
	return 0;
}
