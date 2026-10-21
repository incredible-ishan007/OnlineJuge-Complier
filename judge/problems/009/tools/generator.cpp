#include <bits/stdc++.h>
using namespace std;

using ll = long long;

mt19937_64 rng(
    chrono::steady_clock::now().time_since_epoch().count()
);

ll rnd(ll l, ll r)
{
    return l + rng() % (r - l + 1);
}

int main()
{
    const int TESTS = 25;

    for(int tc = 1; tc <= TESTS; tc++)
    {
        string file =
            "problems/009/tests/test" +
            to_string(tc) + ".in";

        ofstream out(file);

        if(!out)
        {
            cout << "Could not create " << file << '\n';
            return 1;
        }

        int n, k, q;
        vector<int> nums;

        if(tc == 1)
        {
            n = 2;
            k = 1;
            q = 1;

            nums = {1, 1};

            out << n << " " << k << '\n';

            for(int x : nums)
                out << x << " ";
            out << '\n';

            out << q << '\n';
            out << "0 1\n";
        }
        else if(tc == 2)
        {
            n = 3;
            k = 1;
            q = 2;

            nums = {3, 3, 3};

            out << n << " " << k << '\n';

            for(int x : nums)
                out << x << " ";
            out << '\n';

            out << q << '\n';
            out << "1 2\n";
            out << "0 2\n";
        }
        else if(tc == 3)
        {
            n = 4;
            k = 2;
            q = 3;

            nums = {1, 2, 2, 1};

            out << n << " " << k << '\n';

            for(int x : nums)
                out << x << " ";
            out << '\n';

            out << q << '\n';
            out << "0 1\n";
            out << "0 3\n";
            out << "1 2\n";
        }
        else if(tc == 4)
        {
            n = 10;
            k = 5;
            q = 5;

            nums = {1,2,3,4,5,5,4,3,2,1};

            out << n << " " << k << '\n';

            for(int x : nums)
                out << x << " ";
            out << '\n';

            out << q << '\n';
            out << "0 9\n";
            out << "0 4\n";
            out << "5 9\n";
            out << "1 8\n";
            out << "2 7\n";
        }
        else
        {
            if(tc <= 8)
                n = rnd(5, 30);
            else if(tc <= 14)
                n = rnd(100, 1000);
            else if(tc <= 20)
                n = rnd(5000, 20000);
            else
                n = rnd(50000, 100000);

            k = rnd(1, min(n, 20));

            if(tc >= 23)
                q = 100000;
            else if(tc >= 15)
                q = rnd(1000, 10000);
            else
                q = rnd(20, 200);

            nums.resize(n);

            int type = rnd(1, 4);

            for(int i = 0; i < n; i++)
            {
                if(type == 1)
                    nums[i] = rnd(1, 5);
                else if(type == 2)
                    nums[i] = rnd(1, 50);
                else if(type == 3)
                    nums[i] = rnd(1, 100000);
                else
                    nums[i] = rnd(1, 1000);
            }

            out << n << " " << k << '\n';

            for(int i = 0; i < n; i++)
            {
                out << nums[i];

                if(i + 1 < n)
                    out << " ";
            }

            out << '\n';

            out << q << '\n';

            for(int i = 0; i < q; i++)
            {
                int l = rnd(0, n - 2);
                int r = rnd(l + 1, n - 1);

                out << l << " " << r << '\n';
            }
        }

        out.close();

        cout << "Generated test " << tc << '\n';
    }

    cout << "All 25 tests generated.\n";

    return 0;
}