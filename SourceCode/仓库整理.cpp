/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC420G].cpp
    @ Date:         27/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>

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

const int MAXN = 800005; 

int bit[MAXN];
int bitN;

inline void add(int i, int v) {
    for (; i <= bitN; i += i & (-i))
        bit[i] += v;
}

inline int query(int i) {
    int s = 0;
    for (; i > 0; i -= i & (-i))
        s += bit[i];
    return s;
}

struct Seg {
    int pos;    
    int len;    
    int val;   
};

Seg segs[MAXN];
int cnt = 0;

signed main() {
    freopen("Warehouse.in", "r", stdin);
    freopen("Warehouse.out", "w", stdout);
    
    int k; fin >> k;
    
    if (k == 0) {
        printf("0\n");
        return 0;
    }
    
    vector<int> xs;
    vector<pair<int, int>> ops(k);
    
    for (int i = 0; i < k; i ++ ) {
        int x, y;
        fin >> x >> y;
        ops[i] = {x, y};
        xs.push_back(x);
        xs.push_back(y);
        if (x > 1) xs.push_back(x - 1);
        if (y > 1) xs.push_back(y - 1);
    }
    
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    
    int m = xs.size();
    
    vector<int> Seg(m, 0);
    int prev = 0;
    
    for (int i = 0; i < m; i ++ ) {
        int cur = xs[i];
        if (cur > prev + 1) {
            
            int idx = (int)(lower_bound(xs.begin(), xs.end(), cur - 1) - xs.begin());
            Seg[idx] += cur - prev - 1;
        }
        Seg[i] += 1; 
        prev = cur;
    }

    map<int, int> pos;
    for (int i = 0; i < k; i ++ ) {
        int x = ops[i].first, y = ops[i].second;
        int vx = pos.count(x) ? pos[x] : x;
        int vy = pos.count(y) ? pos[y] : y;
        pos[x] = vy;
        pos[y] = vx;
    }

    cnt = 0;
    for (int i = 0; i < m; i ++ ) {
        if (Seg[i] == 0) continue;
        int p = xs[i];
        int v = pos.count(p) ? pos[p] : p; 
        
        int rank = (int)(lower_bound(xs.begin(), xs.end(), v) - xs.begin()) + 1;
        
        segs[cnt ++ ] = {p, Seg[i], rank};
    }
    
    bitN = m; 
    
    int ans = 0;
    for (int i = 0; i < cnt; i ++ ) {
        int v = segs[i].val;
        int w = segs[i].len;
        
        int totalInserted = query(bitN);
        int lessEqual = query(v);
        ans += (totalInserted - lessEqual) * w;
        add(v, w);
    }
    
    printf("%lld\n", ans);
    return 0;
}