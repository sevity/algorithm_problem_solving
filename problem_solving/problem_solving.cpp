#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
struct result { bool cycle; vi sorted; };
result topological_sort(int max_v, int start_v, vvi& adj_list, bool base1 = false) {
	if (base1) max_v++;
	// cycle 검출을 위해 finish배열 하나더 기용해준다.
	// visit되고 finish되기전에 다시 방문되면 사이클로 보는것
	vi visit(max_v), finish(max_v);
	result r = { false, vi() };
	deque<int> sorted; bool cycle = false;
	function<void(int)> dfs = [&](int v) {
		visit[v] = 1;
		for (auto adj : adj_list[v]) {
			if (visit[adj] == 0) dfs(adj);
			else if (finish[adj] == 0) {
				cycle = 1;// visit은 1인데, finish 는 0으로 들어왔다? cycle!
			}
		}
		finish[v] = 1;
		sorted.push_front(v);
	};
	if (start_v == -1) {
		for (int i = (int)base1; i < max_v; i++) 
			if (visit[i] == 0) dfs(i);
	}
	else dfs(start_v);
	return { cycle, vi(sorted.begin(), sorted.end()) };
}

int32_t main()
{
	int N, M; cin >> N >> M;
	//vi in(N + 1);  // DFS버전에서는 in-edge관리를 안해도 된다.
	vvi adj_list(N + 1);
	for (int i = 0; i < M; i++) {
		int u, v; cin >> u >> v; adj_list[u].push_back(v);
	}

	// 일단 아이디어는 DFS돌려서 말단까지 가고,
	// 거기서 부터 stack에 넣어주면 위상정렬 정순위가 된다는것.
	result r = topological_sort(N, -1, adj_list, true);
	for (auto a : r.sorted) cout << a << ' ';
	return 0;
}