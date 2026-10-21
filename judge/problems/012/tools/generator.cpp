#include <bits/stdc++.h>
using namespace std;

int main()
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    for(int tc = 1; tc <= 60; tc++)
    {
        string file = "tests/test" + to_string(tc) + ".in";
        ofstream out(file);

        int n, m;

        if(tc == 1)
        {
            n = 0;
            m = 0;
        }
        else if(tc == 2)
        {
            n = 0;
            m = 1;
        }
        else if(tc == 3)
        {
            n = 1;
            m = 0;
        }
        else if(tc == 4)
        {
            n = 1;
            m = 1;
        }
        else if(tc <= 10)
        {
            n = 1 + rng() % 5;
            m = 1 + rng() % 5;
        }
        else if(tc <= 30)
        {
            n = 5 + rng() % 16;
            m = 5 + rng() % 16;
        }
        else
        {
            n = 20 + rng() % 31;
            m = 20 + rng() % 31;
        }

        out << n << ' ' << m << '\n';

        vector<int> a(n), b(m);

        for(int i = 0; i < n; i++)
            a[i] = (int)(rng() % 201) - 100;

        for(int i = 0; i < m; i++)
            b[i] = (int)(rng() % 201) - 100;

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        if(tc == 5)
        {
            fill(a.begin(), a.end(), 5);
            fill(b.begin(), b.end(), 5);
        }

        if(tc == 6)
        {
            fill(a.begin(), a.end(), -100);
            fill(b.begin(), b.end(), 100);
        }

        if(tc == 7)
        {
            fill(a.begin(), a.end(), -100);
            fill(b.begin(), b.end(), -100);
        }

        if(tc == 8)
        {
            fill(a.begin(), a.end(), 100);
            fill(b.begin(), b.end(), 100);
        }

        for(int x : a)
            out << x << ' ';

        out << '\n';

        for(int x : b)
            out << x << ' ';

        out << '\n';

        out.close();
    }

    return 0;
}