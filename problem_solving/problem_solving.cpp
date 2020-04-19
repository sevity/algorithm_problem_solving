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
using vvi = vector<vi>;
typedef long long ll;
const int INF = (int)1e9;

struct point { int x, y; };
int CCW(point A, point B, point C, bool sign_only = true) {
	int r = (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y);
	if (sign_only == false) return r;
	if (r == 0)return 0;
	return r > 0 ? 1 : -1;
}
struct line { point s, e; };
//touch_ok가 false이면, 두 선분이 교차하지 않고 만나기만 하는 경우에는 false를 리턴
bool Intersect(line x, line y, bool touch_ok = false) {
	point a = x.s, b = x.e;
	point c = y.s, d = y.e;
	int ab = CCW(a, b, c) * CCW(a, b, d);
	int cd = CCW(c, d, a) * CCW(c, d, b);
	if (ab == 0 && cd == 0) {
		pair<int, int> aa = { a.x, a.y }, bb = { b.x,b.y },
			cc = { c.x, c.y }, dd = { d.x,d.y };
		if (aa > bb)swap(aa, bb);
		if (cc > dd)swap(cc, dd);
		if (touch_ok) return cc <= bb && aa <= dd;
		return cc < bb&& aa < dd;
	}
	if (touch_ok) return ab <= 0 && cd <= 0;
	return ab < 0 && cd < 0;
}

struct union_find {
	vector<int> parent, cnt;
	union_find(int n) {
		parent.resize(n + 1), cnt.resize(n + 1);
		REP1(i, n)parent[i] = i, cnt[i] = 1;
	}
	int find(int x) {
		if (parent[x] == x) return x;
		else return parent[x] = find(parent[x]);
	}

	int uni(int x, int y) {
		int xp = find(x), yp = find(y);
		if (xp != yp) {
			cnt[xp] += cnt[yp];
			parent[yp] = xp;
		}
		return cnt[xp];
	}
};

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	int N; cin >> N;
	vector<line> vl(N + 1);
	REP(i, N) {
		int a, b, c, d; cin >> a >> b >> c >> d; vl[i + 1] = { a,b,c,d };
	}
	union_find uf(N);
	int max_cnt = 1;  // 여기!!!
	for (int i = 1; i < N; i++)
	{
		for (int j = i + 1; j <= N; j++)
			if (Intersect(vl[i], vl[j], true))
				max_cnt = max(max_cnt, uf.uni(i, j));  // 여기!!!
	}
	vi cnt(N + 1, 0);
	REP1(i, N) {
		cnt[uf.find(i)]++;
	}
	int gcnt = 0;
	REP1(i, N)if (cnt[i] > 0)gcnt++;
	cout << gcnt << ' ' << max_cnt << '\n';

	return 0;
}


