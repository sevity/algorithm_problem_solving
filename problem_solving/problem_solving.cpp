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
vector<vi> treefy(vector<vi> & adj_list, int root) {
    vector<vi> tree(adj_list.size());
    function<void(int, int)> dfs = [&](int node, int parent) {
        for (auto adj : adj_list[node]) {
            if (adj == parent) continue;  // 부모방향 간선제거
            tree[node].push_back(adj);
            dfs(adj, node);
        }
    };
    dfs(root, -INF);
    return tree;
}

int32_t main()
{
    ios::sync_with_stdio(0); cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif
    int n; cin >> n;
    vector<vector<int>> adj_list(n + 1);
    REP(i, n-1) {
        int u, v; cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    vvi tree = treefy(adj_list, 1);
    vvi dp(n + 1, vi(21, INF));
    function<int(int, int)> dfs = [&](int nd, int cr)->int {
        int& res = dp[nd][cr];
        if (res < INF) return res;
        int rr = 0;
        for (auto nxt : tree[nd]) {
            int r = INF;
            for (int i = 1; i <= 20; i++) {
                if (i == cr)continue;
                r = min(r,dfs(nxt, i));
            }
            rr += r;
        }
        return res = rr + cr;
    };
    int ans = INF;
    REP1(i, 20)ans = min(ans, dfs(1, i));
    cout << ans << endl;
    return 0;
}

