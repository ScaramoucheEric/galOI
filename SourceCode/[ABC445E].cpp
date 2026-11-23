// /*
//     @ Author:       Eric / Sky__White
//     @ Filename:     [ABC445E].cpp
//     @ Time:         02/14/2026
//     @ Email:        acwing@foxmail.com / 17802535158@163.com
// */

// #include <cstring>
// #include <iostream>
// #include <algorithm>
// #include <functional>
// #include <cstdio>
// #include <unordered_map>

// namespace std {
//     class Read {
//         public:
//         template<typename T>
//         inline Read operator >> (T & x) {
//             T sum = 0, opt = 1;
//             char ch = getchar();
//             while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
//             while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
//             x = sum * opt; return *this;
//         }
//     };
// }

// #define int long long
// #define all(a) a.begin(), a.end()

// using namespace std; Read fin;

// const int Mod = 998244353;

// unordered_map<int, int> res1, res2;

// struct Node {
//     vector<int> p;
//     unordered_map<int, int> st;

//     void init(int x) {
//         for (int i = 2; i <= x; i ++ ) {
//             if (x % i == 0) p.push_back(i);
//             while(x % i == 0) x /= i, st[i] ++ ;
//             if (st[i] > res1[i]) res2[i] = res1[i], res1[i] = st[i];
//             else if (st[i] > res2[i]) res2[i] = st[i];
//         }
//     }
// };

// int qpow(int a, int b) {
//     if (b == 0) return 1;
//     if (b == 1) return a;

//     int res = 1;
//     while(b) {
//         if (b & 1) (res *= a) %= Mod;
//         (a *= a) %= Mod;
//         b >>= 1;
//     }

//     return res;
// }

// void solve() {
//     int n; fin >> n;
//     res1.clear();
//     res2.clear();

//     vector<int> arr(n + 1);

//     for (int i = 1; i <= n; i ++ )
//         fin >> arr[i];

//     vector<Node> num(n + 1);
//     for (int i = 1; i <= n; i ++ ) {
//         num[i].init(arr[i]);
//     }

//     int ans = 1;
//     for (auto [p, a] : res1)
//         ans = qpow(p, a) * ans % Mod;
//     for (int i = 1; i <= n; i ++ ) {
//         int dl = 1;
//         for (auto [p, a] : num[i].st) {
//             if (res1[p] == a) dl = dl * qpow(p, a - res2[p]) % Mod;
//         }
//         // cout << dl << ":";
//         // cout << res1[5] << " " << res2[5] << ":";

//         int aans = ans;
//         (aans *= qpow(dl, Mod - 2)) %= Mod;

//         cout << aans << " ";
//     }
//     cout << endl;
//     // cout << ans << endl;
// }

// signed main() {
//     int T; fin >> T;

//     while(T -- ) {
//         solve();
//     }
// }

#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <map>

using namespace std;

const int MOD = 998244353;
const int MAX_A = 10000000;

vector<int> spf; // smallest prime factor

void sieve() {
    spf.resize(MAX_A + 1);
    for (int i = 2; i <= MAX_A; i++) {
        spf[i] = i;
    }
    for (int i = 2; i * i <= MAX_A; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j <= MAX_A; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
}

vector<pair<int, int>> facinit(int x) {
    vector<pair<int, int>> facs;
    while (x > 1) {
        int p = spf[x];
        int exp = 0;
        while (x % p == 0) {
            x /= p;
            exp++;
        }
        facs.emplace_back(p, exp);
    }
    return facs;
}

long long modpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    
    vector<vector<pair<int, int>>> facs(N);
    for (int i = 0; i < N; i++) {
        facs[i] = facinit(A[i]);
    }
    
    map<int, vector<int>> exp_count;
    for (int i = 0; i < N; i++) {
        for (auto [p, exp] : facs[i]) {
            exp_count[p].push_back(exp);
        }
    }
    
    long long full_lcm = 1;
    map<int, int> max_exp;
    map<int, int> second_max_exp;
    
    for (auto& [p, exps] : exp_count) {
        while (exps.size() < N) {
            exps.push_back(0);
        }
        sort(exps.rbegin(), exps.rend());
        max_exp[p] = exps[0];
        second_max_exp[p] = exps[1];
        full_lcm = full_lcm * modpow(p, exps[0]) % MOD;
    }
    
    for (int i = 0; i < N; i++) {
        long long ans = full_lcm;
        for (auto [p, exp] : facs[i]) {
            if (exp == max_exp[p]) {
                int cnt_max = 0;
                for (int j = 0; j < N; j++) {
                    bool has_max = false;
                    for (auto [pj, expj] : facs[j]) {
                        if (pj == p && expj == max_exp[p]) {
                            has_max = true;
                            break;
                        }
                    }
                    if (has_max) cnt_max++;
                }
                
                if (cnt_max == 1) {
                    int diff = max_exp[p] - second_max_exp[p];
                    ans = ans * modpow(modpow(p, diff), MOD - 2) % MOD;
                }
            }
        }
        cout << ans << (i == N - 1 ? "\n" : " ");
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    sieve();
    
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    
    return 0;
}