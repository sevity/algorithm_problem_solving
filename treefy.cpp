//무방향그래프를 인풋으로 받아, 특정 정점을 루트를 가지는 방향그래프(트리)로 만들어준다.
vector<vi> treefy(vector<vi>& adj_list, int root) {
    vector<vi> tree(adj_list.size());
    function<void(int, int)> dfs = [&](int node, int parent) {
        for (auto adj : adj_list[node]) {
            if (adj == parent) continue;  // 부모방향 간선제거
            tree[node].push_back(adj);
            dfs(adj, node);
        }
    };
    dfs(root, -1);
    return tree;
}