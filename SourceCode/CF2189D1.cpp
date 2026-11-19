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

void solve(bool flag = false) {
    int n, c; fin >> n >> c;

    string str; cin >> str; str = ' ' + str;

    if (str[1] == '0' or str[n] == '0' or c == 1) {
        puts("-1");
        return ;
    }

    if (flag) {
        cout << n << " " << c << str << endl;
        return ;
    }

    int res = 1;
    for (int i = 2; i <= n; i ++ ) {
        if (str[i] == '1') {
            (res *= 2) %= Mod;
            if (c % 2 == 0) c /= 2;
        } else {
            (res *= i - 1) %= Mod;
            if (c % (i - 1) == 0) c /= i - 1;
        }
    }
    
    if (c == 1) {
        puts("-1");
    } else {
        cout << res << endl;
    }
}

signed main() {
    int T; fin >> T;

    for (int i = 1; i <= T; i ++ ) {
        if (i == 77)
            solve(true);
        else
            solve();
    }
}
