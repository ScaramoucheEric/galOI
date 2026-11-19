#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

signed main() {
    int n, m, c;
    cin >> n >> m >> c;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    sort(all(arr));
    
    vector<int> B(2 * n);
    for (int i = 0; i < n; i++) {
        B[i] = arr[i];
        B[i + n] = arr[i] + m;
    }
    
    vector<int> cnt(2 * n, 0);
    int k = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (i > 0 && B[i] == B[i-1]) {
            cnt[k-1]++;
        } else {
            B[k] = B[i];
            cnt[k] = 1;
            k++;
        }
    }
    int tot = k;
    
    int ans = 0;
    int Pcnt = 0;
    int l = 0;
    
    for (int r = 0; r < tot; r++) {
        Pcnt += cnt[r];
        
        while (Pcnt - cnt[l] >= c) {
            Pcnt -= cnt[l];
            l++;
        }
        
        if (Pcnt >= c) {
            
            int sidx = r;
            int re = c - (Pcnt - cnt[r]);
            if (re <= 0) {
                sidx = r;
            } else {
                sidx = r;
            }

            int Ps = cnt[sidx];
            int start = (l == 0) ? -1 : B[l-1];
            int end = B[l];
            int len = end - start;
            
            if (start < 0) {
                len = end + 1; 
            }
            
            ans += len * Ps;
        }
    }
    
    if (n == c) {
        ans = m * n;
    }
    
    cout << ans << endl;
    
    return 0;
}