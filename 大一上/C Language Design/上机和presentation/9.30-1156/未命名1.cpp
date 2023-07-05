int a,x,y,z;
	while(scanf("%d",&a)!=EOF)
	{
		x=a/100;
		a=a%100; 
		y=a/10;
		z=a%10;
		if(x==0&&y==0)
		{
		printf("%d\n",z);
	    }
		else if(x==0&&y!=0&&z!=0)
		{
		printf("%d",z);
		printf("%d\n",y);
		}
		else if(x==0&&y!=0&&z==0)
		{
		printf("%y\n",y);
		}
		else if(x!=0&&z!=0)
		{
		printf("%d",z);
			printf("%d",y);
				printf("%d\n",x);
			}
		else if(x!=0&&y==0&&z==0)
			{
				printf("%d\n",x);
			}
				else if(x!=0&&z==0&&y!=0)
				
				{
								printf("%d",y);
					printf("%d\n",x);
			}
	}
	return 0;
 }

