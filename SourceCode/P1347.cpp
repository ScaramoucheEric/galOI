#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
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

using namespace std; Read fin;

#define int long long
#define all(a) a.begin(), a.end()

signed main() {
    int n, m; fin >> n >> m;

    vector<vector<int> > G(n + 1);
    vector<int> ind(n + 1, 0), temp;
    vector<int> res;

    for (int i = 1; i <= m; i ++ ) {
        char a, b, op;
        cin >> a >> op >> b;
        // printf("%c,%c\n", a, b);

        ind[b - 'A' + 1] ++ ;
        G[a - 'A' + 1].push_back(b - 'A' + 1);

        temp = ind;
        int t = [&]() -> int {
            queue<int> q;
            int cnt = 0;

            bool flag = false;

            res.clear();

            for (int i = 1; i <= n; i ++ )
                if (ind[i] == 0) {
                    cnt ++ ;
                    q.push(i);
                }
            if (cnt > 1) flag = true;

            while(q.size()) {
                auto u = q.front(); q.pop();
                cnt = 0;
                if (q.size() > 1) flag = true;
                res.push_back(u);

                for (auto v : G[u]) {
                    ind[v] -- ;
                    if (ind[v] == 0)
                        q.push(v), cnt ++ ;
                }
                if (cnt > 1)
                    flag = true;
            };
            if (res.size() < n)
                return -1ll;
            else if (flag)
                return 0ll;
            return 1ll;

        }();

        if (t == 1) {
            printf("Sorted sequence determined after %lld relations: ", i);
            for (int j : res)
                printf("%c", j + 'A' - 1);
            puts(".");
            return 0;
        } else if (t == -1) {
            printf("Inconsistency found after %lld relations.\n", i);
            return 0;
        }
        ind = temp;
    }

    puts("Sorted sequence cannot be determined.");
}