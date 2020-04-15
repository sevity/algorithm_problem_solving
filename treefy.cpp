#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<(int)(n);i++)
using vi = vector<int>;
const int INF = (int)1e9, MAXN = 100001;

//무방향그래프를 인풋으로 받아, 특정 정점을 루트를 가지는 방향그래프(트리)로 만들어준다.
vector<vi> treefy(vector<vi>& adj_list, int root) {
    vector<vi> tree(adj_list.size());
    function<void(int, int)> dfs = [&](int node, int parent) {
        for (auto adj : adj_list[node]) {
            if (adj == parent) continue;  // 부모방향 간선제거
            tree[node].push_back(adj);
            dfs(adj, node);
        }
    };
    dfs(root, -1);
    return tree;
}

int N, R, Q, U, V;
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> R >> Q;
    vector<vi> adj_list(N + 1);
    REP(i, N - 1) {
        cin >> U >> V;
        adj_list[U].push_back(V);
        adj_list[V].push_back(U);
    }
    vector<vi> tree = treefy(adj_list, R);

    vi dp(MAXN, INF);
    function<int(int)> cnt_sub = [&](int root) {
        int& res = dp[root];
        if (res < INF) return res;
        int sum = 1; for (auto adj : tree[root]) sum += cnt_sub(adj);
        return res = sum;
    };
    cnt_sub(R);

    while (Q--) cin >> U, cout << dp[U] << '\n';
    return 0;
}

