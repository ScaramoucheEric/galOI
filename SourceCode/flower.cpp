/*
    @ Author:       Eric / Sky__White
    @ Filename:     flower.cpp
    @ Date:         18/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <vector>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator >> (T & x) {
            T sum = 0; short opt = 1;
            char ch = getchar();
            while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt; return *this;
        }
    };
}
#define int long long
#define all(arr) arr.begin(), arr.end()

using namespace std; Read fin;

const int Mod = 998244353;

using PII = pair<int, int> ;

signed main() {
    freopen("flower.in", "r", stdin);
    freopen("flower.out", "w", stdout);
    
    int n; fin >> n;

    vector<int> arr(n + 1);

    for (int i = 1; i <= n; i ++ ) fin >> arr[i];

    function<int(int, int)> dfs = [&](int l, int r) -> int {
        if (l == r) {
            return arr[l] % Mod;
        }

        int m = (l + r) >> 1;
        int res = (dfs(l, m) + dfs(m + 1, r)) % Mod;

        int cntL = m - l + 1;
        int cntR = r - m;

        vector<int> Fl(cntL + 1), Gl(cntL + 1), Fr(cntR + 1), Gr(cntR + 1);

        int no = 0, take = 0;
        for (int i = m - 1; i >= l; i -- ) {
            int pos = i - l + 1;
            int new_no = max(no, take);
            int new_take = no + arr[i];
            no = new_no;
            take = new_take;
            Gl[pos] = max(no, take);
        }

        no = 0, take = 0;
        for (int i = m; i >= l; i -- ) {
            int pos = i - l + 1;
            int new_no = max(no, take);
            int new_take = no + arr[i];
            no = new_no;
            take = new_take;
            Fl[pos] = max(no, take);
        }

        no = 0, take = 0;
        for (int j = m + 2; j <= r; j ++ ) {
            int pos = j - (m + 1) + 1;
            int new_no = max(no, take);
            int new_take = no + arr[j];
            no = new_no;
            take = new_take;
            Gr[pos] = max(no, take);
        }

        no = 0, take = 0;
        for (int j = m + 1; j <= r; j ++ ) {
            int pos = j - (m + 1) + 1;
            int new_no = max(no, take);
            int new_take = no + arr[j];
            no = new_no;
            take = new_take;
            Fr[pos] = max(no, take);
        }

        vector<int> idx(cntL);
        for (int i = 0; i < cntL; i ++ ) idx[i] = l + i;

        sort(idx.begin(), idx.end(), [&](int i, int j) {
            return (Fl[i - l + 1] - Gl[i - l + 1]) < (Fl[j - l + 1] - Gl[j - l + 1]);
        });

        vector<int> sumF(cntL + 1, 0), sumG(cntL + 1, 0);
        for (int k = 0; k < cntL; k ++ ) {
            int i = idx[k];
            int pos = i - l + 1;
            sumF[k + 1] = (sumF[k] + Fl[pos]) % Mod;
            sumG[k + 1] = (sumG[k] + Gl[pos]) % Mod;
        }

        vector<PII> R;
        R.reserve(cntR);
        for (int j = m + 1; j <= r; j ++ ) {
            int pos = j - (m + 1) + 1;
            int rhs = Fr[pos] - (pos == 1 ? 0 : Gr[pos]);
            R.emplace_back(rhs, j);
        }

        sort(all(R), [&](PII x, PII y) {
            return x.first < y.first;
        });

        int cs = 0, p = 0;
        
        for (auto [rhs, j] : R) {
            while (p < cntL && (Fl[idx[p] - l + 1] - Gl[idx[p] - l + 1]) < rhs) {
                p ++ ;
            }

            int pos = p;
            int fr = Fr[j - (m + 1) + 1] % Mod;
            int gr = (j == m + 1 ? 0 : Gr[j - (m + 1) + 1]) % Mod;

            int cur = (sumG[pos] + 1LL * pos * fr + (sumF[cntL] - sumF[pos] + Mod) % Mod + 1LL * (cntL - pos) * gr) % Mod;

            cs = (cs + cur) % Mod;
        }

        return (res + cs) % Mod;
    };

    cout << dfs(1, n) << '\n';
    return 0;
}