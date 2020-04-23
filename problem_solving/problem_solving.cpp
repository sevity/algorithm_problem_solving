#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

bool has_cycle(int max_v, int cur_v, vvi& adj_list, bool base1 = false) {
    if (base1) max_v++;
    static vi visited; if (visited.size() != max_v)visited.resize(max_v, 0);
    function<bool(int)> dfs = [&](int cur_v) -> bool {
        if (visited[cur_v]) {
            if (visited[cur_v] == -1) return true;
            return false;
        }
        visited[cur_v] = -1;
        for (int adj : adj_list[cur_v]) {
            if (dfs(adj)) {
                return true;
            }
        }
        visited[cur_v] = 1;
        return false;
    };
    return dfs(cur_v);
}

int main()
{
    int N, M; cin >> N >> M;
    vector<vector<int>> adj_list(N);
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        adj_list[u].push_back(v);
    }

    bool ans = false;
    for (int i = 0; i < N; i++) {
        if (has_cycle(N, i, adj_list)) { ans = true; break; }
    }

    printf("%d\n", ans ? 1 : 0);
    return 0;
}