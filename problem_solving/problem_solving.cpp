#include <bits/stdc++.h>
#ifdef WIN32
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
void make_tree(int root, int parent, vector<vi>& adj_list) {
    for (auto adj : adj_list[root]) {
        parent[adj] = root;
        make_tree(adj, root, adj_list);
    }
}
int32_t main()
{
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef WIN32
    freopen("input.txt", "rt", stdin);
#endif
    cin >> N >> R >> Q;
    vector<vector<int>> adj_list(N + 1);
    REP(i, N-1) {
        cin >> U >> V;
        adj_list[U].push_back(V);
        adj_list[V].push_back(U);
    }
    make_tree(R, -1);
    return 0;
}
