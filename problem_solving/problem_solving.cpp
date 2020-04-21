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
#define all(r) (r).begin(),(r).end()
typedef long long ll;
const int INF = (int)1e9;

struct node { map<string, node> child; };
node* insert(node* n, string s) {  // 여기 포인터로 안하고 레퍼런스로 하려고 했는데 잘 안됐다.
    auto& m = n->child;
    if (m.count(s)==0) m[s] = node();  // 자식노드 할당을 이런식으로 한다는게 생각보다 어려웠다. (node()부분)
    return &m[s];    
}
void dfs(node& n, int lv=0) {
    auto& m = n.child;
    for (auto a : m) {
        REP(i, lv)cout << "--";
        cout << a.first << '\n';
        dfs(a.second, lv + 1);
    }
}
int32_t main()
{
    ios::sync_with_stdio(0); cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif
    int N; cin >> N;
    node root;
    REP(i, N) {
        node* n = &root; // 여기 포인터로 안하고 레퍼런스로 하려고 했는데 잘 안됐다.
        int M; cin >> M; string s; REP(j, M) {
            cin >> s;
            n = insert(n, s);
        }
    }
    dfs(root);
    return 0;
}