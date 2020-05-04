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
    ios::sync_with_stdio(false); cin.tie(0);
    FileInput;
	CASE_T{
		int V, E; cin >> V >> E;
		vvi adj_list(V), adj_list2(V);
		REP(i, E) {
			int a, b; cin >> a >> b;
			adj_list[a].push_back(b);
			adj_list2[b].push_back(a); // 역방향
		}

		// step1. dfs로 방문하며 말단부터 stack push
		vi visit(V); stack<int> S;
		function<void(int n)> dfs = [&](int n) {
			if (visit[n]) return;
			visit[n] = 1;
			for (auto a : adj_list[n]) dfs(a);
			S.push(n);
		};
		REP(i, V) if (visit[i] == 0) dfs(i);

		// step2. stack에서 꺼내면서
		// 역방향으로 접근가능한 정점들을 SCC로 판정
		visit.clear(); visit.resize(V);
		vi scc(V);  // map. scc[v]=1 이면 v정점은 1번 SCC에 속한다고 하는것
		int scc_ix = 0;
		while (S.size()) {
			int n = S.top(); S.pop();
			if (visit[n]) continue;
			//vi ans2;
			function<void(int n)> dfs = [&](int n) {
				if (visit[n]) return;
				visit[n] = 1;
				//ans2.push_back(n);
				scc[n] = scc_ix;
				for (auto a : adj_list2[n]) dfs(a);
			};
			dfs(n);
			scc_ix++;
			//sort(ALL(ans2));
			//ans.push_back(ans2);
		}
		vi indegree(scc_ix); // map. indegree[1]=2 이면 1번 SCC로 들어오는 indegree는 2라고 하는 것
		REP(u,V){
			for (auto v : adj_list[u]) {
				if (scc[u] != scc[v]) 
					indegree[scc[v]]++;
			}
		}
		int zero_indegree_cnt = 0, zic_ix=-1;
		REP(i, scc_ix)if (indegree[i] == 0) zero_indegree_cnt++, zic_ix=i;
		if(zero_indegree_cnt == 1)
		{
			REP(u,V)
			{
				if (scc[u] == zic_ix) { OUT(u); }
			}
		}else
		{
			OUT("Confused");
		}
		cout << endl;
	}
    return 0;
}
