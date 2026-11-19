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

const int INF = 0x3f3f3f3f3f3f3f3f;

void solve();

signed main() {
    #ifndef ONLINE_JUDGE
    IO("P17651")
    #endif

    int T = 1; fin >> T;

    while(T -- ) {
        solve();
    }
}

void solve() {
    int n, q; fin >> n >> q;

    vector<int> arr(n + 1);
    
    for (int i = 1; i <= n; i ++ ) fin >> arr[i], arr[i] *= 2;

    sort(1 + all(arr));

    while(q -- ) {
        int k, R; fin >> k >> R;

        vector<int> sure(R + 1);

        for (int i = 1; i <= R; i ++ ) fin >> sure[i], sure[i] *= 2;

        sort(1 + all(sure));

        int l = 0, r = 1e9, best = -1;

        while(l <= r) {
            int mid = l + r >> 1;

            int pos = 1;

            vector<bool> st(n + 1);

            for (int i = 1; i <= n and pos <= R; i ++ ) {
                while(pos <= R and arr[i] > sure[pos] + mid) 
                    pos ++ ;
                if (pos <= R and arr[i] >= sure[pos] - mid and arr[i] <= sure[pos] + mid)
                    st[i] = true;
            }

            struct Node {
                int l, r;

                bool operator < (const Node W) const {
                    if (r != W.r) return r < W.r;
                    return l < W.l;
                }
            }; vector<Node> a;

            for (int i = 1; i <= n; i ++ )
                if (!st[i])
                    a.push_back({arr[i] - mid, arr[i] + mid});
            
            sort(all(a));

            st.assign(a.size(), false);

            int cnt = 0;
            int last = -INF;
            for (int i = 0; i < a.size(); i++) {
                if (last < a[i].l) {
                    cnt ++ ;
                    last = a[i].r;
                }
            }

            if (cnt + R <= k) r = mid - 1, best = mid;
            else l = mid + 1;
        }

        if (~best) cout << best / 2 << (best & 1 ? ".5" : "") << " ";
        else cout << -1 << " ";
    }
    cout << endl;
}