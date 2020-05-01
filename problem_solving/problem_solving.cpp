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
#define int long long
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

struct node { int v, w; };

//무방향그래프를 인풋으로 받아, 트리로 만들어준다.LCA를 위한 작업도 해준다.
struct result { vvi tree; int root; vi parent, level, dist, dist2; int max_level; vvi ancestor; };
result treefy(vector<vector<node>>& adj_list, int root = -1, bool base1 = false) {
	int max_v = (int)adj_list.size();
	vector<vi> tree(max_v);
	vi parent(max_v), level(max_v), dist(max_v), dist2(max_v);
	int max_level = 0; while ((1 << max_level) < max_v) max_level++;
	vvi ac(max_v, vi(max_level + 1, -INF));  // ac[x][y] :: x의 2^y번째 조상을 의미
	function<void(node, int, int)> dfs = [&](node n, int par, int lv) {
		parent[n.v] = par, level[n.v] = lv, dist2[n.v] = n.w;
		ac[n.v][0] = par;  // 첫번째(2^0) 조상은 부모
		for (int i = 1; i <= max_level; i++) {
			//아래 두줄을 통해 과거 조상들을 2^k 스케일로 쭉쭉 구해나간다.
			int tmp = ac[n.v][i - 1];  // tmp :: node의 2^(i-1)번째 조상
			if (tmp == -INF) break;
			ac[n.v][i] = ac[tmp][i - 1];
		}
		for (auto adj : adj_list[n.v]) {
			if (adj.v == par) continue;  // 부모방향 간선제거
			tree[n.v].push_back(adj.v);
			dist[adj.v] = dist[n.v] + adj.w;
			dfs(adj, n.v, lv + 1);
		}
	};
	dfs({ root,0 }, -INF, 1);
	return { tree, root, parent, level, dist, dist2, max_level, ac };
}

int lca(int node_a, int node_b, vvi& tree, vi& level, vvi& ancestor)
{
	int max_v = (int)tree.size();
	int a = node_a, b = node_b;
	int max_level = 0; while ((1 << max_level) < max_v) max_level++;
	if (level[a] != level[b])
	{
		if (level[a] > level[b]) swap(a, b);  // b가 더 깊도록 조정

		//b를 올려서 level을 맞춘다.
		for (int i = max_level; i >= 0; i--)
		{
			// b의 2^i번째 조상이 a의 level보다 깊거나 같으면 계속 조상을 타고 올라간다.
			// 이 때 단순히 2^k조상들만 보는게 아니라 모든 레벨의 조상을 검토하게 됨에 주의
			if (ancestor[b][i] != -INF && level[a] <= level[ancestor[b][i]])
				b = ancestor[b][i];
		}
	}
	int lca = a;
	//a와 b가 다르다면 현재 깊이가 같으니, 깊이를 a,b동시에 계속 올려준다.
	if (a != b)
	{
		assert(level[a] == level[b]);
		for (int i = max_level; i >= 0; i--)
		{
			if (ancestor[a][i] != ancestor[b][i])
			{
				a = ancestor[a][i];
				b = ancestor[b][i];
			}
			lca = ancestor[a][i];
		}
	}
	return lca;
}
int32_t main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	FileInput;

	int N; cin >> N; vector<vector<node>> adj_list(N + 1);
	for (int i = 0; i < N - 1; i++) {
		int u, v, w; cin >> u >> v >> w;
		adj_list[u].push_back({ v,w });
		adj_list[v].push_back({ u,w });
	}
	result r = treefy(adj_list, 1, true);

	int mm; cin >> mm; for (int z = 0; z < mm; z++)
	{
		IN(op);
		if (op == 1) {

			int a, b; cin >> a >> b;
			int ca = lca(a, b, r.tree, r.level, r.ancestor);
			OUT(r.dist[a] + r.dist[b] - 2 * r.dist[ca]);
		}
		else {
			int a, b, c; cin >> a >> b >> c;
			int ca = lca(a, b, r.tree, r.level, r.ancestor);
			int len_to_ca = r.level[a] - r.level[ca] + 1;
			if (c <= len_to_ca) {
				int target_lv = r.level[a] - c + 1;
				//binary lifting 필요
				for (int i = r.max_level; i >= 0; i--)
				{
					if (r.ancestor[a][i] != -INF && target_lv <= r.level[r.ancestor[a][i]])
						a = r.ancestor[a][i];
				}
				assert(r.level[a] == target_lv);
				OUT(a);
			}
			else {
				c -= len_to_ca;  // 6이면 2가됨
				int target_lv = r.level[ca] + c;
				for (int i = r.max_level; i >= 0; i--)
				{
					if (r.ancestor[b][i] != -INF && target_lv <= r.level[r.ancestor[b][i]])
						b = r.ancestor[b][i];
				}
				assert(r.level[b] == target_lv);
				OUT(b);
			}
		}

	}
	return 0;
}