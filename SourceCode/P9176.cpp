/*
    @ Author:       Eric / Sky__White
    @ Filename:     P9176.cpp
    @ Date:         30/09/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
#include <cstdio>
#include <vector>

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
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);
#define endl "\n"

#define N 200001

using namespace std;
int n, sum;
int v[N], a[N], b[N], c[N];

void add(int x, int k){
    for (int i = x; i <= n; i += i & -i) {
        c[i] += k;
    }
}
int qry(int x) {
    int cnt = 0;
    for (int i = x; i; i -= i & -i) {
        cnt += c[i];
    }
    return cnt;
}
int bin() {
    int l = 1, r = n;
    while (l <= r) {
        int mid = l + r >> 1;
        if (qry(mid) >= sum + 1 >> 1){
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return l;
}
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i ++ ) {
        cin >> v[i] >> a[i];
        b[i] = v[i];
    }
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i ++ ) {
        v[i] = lower_bound(b + 1, b + n + 1, v[i]) - b;
        sum += a[i];
        add(v[i], a[i]);
        cout << b[bin()] << endl;
    }
    return 0;
}
