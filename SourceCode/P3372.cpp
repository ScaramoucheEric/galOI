/*
    @ Author:       Eric / Sky__White
    @ Filename:     P3372.cpp
    @ Date:         30/06/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define int long long
#define lc (p << 1)
#define rc (p << 1 | 1)

const int N = 100010 << 2;

struct Node
{
    int l, r, sum, lazy;
}t[N];
int n, q;

int a[N];

void updata(int p)
{
    t[p].sum = t[lc].sum + t[rc].sum;
}
void downdata(int p)
{
    if (t[p].lazy == 0) return ;
    
    t[lc].lazy += t[p].lazy;
    t[rc].lazy += t[p].lazy;
    t[lc].sum += t[p].lazy * (t[lc].r - t[lc].l + 1);
    t[rc].sum += t[p].lazy * (t[rc].r - t[rc].l + 1);
    
    t[p].lazy = 0;
}

void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    
    if (l == r)
    {
        t[p].sum = a[l];
        return ;
    }
    
    int mid = l + r >> 1;
    
    build(lc, l, mid);
    build(rc, mid + 1, r);
    
    updata(p);
    
    return ;
}

void add(int p, int l, int r, int k)
{
    if (l <= t[p].l && r >= t[p].r)
    {
        t[p].sum += k * (t[p].r - t[p].l + 1);
        t[p].lazy += k;
        return ;
    }
    downdata(p);
    
    int mid = t[p].l + t[p].r >> 1;
    
    if (l <= mid) add(lc, l, r, k);
    if (r > mid) add(rc, l, r, k);
    
    updata(p);
}

int query(int p, int l, int r)
{
    if (l <= t[p].l && r >= t[p].r) return t[p].sum;
    
    downdata(p);
    
    int mid = t[p].l + t[p].r >> 1, res = 0;
    if (l <= mid) res += query(lc, l, r);
    if (r > mid) res += query(rc, l, r);

    return res;
}

signed main()
{
    cin >> n >> q;
    for (int i = 1; i <= n; i ++ )
        cin >> a[i];
        
    build(1, 1, n);
    
    while(q -- )
    {
        int op, x, y;
        cin >> op >> x >> y;
        
        if (op == 2)
            printf("%lld\n", query(1, x, y));
        else
        {
            int k;
            cin >> k;
            
            add(1, x, y, k);

            cout << query(1, 1, 2) << endl;
        }
    }
}