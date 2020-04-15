#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define REP1(i,n) for(int i=1;i<=(int)(n);i++)
using vi = vector<int>;
using vvi = vector<vi>;
struct union_find {
    vi parent;
    union_find(int n) {
        parent.resize(n + 1);
        REP1(i, n)parent[i] = i;
    }
    int find(int x) {
        int ox = x;
        while (parent[x] != x) x = parent[x];
        return parent[ox] = x;;
    }

    void uni(int x, int y) {
        int xp = find(x), yp = find(y);
        parent[yp] = xp;
    }
};

int main()
{
    int N = 7;
    cout << N << '\n';
    vvi adj_list(N + 1);
    union_find uf(N);
    int U, V; 
    REP(i, N - 1) {  // 트리는 반드시 N-1개의 간선을 가진다.
        A:
        U = rand() % N + 1;
        V = rand() % N + 1;
        if (uf.find(U) == uf.find(V)) goto A;  // 사이클을 가지면 채택하지 않는다.
        uf.uni(U, V);
        cout << U << ' ' << V << '\n';
        adj_list[U].push_back(V);
        adj_list[V].push_back(U);
    }
    return 0;
}
