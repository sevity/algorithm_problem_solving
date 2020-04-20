#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
vi getPi(string p) {
    int m = (int)p.length();
    vi pi(m);
    for (int j = 0, i = 1; i < m; i++) {
        while (j > 0 && p[i] != p[j]) j = pi[j - 1];
        if (p[i] == p[j]) pi[i] = ++j;
    }
    return pi;
}

//p가 발견된 위치들을 리턴(0 base)
vi KMP(string t, string p) {
    int n = (int)t.length(), m = (int)p.length();
    vi pi = getPi(p);
    vi r;
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && t[i] != p[j]) j = pi[j - 1];
        if (t[i] == p[j]) {
            if (j == m - 1) 
                r.push_back(i - m + 1), 
                j = pi[j];  //j=0이 아님에 주의(오버랩고려)
            else j++;
        }
    }
    return r;
}

int32_t main()
{
    ios::sync_with_stdio(0); cin.tie(0);

    string t, p;
    getline(cin, t), getline(cin, p);
    vi v = KMP(t,p);
    cout << v.size() << '\n';
    for (auto a : v)cout << a + 1 << ' ';
    cout << '\n';
    return 0;
}

