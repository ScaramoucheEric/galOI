#include <iostream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

int main() {
    int X, Q;
    cin >> X >> Q;
    
    priority_queue<int> low;
    priority_queue<int, vector<int>, greater<int>> high;
    
    low.push(X);
    
    vector<int> res;
    
    for (int i = 0; i < Q; i++) {
        int a, b;
        cin >> a >> b;
        
        if (a <= low.top()) {
            low.push(a);
        } else {
            high.push(a);
        }
        
        if (b <= low.top()) {
            low.push(b);
        } else {
            high.push(b);
        }
        
        while (low.size() > high.size() + 1) {
            high.push(low.top());
            low.pop();
        }
        
        while (high.size() > low.size()) {
            low.push(high.top());
            high.pop();
        }
        
        res.push_back(low.top());
    }
    
    for (int ans : res) {
        cout << ans << endl;
    }
    
    return 0;
}