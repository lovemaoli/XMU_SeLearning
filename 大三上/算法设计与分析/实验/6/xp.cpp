#include<bits/stdc++.h>
using namespace std;

struct Node {
    vector<int> solution;
    int cost;
    bool operator<(const Node& rhs) const {
        if(cost == rhs.cost){
            if(solution.size() == rhs.solution.size()){
                for(int i = 0; i < solution.size(); ++i){
                    if(solution[i] == rhs.solution[i]){
                        continue;
                    }
                    return solution[i] > rhs.solution[i];
                }
            }
            return solution.size() > rhs.solution.size();
        }
        return cost > rhs.cost;
    }
};

int main() {
    int n;
    cin >> n;
    vector<vector<int>> conn(n, vector<int>(n));
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            cin >> conn[i][j];
            conn[j][i] = conn[i][j];
        }
    }

    priority_queue<Node> pq; // 优先队列
    Node node;
    node.cost = 0;
    pq.push(node);

    int min_cost = INT_MAX;
    vector<int> best_solution;
    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();
        if(node.solution.size() == n) {
            if (node.cost < min_cost) {
                min_cost = node.cost;
                best_solution = node.solution;
            }
            continue;
        }
        for(int i = 0; i < n; ++i) {
            // 取得下一个节点
            if (find(node.solution.begin(), node.solution.end(), i) != node.solution.end()) {
                continue;
            }
            Node new_node;
            new_node.solution = node.solution;
            new_node.solution.push_back(i);
            new_node.cost = node.cost;
            for(int j = 0; j < new_node.solution.size() - 1; ++j) {
                new_node.cost += conn[new_node.solution[j]][new_node.solution[new_node.solution.size() - 1]] * (new_node.solution.size() - j - 1);
                //调试
                // cout << "conn[" << new_node.solution[j] << "][" << new_node.solution[new_node.solution.size() - 1] << "] = " << conn[new_node.solution[j]][new_node.solution[new_node.solution.size() - 1]] << endl;
            }
            //输出调试信息
            // cout << "new_node.cost = " << new_node.cost << endl;
            // for (int j = 0; j < new_node.solution.size(); ++j) {
                // cout << new_node.solution[j] + 1 << " ";
            // }
            // cout << endl;

            pq.push(new_node);
        }
    }

    cout << min_cost << endl;
    int ans[n];
    for (int i = 0; i < n; ++i) {
        ans[best_solution[i]] = i + 1;
    }
    for (int i = 0; i < best_solution.size(); ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}