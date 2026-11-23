/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC450D].cpp
    @ Date:         03/21/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

#define int int
#define all(a) a.begin(), a.end()

int main() {
    int N, K;
    cin >> N >> K;
    
    vector<int> A(N);
    for (int i = 0; i < N; i ++ ) {
        cin >> A[i];
    }
    
    set<int> mods;
    for (int i = 0; i < N; i ++ ) {
        mods.insert(A[i] % K);
    }

    if (mods.size() == 1) {
        cout << 0 << endl;
        return 0;
    }
    
    vector<int> r(mods.begin(), mods.end());
    int M = r.size();
    
    vector<int> r2 = r;
    for (int i = 0; i < M; i ++ ) {
        r2.push_back(r[i] + K);
    }
    
    int ans = K;
    int count = 0;
    vector<int> fq(M, 0);
    int j = 0;
    for (int i = 0; i < M; i ++ ) {
        while (j < r2.size() && count < M) {
            int idx = (r2[j] % K + K) % K;
            int pos = lower_bound(all(r), idx) - r.begin();
            if (pos < M && r[pos] == idx) {
                if (fq[pos] == 0) count ++ ;
                fq[pos] ++ ;
            }
            j ++ ;
        }

        if (count == M) {
            ans = min(ans, r2[j-1] - r2[i]);
        }
        int idx_i = (r2[i] % K + K) % K;
        int pos_i = lower_bound(r.begin(), r.end(), idx_i) - r.begin();
        if (pos_i < M && r[pos_i] == idx_i) {
            fq[pos_i] -- ;
            if (fq[pos_i] == 0) count -- ;
        }
    }
    
    cout << ans << endl;
    
    return 0;
}