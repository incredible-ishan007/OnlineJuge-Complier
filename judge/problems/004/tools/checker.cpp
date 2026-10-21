#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

long long power(long long a, long long b)
{
    long long ans = 1;

    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;

        a = a * a % MOD;
        b /= 2;
    }

    return ans;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
        return 2;

    ifstream in(argv[1]);
    ifstream out(argv[2]);

    if (!in || !out)
        return 2;

    int T;
    in >> T;

    while (T--)
    {
        int N;
        in >> N;

        vector<long long> A(N);

        for (int i = 0; i < N; i++)
            in >> A[i];

        vector<vector<long long>> dp(
            N + 1,
            vector<long long>(N + 1)
        );

        dp[0][0] = 1;

        for (long long x : A)
        {
            for (int sz = N - 1; sz >= 0; sz--)
            {
                for (int sum = 0; sum + x <= N; sum++)
                {
                    dp[sz + 1][sum + x] += dp[sz][sum];

                    if (dp[sz + 1][sum + x] >= MOD)
                        dp[sz + 1][sum + x] -= MOD;
                }
            }
        }

        long long ans = 0;

        for (int k = 1; k < N; k++)
        {
            long long cnt = dp[k][k];

            long long ways = power(k, N - k - 1);
            ways = ways * power(N - k, k - 1) % MOD;

            ans = (ans + cnt * ways) % MOD;
        }

        ans = ans * power(2, MOD - 2) % MOD;

        long long expected;

        if (!(out >> expected))
            return 1;

        if (expected != ans)
            return 1;
    }

    string extra;

    if (out >> extra)
        return 1;

    return 0;
}