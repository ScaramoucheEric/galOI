#include <cstdio>
#include <cstring>
#include <algorithm>

const int Mod = 998244353;

const int N = 7000;

using namespace std;

namespace Sky
{
    long long Ans, n, P[N + 10];
    int f[N + 10][N + 10], tot;
    void Main()
    {
        tot = Ans = 0;
        memset(f, 0, sizeof(f));

        scanf("%lld", &n);
        
		for(int i = 1; 1ll * i * i <= n; i++)
        {
            if(n % i == 0)
            {
                P[ ++ tot] = i;
                if(n / i != i) P[ ++ tot] = n / i;
            }
        }
        sort(P + 1, P + 1 + tot);
        P[tot + 1] = n * 5;
        f[1][1] = 1;
        for (int i = 1; i <= tot; i++)
        {
            int l = i + 1;
            for (int j = 1; j < tot; j++)
            {
                if (f[i][j] == 0) continue;
                if (P[i] * P[j + 1] <= n)
                {
                    while (P[l + 1] <= P[i] * P[j + 1]) l++;
                    if (P[l] == P[i] * P[j + 1]) (f[l][j + 1] += f[i][j]) %= Mod;
                }
                (f[i][j + 1] += f[i][j]) %= Mod;
            }
        }
        printf("%d\n", f[tot][tot] - 1);
    }
}

using namespace Sky;

int main()
{
    int T; scanf("%d", &T);

    while(T -- ) 
		Main();
    
	return 0;
}

