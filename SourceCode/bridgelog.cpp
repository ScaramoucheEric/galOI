#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <set>
#include <utility>
#include <cstdio>
#include <cctype>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read& operator >> (T & x) {
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
#define endl "\n"
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);

using namespace std; Read fin;

struct Bri {
    int s, b, e, root;
    set<pair<int, int> > used;

    int curV, curU;
    vector<pair<int, int> > G;

    Bri() : s(1), b(0), e(0), root(1), curV(2), curU(1) {}

    bool add() {
        if (e + 1 > s * (s - 1) / 2)
            return false;

        while (curV <= s) {
            if (curU >= curV) {
                curV ++ ;
                curU = 1;
                continue;
            }

            pair<int, int> p = {curU, curV};
            curU ++ ;

            if (used.find(p) == used.end()) {
                used.insert(p);
                G.push_back(p);
                e ++ ;
                return true;
            }
        }

        return false;
    }

    bool build(const vector<int>& k) {
        int m = k.size() - 1;

        for (int i = 1; i <= m; i ++ ) {
            int delta = k[i] - b;

            if (i == 1 and k[i] != 1)
                return false;
            if (k[i] < 0 or k[i] > i or delta > 1)
                return false;

            if (delta == 1) {
                int tail = (b == 0 ? root : s + b);
                int nxt = s + b + 1;
                G.push_back({tail, nxt});
                b ++ ;
            }
            else if (delta == 0) {
                if (!add())
                    return false;
            }
            else {
                int x = -delta;
                if (b < x)
                    return false;

                if (x == 1) {
                    if (s < 2)
                        return false;

                    int u = (root == 1 ? 2 : 1);
                    used.insert({min(root, s + 1), max(root, s + 1)});
                    used.insert({min(u, s + 1), max(u, s + 1)});
                    G.push_back({u, s + 1});

                    s += 1;
                    b -= 1;
                    e += 2;
                    root = s;
                }
                else {
                    used.insert({min(root, s + 1), max(root, s + 1)});
                    for (int j = 1; j < x; j ++ )
                        used.insert({s + j, s + j + 1});
                    used.insert({min(root, s + x), max(root, s + x)});

                    G.push_back({root, s + x});

                    s += x;
                    b -= x;
                    e += x + 1;
                    root = s;
                }

                if (e > s * (s - 1) / 2)
                    return false;
            }

            if (b != k[i])
                return false;
        }

        return true;
    }

    int Count() const {
        return s + b;
    }
};

void solve();

signed main() {
    #ifndef ONLINE_JUDGE
    IO("bridgelog")
    #endif

    int T = 1;
    fin >> T;

    while(T -- ) {
        solve();
    }
}

void solve() {
    int m; fin >> m;

    vector<int> k(m + 1);
    for (int i = 1; i <= m; i ++ )
        fin >> k[i];

    Bri sol;
    if (!sol.build(k)) {
        cout << -1 << endl;
        return;
    }

    cout << sol.Count() << endl;
    for (auto [u, v] : sol.G)
        cout << u << " " << v << endl;
}
