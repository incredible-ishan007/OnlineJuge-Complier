#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 3)
        return 2;

    ifstream in(argv[1]);
    ifstream out(argv[2]);

    if(!in || !out)
        return 2;

    int n;
    in >> n;

    vector<long long> pref(n);

    for(int i = 0; i < n; i++)
    {
        long long x;
        in >> x;

        if(i == 0)
            pref[i] = x;
        else
            pref[i] = pref[i - 1] + x;
    }

    long long expected = pref[n - 1];

    for(int i = n - 2; i >= 1; i--)
    {
        expected = max(expected, pref[i] - expected);
    }

    long long answer;

    if(!(out >> answer))
        return 1;

    if(answer != expected)
        return 1;

    string extra;

    if(out >> extra)
        return 1;

    return 0;
}