#include <bits/stdc++.h>
using namespace std;

string solve(const string& s)
{
    int n = s.size();

    vector<int> pi(n + 1, 0);

    pi[0] = -1;

    int k = -1;

    for(int i = 1; i <= n; i++)
    {
        while(k >= 0 && s[k] != s[i - 1])
            k = pi[k];

        pi[i] = ++k;
    }

    return s.substr(0, pi[n]);
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
    in >> s;

    string expected = solve(s);

    string userAns;

    if(!(out >> userAns))
        return 1;

    // Our problem uses -1 when no border exists.
    if(expected.empty())
        expected = "-1";

    if(userAns != expected)
        return 1;

    // Reject extra output.
    string extra;

    if(out >> extra)
        return 1;

    return 0;
}