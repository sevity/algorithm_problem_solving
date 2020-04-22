/*{{{*/
#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "dbg.h"  // https://github.com/sharkdp/dbg-macro
#define FileInput freopen("input.txt", "rt", stdin);
#else
#define dbg(...)
#define FileInput
#endif
//#define int long long
#define FastIO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define CASET int ___T; cin>>___T;for(int cs=1;cs<=___T;cs++)
using namespace std;
#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define REP1(i,n) for(int i=1;i<=(int)(n);i++)
using vi = vector<int>;
using vs = vector<string>;
using vvi = vector<vi>;
#define SZ(X) ((int)(X).size())
#define ALL(X) (X).begin(), (X).end()
#define OUT(x) {cout << (x) << '\n'; }
#define IN(n) int n;cin>>n
template <class T>
void OUTV(const vector<T> & v) {REP(i,v.size()) cout << v[i] << (i + 1 == v.size() ? '\n' : ' ');}
typedef long long ll;
const int INF = (int)1e9;
/*}}}*/

int32_t main()
{
    FastIO; FileInput;
    IN(N); IN(M);
    vi in(N+1);
    vvi adj_list(N + 1);
    for (int i = 0; i < M; i++) {
        IN(u); IN(v);
        adj_list[u].push_back(v); in[v]++;
    }
    queue<int> q; vi visit(N + 1);
    function<void(int n)> enqueue = [&](int n) {
        if (in[n] > 0) { in[n]--; return; }
        if (visit[n]) return;
        visit[n] = 1;
        q.push(n);
    };
    REP1(j, N) enqueue(j);
    while (q.size()) {
        int n = q.front(); q.pop();
        cout << n << ' ';
        for (auto adj : adj_list[n]) {
            enqueue(adj);
        }
    }

    return 0;
}
