#include <bits/stdc++.h>
using namespace std;

mt19937 rng(
    chrono::steady_clock::now().time_since_epoch().count()
);

int rnd(int l, int r)
{
    return l + rng() % (r - l + 1);
}

int main()
{
    const int TESTS = 25;

    for(int tc = 1; tc <= TESTS; tc++)
    {
        string file =
            "problems/010/tests/test" +
            to_string(tc) + ".in";

        ofstream out(file);

        if(!out)
        {
            cout << "Could not create " << file << '\n';
            return 1;
        }

        int n;
        vector<int> nums;

        if(tc == 1)
        {
            n = 1;
            nums = {5};
        }
        else if(tc == 2)
        {
            n = 2;
            nums = {1, 2};
        }
        else if(tc == 3)
        {
            n = 2;
            nums = {2, 1};
        }
        else if(tc == 4)
        {
            n = 5;
            nums = {5, 2, 6, 1, 3};
        }
        else if(tc == 5)
        {
            n = 10;
            nums = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        }
        else if(tc == 6)
        {
            n = 10;
            nums = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        }
        else if(tc == 7)
        {
            n = 10;
            nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        }
        else if(tc == 8)
        {
            n = 12;
            nums = {
                -10000, 10000, -10000, 10000,
                0, 0, -1, 1, -1, 1, 5, -5
            };
        }
        else if(tc <= 12)
        {
            n = rnd(10, 50);
            nums.resize(n);

            for(int i = 0; i < n; i++)
                nums[i] = rnd(-20, 20);
        }
        else if(tc <= 17)
        {
            n = rnd(1000, 5000);
            nums.resize(n);

            for(int i = 0; i < n; i++)
                nums[i] = rnd(-10000, 10000);
        }
        else if(tc <= 20)
        {
            n = rnd(10000, 30000);
            nums.resize(n);

            for(int i = 0; i < n; i++)
                nums[i] = rnd(-10000, 10000);
        }
        else
        {
            n = 100000;
            nums.resize(n);

            int type = tc - 20;

            for(int i = 0; i < n; i++)
            {
                if(type == 1)
                    nums[i] = rnd(-10000, 10000);
                else if(type == 2)
                    nums[i] = rnd(-10, 10);
                else if(type == 3)
                    nums[i] = (i % 2 == 0 ? 10000 : -10000);
                else if(type == 4)
                    nums[i] = i % 1000;
                else
                    nums[i] = 10000 - (i % 20001);
            }
        }

        out << n << '\n';

        for(int i = 0; i < n; i++)
        {
            out << nums[i];

            if(i + 1 < n)
                out << " ";
        }

        out << '\n';

        out.close();

        cout << "Generated test " << tc << '\n';
    }

    cout << "All 25 tests generated.\n";

    return 0;
}