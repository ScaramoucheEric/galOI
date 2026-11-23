#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <cstdio>
#include <cctype>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read& operator >> (T & x) {
            T sum = 0; short opt = 1;
            char ch = getchar();
            while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt; return *this;
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()
#define endl "\n"
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);

using namespace std; Read fin;

int big_sum(const vector<int>& a, int cnt) {
    int n = a.size();
    int res = 0;
    for (int i = n - cnt; i < n; i ++ )
        res += a[i];
    return res;
}

int small_sum(const vector<int>& a, int cnt) {
    int res = 0;
    for (int i = 0; i < cnt; i ++ )
        res += a[i];
    return res;
}

int Solve(vector<int> L, vector<int> R) {
    if (L.size() > R.size())
        swap(L, R);

    sort(all(R));

    int cntL = (int)L.size();
    int cntR = (int)R.size();
    int diff = cntR - cntL;

    int pos = diff / 4;
    int ne = (diff + 2) / 4;

    int nesum = small_sum(R, ne);

    vector<int> rest;
    rest.reserve(cntL + cntR - ne);
    rest.insert(rest.end(), all(L));
    for (int i = ne; i < cntR; i ++ )
        rest.push_back(R[i]);

    sort(all(rest));

    int cnt = cntL + pos;
    int sum = big_sum(rest, cnt);

    return sum - nesum;
}

void solve();

signed main() {
    #ifndef ONLINE_JUDGE
    IO("turnlist")
    #endif

    int T = 1;
    fin >> T;

    while(T -- ) {
        solve();
    }
}

const int INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n; fin >> n;

    vector<int> L, R;
    for (int i = 1; i <= n; i ++ ) {
        char c; cin >> c;
        int x; fin >> x;

        if (c == 'L')
            L.push_back(x);
        else
            R.push_back(x);
    }

    cout << Solve(L, R) << endl;
}
