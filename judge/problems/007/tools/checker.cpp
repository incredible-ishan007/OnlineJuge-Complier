#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll getArea(ll x, ll s, const vector<ll>& divs, const vector<ll>& pref)
{
    if(x == 0)
        return 0;

    int id = upper_bound(divs.begin(), divs.end(), x) - divs.begin() - 1;

    ll ans = pref[id];

    if(id + 1 < (int)divs.size())
        ans += (x - divs[id]) * (s / divs[id + 1]);

    return ans;
}

ll solveQuery(ll s, ll x, ll y,
              const vector<ll>& divs,
              const vector<ll>& pref)
{
    int id = lower_bound(divs.begin(), divs.end(), y) - divs.begin();

    ll yc = divs[id];
    ll xc = s / yc;

    if(x <= xc)
        return x * y;

    ll ans = xc * y;

    ans += getArea(x, s, divs, pref);
    ans -= getArea(xc, s, divs, pref);

    return ans;
}

int main(int argc, char* argv[])
{
    if(argc != 3)
        return 2;

    ifstream in(argv[1]);
    ifstream out(argv[2]);

    if(!in || !out)
        return 2;

    int t;
    in >> t;

    while(t--)
    {
        ll s;
        int q;

        in >> s >> q;

        vector<ll> divs;

        for(ll i = 1; i * i <= s; i++)
        {
            if(s % i == 0)
            {
                divs.push_back(i);

                if(i != s / i)
                    divs.push_back(s / i);
            }
        }

        sort(divs.begin(), divs.end());

        int n = divs.size();

        vector<ll> pref(n);

        for(int i = 0; i < n; i++)
        {
            ll prev = (i == 0 ? 0 : divs[i - 1]);

            pref[i] =
                (divs[i] - prev) * (s / divs[i]);

            if(i > 0)
                pref[i] += pref[i - 1];
        }

        for(int i = 0; i < q; i++)
        {
            ll x, y;
            in >> x >> y;

            ll expected =
                solveQuery(s, x, y, divs, pref);

            ll answer;

            if(!(out >> answer))
                return 1;

            if(answer != expected)
                return 1;
        }
    }

    string extra;

    if(out >> extra)
        return 1;

    return 0;
}