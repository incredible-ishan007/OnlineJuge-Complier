#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

string randomString(int n)
{
    string s(n, 'a');

    for(int i = 0; i < n; i++)
        s[i] = char('a' + rng() % 26);

    return s;
}

string sameChar(int n)
{
    char c = char('a' + rng() % 26);
    return string(n, c);
}

string periodicString(int n, int p)
{
    string pattern = randomString(p);
    string s;

    s.reserve(n);

    for(int i = 0; i < n; i++)
        s += pattern[i % p];

    return s;
}

string prefixSuffix(int n)
{
    if(n == 1)
        return "a";

    int len = 1 + rng() % (n - 1);

    string s = randomString(n);

    // Force prefix of length len
    // to be equal to suffix of length len.
    // Works even when prefix and suffix overlap.
    for(int i = 0; i < len; i++)
        s[n - len + i] = s[i];

    return s;
}

string nestedBorder(int n)
{
    string s(n, 'a');

    for(int i = 0; i < n; i++)
    {
        if(i % 7 == 0)
            s[i] = 'b';
        else if(i % 11 == 0)
            s[i] = 'c';
    }

    return s;
}

int main()
{
    for(int tc = 1; tc <= 60; tc++)
    {
        ofstream out("problems/014/tests/test" + to_string(tc) + ".in");

        int n;
        string s;

        // -------------------------
        // Tiny fixed cases
        // -------------------------

        if(tc == 1)
        {
            n = 1;
            s = "a";
        }
        else if(tc == 2)
        {
            n = 2;
            s = "aa";
        }
        else if(tc == 3)
        {
            n = 2;
            s = "ab";
        }
        else if(tc == 4)
        {
            n = 5;
            s = "level";
        }
        else if(tc == 5)
        {
            n = 6;
            s = "ababab";
        }
        else if(tc == 6)
        {
            n = 5;
            s = "abcde";
        }

        // -------------------------
        // Small random
        // -------------------------

        else if(tc <= 12)
        {
            n = 3 + rng() % 18;
            s = randomString(n);
        }

        // -------------------------
        // Same character
        // -------------------------

        else if(tc <= 18)
        {
            n = 10 + rng() % 91;
            s = sameChar(n);
        }

        // -------------------------
        // Periodic strings
        // -------------------------

        else if(tc <= 26)
        {
            n = 20 + rng() % 181;

            int p = 1 + rng() % min(n, 8);

            s = periodicString(n, p);
        }

        // -------------------------
        // Strings with a known border
        // -------------------------

        else if(tc <= 34)
        {
            n = 20 + rng() % 181;

            s = prefixSuffix(n);
        }

        // -------------------------
        // Complicated border patterns
        // -------------------------

        else if(tc <= 40)
        {
            n = 100 + rng() % 901;

            s = nestedBorder(n);
        }

        // -------------------------
        // Medium random
        // -------------------------

        else if(tc <= 47)
        {
            n = 500 + rng() % 1501;

            s = randomString(n);
        }

        // -------------------------
        // Large periodic
        // -------------------------

        else if(tc <= 52)
        {
            n = 10000 + rng() % 10001;

            int p;

            if(tc == 48)
                p = 1;
            else if(tc == 49)
                p = 2;
            else if(tc == 50)
                p = 3;
            else
                p = 5 + rng() % 16;

            s = periodicString(n, p);
        }

        // -------------------------
        // Large random
        // -------------------------

        else if(tc <= 56)
        {
            n = 50000 + rng() % 50001;

            s = randomString(n);
        }

        // -------------------------
        // Maximum constraints
        // -------------------------

        else
        {
            n = 100000;

            if(tc == 57)
            {
                // aaaaaaaa...
                s = sameChar(n);
            }
            else if(tc == 58)
            {
                // abababab...
                s = periodicString(n, 2);
            }
            else if(tc == 59)
            {
                // Period 7
                s = periodicString(n, 7);
            }
            else
            {
                // Large random
                s = randomString(n);
            }
        }

        // -------------------------
        // Write test
        // -------------------------

        out << n << '\n';
        out << s << '\n';
    }

    return 0;
}