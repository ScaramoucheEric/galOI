/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC432C].cpp
    @ Time:         11/15/2025
    @ Email:        acwing@foxmail.com
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

inline int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

signed main() {
    int n, x, y;
    cin >> n >> x >> y;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    int d = y - x;
    int g = gcd(x, d);
    int k = d / g;
    
    int r = arr[0] % k;
    for (int i = 1; i < n; i++) {
        if (arr[i] % k != r) {
            cout << -1 << endl;
            return 0;
        }
    }
    
    int m = x / g;
    vector<int> q(n);
    for (int i = 0; i < n; i++) {
        q[i] = (arr[i] - r) / k;
    }
    
    int t_min = 0;
    int t_max = 1e18;
    
    for (int i = 0; i < n; i++) {
        t_min = max(t_min, m * q[i]);
        t_max = min(t_max, m * q[i] + arr[i]);
    }
    
    if (t_min > t_max) {
        cout << -1 << endl;
        return 0;
    }
    
    int sum = 0;
    for (int i : q)
        sum += i;
    int L_max = n * t_max - m * sum;
    
    cout << L_max << endl;
    
    return 0;
}