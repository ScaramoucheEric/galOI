#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
#include <map>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

using PII = pair<int,int> ;

const int Mod = 1e9 + 7;

signed main() {
    // freopen("automobil.in", "r", stdin);
    // freopen("automobil.out", "w", stdout);

    int n, m, q; cin >> n >> m >> q;

    map<int, int> R, C;

    while(q -- ) {
        char ch; cin >> ch;
        int a, b; cin >> a >> b;
        if (ch == 'R') {
            if (R.count(a)) {
                R[a] = R[a] * b % Mod;
            } else {
                R[a] = b;
            }
        } else {
            if (C.count(a)) {
                C[a] = C[a] * b % Mod;
            } else {
                C[a] = b;
            }
        }
    }
    
    vector<PII> RR(all(R)), SS(all(C));
    
    int cnt = n * m % Mod;
    int sum = (1 + cnt) * cnt / 2 % Mod;

    for (auto r : RR) {
        int rr = r.first;
        int mul = r.second;
        
        int start = (rr - 1) * m + 1;
        int end = rr * m;
        int row_sum = (start + end) * m / 2 % Mod;
        
        sum = (sum - row_sum + Mod) % Mod;
        sum = (sum + row_sum * mul % Mod) % Mod;
    }

    for (auto s : SS) {
        int c = s.first;
        int mul = s.second;
        
        int start = c;
        int end = c + (n - 1) * m;
        int col_sum = (start + end) * n / 2 % Mod;
        
        sum = (sum - col_sum + Mod) % Mod;
        sum = (sum + col_sum * mul % Mod) % Mod;
    }

    // for (int i= 1; i <= n; i ++ )
    //     cout << sum << endl;

    for (auto r : R) {
        for (auto s : SS) {
            int rr = r.first;
            int cc = s.first;
            int mulr = r.second;
            int mulc = s.second;
            
            int pos = (rr - 1) * m + cc;
            pos %= Mod;
            
            sum = (sum + pos - pos * mulr % Mod + Mod) % Mod;
            sum = (sum - pos * mulc % Mod + Mod) % Mod;
            sum = (sum + pos * mulr % Mod * mulc % Mod) % Mod;
        }
    }

    cout << sum << endl;

    return 0;
}