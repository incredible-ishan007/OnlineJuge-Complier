#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 3)
        return 2;

    ifstream in(argv[1]);
    ifstream out(argv[2]);

    if (!in || !out)
        return 2;

    int t;
    in >> t;

    while (t--)
    {
        int n;
        in >> n;

        vector<int> a(n);

        for (int i = 0; i < n; i++)
            in >> a[i];

        vector<int> left(n, -1);
        vector<int> right(n, -1);

        int need = a[n - 1];

        for (int i = n - 2; i >= 0; i--)
        {
            right[i] = need;

            if (a[i] < need)
                break;
            else
                need = a[i] - need;
        }

        need = a[0];

        for (int i = 1; i < n; i++)
        {
            left[i] = need;

            if (a[i] < need)
                break;
            else
                need = a[i] - need;
        }

        int ans = 0;

        if (right[0] != -1)
            ans++;

        if (left[n - 1] != -1)
            ans++;

        for (int i = 1; i < n - 1; i++)
        {
            if (left[i] != -1 && right[i] != -1)
                ans++;
        }

        int userAnswer;

        if (!(out >> userAnswer))
            return 1;

        if (userAnswer != ans)
            return 1;
    }

    string extra;

    if (out >> extra)
        return 1;

    return 0;
}