//������׷����� ��ǲ���� �޾�, Ư�� ������ ��Ʈ�� ������ ����׷���(Ʈ��)�� ������ش�.
vector<vi> treefy(vector<vi>& adj_list, int root) {
    vector<vi> tree(adj_list.size());
    function<void(int, int)> dfs = [&](int node, int parent) {
        for (auto adj : adj_list[node]) {
            if (adj == parent) continue;  // �θ���� ��������
            tree[node].push_back(adj);
            dfs(adj, node);
        }
    };
    dfs(root, -1);
    return tree;
}