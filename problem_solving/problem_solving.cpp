#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "dbg.h"  // https://github.com/sharkdp/dbg-macro
#else
#define dbg(...)
#endif
using namespace std;
#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define REP1(i,n) for(int i=1;i<=(int)(n);i++)
using vi = vector<int>;
typedef long long ll;
const int INF = (int)1e9, MAXN = 100001;
int N, R, Q, U, V;
vector<vi> adj_list(MAXN);

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

vi dp(MAXN, INF);
int cnt_sub(vector<vi>& tree, int root) {
    int& res = dp[root];
    if (res < INF) return res;
    int sum = 1;
    for (auto adj : tree[root]) {
        sum += cnt_sub(tree, adj);
    }
    return res = sum;
}
int32_t main()
{
    ios::sync_with_stdio(0); cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif
    cin >> N >> R >> Q;
    REP(i, N - 1) {
        cin >> U >> V;
        adj_list[U].push_back(V);
        adj_list[V].push_back(U);
    }
    dbg(adj_list);
    vector<vi> tree = treefy(adj_list, R);
    dbg(tree);
    cnt_sub(tree, R);
    dbg(dp);
    while (Q--) {
        cin >> U;
        cout << dp[U] << '\n';
    }
    return 0;
}
