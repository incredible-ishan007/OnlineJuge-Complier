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

string randomSmallString(int n)
{
    string s(n, 'a');

    for(int i = 0; i < n; i++)
        s[i] = char('a' + rng() % 3);

    return s;
}

int main()
{
    for(int tc = 1; tc <= 60; tc++)
    {
        ofstream out(
            "problems/020/tests/test" +
            to_string(tc) + ".in"
        );

        string s;

        // -------------------------
        // Tiny cases
        // -------------------------

        if(tc == 1)
        {
            s = "a";
        }
        else if(tc == 2)
        {
            s = "ab";
        }
        else if(tc == 3)
        {
            s = "aa";
        }
        else if(tc == 4)
        {
            s = "aba";
        }
        else if(tc == 5)
        {
            s = "abc";
        }
        else if(tc == 6)
        {
            s = "aaaa";
        }

        // -------------------------
        // Basic examples
        // -------------------------

        else if(tc == 7)
        {
            s = "level";
        }
        else if(tc == 8)
        {
            s = "ababab";
        }
        else if(tc == 9)
        {
            s = "abcab";
        }
        else if(tc == 10)
        {
            s = "aabaaab";
        }

        // -------------------------
        // All same character
        // -------------------------

        else if(tc <= 15)
        {
            int n = 5 + rng() % 46;

            s = string(n, 'a');
        }

        // -------------------------
        // Alternating characters
        // -------------------------

        else if(tc <= 20)
        {
            int n = 10 + rng() % 91;

            s.resize(n);

            for(int i = 0; i < n; i++)
                s[i] = (i % 2 ? 'b' : 'a');
        }

        // -------------------------
        // Periodic strings
        // -------------------------

        else if(tc <= 26)
        {
            int n = 50 + rng() % 151;

            int period = 2 + rng() % 6;

            string pattern;

            for(int i = 0; i < period; i++)
                pattern += char('a' + rng() % 4);

            s.resize(n);

            for(int i = 0; i < n; i++)
                s[i] = pattern[i % period];
        }

        // -------------------------
        // Small alphabet random
        // -------------------------

        else if(tc <= 32)
        {
            int n = 100 + rng() % 401;

            s = randomSmallString(n);
        }

        // -------------------------
        // Random medium
        // -------------------------

        else if(tc <= 40)
        {
            int n = 500 + rng() % 1501;

            s = randomString(n);
        }

        // -------------------------
        // Long prefix + different end
        // -------------------------

        else if(tc == 41)
        {
            int n = 10000;

            s = string(n, 'a');

            s[n - 1] = 'b';
        }

        // -------------------------
        // Long prefix/suffix match
        // -------------------------

        else if(tc == 42)
        {
            int n = 10000;

            s = string(n, 'a');

            s[n - 1] = 'b';

            // Long border of 'a'.
            // Expected answer has length n - 2.
        }

        // -------------------------
        // Large alternating
        // -------------------------

        else if(tc == 43)
        {
            int n = 100000;

            s.resize(n);

            for(int i = 0; i < n; i++)
                s[i] = (i % 2 ? 'b' : 'a');
        }

        // -------------------------
        // Large all same
        // -------------------------

        else if(tc == 44)
        {
            int n = 100000;

            s = string(n, 'a');
        }

        // -------------------------
        // Large periodic
        // -------------------------

        else if(tc == 45)
        {
            int n = 100000;

            string pattern = "abc";

            s.resize(n);

            for(int i = 0; i < n; i++)
                s[i] = pattern[i % 3];
        }

        // -------------------------
        // Large periodic
        // -------------------------

        else if(tc == 46)
        {
            int n = 100000;

            string pattern = "aabb";

            s.resize(n);

            for(int i = 0; i < n; i++)
                s[i] = pattern[i % 4];
        }

        // -------------------------
        // Large small-alphabet random
        // -------------------------

        else if(tc == 47)
        {
            s = randomSmallString(100000);
        }

        // -------------------------
        // Large random
        // -------------------------

        else if(tc <= 52)
        {
            s = randomString(100000);
        }

        // -------------------------
        // Constructed long border
        // -------------------------

        else if(tc == 53)
        {
            string prefix;

            for(int i = 0; i < 49999; i++)
                prefix += char('a' + rng() % 3);

            s = prefix + "z" + prefix;
        }

        // -------------------------
        // Long border with nested borders
        // -------------------------

        else if(tc == 54)
        {
            string pattern = "abababab";

            s.resize(100000);

            for(int i = 0; i < 100000; i++)
                s[i] = pattern[i % pattern.size()];

            // Break the longest possible border.
            s[99999] = 'c';
        }

        // -------------------------
        // Large almost-periodic
        // -------------------------

        else if(tc == 55)
        {
            s.resize(100000);

            for(int i = 0; i < 100000; i++)
                s[i] = char('a' + (i % 5));

            // Small disturbance near the end.
            s[99999] = 'z';
        }

        // -------------------------
        // Large repeated blocks
        // -------------------------

        else if(tc == 56)
        {
            string block = "abcabc";

            s.resize(100000);

            for(int i = 0; i < 100000; i++)
                s[i] = block[i % block.size()];
        }

        // -------------------------
        // Long prefix but no huge
        // border
        // -------------------------

        else if(tc == 57)
        {
            s.resize(100000);

            for(int i = 0; i < 99999; i++)
                s[i] = 'a';

            s[99999] = 'b';
        }

        // -------------------------
        // Random with long common
        // prefix/suffix
        // -------------------------

        else if(tc == 58)
        {
            string border = randomSmallString(40000);

            string middle = randomSmallString(20000);

            s = border + middle + border;

            // Length = 100000
        }

        // -------------------------
        // Maximum random
        // -------------------------

        else if(tc == 59)
        {
            s = randomString(100000);
        }

        // -------------------------
        // Maximum random small range
        // -------------------------

        else
        {
            s = randomSmallString(100000);
        }

        // -------------------------
        // Write test
        // -------------------------

        out << s << '\n';
    }

    return 0;
}