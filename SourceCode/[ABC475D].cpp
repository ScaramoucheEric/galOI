#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

const int MAX_VAL = 10000000;
vector<bool> is_prime(MAX_VAL + 1, true);

void sieve() {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= (int)sqrt(MAX_VAL); ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAX_VAL; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

bool is_isomorphic(const string& s, const string& t) {
    if (s.length() != t.length()) return false;
    char map_st[256] = {0};
    char map_ts[256] = {0};
    for (size_t i = 0; i < s.length(); ++i) {
        char cs = s[i];
        char ct = t[i];
        if (map_st[cs] == 0) {
            map_st[cs] = ct;
        } else if (map_st[cs] != ct) {
            return false;
        }
        if (map_ts[ct] == 0) {
            map_ts[ct] = cs;
        } else if (map_ts[ct] != cs) {
            return false;
        }
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string S;
    if (!(cin >> S)) return 0;
    
    sieve();

    map<string, int> st;
    
    int n = S.length();

    st["00000"] = 0;

    long long low = (n == 1) ? 2 : 1;
    if (n > 1) {
        low = 1;
        cout << low << endl;
        for (int i = 0; i < n - 1; i += 1) low *= 10;
    }
    long long high = 1;
    for (int i = 0; i < n; i ++ ) high *= 10;

    // high -= 1;
    
    for (long long num = low; num <= high; ++num) {
        if (!is_prime[num]) continue;
        string T = to_string(num);
        if ((int)T.length() != n) continue;
        if (is_isomorphic(S, T)) {
            cout << num << "\n";
            return 0;
        }
    }
    
    cout << "-1\n";
    return 0;
}