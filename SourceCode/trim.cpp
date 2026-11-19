#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstdio>
#include <queue>
#include <map>
#include <set>

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
    IO("trim")
    #endif

    ios::sync_with_stdio(false);
    cin.tie(0);

    int T = 1;

    while(T -- ) {
        solve();
    }
}

const int Mod = 1e9 + 7;
const int Base = 13331;

void solve() {
    int n, q; cin >> n >> q;

    vector<string> str(n + 1);
    int max_len = 0;

    vector<vector<int> > h(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        cin >> str[i];
        str[i] = " " + str[i];
        // cout << str[i].size() - 1 << endl;

        max_len = max((int)str[i].size() - 1, max_len);

        h[i].resize(str[i].size());        
    }

    vector<int> p(max_len + 1);

    p[0] = 1;
    for (int i = 1; i <= max_len; i ++ )
        p[i] = p[i - 1] * Base % Mod;

    for (int i = 1; i <= n; i ++ ) {
        for (int j = 1; j <= str[i].size() - 1; j ++ ) {
            h[i][j] = (h[i][j - 1] + (str[i][j] - 'a' + 1) * p[j] % Mod) % Mod;
        }
    }

    struct Query {
        int id, l, r, k;
        
        bool operator <(const Query W) const {
            return id < W.id;
        }
    }; vector<Query> que(q + 1);

    for (int i = 1; i <= q; i ++ )
        que[i].id = i, cin >> que[i].l >> que[i].r >> que[i].k;

    if (n <= 2000 and q <= 200) {
        for (int i = 1; i <= q; i ++ ) {
            int l = que[i].l, r = que[i].r, k = que[i].k;
            
            set<int> st;
            for (int i = l; i <= r; i ++ ) {
                st.insert(h[i][min((int)str[i].size(), max((int)str[i].size() - k - 1, 0ll))]);
            }

            cout << st.size() << endl;
        }
    } else if (n <= 50000 and q <= 200) {
        for (int i = 1; i <= q; i ++ ) {
            int l = que[i].l, r = que[i].r, k = que[i].k;
            
            set<int> st;
            for (int i = l; i <= r; i ++ ) {
                st.insert(h[i][min((int)str[i].size(), max((int)str[i].size() - k - 1, 0ll))]);
            }

            cout << st.size() << endl;
        }
    }
    // cout << max_len << endl;

    // vector<pair<int, int> > res;

    // function<pair<vector<vector<int> >, int>(int)> calc = [&](int era) -> pair<vector<vector<int> >, int> {
    //     map<int, vector<int> > st;
    //     for (int i = 1; i <= n; i ++ ) {
    //         st[h[i][min((int)str[i].size(), max((int)str[i].size() - era - 1, 0ll))]].push_back(i);
    //         // cout << era << "-" << max((int)str[i].size() - era - 1, 0ll) << " ";
    //     }
    //     // cout << endl;
    //     vector<vector<int> > temp;

    //     for (auto i : st)
    //         temp.push_back(i.second);

    //     return {temp, st.size()};
    // };

    // auto last = calc(0);
    // sort(all(last.first));
    
    // // cout << calc(0) << " " << calc(1) << " " << calc(2) << endl;

    // res.push_back({0, last.second});

    // int l = 0, r = max_len;

    // while(l <= r) {
    //     int mid = l + r >> 1;

    //     auto temp = calc(mid);
    //     // cout << l << " " << r << " " << mid << " " << temp << " " << last << endl;

    //     if (temp.second == last.second) l = mid + 1;
    //     else {
    //         r = mid - 1;
    //         if (calc(mid - 1).second == last.second) {
    //             r = max_len;
    //             l = mid + 1;
                
    //             sort(all(temp.first));



    //             res.push_back({mid, last.second});
    //         }
    //     }
    // }

    // for (auto i : res)
    //     cout << i.first << " " << i.second << endl;
    
}