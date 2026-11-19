/*
    @ Author:       Eric / Sky__White
    @ Filename:     [AcWing 241].cpp
    @ Time:         11/28/2025
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
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

using namespace std; Read fin;

class BIT {
    public:
        vector<int> arr;
        inline void init(int x) {
            arr.resize(x + 1);
        }
        inline int lowbit(int x) {
            return x & -x;
        }
        inline int query(int x) {
            int sum = 0;
            for (int i = x; i; i -= lowbit(i))
                sum += arr[i];
            return sum;
        }
        inline void add(int x) {
            for (int i = x; i < arr.size(); i += lowbit(i))
                arr[i] ++ ;
        }
};

signed main() {
    int n; fin >> n;

    BIT T; T.init(n);

    int vv = 0, tt = 0;

    for (int i = 1; i <= n; i ++ ) {
        int x; fin >> x;
        int t = T.query(x);
        int v = T.query(n) - T.query(x);
        T.add(x);
        vv += (v) * (n - x - v);
        tt += (t) * (x - 1 - t);
        // cout << (v) * (n - x - v) << " " << (t) * (x - 1 - t) << endl;

        // for (int i = 1; i <= n; i ++ )
        //     cout << T.query(i) - T.query(i - 1) << " ";
        // cout << endl;

        // for (int i = 1; i <= n; i ++ )
        //     cout << T.query(i) << " ";
        // cout << endl << endl;
    }
    
    cout << vv << " " << tt << endl;

    return 0;
}