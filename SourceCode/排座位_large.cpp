#include <bits/stdc++.h>
using namespace std;

struct BIT{
    int n;
    vector<int> t;
    BIT(int n=0):n(n),t(n+1,0){}
    void add(int i,int v){ for(;i<=n;i+=i&-i) t[i]+=v; }
    int sum(int i){ int s=0; for(;i>0;i-=i&-i) s+=t[i]; return s; }
};

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

    vector<int> L(maxg+1, INT_MAX), R(maxg+1, INT_MIN);
    for(int i=1;i<=n;i++){
        int g=seatGroup[i];
        L[g]=min(L[g], i);
        R[g]=max(R[g], i);
    }

    vector<int> lp(maxg+1), rp(maxg+1);
    for(int g=1; g<=(int)maxg; g++){
        if(L[g]==INT_MAX){ lp[g]=1; rp[g]=0; }
        else { lp[g]=L[g]; rp[g]=R[g]; }
    }

    BIT bit(n);
    vector<int> res(n+1, -1);
    long long totalCost=0;
    int occupied=0;

    for(int t=1;t<=n;t++){
        int g = persons[t];
        int a = lp[g], b = rp[g];
        int chosen=-1;
        int costA = INT_MAX, costB = INT_MAX;
        if(a<=b){
            int leftA = bit.sum(a-1);
            costA = min(leftA, occupied - leftA);
            int leftB = bit.sum(b-1);
            costB = min(leftB, occupied - leftB);
            if(costA <= costB) chosen = a; else chosen = b;
        }
        else{
            // should not happen if input consistent, but just in case
            chosen = a; // invalid but will be skipped
        }
        // assign
        res[t]=chosen;
        bit.add(chosen, 1);
        occupied++;
        totalCost += min(bit.sum(chosen-1), occupied - 1 - bit.sum(chosen-1));
        // update pointers
        if(chosen==lp[g]) lp[g]++;
        else if(chosen==rp[g]) rp[g]--;
    }

    cout<<totalCost<<"\n";
    for(int i=1;i<=n;i++){
        if(i>1) cout<<" ";
        cout<<res[i];
    }
    cout<<"\n";
    return 0;
}
