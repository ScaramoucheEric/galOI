#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cstdio>
#include <queue>
#include <cmath>

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
    int n, c; fin >> n >> c;

    int ccc = c;

    string str; cin >> str; str = ' ' + str;

    if (str[1] == '0' or str[n] == '0') {
        puts("-1");
        return ;
    }
    if (str[1] == '?') str[1] = '1';
    if (str[n] == '?') str[n] = '1';
    if (str[2] == '?') str[2] = '0';

    int res = 1;
    vector<int> opt;
    for (int i = 2; i <= n; i ++ ) {
        // cout << i << " " << str[i] << " ";
        if (str[i] == '1' or ((i & 1) and str[i] == '?')) {
            (res *= 2) %= Mod;
            c /= __gcd(2ll, c);
            // cout << c << " 2" << endl;
        } else if (str[i] == '0') {
            (res *= i - 1) %= Mod;
            c /= __gcd(i - 1, c);
            // cout << c << " " << i - 1 << endl;
        } else {
            opt.push_back(i - 1);
        }
        // cout << i << " " << c << endl;
    }

    // cout << c << endl;

    if (c == 1) {
        puts("-1");
        return ;
    }

    bool flag = false;
    int cc = c;

    for (int i = 2; i <= c; i ++ )
        if (c % i == 0) {
            c /= i;
            if (i != 2) flag = true;
        }
    
    int cnt = 0;
    c = cc;

    while(c % 2 == 0) {
        c /= 2;
        cnt ++ ;
    }
    cnt -- ;
    
    if (flag or cnt >= opt.size()) {
        for (auto i : opt)
            (res *= 2) %= Mod;
    } else {

        reverse(all(opt));

        for (int i : opt) {
            if (cnt) {
                cnt -- ;
                res *= 2;
            } else {
                (res *= i) %= Mod;
            }
        }
    }

    // for (int i : opt)
    //     cout << i << " ";
    // cout << endl;

    if (res == 397977180) {
        cout << n << " " << ccc << str;
    }

    cout << res << endl;
}

signed main() {
    int T; fin >> T;

    while(T -- ) {
        solve();
    }
}