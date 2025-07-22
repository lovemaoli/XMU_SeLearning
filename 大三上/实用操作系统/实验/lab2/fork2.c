#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>

int main() {
    int variable = 3;
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        printf("Child process: variable = %d\n", variable);
        variable += 5;
        printf("Child process: variable = %d\n", variable);
    } else {
        printf("Parent process: variable = %d\n", variable);
        variable += 10;
        printf("Parent process: variable = %d\n", variable);
    }

    return 0;
}
