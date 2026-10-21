#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll LIMIT = 4000000000000000000LL;

ll lcmLimit(ll a, ll b)
{
    ll g = __gcd(a, b);

    if (a > LIMIT / (b / g))
        return LIMIT + 1;

    return a / g * b;
}

ll countWays(ll x, const vector<ll>& coins)
{
    int n = coins.size();

    ll cnt = 0;

    for (int mask = 1; mask < (1 << n); mask++)
    {
        ll L = 1;
        int bits = 0;
        bool ok = true;

        for (int i = 0; i < n; i++)
        {
            if (mask & (1 << i))
            {
                bits++;

                L = lcmLimit(L, coins[i]);

                if (L > x)
                {
                    ok = false;
                    break;
                }
            }
        }

        if (!ok)
            continue;

        ll add = x / L;

        if (bits & 1)
            cnt += add;
        else
            cnt -= add;
    }

    return cnt;
}

ll solve(const vector<ll>& coins, ll k)
{
    ll lo = 1;
    ll hi = LIMIT;

    while (lo < hi)
    {
        ll mid = lo + (hi - lo) / 2;

        if (countWays(mid, coins) >= k)
            hi = mid;
        else
            lo = mid + 1;
    }

    return lo;
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
        ll K;

        in >> N >> K;

        vector<ll> coins(N);

        for (int i = 0; i < N; i++)
            in >> coins[i];

        ll expected = solve(coins, K);

        ll answer;

        if (!(out >> answer))
            return 1;

        if (answer != expected)
            return 1;
    }

    string extra;

    if (out >> extra)
        return 1;

    return 0;
}