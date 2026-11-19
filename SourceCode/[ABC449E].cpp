/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC449E].cpp
    @ Time:         03/14/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>

using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    cin >> N >> M;
    
    vector<int> A(N);
    vector<ll> count(M + 1, 0);
    
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        count[A[i]]++;
    }
    
    ll max_freq = 0;
    for (int v = 1; v <= M; v++) {
        max_freq = max(max_freq, count[v]);
    }
    
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    for (int v = 1; v <= M; v++) {
        pq.push({count[v], v});
    }
    
    vector<int> extended_A = A;
    vector<int> cycle;
    
    ll total_steps = max_freq * M;
    
    for (ll step = 0; step < total_steps + M; step++) {
        auto [cnt, val] = pq.top();
        pq.pop();
        
        extended_A.push_back(val);
        
        pq.push({cnt + 1, val});
        
        if (step >= total_steps) {
            cycle.push_back(val);
        }
    }
    
    int Q; cin >> Q;
    
    ll prefix_length = N + total_steps;
    
    while (Q--) {
        ll X;
        cin >> X;

        X--;
        
        if (X < N) {
            cout << A[X] << "\n";
        } else if (X < prefix_length) {
            cout << extended_A[X - N] << "\n";
        } else {
            ll remaining = X - prefix_length;
            cout << cycle[remaining % M] << "\n";
        }
    }
    
    return 0;
}