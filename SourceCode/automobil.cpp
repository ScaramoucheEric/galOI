#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

using PII = pair<int,int> ;

const int Mod = 1e9 + 7;

signed main() {
    // freopen("automobil.in", "r", stdin);
    // freopen("automobil.out", "w", stdout);

    int n, m, q; cin >> n >> m >> q;

    vector<PII> R, S;

    while(q -- ) {
        char ch; cin >> ch;
        int a, b; cin >> a >> b;
        if (ch == 'R')
            R.push_back({a, b});
        else
        S.push_back({a, b});
    }
    
    sort(all(R));
    
    if (R.size() > 1)
    for (int i = 0; i < R.size() - 1; i ++ ) {
        if (R[i].first == R[i + 1].first) {
            (R[i].second *= R[i + 1].second) %= Mod;
            R.erase(R.begin() + i + 1);
        }
    }
    if (S.size() > 1)
    for (int i = 0; i < S.size() - 1; i ++ ) {
        if (S[i].first == S[i + 1].first) {
            (S[i].second *= S[i + 1].second) %= Mod;
            S.erase(S.begin() + i + 1);
        }
    }

    int cnt = n * m % Mod;

    int sum = (1 + cnt) * cnt / 2 % Mod;

    // cout << sum << endl;

    for (auto r : R) {
        int t = r.first * m % Mod;
        (sum += ((t - m + 1 + t) * m / 2 % Mod) * (r.second - 1) % Mod) %= Mod;
    }
        // cout << "sum " << sum << endl;
    for (auto s : S) {
        int t = s.first * n % Mod;
        (sum += ((s.first + cnt - m + s.first) * n / 2 % Mod) * (s.second - 1) % Mod) %= Mod;
        cout << s.first + cnt - m << endl;
        cout << s.first << " " << cnt << " " << m << endl;
        cout << "sum " << sum << endl;
    }

    // cout << sum << endl;

    for (auto r : R) {
        for (auto s : S) {
            int num = (r.first - 1) * m + s.first % Mod;
            sum = ((sum + Mod) - (num * (s.second - 1) + num * (r.second - 1) + num) % Mod) % Mod;
            (sum += num * s.second * r.second) %= Mod;
            // cout << sum << " " << s.first << " " << s.second << " " << r.first << " " << r.second << " " << num << endl;
        }
    }

    cout << sum << endl;

    return 0;
}