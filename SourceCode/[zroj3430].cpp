/*
    @ Author:       Eric / Sky__White
    @ Filename:     [zroj3430].cpp
    @ Time:         11/19/2025
    @ Email:        acwing@foxmail.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
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
    } fin;
}

#define int long long
#define all(a) a.begin(), a.end()

using namespace std;

const int INF = 0x3f3f3f3f3f3f3f3f;

struct Per {
    int l, r;
};

struct Score {
    int x, y;
};

vector<Per> per;

struct L {
    int id;

    bool operator < (const L & l) const {
        return per[id].l < per[l.id].l;
    }
};
struct R {
    int id;

    bool operator < (const R & r) const {
        return per[id].r < per[r.id].r;
    }
};

signed main() {
    int n, m; fin >> n >> m;

    per.resize(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> per[i].l >> per[i].r;
    }

    vector<Score> sc(m + 1);

    for (int i = 1; i <= m; i ++ ) {
        fin >> sc[i].x >> sc[i].y;
    }

    sort(1 + all(sc), [&](Score a, Score b) {
        return a.x < b.x;
    });

    for (int i = 1; i < m; i ++ ) {
        sc[i + 1].y = min(sc[i].y, sc[i + 1].y);
    }
    
    //        n - 7 69
    // 7 70       3 79
    // 4 80       2 89
    // 2 90       1 99
    // 1 100      1 INF
    // 0

    for (int i = 1; i < m; i ++ ) {
        sc[i].y -= sc[i + 1].y;
    }

    // for (int i = 1; i <= m; i ++ ) {
    //     cout << sc[i].x << " " << sc[i].y << "\n";
    // }
    // cout << endl;

    vector<int> score;
    score.clear();

    for (int i = 1; i < sc.size() - 1; i ++ ) {
        for (int j = 1; j <= sc[i].y; j ++ )
            score.push_back(sc[i + 1].x - 1);
    }

    for (int i = 1; i <= sc.back().y; i ++ ) {
        score.push_back(INF);
    }
    
    // int opt = 0;

    // cout << endl;
    // for (auto i : score) cout << i << " ";
    // cout << endl;

    while(score.size() < n)
        score.push_back(sc[1].x - 1);
    
    // cout << opt << endl;
    
    sort(all(score), greater<int>());

    if (score.size() > n) {
        score.resize(n);
    }

    // for (int i = 0; i < n; i ++ ) {
    //     cout << score[i] << " ";
    // }
    // cout << endl;

    sort(all(score));

    vector<int> a0, a1;
    for (int i = 0; i < n; i ++ ) {
        a0.push_back(i + 1);
        a1.push_back(i + 1);
    }

    sort(all(a0), [&](int a, int b) { return per[a].l < per[b].l; });
    sort(all(a1), [&](int a, int b) { return per[a].r < per[b].r; });

    queue<int> A0, A1;

    for (auto i : a0) A0.push(i);
    for (auto i : a1) A1.push(i);

    priority_queue<L> q0;
    priority_queue<R> q1;

    int pos = 0;

    while(pos < n) {
        while(score[pos] > per[A1.front()].r) {
            q1.push({A1.front()});
            A1.pop();
        }
        while(score[pos] > per[A0.front()].l) {
            q0.push({A0.front()});
            A0.pop();
        }
    }

    vector<bool> st(n + 1, false);

    int res = 0;

    while(q1.size()) {
        int u = q1.top().id; q1.pop();
        
        if (st[u]) continue;
        
        cout << u << endl;
        st[u] = true;
        res += 1;
    }
    while(q0.size()) {
        int u = q0.top().id; q0.pop();
        
        if (st[u]) continue;

        cout << u << endl;
        st[u] = true;
        res += 0;
    }

    for (int i = 1; i <= n; i ++ )
        if (!st[i]) res += -1;

    cout << res << endl;

    return 0;
}