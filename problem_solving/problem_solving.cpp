/*{{{*/
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include "dbg.h"  // https://github.com/sharkdp/dbg-macro
#define FileInput freopen("input.txt", "rt", stdin)
#else
#define dbg(...)
#define FileInput
#endif
//#define int long long
#define FastIO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define CASE_T int ___T; cin>>___T;for(int cs=1;cs<=___T;cs++)
#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define REP1(i,n) for(int i=1;i<=(int)(n);i++)
using vi = vector<int>;
using vs = vector<string>;
using vvi = vector<vi>;
#define endl '\n';
#define SZ(x) (int)x.size()
#define ALL(x) x.begin(), x.end()
#define IN(n) int n;cin>>n
#define IN2(a,b) int a,b;cin>>a>>b
#define OUT(x) cout << (x) << endl
template <class T>
void OUTV(vector<T>& v) { REP(i, SZ(v)) cout << v[i] << (i + 1 == SZ(v) ? '\n' : ' '); }
typedef long long ll;
const int INF = (int)1e9;
/*}}}*/

int32_t main()
{
	FastIO; FileInput;

	REP(a, 2)REP(b, 2)REP(c, 2)REP(d, 2) {
		// (A and B) or (C and D)를 (A or C) and (A or D) and (B or C) and (B or D)
		int x = (a & b) | (c & d);
		int y = (a | c) & (a | d) & (b | c) & (b | d);
		assert(x == y);
	}

	return 0;
}