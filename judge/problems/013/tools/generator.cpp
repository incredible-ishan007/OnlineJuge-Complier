#include <bits/stdc++.h>
using namespace std;

int main()
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    for(int tc = 1; tc <= 60; tc++)
    {
        ofstream out("tests/test" + to_string(tc) + ".in");

        int n;

        if(tc == 1)
            n = 1;
        else if(tc == 2)
            n = 2;
        else if(tc == 3)
            n = 5;
        else if(tc == 4)
            n = 10;
        else if(tc <= 10)
            n = 1 + rng() % 20;
        else if(tc <= 30)
            n = 20 + rng() % 181;
        else if(tc <= 50)
            n = 500 + rng() % 1501;
        else
            n = 200000;

        out << n << '\n';

        for(int i = 0; i < n; i++)
        {
            long long x;

            if(tc == 1)
                x = 0;
            else if(tc == 2)
                x = 1;
            else if(tc == 3)
                x = 0;
            else if(tc == 4)
                x = 1000000000LL;
            else if(tc == 5)
                x = 1;
            else if(tc == 6)
                x = i;
            else if(tc == 7)
                x = n - i;
            else if(tc == 8)
                x = (i % 2 == 0 ? 0 : 1000000000LL);
            else if(tc == 9)
                x = 1;
            else
                x = rng() % 1000000001LL;

            out << x;

            if(i + 1 < n)
                out << ' ';
        }

        out << '\n';
    }

    return 0;
}