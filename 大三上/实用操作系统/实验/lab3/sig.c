#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pid_t pid1,pid2;

void fun(int sig)
{
	kill(pid1,SIGUSR1);
	kill(pid2,SIGUSR1);
}

void fun1(int sig)
{
	printf("Child1 process1  is  killed by parent!\n");
}

void fun2(int sig)
{
	printf("Child2 process2  is  killed by parent!\n");
}

 int main(int argc(),char *argv[])
{
	pid1 = fork();
	
	if(pid1 > 0)
	{
		pid2 = fork();
		//父进程
		if(pid2 > 0)
		{
			signal(SIGINT,fun);
			wait(NULL);
			wait(NULL);
			printf("Parent process exit!\n");
		}
		//子进程2接收信号
		if(pid2 == 0)
		{
			signal(SIGUSR1,fun2);
			pause();
		}
	}
	//子进程1接收信号
	if(pid1 == 0)
	{
		signal(SIGUSR1,fun1);
		pause();
	}
	return 0;
}

