#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>

using namespace std;

// #define int long long
#define all(a) a.begin(), a.end()

class Tree {
    public:
        vector<int> arr;
        void init(int n) {
            arr.resize(n + 1, 0);
        }
        inline int lowbit(int x) {
            return x & -x;
        }
        int sum(int x) {
            int t = 0;
            for (int i = x; i; i -= lowbit(i)) {
                t += arr[i];
            }
            return t;
        }
        int query(int l, int r) {
            return sum(r) - sum(l - 1);
        }
        void add(int x) {
            for (int i = x; i < arr.size(); i += lowbit(i))
                arr[i] += 1;
        }
} T;

struct Node {
    int pos, id, type;

    bool operator < (const Node W) const {
        if (pos != W.pos)
            return pos < W.pos;
        return type < W.type;
    }
};

signed main() {
    int n, m; cin >> n >> m;

    int max__ = 0;

    map<int, vector<Node> > arr;

    for (int i = 1; i <= n; i ++ ) {
        int x, y; cin >> x >> y;
        x ++ , y ++ ;
        x ++ , y ++ ;

        arr[x].push_back({y, i, 1});
        max__ = max(max__, y + 5);
    }

    vector<array<int, 5> > que(m + 1);

    for (int i = 1; i <= m; i ++ ) {
        for (int j = 1; j <= 4; j ++ )
            cin >> que[i][j], que[i][j] += 2;
        int &x = que[i][1], &y = que[i][2], &ex = que[i][3], &ey = que[i][4];
        arr[x - 1].push_back({y - 1, i, 2});
        arr[x - 1].push_back({ey, i, 2});
        arr[ex].push_back({y - 1, i, 2});
        arr[ex].push_back({ey, i, 2});
        max__ = max(max__, y + 5);
        max__ = max(max__, ey + 5);
    }

    cout << max__ << endl;

    T.init(max__);

    map<pair<int,int> , int> presum;

    for (auto &[x, Y] : arr) {
        sort(all(Y));

        cout << Y.size() << endl;

        for (auto &[y, id, type] : Y) {
            if (type == 1)
                T.add(y);
            else
                presum[{x, y}] = T.sum(y);
        }
    }
    
    puts("ERROR");
    // return 0;

    for (int i = 1; i <= m; i ++ ) {
        int &x = que[i][1], &y = que[i][2], &ex = que[i][3], &ey = que[i][4];
        cout << presum[{ex, ey}] - presum[{ex, y - 1}] - presum[{x - 1, ey}] + presum[{x - 1, y - 1}] << endl;
    }

    return 0;
}