#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main()
{
    for(int tc = 1; tc <= 60; tc++)
    {
        ofstream out("problems/017/tests/test" + to_string(tc) + ".in");

        int n;
        vector<int> a;

        // -------------------------
        // Tiny cases
        // -------------------------

        if(tc == 1)
        {
            n = 1;
            a = {0};
        }
        else if(tc == 2)
        {
            n = 1;
            a = {10000};
        }
        else if(tc == 3)
        {
            n = 5;
            a = {1, 2, 3, 4, 5};
        }
        else if(tc == 4)
        {
            n = 5;
            a = {5, 4, 3, 2, 1};
        }
        else if(tc == 5)
        {
            n = 5;
            a = {1, 3, 7, 2, 6};
        }
        else if(tc == 6)
        {
            n = 10;
            a = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
        }

        // -------------------------
        // Small random
        // -------------------------

        else if(tc <= 15)
        {
            n = 5 + rng() % 46;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = rng() % 101;
        }

        // -------------------------
        // Consecutive values
        // -------------------------

        else if(tc <= 20)
        {
            n = 100 + rng() % 101;

            int start = rng() % 100;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = start + i;
        }

        // -------------------------
        // Reverse consecutive
        // -------------------------

        else if(tc <= 25)
        {
            n = 100 + rng() % 101;

            int start = 1000;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = start - i;
        }

        // -------------------------
        // Duplicates
        // -------------------------

        else if(tc <= 30)
        {
            n = 500 + rng() % 501;

            a.resize(n);

            int x = rng() % 10001;

            for(int i = 0; i < n; i++)
                a[i] = x;
        }

        // -------------------------
        // Lots of merging
        // -------------------------

        else if(tc <= 36)
        {
            n = 1000 + rng() % 1001;

            a.resize(n);

            vector<int> values;

            int start = rng() % 100;

            for(int i = 0; i < 500; i++)
                values.push_back(start + i);

            for(int i = 0; i < n; i++)
                a[i] = values[rng() % values.size()];
        }

        // -------------------------
        // Random medium
        // -------------------------

        else if(tc <= 44)
        {
            n = 2000 + rng() % 3001;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = rng() % 10001;
        }

        // -------------------------
        // Sparse values
        // -------------------------

        else if(tc <= 48)
        {
            n = 5000 + rng() % 5001;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = rng() % 10001;

            // Spread values by making most values distinct-ish.
            for(int i = 0; i < n; i++)
            {
                if(i % 2 == 0)
                    a[i] = (i * 37) % 10001;
            }
        }

        // -------------------------
        // Large consecutive
        // -------------------------

        else if(tc == 49)
        {
            n = 10000;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = i % 10001;
        }

        // -------------------------
        // Large reverse
        // -------------------------

        else if(tc == 50)
        {
            n = 10000;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = 10000 - (i % 10001);
        }

        // -------------------------
        // Maximum random
        // -------------------------

        else if(tc <= 55)
        {
            n = 30000;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = rng() % 10001;
        }

        // -------------------------
        // Maximum all duplicates
        // -------------------------

        else if(tc == 56)
        {
            n = 30000;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = 5000;
        }

        // -------------------------
        // Maximum consecutive
        // -------------------------

        else if(tc == 57)
        {
            n = 30000;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = i % 10001;
        }

        // -------------------------
        // Maximum alternating
        // -------------------------

        else if(tc == 58)
        {
            n = 30000;

            a.resize(n);

            for(int i = 0; i < n; i++)
            {
                if(i % 2 == 0)
                    a[i] = 0;
                else
                    a[i] = 10000;
            }
        }

        // -------------------------
        // Maximum random small range
        // -------------------------

        else if(tc == 59)
        {
            n = 30000;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = rng() % 51;
        }

        // -------------------------
        // Maximum shuffled range
        // -------------------------

        else
        {
            n = 30000;

            a.resize(n);

            for(int i = 0; i < n; i++)
                a[i] = i % 10001;

            shuffle(a.begin(), a.end(), rng);
        }

        // -------------------------
        // Write test
        // -------------------------

        out << n << '\n';

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