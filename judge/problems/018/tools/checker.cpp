#include <bits/stdc++.h>
using namespace std;

string solve(string s, string target)
{
    int n = s.size();

    vector<int> freq(26, 0);

    for (char c : s)
        freq[c - 'a']++;

    char odd = 'A';

    // Find the middle character.
    for (int i = 0; i < 26; i++)
    {
        if (freq[i] % 2)
        {
            if (odd != 'A')
                return "";

            odd = char('a' + i);
            freq[i]--;
        }
    }

    int idx = -1;
    char bestChar = 0;

    // Follow target on the left half.
    for (int i = 0; i < n / 2; i++)
    {
        int c = target[i] - 'a' + 1;

        while (c < 26 && freq[c] == 0)
            c++;

        if (c < 26)
        {
            idx = i;
            bestChar = char('a' + c);
        }

        int x = target[i] - 'a';

        if (freq[x] == 0)
            break;

        freq[x] -= 2;
    }

    string best = "";

    // Case 1:
    // We can completely follow target's left half.
    bool allConsumed = true;

    for (int i = 0; i < 26; i++)
    {
        if (freq[i] != 0)
        {
            allConsumed = false;
            break;
        }
    }

    if (allConsumed)
    {
        string left = target.substr(0, n / 2);

        string rev = left;
        reverse(rev.begin(), rev.end());

        string candidate;

        if (n % 2)
            candidate = left + string(1, odd) + rev;
        else
            candidate = left + rev;

        if (candidate > target)
            best = candidate;
    }

    // Case 2:
    // Increase one position and make the rest minimum.
    if (idx != -1)
    {
        // Rebuild frequencies.
        fill(freq.begin(), freq.end(), 0);

        for (char c : s)
            freq[c - 'a']++;

        // Remove middle character.
        for (int i = 0; i < 26; i++)
        {
            if (freq[i] % 2)
                freq[i]--;
        }

        // Consume target prefix.
        for (int i = 0; i < idx; i++)
        {
            freq[target[i] - 'a'] -= 2;
        }

        string left = target.substr(0, idx);

        // Put the smallest possible character > target[idx].
        left += bestChar;

        freq[bestChar - 'a'] -= 2;

        // Fill remaining left half lexicographically smallest.
        for (int x = 0; x < 26; x++)
        {
            left += string(freq[x] / 2, char('a' + x));
        }

        string rev = left;
        reverse(rev.begin(), rev.end());

        string candidate;

        if (n % 2)
            candidate = left + string(1, odd) + rev;
        else
            candidate = left + rev;

        if (best == "" || candidate < best)
            best = candidate;
    }

    return best;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
        return 2;

    ifstream in(argv[1]);
    ifstream out(argv[2]);

    if (!in || !out)
        return 2;

    string s, target;

    if (!(in >> s >> target))
        return 2;

    string expected = solve(s, target);

    // Platform representation for empty answer.
    if (expected.empty())
        expected = "-1";

    string actual;

    if (!getline(out, actual))
        actual = "";

    // Remove Windows CR.
    if (!actual.empty() && actual.back() == '\r')
        actual.pop_back();

    if (actual != expected)
        return 1;

    // Reject extra output.
    string extra;

    while (getline(out, extra))
    {
        if (!extra.empty() && extra != "\r")
            return 1;
    }

    return 0;
}