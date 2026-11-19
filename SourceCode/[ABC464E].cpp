#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>

using namespace std;

struct SegTree {
    int n;
    vector<int> mx, lazy;
    SegTree(int n) : n(n), mx(4 * n + 5, 0), lazy(4 * n + 5, 0) {}

    void apply(int p, int v) {
        mx[p] = max(mx[p], v);
        lazy[p] = max(lazy[p], v);
    }

    void push(int p) {
        if (lazy[p]) {
            apply(p << 1, lazy[p]);
            apply(p << 1 | 1, lazy[p]);
            lazy[p] = 0;
        }
    }

    void update(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) {
            apply(p, v);
            return;
        }
        push(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
    }

    int query(int p, int l, int r, int pos) {
        if (l == r) return mx[p];
        push(p);
        int mid = (l + r) >> 1;
        if (pos <= mid) return query(p << 1, l, mid, pos);
        return query(p << 1 | 1, mid + 1, r, pos);
    }

    void update(int l, int r, int v) { update(1, 1, n, l, r, v); }
    int query(int pos) { return query(1, 1, n, pos); }
};

int main() {
    int H, W, Q;
    cin >> H >> W >> Q;

    vector<vector<pair<int, int>>> ops(H + 1);
    vector<char> ch(Q + 1);

    for (int i = 1; i <= Q; i++) {
        int R, C;
        char X;
        cin >> R >> C >> X;
        ops[R].push_back({C, i});
        ch[i] = X;
    }

    vector<string> ans(H + 1);
    SegTree seg(W);

    for (int row = H; row >= 1; row--) {
        for (auto &p : ops[row]) {
            int C = p.first, id = p.second;
            seg.update(1, C, id);
        }

        string line(W, 'A');
        for (int col = 1; col <= W; col++) {
            int id = seg.query(col);
            if (id) line[col - 1] = ch[id];
        }
        ans[row] = line;
    }

    for (int i = 1; i <= H; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
