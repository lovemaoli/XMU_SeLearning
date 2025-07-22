#include <stdio.h>
#include <stdbool.h>

#define P 5 // 进程数
#define R 3 // 资源种类数

int available[R] = {3, 3, 2};  // 可用资源向量
int maximum[P][R] = {  // 最大需求矩阵
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};
int allocation[P][R] = {  // 分配矩阵
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};
int need[P][R];  // 需求矩阵

void calculateNeed() {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

bool isSafe() {
    int work[R];
    bool finish[P] = {0};
    int safeSequence[P];
    int count = 0;

    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                bool canAllocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int k = 0; k < R; k++) {
                        work[k] += allocation[p][k];
                    }
                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            return false;
        }
    }

    printf("系统处于安全状态。\n安全序列是: ");
    for (int i = 0; i < P; i++) {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}

void printAllocationAndAvailable() {
    printf("资源分配矩阵 A:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }
    printf("可用资源向量 V:\n");
    for (int i = 0; i < R; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");
}

void requestResources(int processId, int request[]) {
    printf("进程 %d 请求资源：", processId);
    for (int i = 0; i < R; i++) {
        printf("%d ", request[i]);
    }
    printf("\n");

    for (int i = 0; i < R; i++) {
        if (request[i] > need[processId][i]) {
            printf("请求超出需求。\n");
            return;
        }
    }

    for (int i = 0; i < R; i++) {
        if (request[i] > available[i]) {
            printf("没有足够的资源。\n");
            return;
        }
    }

    for (int i = 0; i < R; i++) {
        available[i] -= request[i];
        allocation[processId][i] += request[i];
        need[processId][i] -= request[i];
    }

    if (isSafe()) {
        printf("资源已分配给进程 %d。\n", processId);
        printAllocationAndAvailable();
    } else {
        for (int i = 0; i < R; i++) {
            available[i] += request[i];
            allocation[processId][i] -= request[i];
            need[processId][i] += request[i];
        }
        printf("分配后系统处于不安全状态，分配请求被拒绝。\n");
    }
}

int main() {
    calculateNeed();

    int processId;
    int request[R];
    printAllocationAndAvailable();
    while (true) {
        printf("输入进程ID和资源请求: ");
        scanf("%d", &processId);
        if (processId == -1) break;

        for (int i = 0; i < R; i++) {
            scanf("%d", &request[i]);
        }

        requestResources(processId, request);

        printf("按空格键查看下一次申请情况...");
        while (getchar() != ' ');
    }

    return 0;
}
