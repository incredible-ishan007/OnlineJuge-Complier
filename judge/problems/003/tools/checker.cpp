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

    int T;
    in >> T;

    while (T--)
    {
        int n;
        in >> n;

        int cnt0 = 0;
        int cnt1 = 0;
        int cnt2 = 0;

        for (int i = 0; i < n; i++)
        {
            int x;
            in >> x;

            int type = x % 3;

            if (type == 0)
                cnt0++;
            else if (type == 1)
                cnt1++;
            else
                cnt2++;
        }

        bool ans;

        if (cnt0 % 2 == 0)
        {
            ans = cnt1 >= 1 && cnt2 >= 1;
        }
        else
        {
            ans = cnt1 - cnt2 > 2 ||
                  cnt2 - cnt1 > 2;
        }

        string userAnswer;

        if (!(out >> userAnswer))
            return 1;

        if (userAnswer != "true" &&
            userAnswer != "false")
            return 1;

        bool given = (userAnswer == "true");

        if (given != ans)
            return 1;
    }

    string extra;

    if (out >> extra)
        return 1;

    return 0;
}