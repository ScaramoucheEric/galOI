#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cstdio>
#include <set>
#include <bitset>
#include <functional>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator >> (T & x) {
            T sum = 0, opt = 1;
            char ch = getchar();
            while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt; return *this;
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout)

using namespace std; Read fin;

signed main() {
    int k, m; fin >> k >> m;

    int idx = 0;
    map<char, int> tab; tab['#'] = idx ++ , tab['$'] = idx ++ ;

    for (int i = 0; i < 10; i ++ )
        tab['0' + i] = idx ++ ;
    for (int i = 0; i < 26; i ++ )
        tab['A' + i] = idx ++ ;
    for (int i = 0; i < 26; i ++ )
        tab['a' + i] = idx ++ ;

    function<void()> solve = [&]() {
        string a, b; cin >> a >> b;
        bitset<6000> A, B;
        int N = k * 6;
        while(a.size()) {
            int t = tab[a.back()];
            A <<= 6; A |= t; a.pop_back();
        }
        while(b.size()) {
            int t = tab[b.back()];
            B <<= 6; B |= t; a.pop_back();
        }

        auto t = A;

        int cnt = 0;
        while(A != B) {
            if (A[N - 1] == 1) {
                A[N - 1] = 0;
                A <<= 1;
                A[0] = 1;
            } else 
                A <<= 1;

            cnt ++ ;
            if (t == A) break;
        }

        if (A == B)
            cout << cnt << endl;
        else cout << -1 << endl;
    };

    for (int i = 1; i <= m; i ++ ) {
        solve();
    }
}