#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include "dbg.h"  // https://github.com/sharkdp/dbg-macro
#else
#define dbg(...)
#endif

//#define int long long
using namespace std;
#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define REP1(i,n) for(int i=1;i<=(int)(n);i++)
using vi = vector<int>;
using vs = vector<string>;
using vvi = vector<vi>;
#define all(r) (r).begin(),(r).end()
typedef long long ll;
const int INF = (int)1e9;

struct trie {
    struct node { map<char, node> child; bool end = false; };
    node root;
    map<string, int> cnt;
    int tot_cnt=0;
    node* insert(node* n, char c) {
        auto& m = n->child;
        if (m.count(c) == 0) m[c] = node();
        return &m[c];
    }
    void insert(string s) {
        node* n = &root;
        int m = s.length();
        for(int j=0;j<m;j++) n = insert(n, s[j]);
        n->end = true;
        cnt[s]++, tot_cnt++;
    }

    node* find(node* n, char c) {
        auto& m = n->child;
        if (m.count(c) == 0) return NULL;
        return &m[c];
    }

    bool find(string s) {
        node* n = &root;
        int m = s.length();
        for (int j = 0; j < m; j++) {
            n = find(n, s[j]);
            if (n == NULL) return false;
        }
        return n->end;
    }
};

int32_t main()
{
    ios::sync_with_stdio(0); cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif
    string s;
    trie t;
    while (getline(cin, s)) {
        t.insert(s);
    }
    //int sum = accumulate(t.cnt.begin(), t.cnt.end(), 0);
    cin.precision(4);
    for (auto a : t.cnt) {
        cout << a.first << ' ' << fixed << 100.0*a.second / t.tot_cnt << '\n';
    }
    return 0;
}