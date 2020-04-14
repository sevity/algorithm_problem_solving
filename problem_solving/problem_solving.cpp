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
const int INF = (int)1e9;
int N, R, Q, U, V;
vector<vector<int>> adj_list(100001);
int parent[100001];
void make_tree(int root, int par) {
    for (auto adj : adj_list[root]) {
        if (adj == par) continue;
        parent[adj] = root;
        make_tree(adj, root);
    }
}
int dp[100001];
int cnt_sub(int root) {
    int& res = dp[root];
    if (res < INF) return res;
    if (adj_list[root].size() == 1) return res = 1;
    
    int sum = 1;
    for (auto adj : adj_list[root]) {
        if (adj == parent[root]) continue;
        sum += cnt_sub(adj);
    }
    return res = sum;
}

int32_t main()
{
    ios::sync_with_stdio(0); cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif
    fill(dp, dp + 100001, INF);
    cin >> N >> R >> Q;
    REP(i, N-1) {
        cin >> U >> V;
        adj_list[U].push_back(V);
        adj_list[V].push_back(U);
    }
    dbg(adj_list);
    make_tree(R,-1);
    dbg(parent);
    cnt_sub(R);
    dbg(dp);
    while (Q--) {
        cin >> U;
        cout << dp[U] << '\n'
    }
    return 0;
}
