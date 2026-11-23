/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC462D].cpp
    @ Date:         06/13/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
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

template<typename T>
struct Node {
    int n;
    vector<T> bit;
    Node(int n_) : n(n_), bit(n_ + 1, 0) {}
    void add(int idx, T a) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += a;
    }
    T sum(int idx) {
        T res = 0;
        for (; idx > 0; idx -= idx & -idx) res += bit[idx];
        return res;
    }
    T sum(int l, int r) {
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }
};

signed main() {
    int N, D; fin >> N >> D;

    vector<pair<int, int> > arr(N);
    vector<int> T;

    for (int i = 0; i < N; ++i) {
        fin >> arr[i].first >> arr[i].second;
        T.push_back(arr[i].second);
    }

    sort(arr.begin(), arr.end());

    sort(all(T));
    T.erase(unique(all(T)), T.end());
    int M = T.size();

    Node<int> bcnt(M), bsum(M);
    int ans = 0;

    for (int i = 0; i < N; ++i) {
        int s = arr[i].first;
        int t = arr[i].second;

        if (t >= s + D) {
            int L = s + D;
            int R = t;

            int lidx = lower_bound(all(T), L) - T.begin() + 1;
            int ridx = upper_bound(all(T), R) - T.begin();

            if (lidx <= ridx) {
                int cnt = bcnt.sum(lidx, ridx);
                int sumT = bsum.sum(lidx, ridx);
                ans += sumT - cnt * (L - 1);
            }

            int idxT = lower_bound(all(T), t) - T.begin() + 1;
            int leq = bcnt.sum(idxT);
            int total_prev = i;
            int gt = total_prev - leq;
            ans += gt * (t - s - D + 1);
        }

        int idxT = lower_bound(all(T), t) - T.begin() + 1;
        bcnt.add(idxT, 1);
        bsum.add(idxT, t);
    }

    cout << ans << endl;
    return 0;
}