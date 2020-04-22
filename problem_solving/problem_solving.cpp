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
	FastIO; FileInput; CASE_T{
		IN(n); vi v(n + 1), in(n + 1); REP1(i,n)cin >> v[i];
		vvi adj_mat(n + 1, vi(n + 1, 0));
		REP1(i, n - 1) {
			for (int j = i + 1; j <= n; j++) adj_mat[v[i]][v[j]] = 1, in[v[j]]++;
		}
		int ok = 1;
		IN(m); REP(i, m) {
			IN(u); IN(v);
			if (adj_mat[u][v]) swap(u, v);
			adj_mat[v][u] = 0, in[u]--;
			adj_mat[u][v] = 1, in[v]++;
		}
		if (!ok) { OUT("IMPOSSIBLE"); continue; }
		queue<int> q;
		function<void(int n)> enqueue = [&](int n) {
			if ((in[n]--) > 0) return;
			q.push(n);
		};
		vi ans; int N = n;
		REP1(i, N) enqueue(i);
		REP(t,N) {  // 정확히 n번 dequeue로 끝난다.
			if (q.size() == 0) { OUT("IMPOSSIBLE"); goto Next; }
			int n = q.front(); q.pop();
			ans.push_back(n);
			REP1(i,N)if (adj_mat[n][i]) enqueue(i);
		}
		OUTV(ans);
	Next:
		int aasdf = 1;
	}

	return 0;
}