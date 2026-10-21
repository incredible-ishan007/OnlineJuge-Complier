#include <bits/stdc++.h>
using namespace std;

string solve(string s)
{
    int n = s.size();

    vector<int> lps(n, 0);

    int pref = 0;
    int suff = 1;

    while(suff < n)
    {
        if(s[pref] == s[suff])
        {
            lps[suff] = pref + 1;
            suff++;
            pref++;
        }
        else
        {
            if(pref == 0)
            {
                suff++;
                continue;
            }

            pref = lps[pref - 1];
        }
    }

    string ans = "";

    for(int i = 0; i < lps[n - 1]; i++)
    {
        ans += s[i];
    }

    return ans;
}

int main(int argc, char* argv[])
{
    if(argc != 3)
        return 2;

    ifstream in(argv[1]);
    ifstream out(argv[2]);

    if(!in || !out)
        return 2;

    string s;

    if(!(in >> s))
        return 2;

    string expected = solve(s);

    /*
        Read contestant answer as a whole line.

        This is important because the correct answer
        can be an empty string.
    */

    string actual;

    if(!getline(out, actual))
        actual = "";

    // Remove Windows CR if present.
    if(!actual.empty() && actual.back() == '\r')
        actual.pop_back();

    /*
        Exact string comparison.
    */

    if(actual != expected)
        return 1;

    /*
        Reject extra non-empty lines.
    */

    string extra;

    while(getline(out, extra))
    {
        if(!extra.empty() && extra != "\r")
            return 1;
    }

    return 0;
}