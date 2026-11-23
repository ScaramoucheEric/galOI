#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

const int MAXN = 500005;
const int MAXV = 500005;

class Node {
    private:
        vector<int> tree;
        int n;
        
    public:
        Node(int size) : n(size + 2), tree(size + 5, 0) {}
        
        inline int lowbit(int x) {
            return x & -x;
        }

        inline void add(int x) {
            for (int i = x; i <= n; i += lowbit(i))
                tree[i] += 1;
        }
        
        void update(int idx, int delta) {
            idx++;
            while (idx <= n) {
                tree[idx] += delta;
                idx += idx & -idx;
            }
        }
        
        int query(int idx) {
            idx++;
            int sum = 0;
            while (idx > 0) {
                sum += tree[idx];
                idx -= idx & -idx;
            }
            return sum;
        }
        
        int range_sum(int l, int r) {
            if (l > r) return 0;
            return query(r) - query(l - 1);
        }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, qq;
    cin >> n >> qq;
    
    vector<int> arr(n + 1);
    Node count_tree(MAXV), sum_tree(MAXV);
    
    for (int i = 1; i <= n; i ++) {
        cin >> arr[i];
        count_tree.update(arr[i], 1);
        sum_tree.update(arr[i], arr[i]);
    }
    
    while (qq --) {
        int type; cin >> type;
        
        if (type == 1) {
            int x, y;
            cin >> x >> y;
            
            count_tree.update(arr[x], -1);
            sum_tree.update(arr[x], -arr[x]);
            
            arr[x] = y;
            count_tree.update(arr[x], 1);
            sum_tree.update(arr[x], arr[x]);
        } else {
            int l, r; cin >> l >> r;
            
            int cnt_less = count_tree.query(l - 1);
            int part1 = cnt_less * l;
            
            
            int part2 = sum_tree.range_sum(l, r);
            
            
            int cnt_greater = count_tree.range_sum(r + 1, MAXV);
            int part3 = cnt_greater * r;
            
            cout << part1 + part2 + part3 << endl;
        }
    }
    
    return 0;
}