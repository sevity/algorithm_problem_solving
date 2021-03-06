#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define REP1(i,n) for(int i=1;i<=(int)(n);i++)
using vi = vector<int>;
using vvi = vector<vi>;

struct result { vi scc_map;  vvi scc_list; };
result scc_dag_tarjan(vvi& adj_list, int base1)
{
    int max_v = (int)adj_list.size() - 1;  // base1==0일때 테스트 안됨!
    //타잔은 수행후 SCC들이 역순으로 위상정렬을 이루므로,
    //그 성질을 이용하면 좋다(2-SAT등)

    vvi ans;
    stack<int> S;
    //아래에서 visit는 ord와 통합가능하지만, 가독성을 위해 남겨둠
    vi scc_map(max_v + base1, -1), visit(max_v + base1), ord(max_v + base1), parent(max_v + base1); int g_ix = 0;
    // 코사라주나 단절선 구하는것과 다르게 finish 운영해줌
    // 일반적으로 finish배열이 dfs리턴할때 true해주는것과 다르게
    // SCC분리가 끝났음을 의미
    vi finish(max_v + base1);
    static int scc_ix = base1;
    function<int(int)> dfs = [&](int n)-> int  // low를 리턴
    {
        visit[n] = 1;
        ord[n] = ++g_ix;
        int low = ord[n];
        S.push(n);  // 스택에 먼저 푸시
        for (auto adj : adj_list[n])
        {
            if (visit[adj] == 0)  // tree edge 의 경우
            {
                int r = dfs(adj);
                // 단절점 로직의 경우 여기서 자식트리중 하나라도 자신위로 올라가지 못하면 단절점으로 판정하지만
                // SCC 타잔에서는 그러한 로직은 없고, 루프하단에 result == ord[n] 으로
                // 자신포함 자식트리중 도달가능한 가장 높은 정점이 자신일 경우 SCC 추출하는 로직으로 바뀐다.
                // if (r > ord[n]) ans.insert({ min(n,adj), max(n,adj) });
                low = min(low, r);
            }
            // 방문은 했으나 아직 SCC로 추출되지는 않은 이웃
            else if (finish[adj] == 0)  // back edge 또는 cross edge의 일부
                low = min(low, ord[adj]);  // 접근가능한 백정점 순서로 업데이트
        }
        // 자신포함 자식트리중 도달가능한 가장 높은 정점이 자신일 경우 SCC 추출
        if (low == ord[n])
        {
            vi scc;
            while (S.size())
            {
                int a = S.top(); S.pop();
                scc.push_back(a);
                scc_map[a] = scc_ix;
                finish[a] = 1;
                if (a == n) break;
            }
            sort(scc.begin(), scc.end());
            ans.push_back(scc);
            scc_ix++;
        }

        return low;
    };
    for (int i = base1; i < max_v + base1; i++) if (visit[i] == 0) dfs(i);
    return { scc_map, ans };
}

#define DBL(a) (2*(a))
#define CONV(a) (a)<0?(a)*-2:(a)*2+1
int32_t main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int N, M; cin >> N >> M;
    vvi adj_list(DBL(N+1));
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        a = CONV(a);
        b = CONV(b);

        //nice magic property!
        int na = a ^ 1;
        int nb = b ^ 1;

        //not a -> b
        adj_list[na].push_back(b);

        //not b -> a
        adj_list[nb].push_back(a);
    }
    auto r = scc_dag_tarjan(adj_list, true);
    for (int i = 1; i <= N; i++)
    {
        if (r.scc_map[CONV(i)] == r.scc_map[CONV(-i)]) { cout << 0 << '\n'; return 0; }
    }
    // 여기까지 오면 변수조합이 있는건 보장된다. 모순만 없도록 배열해주면 됨
    cout << 1 << '\n';
    for (int i = 1; i <= N; i++) {
        // 아랫부분 아직 제대로 이해 못한 상태 ㅠ
    	// 소스가 워낙 간결해서 일단 채택은 해 두었다.
        cout << (r.scc_map[CONV(i)] < r.scc_map[CONV(-i)]) << ' ';  
    }
    return 0;
}
