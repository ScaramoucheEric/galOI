#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstdio>
#include <queue>

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
#define endl "\n"
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);

using namespace std; Read fin;

signed main() {
    #ifndef ONLINE_JUDGE
    IO("P17648")
    #endif

    int n, m, k; fin >> n >> m >> k;

    vector<vector<int> > b(m + 1, vector<int>(n + 1));
    vector<int> a(n + 1);

    for (int i = 1; i <= n; i ++ )
        fin >> a[i];

    for (int i = 1; i <= m; i ++ )
        for (int j = 1; j <= n; j ++ ) {
            fin >> b[i][j];
        }

    vector<vector<bool> > st(k + 1, vector<bool>(m + 1, true));

    int p = true;

    while(k -- ) {
        int op; fin >> op;

        if (op == 1) {
            int x, y; fin >> x >> y;
            a[x] += y;
        } else {
            int j; string s; fin >> j; cin >> s;

			for(int t = 1; t <= m; t ++ ) {
				if(!st[j][t]) {
					continue;
				}
				bool flag = true;
				for(int i = 1; i <= n; i ++ ) {
					if(a[i] < b[t][i]) {
						flag = false;
						break;
					}
				}

				if(s == "win") {
					if(!flag) {
						st[j][t] = false;
					}
				} else {
					if(flag) {
						st[j][t] = false;
					}
				}
			}

			bool ok = false;

			for(int t = 1; t <= m; t ++ ) {
				if(st[j][t]) {
					ok = true;
					break;
				}
			}

			if(!ok) {
				p = false;
			}
		}
	}

	if(p) {
        puts("Yes");
	} else {
        puts("No");
	}
	return 0;
}