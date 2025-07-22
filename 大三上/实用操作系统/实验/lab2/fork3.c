#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void child_process(int num) {
    printf("子进程%d正在执行.....\n", num);
    while (1) {
        sleep(1);
    }
}

int main() {
    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 < 0) {
        perror("fork");
        exit(1);
    } else if (pid1 == 0) {
        child_process(1);
        exit(0);
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(1);
    } else if (pid2 == 0) {
        child_process(2);
        exit(0);
    }

    printf("父进程正在执行.....\n");
    sleep(3);
    
    kill(pid1, SIGKILL);
    printf("子进程1被父进程杀死\n");
    kill(pid2, SIGKILL);
    printf("子进程2被父进程杀死\n");

    printf("父进程结束\n");
    return 0;
}
