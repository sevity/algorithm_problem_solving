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

using vi = vector<int>;
using vvi = vector<vi>;
bool has_cycle(int max_v, int cur_v, vvi& adj_list, bool base1 = false) {
    if (base1) max_v++;
    static vi visited; if (visited.size() != max_v)visited.resize(max_v, 0);
    function<bool(int)> dfs = [&](int v) -> bool {
        if (visited[v]) {
            if (visited[v] == -1) return true;
            return false;
        }
        visited[v] = -1;
        for (int adj : adj_list[v]) {
            if (dfs(adj)) {
                return true;
            }
        }
        visited[v] = 1;
        return false;
    };
    return dfs(cur_v);
}

using vi = vector<int>;
using vvi = vector<vi>;
struct result0 { bool cycle; vi sorted; };
result0 topological_sort0(int max_v, int start_v, vvi& adj_list, bool base1 = false) {
    if (base1) max_v++;
    // cycle 검출을 위해 finish배열 하나더 기용해준다.
    // visit되고 finish되기전에 다시 방문되면 사이클로 보는것
    vi visit(max_v), finish(max_v);
    result0 r = { false, vi() };
    deque<int> sorted; bool gcycle = false;
    function<void(int)> dfs = [&](int v) {
        bool cycle = false;
        visit[v] = 1;
        for (auto adj : adj_list[v]) {
            if (visit[adj] == 0) dfs(adj);
            else if (finish[adj] == 0) {
                gcycle = cycle = 1;// visit은 1인데, finish 는 0으로 들어왔다? cycle!
            }
        }
        finish[v] = 1;
        if(cycle==0) sorted.push_front(v);
    };
    if (start_v == -1) {
        for (int i = (int)base1; i < max_v; i++)
            if (visit[i] == 0) dfs(i);
    }
    else dfs(start_v);
    return { gcycle, vi(sorted.begin(), sorted.end()) };
}

bool overflow = false;
struct result { bool cycle; int cnt; };
result topological_sort(int max_v, vvi& adj_list, bool base1 = false) {
    if (base1) max_v++;
    // cycle 검출을 위해 finish배열 하나더 기용해준다.
    // visit되고 finish되기전에 다시 방문되면 사이클로 보는것
    vi visit(max_v), finish(max_v);
    vi dp(max_v, -1);
    deque<int> sorted; bool cycle = false;
    function<int(int)> dfs = [&](int v)->int {
        //visit[v] = 1;
        int& res = dp[v];
        if (dp[v] != -1) return res;
        int r = (v == 2 ? 1 : 0);
        for (auto adj : adj_list[v]) {
            if (visit[adj] == 0) {
                if (r >= 1e10) overflow = 1, r %= (int)1e10;
                r += dfs(adj);
            }
            else if (finish[adj] == 0) {
                cycle = 1;// visit은 1인데, finish 는 0으로 들어왔다? cycle!
                OUT("err");
                return res = INF;
            }
        }
        finish[v] = 1;
        if (r >= 1e10) overflow = 1, r %= (int)1e10;
        return res = r;
    };
    int cnt = dfs(1);
    return { cycle, cnt };
}


int32_t main()
{
    FastIO; FileInput;
    int N, M; cin >> N >> M;
    vvi adj_list(N + 1);
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v; adj_list[u].push_back(v);
    }
    result0 r0 = topological_sort0(N, 1, adj_list, true);
    dbg(r0.sorted);
    map<int, int> m; for (auto a : r0.sorted) m[a]++;
    m[1]++; //1번 노드는 사이클 있더라도 포함시킨다.
    vvi adj_list2(N + 1);
    for (int i = 1; i <= N; i++) {
        if (m.count(i) == 0) continue;
        for(auto adj:adj_list[i])
        {
            if (m.count(adj) == 0) continue;
            adj_list2[i].push_back(adj);
        }
    }
    dbg(adj_list2);

    if(has_cycle(N, 1, adj_list2, true))
    {
        OUT("inf");
        return 0;
    }
    result r = topological_sort(N, adj_list2, true);
    if (overflow)
    {
	    cout << setfill('0') << setw(9) << r.cnt % (int)1e9 << endl;
    }
    else { OUT(r.cnt); }
    return 0;
}