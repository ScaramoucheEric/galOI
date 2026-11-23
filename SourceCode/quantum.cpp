/*
    @ Author:       Eric / Sky__White
    @ Filename:     quantum.cpp
    @ Date:         21/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <vector>
#include <set>
#include <queue>
#include <ctime>

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
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

struct Node {
    int cnt, sum;
    Node(int c = -1, int s = -1) : cnt(c), sum(s) {}
};

int n, m, K, p;
vector<int> N, M, KK;
vector<vector<vector<vector<Node> > > > dp;

const int MAX = 60;

vector<int> bin(int x) {
    vector<int> res(MAX + 1, 0);
    for (int i = MAX; i >= 0; i -- ) {
        if (x >= (1LL << i)) {
            res[MAX - i] = 1;
            x -= (1LL << i);
        }
    }
    return res;
}

Node dfs(int pos, int opi, int opj, int opx) {
    if (pos == (int)N.size()) {
        return Node(1, 0);
    }

    Node &now = dp[pos][opi][opj][opx];
    if (now.cnt != -1) return now;

    Node res(0, 0);

    int upi = opi ? N[pos] : 1;
    int upj = opj ? M[pos] : 1;
    int kbit = KK[pos];

    int w = (1LL << (MAX - pos)) % p;

    for (int a = 0; a <= upi; a ++ ) {
        for (int b = 0; b <= upj; b ++ ) {
            int x = a ^ b;

            int nopi = opi && (a == upi);
            int nopj = opj && (b == upj);

            int nlx;
            if (!opx) {
                nlx = 0;
            } else {
                if (x < kbit) continue;
                nlx = (x == kbit);
            }

            Node tt = dfs(pos + 1, nopi, nopj, nlx);

            res.cnt = (res.cnt + tt.cnt) % p;

            int t = 0;
            if (x == 1)
                t = w * tt.cnt % p;

            res.sum = (res.sum + tt.sum + t) % p;
        }
    }

    return now = res;
}

signed main() {
    // freopen("quantum.in", "r", stdin);
    // freopen("quantum.out", "w", stdout);

    int T; fin >> T;

    while (T -- ) {
        fin >> n >> m >> K >> p;

        N = bin(n - 1);
        M = bin(m - 1);
        KK = bin(K);

        dp.assign(MAX + 1, vector<vector<vector<Node> > >(2, vector<vector<Node> >(2, vector<Node>(2))));

        Node res = dfs(0, 1, 1, 1);

        int ans = (res.sum - (K % p) * res.cnt % p + p) % p;
        cout << ans << '\n';
    }

    return 0;
}