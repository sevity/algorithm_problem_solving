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

struct result { vvi scc_list; vvi scc_adj_list; vi scc_cost; int scc_start_v; vi scc_end_v; };
result scc_dag_kosaraju(int max_v, int start_v, vi& end_v, vvi& adj_list, vvi& adj_rlist, vi& cost, int base1)
{
	// step1. dfs로 방문하며 말단부터 stack push
	vi visit(max_v + base1); stack<int> S;
	function<void(int n)> dfs = [&](int n) {
		if (visit[n]) return;
		visit[n] = 1;
		for (int a : adj_list[n]) dfs(a);
		S.push(n);
	};
	for (int i = base1; i < max_v + base1; i++) if (visit[i] == 0) dfs(i);
	// step2. stack에서 꺼내면서
	// 역방향으로 접근가능한 정점들을 SCC로 판정
	visit.clear(); visit.resize(max_v + base1);
	vi scc(max_v + base1);  // map. scc[v]=1 이면 v정점은 1번 SCC에 속한다고 하는것
	int scc_ix = base1;
	vvi scc_list; if (base1) scc_list.push_back(vi());
	while (S.size()) {
		int n = S.top(); S.pop();
		if (visit[n]) continue;
		vi sl;
		function<void(int n)> dfs = [&](int n) {
			if (visit[n]) return;
			visit[n] = 1;
			scc[n] = scc_ix;
			sl.push_back(n);
			for (auto a : adj_rlist[n]) dfs(a);
		};
		dfs(n);
		scc_list.push_back(sl);
		scc_ix++;
	}
	vvi scc_adj_list(scc_ix); int scc_start_v = -1; vi scc_end_v(scc_ix), scc_cost(scc_ix);
	for (int u = base1; u < max_v + base1; u++) {
		if (u == start_v) scc_start_v = scc[u];
		if (end_v[u]) scc_end_v[scc[u]] = 1;
		scc_cost[scc[u]] += cost[u];
		for (auto v : adj_list[u]) {
			if (scc[u] != scc[v]) {
				//cout << scc[u] << ' ' << scc[v] << endl;
				scc_adj_list[scc[u]].push_back(scc[v]);
			}
		}
	}
	return { scc_list, scc_adj_list, scc_cost, scc_start_v, scc_end_v };
}
struct node { int v, w; };
using vvn = vector<vector<node>>;
struct result2 { vi max_dist; int max_value; vi path; };
result2 longest(int max_v, int start_v, vvi& adj_list, vi& in_edge, vi& cost, vi& end_v, int base1) {
	vi visit(max_v + base1), max_dist(max_v + base1, -INF);
	vi from(max_v + base1, INF);
	queue<node> q;
	function<bool(node)> enqueue = [&](node n)->bool {
		if (in_edge[n.v] != 0) return false;
		q.push(n);
		return true;
	};
	for (int i = base1; i < max_v + base1; i++) enqueue({ i,cost[i] });
	if (start_v == -1) for (int i = base1; i < max_v + base1; i++) max_dist[i] = cost[i];
	else max_dist[start_v] = cost[start_v];
	vi cal(max_v + base1); cal[start_v] = 1;
	while (q.size()) {
		auto n = q.front(); q.pop();
		for (auto adj : adj_list[n.v]) {
			if (cal[n.v]) max_dist[adj] = max(max_dist[adj], n.w + cost[adj]), cal[adj] = 1;
			in_edge[adj]--;
			if (enqueue({ adj, max_dist[adj] })) from[adj] = n.v;
		}
	}
	//아래는 좀 비효율적, 위의 복잡도를 높이지 않게 하기위해 걍 놔둠
	int ra = -INF, rb = -1;
	for (int i = base1; i < max_v + base1; i++)
		if (end_v[i] && max_dist[i] > ra) ra = max_dist[i], rb = i;
	deque<int> s;
	int ix = rb;
	while (ix != INF)s.push_front(ix), ix = from[ix];
	return { max_dist, ra, vi(s.begin(), s.end()) };
}
int32_t main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	FileInput;
	int V, E; cin >> V >> E;
	vvi adj_list(V + 1), adj_list2(V + 1);
	REP(i, E) {
		int a, b; cin >> a >> b;
		adj_list[a].push_back(b);
		adj_list2[b].push_back(a); // 역방향
	}
	vi cost(V + 1);
	REP1(i, V)cin >> cost[i];
	IN2(S, P);
	vi end_v(V + 1);
	REP(i, P) { IN(p); end_v[p] = 1; }
	auto r = scc_dag_kosaraju(V, S, end_v, adj_list, adj_list2, cost, true);
	int N = SZ(r.scc_adj_list) - 1;
	vi in_edge(N + 1);
	REP1(u, N) for (auto v : r.scc_adj_list[u])in_edge[v]++;
	auto r2 = longest(N, r.scc_start_v, r.scc_adj_list, in_edge, r.scc_cost, r.scc_end_v, true);
	OUT(r2.max_value);
	return 0;
}