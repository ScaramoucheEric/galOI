#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cstdio>
#include <queue>

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

const int Mod = 1e9 + 7;

void solve() {
    int n, m; fin >> n >> m;

    struct Node {
        int a, b;

        bool operator <(const Node & W) const {
            if (a == W.a) return b < W.b;
            return a < W.a;
        }
    }; vector<Node> arr(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> arr[i].a >> arr[i].b;
    }

    vector<Node> ti(m + 1);

    for (int i = 1; i <= m; i ++ ) {
        fin >> ti[i].a >> ti[i].b;
    }

    priority_queue<int> q;

    sort(1 + all(arr));
    sort(1 + all(ti));

    int opt = 1, sum = 0;
    for (int i = 1; i <= n; i ++ ) {
        while(opt <= m and ti[opt].a <= arr[i].a) {
            q.push(ti[opt].b);
            opt ++ ;
        }

        if (q.size() and q.top() <= arr[i].a - arr[i].b or q.empty()) {
            sum += arr[i].b;
        } else {
            sum += arr[i].a - q.top(); q.pop();
            q.push(arr[i].a - arr[i].b);
        }
    }

    cout << sum << endl;

    return ;
}

signed main() {
    // int T; fin >> T;

    // while(T -- ) {
        solve();
    // }
}