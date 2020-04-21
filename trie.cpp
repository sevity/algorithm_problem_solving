#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<(int)(n);i++)
 
struct trie {
    struct node { map<char, node> child; bool end = false; };
    node root;
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
    int N, M; cin >> N >> M;
    trie t;
    REP(i, N) {
        string s; cin >> s;
        t.insert(s);
    }
    int ans = 0;
    REP(i, M) {
        string s; cin >> s;
        ans += t.find(s) ? 1 : 0;
    }
    cout << ans << '\n';
    return 0;
}
