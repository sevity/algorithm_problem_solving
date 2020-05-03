#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define REP1(i,n) for(int i=1;i<=(int)(n);i++)
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
	}
	vvi ans;
	stack<int> S;
	//아래에서 visit는 ord와 통합가능하지만, 가독성을 위해 남겨둠
	vi visit(V + 1), ord(V + 1), parent(V + 1), root(V + 1); int g_ix = 0;
	// 코라사주나 단절선 구하는것과 다르게 finish 운영해줌
	// 일반적으로 finish배열이 dfs리턴할때 true해주는것과 다르게
	// SCC분리가 끝났음을 의미
	vi finish(V + 1);
	function<int(int)> dfs = [&](int n)-> int  // low를 리턴
	{
		visit[n] = 1;
		ord[n] = ++g_ix;
		int low = ord[n];
		S.push(n);  // 스택에 먼저 푸시
		for (auto adj : adj_list[n])
		{
			//if (adj == par) continue;  // SCC는 방향그래프로 주어지므로 parent개념은 없다.
			if (visit[adj] == 0)  // tree edge 의 경우
			{
				int r = dfs(adj);
				// 단절점 로직의 경우 여기서 자식트리중 하나라도 자신위로 올라가지 못하면 단절점으로 판정하지만
				// SCC 타잔에서는 그러한 로직은 없고, 아래에 result == ord[n] 으로
				// 자신포함 자식트리중 도달가능한 가장 높은 정점이 자신일 경우 SCC 추출하는 로직으로 바뀐다.
				// if (r > ord[n]) ans.insert({ min(n,adj), max(n,adj) });
				low = min(low, r);
			}
			// 방문은 했으나 아직 SCC로 추출되지는 않은 이웃
			else if (finish[adj]==0)  // back edge 또는 cross edge의 일부
				low = min(low, ord[adj]);  // 접근가능한 백정점 순서로 업데이트
		}
		// 자신포함 자식트리중 도달가능한 가장 높은 정점이 자신일 경우 SCC 추출
		if (low == ord[n])
		{
			vi scc;
			while(S.size())
			{
				int a = S.top(); S.pop();
				scc.push_back(a);
				finish[a] = 1;
				if (a == n) break;
			}
			sort(scc.begin(), scc.end());
			ans.push_back(scc);
		}
		
		return low;
	};
	REP1(i, V)if (visit[i] == 0)dfs(i), root[i] = 1;
	sort(ans.begin(), ans.end());
	cout << (int)ans.size() << '\n';;
	for(auto a:ans)
	{
		for (auto b : a) cout << b << ' ';
		cout << -1 << '\n';;
	}
	return 0;
}