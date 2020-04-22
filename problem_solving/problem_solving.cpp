/*{{{*/
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include "dbg.h"  // https://github.com/sharkdp/dbg-macro
#define FileInput freopen("input.txt", "rt", stdin);
#else
#define dbg(...)
#define FileInput
#endif
//#define int long long
#define FastIO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define CASE_T int ___T; cin>>___T;for(int cs=1;cs<=___T;cs++)
#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define REP1(i,n) for(int i=1;i<=(int)(n);i++)
using vi = vector<int>;
using vs = vector<string>;
using vvi = vector<vi>;
#define endl '\n';
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(), (x).end()
#define IN(n) int n;cin>>n
#define OUT(x) {cout << (x) << '\n'; }
template <class T>
void OUTV(vector<T>& v) { REP(i, SZ(v)) cout << v[i] << (i + 1 == SZ(v) ? '\n' : ' '); }
typedef long long ll;
const int INF = (int)1e9;
/*}}}*/

int32_t main()
{
    FastIO; FileInput;
    IN(N); IN(M);
    vi in(N + 1); // in-edge를 관리해주는게 핵심
    vvi adj_list(N + 1);
    for (int i = 0; i < M; i++) {
        IN(u); IN(v); adj_list[u].push_back(v); in[v]++;
    }
    priority_queue <int, vector<int>, greater<int> > q;
    function<void(int n)> enqueue = [&](int n) {
        if ((in[n]--) > 0) return;
        q.push(n);
    };
    vi ans;
    REP1(i, N) enqueue(i);
    while (N--) {  // 정확히 n번 dequeue로 끝난다.
        if (!q.size()) { break; }//cycle!
        int n = q.top(); q.pop();
        ans.push_back(n);
        for (auto adj : adj_list[n]) {
            enqueue(adj);
        }
    }
    for (auto a : ans) cout << a << ' ';
    return 0;
}