#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


// ------------------------------------------------------------
// Generate random lowercase string
// ------------------------------------------------------------

string randomString(int n, int alphabet = 26)
{
    string s;

    for(int i = 0; i < n; i++)
        s += char('a' + rng() % alphabet);

    return s;
}


// ------------------------------------------------------------
// Generate a string s which definitely has a palindromic
// permutation.
//
// We first construct the left half and middle, then shuffle
// the complete string.
// ------------------------------------------------------------

string generatePalindromicSource(int n, int alphabet = 26)
{
    string left;

    for(int i = 0; i < n / 2; i++)
        left += char('a' + rng() % alphabet);

    string right = left;

    reverse(right.begin(), right.end());

    string s = left;

    if(n % 2)
        s += char('a' + rng() % alphabet);

    s += right;

    shuffle(s.begin(), s.end(), rng);

    return s;
}


// ------------------------------------------------------------
// Construct one palindrome from s.
// The returned palindrome is valid for s.
// ------------------------------------------------------------

string makePalindrome(string s)
{
    vector<int> freq(26, 0);

    for(char c : s)
        freq[c - 'a']++;

    string left;
    char middle = 0;

    for(int c = 0; c < 26; c++)
    {
        left += string(freq[c] / 2, char('a' + c));

        if(freq[c] % 2)
            middle = char('a' + c);
    }

    string right = left;

    reverse(right.begin(), right.end());

    return left +
           (middle ? string(1, middle) : "") +
           right;
}


// ------------------------------------------------------------
// Create target which is guaranteed to be SMALLER than p
// ------------------------------------------------------------

string makeSmallerTarget(string p)
{
    string target = p;

    int n = p.size();

    vector<int> positions;

    for(int i = 0; i < n; i++)
    {
        if(p[i] > 'a')
            positions.push_back(i);
    }

    if(positions.empty())
        return target;

    // Prefer changing a late position.
    int idx = positions[rng() % positions.size()];

    target[idx]--;

    // Randomize suffix to make comparison interesting.
    for(int i = idx + 1; i < n; i++)
        target[i] = char('a' + rng() % 26);

    return target;
}


// ------------------------------------------------------------
// Create target which is guaranteed to be GREATER than p
// ------------------------------------------------------------

string makeGreaterTarget(string p)
{
    string target = p;

    int n = p.size();

    vector<int> positions;

    for(int i = 0; i < n; i++)
    {
        if(p[i] < 'z')
            positions.push_back(i);
    }

    if(positions.empty())
        return target;

    int idx = positions[rng() % positions.size()];

    target[idx]++;

    for(int i = idx + 1; i < n; i++)
        target[i] = char('a' + rng() % 26);

    return target;
}


// ------------------------------------------------------------
// Target differs from palindrome only near the END.
// This is useful for testing backtracking.
// ------------------------------------------------------------

string makeLateDifferenceTarget(string p)
{
    string target = p;

    int n = p.size();

    for(int i = n - 1; i >= 0; i--)
    {
        if(p[i] > 'a')
        {
            target[i]--;
            break;
        }
    }

    return target;
}


// ------------------------------------------------------------
// Target differs near the BEGINNING.
// ------------------------------------------------------------

string makeEarlyDifferenceTarget(string p)
{
    string target = p;

    int n = p.size();

    for(int i = 0; i < n; i++)
    {
        if(p[i] < 'z')
        {
            target[i]++;
            break;
        }
    }

    return target;
}


// ------------------------------------------------------------
// Generate impossible source:
// more than one character has odd frequency.
// ------------------------------------------------------------

string generateImpossibleSource(int n, int alphabet = 26)
{
    string s = randomString(n, alphabet);

    // Force several odd frequencies by using distinct characters.
    if(n >= 3)
    {
        s[0] = 'a';
        s[1] = 'b';
        s[2] = 'c';
    }

    return s;
}


// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------

int main()
{
    for(int tc = 1; tc <= 60; tc++)
    {
        ofstream out(
            "problems/018/tests/test" +
            to_string(tc) +
            ".in"
        );

        string s, target;

        // ========================================================
        // TINY CASES
        // ========================================================

        if(tc == 1)
        {
            s = "a";
            target = "a";
        }

        else if(tc == 2)
        {
            s = "b";
            target = "a";
        }

        else if(tc == 3)
        {
            s = "a";
            target = "b";
        }

        else if(tc == 4)
        {
            s = "aa";
            target = "aa";
        }

        else if(tc == 5)
        {
            s = "aa";
            target = "ab";
        }

        else if(tc == 6)
        {
            s = "aa";
            target = "zz";
        }

        // ========================================================
        // SMALL BASIC CASES
        // ========================================================

        else if(tc == 7)
        {
            s = "aba";
            target = "aaa";
        }

        else if(tc == 8)
        {
            s = "aba";
            target = "aba";
        }

        else if(tc == 9)
        {
            s = "aba";
            target = "abb";
        }

        else if(tc == 10)
        {
            s = "aabb";
            target = "abba";
        }

        else if(tc == 11)
        {
            s = "aabb";
            target = "baab";
        }

        else if(tc == 12)
        {
            s = "aabb";
            target = "aaaa";
        }

        else if(tc == 13)
        {
            s = "aac";
            target = "abb";
        }

        else if(tc == 14)
        {
            s = "abc";
            target = "abb";
        }

        else if(tc == 15)
        {
            s = "aabbcc";
            target = "abcabc";
        }

        // ========================================================
        // ALL SAME CHARACTER
        // ========================================================

        else if(tc == 16)
        {
            s = "aaaaaaaaaa";
            target = "aaaaaaaaab";
        }

        else if(tc == 17)
        {
            s = "bbbbbbbbbb";
            target = "aaaaaaaaaa";
        }

        else if(tc == 18)
        {
            s = "zzzzzzzzzz";
            target = "zzzzzzzzzz";
        }

        else if(tc == 19)
        {
            s = string(100, 'a');
            target = string(100, 'a');
        }

        else if(tc == 20)
        {
            s = string(100, 'z');
            target = string(100, 'y');
        }

        // ========================================================
        // IMPOSSIBLE PALINDROME CASES
        // ========================================================

        else if(tc == 21)
        {
            s = "abc";
            target = "aaa";
        }

        else if(tc == 22)
        {
            s = "abcd";
            target = "aaaa";
        }

        else if(tc == 23)
        {
            s = "aabbc";
            target = "aaaaa";
        }

        else if(tc == 24)
        {
            s = "aabbcd";
            target = "abcdef";
        }

        else if(tc == 25)
        {
            s = generateImpossibleSource(50, 5);
            target = randomString(50, 5);
        }

        // ========================================================
        // SMALL RANDOM PALINDROMIC SOURCES
        // ========================================================

        else if(tc <= 32)
        {
            int n = 3 + rng() % 28;

            s = generatePalindromicSource(n, 5);

            string p = makePalindrome(s);

            int type = rng() % 5;

            if(type == 0)
                target = p;

            else if(type == 1)
                target = makeSmallerTarget(p);

            else if(type == 2)
                target = makeGreaterTarget(p);

            else if(type == 3)
                target = makeLateDifferenceTarget(p);

            else
                target = randomString(n, 5);
        }

        // ========================================================
        // DUPLICATE HEAVY
        // ========================================================

        else if(tc <= 38)
        {
            int n = 50 + rng() % 51;

            s = generatePalindromicSource(n, 3);

            string p = makePalindrome(s);

            target = makeLateDifferenceTarget(p);
        }

        // ========================================================
        // LONG COMMON PREFIX
        //
        // target is almost identical to a valid palindrome.
        // This forces the solution to look very carefully for
        // the first position where it can become greater.
        // ========================================================

        else if(tc <= 43)
        {
            int n = 100 + rng() % 101;

            s = generatePalindromicSource(n, 10);

            string p = makePalindrome(s);

            target = p;

            // Change a character very late.
            bool changed = false;

            for(int i = n - 1; i >= 0; i--)
            {
                if(target[i] > 'a')
                {
                    target[i]--;
                    changed = true;
                    break;
                }
            }

            if(!changed)
                target = p;
        }

        // ========================================================
        // RANDOM TARGET
        // ========================================================

        else if(tc <= 48)
        {
            int n = 100 + rng() % 101;

            s = generatePalindromicSource(n, 26);

            target = randomString(n, 26);
        }

        // ========================================================
        // LARGE IMPOSSIBLE
        // ========================================================

        else if(tc <= 51)
        {
            int n = 300;

            s = generateImpossibleSource(n, 26);

            target = randomString(n, 26);
        }

        // ========================================================
        // MAXIMUM SIZE - RANDOM PALINDROMIC SOURCE
        // ========================================================

        else if(tc == 52)
        {
            int n = 300;

            s = generatePalindromicSource(n, 26);

            target = randomString(n, 26);
        }

        // ========================================================
        // MAXIMUM SIZE - TARGET EQUALS A PALINDROME
        // ========================================================

        else if(tc == 53)
        {
            int n = 300;

            s = generatePalindromicSource(n, 26);

            target = makePalindrome(s);
        }

        // ========================================================
        // MAXIMUM SIZE - TARGET JUST BELOW PALINDROME
        // ========================================================

        else if(tc == 54)
        {
            int n = 300;

            s = generatePalindromicSource(n, 26);

            string p = makePalindrome(s);

            target = makeSmallerTarget(p);
        }

        // ========================================================
        // MAXIMUM SIZE - TARGET JUST ABOVE PALINDROME
        // ========================================================

        else if(tc == 55)
        {
            int n = 300;

            s = generatePalindromicSource(n, 26);

            string p = makePalindrome(s);

            target = makeGreaterTarget(p);
        }

        // ========================================================
        // MAXIMUM SIZE - SMALL ALPHABET
        // Heavy duplicate / many repeated characters.
        // ========================================================

        else if(tc == 56)
        {
            int n = 300;

            s = generatePalindromicSource(n, 2);

            string p = makePalindrome(s);

            target = makeLateDifferenceTarget(p);
        }

        // ========================================================
        // MAXIMUM SIZE - LONG PREFIX
        // ========================================================

        else if(tc == 57)
        {
            int n = 300;

            s = generatePalindromicSource(n, 4);

            string p = makePalindrome(s);

            target = p;

            // Make target smaller at the last possible useful
            // position.
            for(int i = n - 1; i >= 0; i--)
            {
                if(target[i] > 'a')
                {
                    target[i]--;
                    break;
                }
            }
        }

        // ========================================================
        // MAXIMUM SIZE - ALL SAME
        // ========================================================

        else if(tc == 58)
        {
            int n = 300;

            s = string(n, 'm');

            target = string(n, 'l');
        }

        // ========================================================
        // MAXIMUM SIZE - ALL SAME, NO ANSWER
        // ========================================================

        else if(tc == 59)
        {
            int n = 300;

            s = string(n, 'm');

            target = string(n, 'z');
        }

        // ========================================================
        // MAXIMUM RANDOM
        // ========================================================

        else
        {
            int n = 300;

            s = randomString(n, 26);
            target = randomString(n, 26);
        }


        // ========================================================
        // WRITE TEST
        // ========================================================

        out << s << '\n';
        out << target << '\n';
    }

    return 0;
}