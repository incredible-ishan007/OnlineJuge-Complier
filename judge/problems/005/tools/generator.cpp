#include <bits/stdc++.h>
using namespace std;

using ll = long long;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int main()
{
    const int TESTS = 15;
    const ll MAXK = 2000000000LL;

    for (int tc = 1; tc <= TESTS; tc++)
    {
        string filename = "problems/005/tests/test" + to_string(tc) + ".in";
        ofstream out(filename);

        int n = tc;
        ll k;

        vector<int> pool;

        for (int x = 1; x <= 25; x++)
            pool.push_back(x);

        shuffle(pool.begin(), pool.end(), rng);

        vector<int> coins;

        for (int i = 0; i < n; i++)
            coins.push_back(pool[i]);

        if (tc == 1)
        {
            k = 1;
        }
        else if (tc == 2)
        {
            k = 1;
        }
        else if (tc == 3)
        {
            k = 2;
        }
        else if (tc == 14)
        {
            k = MAXK;
        }
        else if (tc == 15)
        {
            k = MAXK;
        }
        else
        {
            k = 1 + (rng() % 1000000LL);
        }

        out << 1 << '\n';
        out << n << ' ' << k << '\n';

        for (int i = 0; i < n; i++)
        {
            if (i)
                out << ' ';

            out << coins[i];
        }

        out << '\n';

        out.close();
    }

    cout << "Generated " << TESTS << " test files." << '\n';

    return 0;
}