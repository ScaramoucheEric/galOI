#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 10005;

int main() {
    int n;
    cin >> n;
    
    vector<int> tim(n + 1);          
    vector<int> ind(n + 1, 0);   
    vector<int> el(n + 1, 0);   
    vector<vector<int>> G(n + 1); 
    
    for (int i = 0; i < n; i++) {
        int id, opt, pre;
        cin >> id >> opt;
        tim[id] = opt;
        
        while (cin >> pre && pre != 0) {
            G[pre].push_back(id); 
            ind[id]++;
        }
    }
    
    queue<int> q;
    
    for (int i = 1; i <= n; i++) {
        if (ind[i] == 0) {
            q.push(i);
            el[i] = tim[i];
        }
    }
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
    for (int v : G[u]) {
            
            el[v] = max(el[v], el[u] + tim[v]);
            
            ind[v]--;
            if (ind[v] == 0) {
                q.push(v);
            }
        }
        for (int i = 1; i <= n; i ++ ) {
            cout << q.size() << endl;
        }
    }
    
    int result = 0;
    for (int i = 1; i <= n; i++) {
        result = max(result, el[i]);
    }
    
    cout << result << endl;
    
    return 0;
}