#include<bits/stdc++.h>
using namespace std;

#define MAXN 100

typedef struct Node {
    int solution[MAXN];
    int solution_size;
    int cost;
} Node;

int conn[MAXN][MAXN];
Node pq[MAXN * MAXN];
int pq_size = 0;

int cmp(const void* a, const void* b) {
	int i;
    Node* nodeA = (Node*)a;
    Node* nodeB = (Node*)b;
    if(nodeA->cost != nodeB->cost) {
        return nodeA->cost - nodeB->cost;
    }
    if(nodeA->solution_size != nodeB->solution_size) {
        return nodeA->solution_size - nodeB->solution_size;
    }
    for(i = 0; i < nodeA->solution_size; ++i) {
        if(nodeA->solution[i] != nodeB->solution[i]) {
            return nodeA->solution[i] - nodeB->solution[i];
        }
    }
    return 0;
}
void insertion_sort(Node* arr, int size) {
    int i, j;
    Node key;
    for (i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && cmp(&arr[j], &key) > 0) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void push(Node node) {
    pq[pq_size++] = node;
    insertion_sort(pq, pq_size);
}

Node top() {
    return pq[0];
}

void pop() {
	int i;
    for(i = 0; i < pq_size - 1; ++i) {
        pq[i] = pq[i + 1];
    }
    --pq_size;
}

int empty() {
    return pq_size == 0;
}

int find(int* arr, int size, int val) {
	int i;
    for(i = 0; i < size; ++i) {
        if(arr[i] == val) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int n,i,j;
    scanf("%d", &n);
    for (i = 0; i < n - 1; ++i) {
        for (j = i + 1; j < n; ++j) {
            scanf("%d", &conn[i][j]);
            conn[j][i] = conn[i][j];
        }
    }

    Node node;
    node.solution_size = 0;
    node.cost = 0;
    push(node);

    int min_cost = INT_MAX;
    int best_solution[MAXN];
    int best_solution_size = 0;
    while (!empty()) {
        Node node = top();
        pop();
        if(node.solution_size == n) {
            if (node.cost < min_cost) {
                min_cost = node.cost;
                for(i = 0; i < node.solution_size; ++i) {
                    best_solution[i] = node.solution[i];
                }
                best_solution_size = node.solution_size;
            }
            continue;
        }
        for(i = 0; i < n; ++i) {
            if (find(node.solution, node.solution_size, i)) {
                continue;
            }
            Node new_node;
            for(j = 0; j < node.solution_size; ++j) {
                new_node.solution[j] = node.solution[j];
            }
            new_node.solution[node.solution_size] = i;
            new_node.solution_size = node.solution_size + 1;
            new_node.cost = node.cost;
            for(j = 0; j < new_node.solution_size - 1; ++j) {
                new_node.cost += conn[new_node.solution[j]][new_node.solution[new_node.solution_size - 1]] * (new_node.solution_size - j - 1);
            }
            if(new_node.cost >= min_cost) {
                continue;
            }
            push(new_node);
        }
    }

    printf("%d\n", min_cost);
    int ans[MAXN];
    for (i = 0; i < n; ++i) {
        ans[best_solution[i]] = i + 1;
    }
    for (i = 0; i < best_solution_size; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");

    return 0;
}
