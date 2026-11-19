#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin>>n)) return 0;
    vector<int> seatGroup(n+1);
    int maxg=0;
    for(int i=1;i<=n;i++){cin>>seatGroup[i]; maxg=max(maxg,seatGroup[i]);}
    vector<int> persons(n+1);
    for(int i=1;i<=n;i++){cin>>persons[i]; maxg=max(maxg,persons[i]);}

    const int INF = 1e9;
    vector<int> L(maxg+1, INF), R(maxg+1, -INF);
    for(int i=1;i<=n;i++){
        int g=seatGroup[i];
        L[g]=min(L[g], i);
        R[g]=max(R[g], i);
    }

    vector<int> res(n+1, -1);
    vector<char> occ(n+1, 0);
    int occupied = 0;
    long long totalCost=0;

    for(int t=1;t<=n;t++){
        int g = persons[t];
        int bestPos=-1, bestCost=INF;
        for(int p=L[g]; p<=R[g]; p++){
            if(occ[p]) continue;
            int left=0;
            for(int i=1;i<p;i++) if(occ[i]) left++;
            int right = occupied - left;
            int cost = min(left, right);
            if(cost < bestCost){ bestCost = cost; bestPos = p; }
        }
        // assign
        occ[bestPos]=1;
        res[t]=bestPos;
        occupied++;
        totalCost += bestCost;
    }

    cout<<totalCost<<"\n";
    for(int i=1;i<=n;i++){
        if(i>1) cout<<" ";
        cout<<res[i];
    }
    cout<<"\n";
    return 0;
}
