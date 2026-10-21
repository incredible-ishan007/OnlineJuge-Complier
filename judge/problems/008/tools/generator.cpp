#include <bits/stdc++.h>
using namespace std;

using ll = long long;

mt19937_64 rng(
    chrono::steady_clock::now().time_since_epoch().count()
);

ll rnd(ll l, ll r)
{
    return l + rng() % (r - l + 1);
}

int main()
{
    const int TESTS = 60;

    for(int tc = 1; tc <= TESTS; tc++)
    {
        string file =
            "problems/008/tests/test" +
            to_string(tc) + ".in";

        ofstream out(file);

        if(!out)
        {
            cout << "Could not create " << file << '\n';
            return 1;
        }

        ll n;

        if(tc == 1)
            n = 1;
        else if(tc == 2)
            n = 9;
        else if(tc == 3)
            n = 10;
        else if(tc == 4)
            n = 11;
        else if(tc == 5)
            n = 99;
        else if(tc == 6)
            n = 100;
        else if(tc == 7)
            n = 999;
        else if(tc == 8)
            n = 1000;
        else if(tc == 9)
            n = 999999;
        else if(tc == 10)
            n = 1000000;
        else if(tc <= 20)
            n = rnd(1, 1000);
        else if(tc <= 35)
            n = rnd(1000, 100000);
        else if(tc <= 50)
            n = rnd(100000, 1000000);
        else
            n = rnd(1, 1000000);

        out << 1 << '\n';
        out << n << '\n';

        out.close();

        cout << "Generated test " << tc << '\n';
    }

    cout << "All 60 tests generated.\n";

    return 0;
}