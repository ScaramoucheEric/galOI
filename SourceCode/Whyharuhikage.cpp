/*
    @ Author:       Eric / Sky__White
    @ Filename:     Whyharuhikage.cpp
    @ Date:         12/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <deque>
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

using i128 = __int128;

int MOD;

int mul_mod(int a, int b) {
    return (int)((i128)a * b % MOD);
}

struct Mat {
    int a[2][2];
    Mat(bool identity = false) {
        memset(a, 0, sizeof(a));
        if (identity) a[0][0] = a[1][1] = 1 % MOD;
    }
    Mat operator*(const Mat& other) const {
        Mat res;
        for (int i = 0; i < 2; ++i)
            for (int k = 0; k < 2; ++k)
                if (a[i][k])
                    for (int j = 0; j < 2; ++j)
                        res.a[i][j] = (res.a[i][j] + mul_mod(a[i][k], other.a[k][j])) % MOD;
        return res;
    }
};

struct Vec {
    int v[2];
    Vec(int x = 0, int y = 0) { v[0] = x % MOD; v[1] = y % MOD; }
    Vec operator*(const Mat& m) const {
        Vec res;
        for (int i = 0; i < 2; ++i) {
            res.v[i] = 0;
            for (int j = 0; j < 2; ++j)
                res.v[i] = (res.v[i] + mul_mod(v[j], m.a[j][i])) % MOD;
        }
        return res;
    }
};

Mat mat_pow(Mat base, int exp) {
    Mat res(true);
    while (exp > 0) {
        if (exp & 1) res = res * base;
        base = base * base;
        exp >>= 1;
    }
    return res;
}

struct FF {
    int f_prev, f_cur, f_next; // F_{d-1}, F_d, F_{d+1}
};

FF FT(int d) {
    if (d == 0) {
        return {1 % MOD, 0 % MOD, 1 % MOD};
    }
    Mat base;
    base.a[0][0] = 1 % MOD; base.a[0][1] = 1 % MOD;
    base.a[1][0] = 1 % MOD; base.a[1][1] = 0 % MOD;
    Mat p = mat_pow(base, d);
    // p = [[F_{d+1}, F_d], [F_d, F_{d-1}]]
    return {p.a[1][1], p.a[0][1], p.a[0][0]};
}

int solve(int n, int d, int mod) {
    MOD = mod;
    if (MOD == 1) return 0;
    if (n == 1) return 1 % MOD;

    auto [f_prev, f_cur, f_next] = FT(d); // F_{d-1}, F_d, F_{d+1}

    Mat A;
    A.a[0][0] = f_next;
    A.a[0][1] = 1 % MOD;
    A.a[1][0] = mul_mod(f_cur, f_cur);
    A.a[1][1] = f_prev;

    Vec init(1 % MOD, f_prev);

    Mat P = mat_pow(A, n - 1);

    auto mat_vec_mul = [](const Mat& m, const Vec& v) -> Vec {
        Vec res;
        for (int i = 0; i < 2; ++i) {
            res.v[i] = 0;
            for (int j = 0; j < 2; ++j)
                res.v[i] = (res.v[i] + mul_mod(m.a[i][j], v.v[j])) % MOD;
        }
        return res;
    };

    Vec result = mat_vec_mul(P, init);
    return result.v[0] % MOD;
}

signed main() {
    freopen("Whyharuhikage.in", "r", stdin);
    freopen("Whyharuhikage.out", "w", stdout);

    int T; fin >> T;
    while (T -- ) {
        int n, d, mod; fin >> n >> d >> mod;
        cout << solve(n, d, mod) << endl;
    }
    return 0;
}