
# [P16746 [GKS 2019 #H] Elevanagram 同余 + DP](https://www.luogu.com.cn/problem/P16746)

### 题面简述：

给出数字 $1\sim 9$ 的出现次数 $A_1,\dots,A_9$，问能否重新排列这些数字，使得到的数能被 $11$ 整除。

### 思路：

$11$ 的判定法则是“交替和模 $11$ 为 $0$”。设总位数为

$$S=\sum_{i=1}^9 A_i,$$

则正号位置有 $p=\lceil S/2\rceil$ 个，负号位置有 $q=\lfloor S/2\rfloor$ 个。

把数字分成两组：$P$ 放正号位，$Q$ 放负号位，要求 $|P|=p,\ |Q|=q$。设所有数字之和为

$$D=\sum_{i=1}^9 i\cdot A_i.$$

交替和为 $0$ 等价于

$$P_{\text{sum}}-Q_{\text{sum}}\equiv 0\pmod{11}
\iff 2P_{\text{sum}}\equiv D\pmod{11}
\iff P_{\text{sum}}\equiv 6D\pmod{11},$$

因为 $2$ 在模 $11$ 下的逆元是 $6$。记 $\text{target}=6D\bmod 11$。

于是问题变成：从第 $i$ 种数字中选 $b_i$ 个（$0\le b_i\le A_i$），使得

$$\sum b_i=p,\qquad \sum i\cdot b_i\equiv \text{target}\pmod{11}.$$

$A_i$ 可以到 $10^9$，不能直接背包。注意到我们只关心 $b_i\bmod 11$ 以及“还能塞多少个 $11$”。把

$$b_i=r_i+11t_i,\qquad r_i\in[0,10],\ t_i\ge 0.$$

其中 $r_i$ 就是 $b_i\bmod 11$。此时：

- 余数贡献只由 $r_i$ 决定：$\sum i\cdot b_i\equiv \sum i\cdot r_i\pmod{11}$；
- 个数贡献为 $\sum b_i=R+11T$，其中 $R=\sum r_i,\ T=\sum t_i$。

固定 $r_i$ 后，$t_i$ 的取值范围是

$$0\le t_i\le \left\lfloor\frac{A_i-r_i}{11}\right\rfloor,$$

前提是 $r_i\le A_i$。记 $cap_i=\left\lfloor (A_i-r_i)/11\right\rfloor$。由于每个 $t_i$ 可以独立取区间 $[0,cap_i]$ 内的任意整数，所以 $T$ 能取到 $[0,\sum cap_i]$ 内的所有整数。

于是做 DP：

- $dp[R][res]$：处理完若干种数字后，$\sum r_i=R$、$\sum i\cdot r_i\bmod 11=res$ 时，$\sum cap_i$ 的最大值；
- 转移时枚举当前数字 $i$ 的 $r_i\in[0,\min(10,A_i)]$：

$$dp'[R+r_i][(res+i\cdot r_i)\bmod 11]=\max\bigl(dp[R][res]+cap_i\bigr).$$

同一个 $(R,res)$ 下容量越大越好，所以只保留最大值即可。

最后枚举 $R$，若存在

$$R\le p,\qquad R\equiv p\pmod{11},\qquad dp[R][\text{target}]\ge \frac{p-R}{11},$$

就输出 `YES`，否则 `NO`。

$R$ 最大只有 $9\times 10=90$，$res$ 只有 $11$ 种，单组复杂度 $O(9\times 91\times 11\times 11)$，非常小。

正确性说明：任何一组合法的 $b_i$ 都能唯一写成 $r_i+11t_i$；反过来，只要 $t_i\le cap_i$，就能还原出不超过 $A_i$ 的 $b_i$。而 $T$ 的可行集合是一段连续的整数区间，所以只需要记录“最大容量”，就能判断某个 $T$ 是否可达。
