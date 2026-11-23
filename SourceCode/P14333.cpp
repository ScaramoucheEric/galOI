/*
    @ Author:       Eric / Sky__White
    @ Filename:     P14333.cpp
    @ Date:         11/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

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
const int INF = 0x3f3f3f3f3f3f3f3f;

signed main() {
    int n, k; fin >> n >> k;

    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i ++ ) fin >> a[i];
    for (int i = 1; i <= n; i ++ ) fin >> b[i];
    vector<int> aa = a, bb = b;

    int l = 0, r = INF, res = INF;

    function<bool(int)> judge = [&](int tim) -> bool {
        int people = 0;
        for (int i = n; i; i -- ) {
            if (tim - a[i] == 0) {
                return false;
            }
            people += (b[i] + tim - a[i] - 1) / (tim - a[i]);
            if ((b[i] + tim - a[i] - 1) / (tim - a[i]) * (tim - a[i]) - b[i] < 0) return false;
            b[i - 1] -= ((b[i] + tim - a[i] - 1) / (tim - a[i]) * (tim - a[i]) - b[i]);
            // cout << b[i] << " ";
        }
        // cout << endl;
        a = aa; b = bb;
        // cout << people << endl;
        if (people > k) return false;
        return true;
    };

    while(l <= r) {
        int mid = l + r >> 1;

        // printf("l = %lld; r = %lld; mid = %lld\n", l, r, mid);

        if (judge(mid)) {
            res = mid, r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << res << endl;

    return 0;
}