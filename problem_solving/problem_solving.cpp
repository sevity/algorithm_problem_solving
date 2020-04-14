#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "dbg.h"  // https://github.com/sharkdp/dbg-macro
#else
#define dbg(...)
#endif
#define int long long
using namespace std;
#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define REP1(i,n) for(int i=1;i<=(int)(n);i++)
using vi = vector<int>;
typedef long long ll;
const int INF = (int)1e9;

int32_t main()
{
    ios::sync_with_stdio(0); cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif
    
    int N; cin >> N;
    vi l(N-1); REP(i, N - 1)cin >> l[i];
    vi c(N); REP(i, N)cin >> c[i];
    int ans = 0, len = 0, cost=c[0];
    for (int i = 1; i < N; i++) {
        len += l[i-1];
        if (c[i] < cost) 
            ans += cost*len, len=0,cost = c[i];
    }
    ans += cost * len;
    cout << ans << '\n';
    return 0;
}


