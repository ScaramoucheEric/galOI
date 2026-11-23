#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdio>

#define int long long
using namespace std; 
typedef pair<int, int> PII;
const int N = 2e5 + 5;
int p[N], s[N];
int ymhzhz(int x, int y){
    return x / y + bool(x % y);
}
int get(int x, int y){
    return 2 * ymhzhz(p[y] - p[x], (s[x] + s[y])) - x % 2;
}
int l[N], r[N], ans[N];
bool vis[N];

void work()
{
    memset(vis, 0, sizeof(vis));
    priority_queue<PII, vector<PII>, greater<PII> > q;
    int n; cin >> n;
    for(int i = 1; i <= n; i++) cin >> p[i];
    for(int i = 1; i <= n; i++) cin >> s[i];
    
    for(int i = 1; i <= n; i++) {
        l[i] = i - 1;
        r[i] = i + 1;
        ans[i] = 0;
    }
    r[n] = 0; 
    
    for(int i = 1; i < n; i++) {
        q.push({get(i, i + 1), i});
    }
    
    while(!q.empty()){
        PII t = q.top(); q.pop();
        int x = t.second;
        int y = r[x];
        
        if(vis[x] || vis[y] || y == 0) continue;
        
        int merge_time = get(x, y);
        ans[x] = ans[y] = merge_time;
        vis[x] = vis[y] = true;
        
        int left_neighbor = l[x];
        int right_neighbor = r[y];
        
        if(left_neighbor > 0) {
            r[left_neighbor] = right_neighbor;
        }
        if(right_neighbor > 0) {
            l[right_neighbor] = left_neighbor;
        }

        if(left_neighbor > 0 && right_neighbor > 0 && 
           !vis[left_neighbor] && !vis[right_neighbor]) {
            q.push({get(left_neighbor, right_neighbor), left_neighbor});
        }
    }
    
    for(int i = 1; i <= n; i++) cout << ans[i] << ' ';

    cout << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int T; cin >> T; 
    while(T--) work();

    return 0;
}