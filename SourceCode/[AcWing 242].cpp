/*
    @ Author:       Eric / Sky__White
    @ Filename:     [AcWing 242].cpp
    @ Time:         11/28/2025
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
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
    } fin;
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std;

class BIT {
    public:
        vector<int> arr;
        int n;
        BIT() {}
        BIT(int n) : n(n) {
            arr.resize(n + 2);
        }
        inline int lowbit(int x) {
            return x & -x;
        }
        void add(int x, int d) {
            for (int i = x; i <= n; i += lowbit(i))
                arr[i] += d;
        }
        int query(int x) {
            int res = 0;
            for (int i = x; i; i -= lowbit(i))
                res += arr[i];
            return res;
        }
};

signed main() {
    int n, m; fin >> n >> m;

    BIT T(n);
    for (int i = 1; i <= n; i ++ ) {
        int x; fin >> x;
        T.add(i, x), T.add(i + 1, -x);
    }

    for (int i = 1, ch, l, r, d; i <= m; i ++ ) {
        ch = getchar();
        if (ch == 'C') {
            fin >> l >> r >> d;
            T.add(l, d), T.add(r + 1, -d);
        } else {
            fin >> d;
            cout << T.query(d) << endl;
        }
    }

    return 0;
}