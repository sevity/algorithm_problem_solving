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
            if(adj>0)dfs(adj, node);
        }
    };
    const int MAGIC = -90947701;
    dfs(root, MAGIC);
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
    set<int> s;
    int a,b,c; REP1(i, N) {
        cin >> a >> b >> c;
        adj_list[a].push_back(b);
        adj_list[a].push_back(c);
        s.insert(b), s.insert(c);
    }  
    int root = -1;
    REP1(i, N) { 
        if (s.find(i) ==s.end() ) { root = i; break; }
    }
    assert(root != -1);
    vvi tree = treefy(adj_list, root);
    vvi ww(N + 1, vi(2,INF));
    function<int(int)> dfs = [&](int nd) {
        int l = ww[nd][0] = tree[nd][0]>0?dfs(tree[nd][0]):0;
        int r = ww[nd][1] = tree[nd][1]>0?dfs(tree[nd][1]):0;
        return l+r+1;
    };
    dfs(root);
    vi mi(N + 1, INF), ma(N + 1, 0);
    function<void(int, int, int)> traverse = [&](int nd, int lv, int xloc) {
        mi[lv] = min(mi[lv], xloc);
        ma[lv] = max(ma[lv], xloc);
        int l = tree[nd][0]; 
        if (l > 0)traverse(l, lv + 1, xloc-ww[l][1]-1);
        int r = tree[nd][1]; 
        if (r > 0)traverse(r, lv + 1, xloc+ww[r][0]+1);
    };
    traverse(root, 1, ww[root][0] + 1);
    int ans_lv = 0, ans_w=0;
    REP1(i, N) {
        int w = ma[i] - mi[i] + 1;
        if (w > ans_w)ans_w = w, ans_lv = i;
    }

    cout << ans_lv << ' '<< ans_w << '\n';
    return 0;
}
