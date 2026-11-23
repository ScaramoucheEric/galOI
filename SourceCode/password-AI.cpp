#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define int long long

const int MAXP = 100000;

struct Node {
    int l, r, s, sum;
    Node(int _l=0, int _r=0, int _s=0, int _sum=0) : l(_l), r(_r), s(_s), sum(_sum) {}
};

vector<Node> tree;
vector<int> root;

void insert(int &p, int pre, int l, int r, int price, int limit) {
    // 复制前一个节点
    tree.push_back(tree[pre]);
    p = (int)tree.size() - 1;
    tree[p].s += limit;
    tree[p].sum += price * limit;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (price <= mid) {
        int left_old = tree[pre].l; // 保存旧左子索引
        int left_new;
        insert(left_new, left_old, l, mid, price, limit);
        tree[p].l = left_new; // 更新当前节点的左子
    } else {
        int right_old = tree[pre].r;
        int right_new;
        insert(right_new, right_old, mid+1, r, price, limit);
        tree[p].r = right_new;
    }
}

int query(int p, int l, int r, int limit) {
    if (l == r) return l * limit;
    int mid = (l + r) >> 1;
    int leftChild = tree[p].l;
    int leftCnt = tree[leftChild].s;
    if (leftCnt >= limit)
        return query(leftChild, l, mid, limit);
    else
        return tree[leftChild].sum + query(tree[p].r, mid+1, r, limit - leftCnt);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    struct Material { int d, p, l; };
    vector<Material> arr(n+1);
    for (int i=1;i<=n;i++) cin >> arr[i].d >> arr[i].p >> arr[i].l;
    sort(arr.begin()+1, arr.end(), [](const Material&a,const Material&b){return a.d>b.d;});
    tree.push_back(Node());
    root.resize(n+1);
    for (int i=1;i<=n;i++) insert(root[i], root[i-1], 1, MAXP, arr[i].p, arr[i].l);
    while (m--) {
        int g, L;
        cin >> g >> L;
        int l=1, r=n, ans=-1;
        while (l<=r) {
            int mid=(l+r)>>1;
            if (tree[root[mid]].s >= L) {
                int cost = query(root[mid], 1, MAXP, L);
                if (cost <= g) { ans=mid; r=mid-1; }
                else l=mid+1;
            } else l=mid+1;
        }
        cout << (ans==-1 ? -1 : arr[ans].d) << '\n';
    }
    return 0;
}