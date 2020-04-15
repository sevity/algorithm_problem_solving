#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "dbg.h"  // https://github.com/sharkdp/dbg-macro
#else
#define dbg(...)
#endif
//#define int long long
using namespace std;
#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define REP1(i,n) for(int i=1;i<=(int)(n);i++)
using vi = vector<int>;
using vvi = vector<vi>;
typedef long long ll;
const int INF = (int)1e9;
//무방향그래프를 인풋으로 받아, 특정 정점을 루트를 가지는 방향그래프(트리)로 만들어준다.
vvi treefy(vvi& adj_list, int root) {
    vvi tree(adj_list.size());
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

int32_t main()
{
    ios::sync_with_stdio(0); cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif

    int N; cin >> N;
    vvi adj_list(N + 1);
    int U, V; REP(i, N - 1) {
        cin >> U >> V;
        adj_list[U].push_back(V);
        adj_list[V].push_back(U);
    }
    vvi tree = treefy(adj_list, 1);
    vvi dp(N + 1, vi(2, INF));  // dp[N+1][2]=INF..;
    function<int(int, int)> dfs = [&](int nd, int inc) {
        int& res = dp[nd][inc];
        if (res < INF) return res;
        if (inc) {
            int n1 = 1;
            for (auto adj : tree[nd]) {
                n1 += min(dfs(adj, 0), dfs(adj, 1));
            }
            return res = n1;
        }
        else {
            int n2 = 0;
            for (auto adj : tree[nd]) n2 += dfs(adj, 1);
            return res = n2;
        }
    };
    cout << min(dfs(1, 0), dfs(1, 1)) << '\n';
    return 0;
}
