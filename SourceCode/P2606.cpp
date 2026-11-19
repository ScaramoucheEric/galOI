#include<bits/stdc++.h>
using namespace std;
const int N = 2000010;
int n, m, inv[N], fact[N], invFact[N];
long long int ans = 1;

void precompute() {
    inv[1] = 1;
    for (int i = 2; i < N; i++) {
        inv[i] = (long long)inv[m % i] * (m - m / i) % m;
    }
    fact[0] = fact[1] = 1;
    invFact[0] = invFact[1] = 1;
    for (int i = 2; i < N; i++) {
        fact[i] = (long long)fact[i - 1] * i % m;
        invFact[i] = (long long)invFact[i - 1] * inv[i] % m;
    }
}

int C(int x, int y) {
    if (y < 0 || y > x) return 0;
    return (long long)fact[x] * invFact[y] % m * invFact[x - y] % m;
}

int ls(int x) {
    return x << 1;
}

int rs(int x) {
    return x << 1 | 1;
}

int w[N << 2];
stack<pair<int, bool> > st;  // {node, visited}

void iterative_dfs() {
    st.push({1, false});
    while (!st.empty()) {
        auto [x, visited] = st.top();
        st.pop();
        if (x > n) {
            w[x] = 0;
            continue;
        }
        if (visited) {
            w[x] = w[ls(x)] + w[rs(x)] + 1;
            ans = ans * C(w[x] - 1, w[ls(x)]) % m;
        } else {
            st.push({x, true});
            st.push({rs(x), false});
            st.push({ls(x), false});
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    if (m == 1) {
        printf("0\n");
        return 0;
    }
    precompute();
    iterative_dfs();
    printf("%lld\n", ans);
    return 0;
}