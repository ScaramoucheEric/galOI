/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC441E].cpp
    @ Time:         01/17/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>

using namespace std;

struct Fen {
    int n;
    vector<int> bit;
    Fen(int n) : n(n), bit(n + 1, 0) {}
    void add(int idx, int delta) {
        idx ++ ; 
        while (idx <= n) {
            bit[idx] += delta;
            idx += idx & -idx;
        }
    }
    int sum(int idx) { 
        idx ++ ;
        int s = 0;
        while (idx > 0) {
            s += bit[idx];
            idx -= idx & -idx;
        }
        return s;
    }
    int query(int l, int r) { 
        if (l > r) return 0;
        return sum(r) - (l == 0 ? 0 : sum(l - 1));
    }
};

int main() {
    int n; string str;
    cin >> n >> str;

    vector<int> P(n + 1);
    P[0] = 0;
    for (int i = 0; i < n; i ++ ) {
        char c = str[i];
        int delta = 0;
        if (c == 'A') delta = 1;
        else if (c == 'B') delta = -1;
        
        P[i + 1] = P[i] + delta;
    }
    
    vector<int> vals = P;
    sort(vals.begin(), vals.end());

    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    function<int(int)> getrank = [&](int x) {
        return lower_bound(vals.begin(), vals.end(), x) - vals.begin();
    };
    int m = vals.size();
    
    Fen bit(m);
    long long ans = 0;

    
    bit.add(getrank(P[0]), 1);

    for (int i = 1; i <= n; i++) {
        int rp = getrank(P[i]);
        
        if (rp > 0) {
            ans += bit.sum(rp - 1);
        }
        
        bit.add(rp, 1);
    }

    cout << ans << endl;

    return 0;
}