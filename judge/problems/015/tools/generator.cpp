#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int randomValue()
{
    return (int)(rng() % 20001) - 10000;
}

int main()
{
    for(int tc = 1; tc <= 60; tc++)
    {
        ofstream out("problems/015/tests/test" + to_string(tc) + ".in");

        int n, k;
        vector<int> a;

        // -------------------------
        // Tiny fixed cases
        // -------------------------

        if(tc == 1)
        {
            n = 1;
            k = 1;
            a = {5};
        }
        else if(tc == 2)
        {
            n = 2;
            k = 1;
            a = {1, 2};
        }
        else if(tc == 3)
        {
            n = 2;
            k = 2;
            a = {1, 2};
        }
        else if(tc == 4)
        {
            n = 5;
            k = 3;
            a = {1, 3, -1, -3, 5};
        }
        else if(tc == 5)
        {
            n = 8;
            k = 3;
            a = {1, 3, -1, -3, 5, 3, 6, 7};
        }
        else if(tc == 6)
        {
            n = 5;
            k = 1;
            a = {5, 4, 3, 2, 1};
        }

        // -------------------------
        // Small random
        // -------------------------

        else if(tc <= 12)
        {
            n = 3 + rng() % 18;
            k = 1 + rng() % n;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = randomValue();
        }

        // -------------------------
        // Increasing arrays
        // -------------------------

        else if(tc <= 18)
        {
            n = 20 + rng() % 81;
            k = 1 + rng() % n;

            a.resize(n);

            int start = -5000;

            for(int i = 0; i < n; i++)
                a[i] = start + i;
        }

        // -------------------------
        // Decreasing arrays
        // -------------------------

        else if(tc <= 24)
        {
            n = 20 + rng() % 81;
            k = 1 + rng() % n;

            a.resize(n);

            int start = 5000;

            for(int i = 0; i < n; i++)
                a[i] = start - i;
        }

        // -------------------------
        // All equal
        // -------------------------

        else if(tc <= 29)
        {
            n = 50 + rng() % 151;
            k = 1 + rng() % n;

            a.resize(n);

            int x = randomValue();

            for(int i = 0; i < n; i++)
                a[i] = x;
        }

        // -------------------------
        // Alternating high / low
        // -------------------------

        else if(tc <= 35)
        {
            n = 100 + rng() % 401;
            k = 1 + rng() % n;

            a.resize(n);

            for(int i = 0; i < n; i++)
            {
                if(i % 2 == 0)
                    a[i] = 10000;
                else
                    a[i] = -10000;
            }
        }

        // -------------------------
        // Random medium
        // -------------------------

        else if(tc <= 43)
        {
            n = 500 + rng() % 1501;
            k = 1 + rng() % n;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = randomValue();
        }

        // -------------------------
        // Large random
        // -------------------------

        else if(tc <= 50)
        {
            n = 10000 + rng() % 10001;
            k = 1 + rng() % n;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = randomValue();
        }

        // -------------------------
        // Large with k = 1
        // -------------------------

        else if(tc == 51)
        {
            n = 100000;
            k = 1;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = randomValue();
        }

        // -------------------------
        // Large with k = n
        // -------------------------

        else if(tc == 52)
        {
            n = 100000;
            k = n;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = randomValue();
        }

        // -------------------------
        // Large increasing
        // -------------------------

        else if(tc == 53)
        {
            n = 100000;
            k = 50000;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = -10000 + (i % 20001);
        }

        // -------------------------
        // Large decreasing
        // -------------------------

        else if(tc == 54)
        {
            n = 100000;
            k = 50000;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = 10000 - (i % 20001);
        }

        // -------------------------
        // Large alternating
        // -------------------------

        else if(tc == 55)
        {
            n = 100000;
            k = 49999;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = (i % 2 == 0 ? 10000 : -10000);
        }

        // -------------------------
        // Large all equal
        // -------------------------

        else if(tc == 56)
        {
            n = 100000;
            k = 50000;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = 7777;
        }

        // -------------------------
        // Maximum random
        // -------------------------

        else
        {
            n = 100000;

            if(tc == 57)
                k = 2;
            else if(tc == 58)
                k = 100;
            else if(tc == 59)
                k = 99999;
            else
                k = 50000;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = randomValue();
        }

        // -------------------------
        // Write test
        // -------------------------

        out << n << ' ' << k << '\n';

        for(int i = 0; i < n; i++)
        {
            out << a[i];

            if(i + 1 < n)
                out << ' ';
        }

        out << '\n';
    }

    return 0;
}