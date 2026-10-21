#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 4)
        return 1;

    ifstream input(argv[1]);
    ifstream userOutput(argv[2]);
    ifstream officialOutput(argv[3]);

    if (!input || !userOutput || !officialOutput)
        return 1;

    int n;
    long long target;

    input >> n >> target;

    vector<long long> a(n);

    for (int i = 0; i < n; i++)
        input >> a[i];

    int i, j;

    if (!(userOutput >> i >> j))
        return 1;

    string extra;

    if (userOutput >> extra)
        return 1;

    if (i < 0 || i >= n || j < 0 || j >= n)
        return 1;

    if (i == j)
        return 1;

    if (a[i] + a[j] != target)
        return 1;

    return 0;
}