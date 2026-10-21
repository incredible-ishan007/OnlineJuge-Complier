#include <bits/stdc++.h>
using namespace std;

int main()
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    for(int tc = 1; tc <= 60; tc++)
    {
        string file = "tests/test" + to_string(tc) + ".in";
        ofstream out(file);

        int n;

        if(tc <= 5)
        {
            n = 2 + rng() % 4;
        }
        else if(tc <= 15)
        {
            n = 5 + rng() % 20;
        }
        else if(tc <= 30)
        {
            n = 20 + rng() % 100;
        }
        else if(tc <= 45)
        {
            n = 100 + rng() % 1000;
        }
        else
        {
            n = 100000;
        }

        out << n << '\n';

        for(int i = 0; i < n; i++)
        {
            int x;

            if(tc == 1)
            {
                x = 0;
            }
            else if(tc == 2)
            {
                x = 10000;
            }
            else if(tc == 3)
            {
                x = -10000;
            }
            else if(tc == 4)
            {
                x = (i % 2 == 0 ? 10000 : -10000);
            }
            else if(tc == 5)
            {
                x = (i % 2 == 0 ? 1 : -1);
            }
            else
            {
                x = (int)(rng() % 20001) - 10000;
            }

            out << x;

            if(i + 1 < n)
                out << ' ';
        }

        out << '\n';

        out.close();
    }

    return 0;
}