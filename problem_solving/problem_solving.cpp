#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
using vi = vector<int>;
using vvi = vector<vi>;

int32_t main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int V, E; cin >> V >> E;
	vvi adj_list(V + 1);
	REP(i, E)
	{
		int A, B; cin >> A >> B;
		adj_list[A].push_back(B);
		adj_list[B].push_back(A);
	}
	set<pair<int, int>> ans;
	//아래에서 visit는 ord와 통합가능하지만, 가독성을 위해 남겨둠
	vi visit(V + 1), ord(V + 1), parent(V + 1), root(V + 1); int g_ix = 0;
	function<int(int, int)> dfs = [&](int n, int par)-> int  // low를 리턴
	{
		visit[n] = 1;
		ord[n] = ++g_ix;
		int low = ord[n];
		for (auto adj : adj_list[n])
		{
			if (adj == par) continue;
			if (visit[adj])  // 백엣지의 경우
				low = min(low, ord[adj]);  // 접근가능한 백정점 순서로 업데이트
			else {  // 트리엣지의 경우
				int r = dfs(adj, n);
				// 자식트리중 하나라도 자신위로 올라가지 못하면
				if (r > ord[n])  // 단절점 케이스와 다르게 r == ord[n]인 경우 그려보면 사이클로 인해 단절선이 아님을 알 수 있다.
				{
					// 전체 자식노드를 보는게 아니라 즉발기로 동작함에 유의
					// 주의할점은 현재 정점의 low값을 최종결정하기전에
					// 단절점 판정이 이루어지는 부분
					ans.insert({ min(n,adj), max(n,adj) });  // 문제 조건에 따라 순서 조정
				}
				low = min(low, r);
			}
		}
		// 단절선에서 루트정점이란 개념은 빠진다.
		// if (par == -1 && child > 1) ans.insert(n);
		return low;
	};
	REP1(i, V)if (visit[i] == 0)dfs(i, -1), root[i] = 1;
	cout << (int)ans.size() << endl;
	for (auto a : ans) cout << a.first << ' ' << a.second << endl;
	return 0;
}