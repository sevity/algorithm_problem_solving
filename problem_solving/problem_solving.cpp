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
typedef long long ll;
const int INF = (int)1e9;
vi parent(10001);
//무방향그래프를 인풋으로 받아, 특정 정점을 루트를 가지는 방향그래프(트리)로 만들어준다.
vector<vi> treefy(vector<vi> & adj_list, int root) {
    vector<vi> tree(adj_list.size());
    function<void(int, int)> dfs = [&](int node, int parent) {
        for (auto adj : adj_list[node]) {
            if (adj == parent) continue;  // 부모방향 간선제거
            ::parent[adj] = node;
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

    int n; cin >> n;
    vi cost(n + 1); REP1(i, n)cin >> cost[i];
    vector<vi> adj_list(n + 1);
    int U, V; while (cin >> U >> V) {
        adj_list[U].push_back(V);
        adj_list[V].push_back(U);
    }
    vector<vi> tree = treefy(adj_list, 1);  // 어차피 트리임이 보장된거 같으니 1번을 임의로 루트로 지정
    dbg(parent);
    vector<vi> dp(n + 1, vi(2, INF));
    function<int(int,int)> dfs = [&](int node, int include) {
        int& res = dp[node][include];
        if (res < INF) return res;
        //포함
        if (include) {
            //이경우 자식노드는 미포함이어야함
            int n1 = cost[node];
            for (auto adj : tree[node]) {
                n1 += dfs(adj, 0);
            }
            return res = n1;
        }
        //미포함
        else {
            //이경우 자식노드는 포함/미포함 둘다가능
            int n2 = 0;
            for (auto adj : tree[node]) {
                n2 += max(dfs(adj, 0), dfs(adj, 1));
            }
            return res = n2;
        }
    };
    int ans = max(dfs(1,0),dfs(1,1));
    dbg(tree);
    dbg(dp);
    cout << ans << '\n';
    vi v;
    function<void(int,int)> traverse = [&](int node, int include) {
        if (include) {
            v.push_back(node);// cout << node << ' ';
            for (auto adj : tree[node]) {
                traverse(adj, 0);
            }
        }
        else {
            for (auto adj : tree[node]) {
                traverse(adj, dp[adj][1] > dp[adj][0]);
            }
        }
    };
    traverse(1, dp[1][1] > dp[1][0]);
    sort(v.begin(), v.end());
    for (auto a : v)cout << a << ' ';
    return 0;
}

