#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
const int INF = (int)1e9;

//무방향그래프를 인풋으로 받아, 트리로 만들어준다.LCA를 위한 작업도 해준다.
struct result { vvi tree; int root; vi parent, level; int max_level; vvi ancestor; };
result treefy(vector<vi>& adj_list, int root = -1, bool base1 = false) {
	int max_v = (int)adj_list.size() + (int)base1;
	vector<vi> tree(max_v);
	if (root == -1)
	{
		// find root(왼쪽이 parent인경우만 성립하는듯, 안그러면 root가 여러개다.)
		map<int, int> m;
		for (int i = (int)base1; i < max_v; i++)
			for (auto a : adj_list[i]) m[a]++;
		for (int i = (int)base1; i < max_v; i++)
			if (m[i] == 0) { root = i; break; }
	}
	vi parent(max_v), level(max_v);
	int max_level = (int)floor(log2(max_v));
	vvi ac(max_v, vi(max_level + 1, -INF));  // ac[x][y] :: x의 2^y번째 조상을 의미
	function<void(int, int, int)> dfs = [&](int node, int par, int lv) {
		parent[node] = par, level[node] = lv;
		ac[node][0] = par;  // 첫번째(2^0) 조상은 부모
		for (int i = 1; i <= max_level; i++) {
			//아래 두줄을 통해 과거 조상들을 2^k 스케일로 쭉쭉 구해나간다.
			int tmp = ac[node][i - 1];  // tmp :: node의 2^(i-1)번째 조상
			if (tmp == -INF) break;
			ac[node][i] = ac[tmp][i - 1];
		}
		for (auto adj : adj_list[node]) {
			if (adj == par) continue;  // 부모방향 간선제거
			tree[node].push_back(adj);
			dfs(adj, node, lv + 1);
		}
	};
	dfs(root, -INF, 1);
	return { tree, root, parent, level,max_level, ac };
}

int lca(int node_a, int node_b, vvi& tree, vi& level, vvi& ancestor)
{
	int max_v = (int)tree.size() + 1;
	int a = node_a, b = node_b;
	int max_level = (int)floor(log2(max_v));
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

	int N; cin >> N; vvi adj_list(N + 1);
	for (int i = 0; i < N - 1; i++) {
		int u, v; cin >> u >> v;
		adj_list[u].push_back(v);
		adj_list[v].push_back(u);
	}
	result r = treefy(adj_list, 1, true);
	int m; cin >> m; for (int z = 0; z < m; z++)
	{
		int a, b; cin >> a >> b;
		int ans = lca(a, b, r.tree, r.level, r.ancestor);
		cout << (ans) << '\n';
	}
	return 0;
}