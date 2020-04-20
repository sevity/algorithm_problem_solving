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

int32_t main()
{
    ios::sync_with_stdio(0); cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif
    while (1) {
        int n; cin >> n;
        if (n == 0) break;
        string s;
        while (n) {
            s += '0' + n % 10;
            n /= 10;
        }
        bool ok = 1;
        REP(i, s.length())if (s[i] != s[s.length() - 1 - i]) ok = 0;
        cout << (ok ? "yes" : "no") << endl;
    }
    return 0;
}

