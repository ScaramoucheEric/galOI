#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

const int mod = 1e9 + 7;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m; cin >> n >> m;

    string str; cin >> str; str = ' ' + str;

    vector<vector<vector<int> > > dp(n + 1, vector<vector<int> >(n + 1, vector<int>(5)));

    int f[505][505],d[505][505];

    function<bool(int,int)> check = [&](int l, int r) -> bool {
        if(d[l][r]!=-1) return d[l][r];
        if(r-l+1>m) return false;
        if(l>r) return d[l][r]=1;
        if((str[l]=='*'||str[l]=='?')&&(str[r]=='*'||str[r]=='?')){
            return d[l][r]=check(l+1,r-1);
        }
        else{
            return d[l][r]=false;
        }
    };

    function<int(int,int,int)> dfs = [&](int l, int r, int t) -> int {
        if(l >= r) {
            return 0;
        }
        if(dp[l][r][t] != -1) return dp[l][r][t];
        int ans = 0;
        if(t == 0) {
            bool ok = (str[l] == '(' or str[l] == '?') and (str[r] == ')' or str[r] == '?');
            if(ok) {
                if(check(l + 1, r - 1)) {
                    ans ++ ;
                }
                ans = (ans % mod + dfs(l + 1, r - 1, 0) % mod) % mod;
                ans = (ans % mod + dfs(l + 1, r - 1, 1) % mod) % mod;
                ans = (ans % mod + dfs(l + 1, r - 1, 2) % mod) % mod;
            }
            else {
                return dp[l][r][t] = 0;
            }
            for(int i = l; i < r; i ++ ) {
                ans = (ans % mod + 1ll * dfs(l, i, 3) % mod * dfs(i + 1, r, 0) % mod) % mod;
                ans = (ans % mod + 1ll * dfs(l, i, 3) % mod * dfs(i + 1, r, 1) % mod) % mod;
            }
        }
        else if(t == 1) {
            for(int i = l; i < r; i ++ ) {
                if(check(l,i)) {
                    ans = (ans % mod + dfs(i + 1, r, 0)) % mod;
                }
                else {
                    break;
                }
            }
        }
        else if(t == 2){
            for(int i = r; i > l; i -- ){
                if(check(i, r)){
                    ans = (ans % mod + dfs(l,i - 1, 0)) % mod;
                }
                else{
                    break;
                }
            }
        } 
        else if(t == 3){
            bool ok = (str[l] == '(' or str[l] == '?') and (str[r] == ')' or str[r] == '?');
            if(ok){
                if(check(l + 1, r - 1)){
                    ans ++ ;
                }
            
                ans=(ans % mod + dfs(l + 1, r - 1, 0) % mod) % mod;
                ans=(ans % mod + dfs(l + 1, r - 1, 1) % mod) % mod;
                ans=(ans % mod + dfs(l + 1, r - 1, 2) % mod) % mod;
                
            }
            else{
                return dp[l][r][t] = 0;
            }
        }
        return dp[l][r][t] = ans;
    };

    cout << dfs(1, n, 0) << endl;
}