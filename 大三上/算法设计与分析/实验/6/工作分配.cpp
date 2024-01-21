#include <bits/stdc++.h>
using namespace std;
#define For(i, a, b) for (int i = (a), _##i = (b); i < _##i; ++i)
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define Forr(i, a, b) for (int i = (a), _##i = (b); i > _##i; --i)
#define FORR(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define all(a) a.begin(), a.end()
#define range(i, a) for (auto& i : a)
#define RANGE(i, a) for (auto i = a.rbegin(); i != a.rend(); ++i)
#define debug(a) #a << " = " << (a) << '\t'
// #define int ll
using ll = long long;
using pii = pair<int, int>;
using pdd = pair<double, double>;

namespace graph {
	template <int N, int M>
	class Dinic {
		public:
			const static int INF;

			void add_edge(int from, int to, int size, int cost);
			// * return: {max_flow, sum_cost}
			std::pair<int, int> exec(int start, int target);
		
		private:
			struct Edge {
				int to, size, cost;
				int next;
			};

			int s, t, n;
			int max_flow, sum_cost;
			int head[N], cur[N], dis[N];
			bool exist[N];
			Edge edge[M];

			bool BFS();
			int DFS(int now, int flow);
	};

	template<int N, int M>
	const int Dinic<N, M>::INF = 1 << 30;

	template<int N, int M>
	std::pair<int, int> Dinic<N, M>::exec(int start, int target) {
		max_flow = sum_cost = 0;
		s = start, t = target;
		while (BFS()) {
			exist[t] = true;
			while(exist[t]) {
				memset(exist, false, sizeof(exist));
				DFS(s, INF);
			}
		}
		return std::make_pair(max_flow, sum_cost);
	}

	template<int N, int M>
	int Dinic<N, M>::DFS(int now, int flow) {
		int rflow = 0;
		if (now == t) {
			max_flow += flow;
			exist[t] = true;
			return flow;
		}
		int used = 0;
		exist[now] = true;
		for (int i = cur[now]; i; i = edge[i].next) {
			cur[now] = i;
			Edge& e = edge[i];
			Edge& _e = edge[i ^ 1];
			if ((!exist[e.to] || e.to == t) && e.size && dis[e.to] == dis[now] + e.cost && (rflow = DFS(e.to, std::min(flow, e.size)))) {
				used += rflow;
				sum_cost += rflow * e.cost;
				e.size -= rflow;
				_e.size += rflow;
				if (used == flow)
					break;
			}
		}
		return used;
	}

	template<int N, int M>
	bool Dinic<N, M>::BFS() {
		std::queue<int> q;
		memcpy(cur, head, sizeof(head));
		memset(dis, 0x3f, sizeof(dis));
		memset(exist, false, sizeof(exist));
		q.push(s);
		dis[s] = 0;
		exist[s] = true;
		while (!q.empty()) {
			int tmp = q.front();
			q.pop();
			exist[tmp] = false;
			for (int i = head[tmp]; i; i = edge[i].next) {
				Edge& now = edge[i];
				if (now.size && dis[now.to] > dis[tmp] + now.cost) {
					dis[now.to] = dis[tmp] + now.cost;
					if (!exist[now.to]) {
						exist[now.to] = true;
						q.push(now.to);
					}
				}
			}
		}
		return dis[t] != 0x3f3f3f3f;
	}

	template<int N, int M>
	void Dinic<N, M>::add_edge(int from, int to, int size, int cost) {
		static int cnt = 1;
		edge[++cnt] = {to, size, cost, head[from]};
		head[from] = cnt;
		edge[++cnt] = {from, 0, -cost, head[to]};
		head[to] = cnt;
	}
}

namespace Solver {
    const int N = 64;
    const int M = 1024;

    int n;
    graph::Dinic<N, M> dinic;
    int cost[N][N];

    void main(int T) {
        cin >> n;
        FOR (i, 1, n)
            FOR (j, 1, n)
                cin >> cost[i][j];
        int s = 0, t = n * 2 + 1;
        FOR (i, 1, n)
            dinic.add_edge(s, i, 1, 0);
        FOR (i, 1, n)
            dinic.add_edge(i + n, t, 1, 0);
        FOR (i, 1, n)
            FOR (j, 1, n)
                dinic.add_edge(i, j + n, 1, cost[i][j]);
        cout << dinic.exec(s, t).second << endl;
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int T = 1;
    // cin >> T;
    FOR (t, 1, T)
        Solver::main(t);
    return 0;
}