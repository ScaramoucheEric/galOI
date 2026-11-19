#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cstdio>
#include <queue>

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

using namespace std; Read fin;

const int Mod = 1e9 + 7;

void solve() {
    int n; fin >> n;

    string s1, s2, sw1, sw2; cin >> s1 >> s2 >> sw1 >> sw2;

    s1 = ' ' + s1; s2 = ' ' + s2;
    sw1 = ' ' + sw1, sw2 = ' ' + sw2;

    struct Node {
        int n;
        vector<int> cnt0, cnt1;
        vector<int> fa;

        Node(int N, string & s) : n(N) {
            cnt0.resize(n + 1); cnt1 = fa = cnt0;

            for (int i = 1; i <= n; i ++ )
                if (s[i] == '1')
                    cnt1[i] = 1;
                else cnt0[i] = 1;

            for (int i = 1; i <= n; i ++ )
                fa[i] = i;
        }

        function<int(int)> find = [&](int x) {
            if (fa[x] == x) return x;
            return fa[x] = find(fa[x]);
        };
        function<void(int, int)> merge = [&](int x, int y) {
            if (find(x) == find(y)) return;

            cnt0[find(y)] += cnt0[find(x)];
            cnt1[find(y)] += cnt1[find(x)];

            fa[find(x)] = find(y);
        };
    }; Node A(n, s1), B(n, s2);

    for (int i = 1; i < n; i ++ ) {
        if (sw1[i] == '1') {
            if (sw1[i + 1] == '1')
                A.merge(i, i + 1);
        }
        
        if (sw2[i] == '1') {
            if (sw2[i + 1] == '1')
                B.merge(i, i + 1);
            // cout << sw2[i] << " " << sw2[i + 1] << " ";
            // cout << i << " " << i + 1 << endl;
        }
    }

    int res = 0;

    // for (int i = 1; i <= n; i ++ )
    //     cout << A.find(i) << " \n"[i == n];
    // for (int i = 1; i <= n; i ++ )
    //     cout << A.cnt0[A.find(i)] << " \n"[i == n];
    // for (int i = 1; i <= n; i ++ )
    //     cout << A.cnt1[A.find(i)] << " \n"[i == n];

    // for (int i = 1; i <= n; i ++ )
    //     cout << B.find(i) << " \n"[i == n];
    // for (int i = 1; i <= n; i ++ )
    //     cout << B.cnt0[B.find(i)] << " \n"[i == n];
    // for (int i = 1; i <= n; i ++ )
    //     cout << B.cnt1[B.find(i)] << " \n"[i == n];

    for (int i = 1; i <= n; i ++ ) {
        if (A.cnt0[A.find(i)] and B.cnt0[B.find(i)]) {
            A.cnt0[A.find(i)] -- , B.cnt0[B.find(i)] -- , res ++ ;
        } else if (A.cnt1[A.find(i)] and B.cnt1[B.find(i)]) {
            A.cnt1[A.find(i)] -- , B.cnt1[B.find(i)] -- , res ++ ;
        } else {
            if (A.cnt0[A.find(i)]) A.cnt0[A.find(i)] -- ;
            else A.cnt1[A.find(i)] -- ;
            if (B.cnt0[B.find(i)]) B.cnt0[B.find(i)] -- ;
            else B.cnt1[B.find(i)] -- ;
        }
        // cout << i << " " << res << endl;
    }

    cout << res << endl;
}

signed main() {
    int T; fin >> T;

    while(T -- ) {
        solve();
    }
}