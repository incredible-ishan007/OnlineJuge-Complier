#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(123456789);

long long rnd(long long l, long long r)
{
    return l + rng() % (r - l + 1);
}

int main()
{
    vector<vector<long long>> tests;

    tests.push_back({0, 0});
    tests.push_back({1, 1});
    tests.push_back({3, 3});
    tests.push_back({0, 1});
    tests.push_back({1, 0});
    tests.push_back({1, 1, 1});
    tests.push_back({0, 0, 0});
    tests.push_back({1, 2, 3});
    tests.push_back({3, 2, 1});
    tests.push_back({5, 5, 5, 5});
    tests.push_back({3, 4, 0, 4, 3});
    tests.push_back({0, 5, 0, 5, 0});
    tests.push_back({5, 0, 5, 0, 5});
    tests.push_back({1000000000LL, 1000000000LL});
    tests.push_back({1000000000LL, 0});
    tests.push_back({0, 1000000000LL});

    for (int tc = 0; tc < 15; tc++)
    {
        int n = rnd(2, 20);

        vector<long long> a(n);

        for (int i = 0; i < n; i++)
            a[i] = rnd(0, 30);

        tests.push_back(a);
    }

    for (int tc = 0; tc < 10; tc++)
    {
        int n = rnd(20, 200);

        vector<long long> a(n);

        for (int i = 0; i < n; i++)
            a[i] = rnd(0, 1000000000LL);

        tests.push_back(a);
    }

    for (int tc = 0; tc < 5; tc++)
    {
        int n = 1000 + tc * 500;

        vector<long long> a(n);

        a[0] = rnd(0, 1000);

        for (int i = 1; i < n; i++)
        {
            if (i % 4 == 0)
                a[i] = rnd(0, 1000000000LL);
            else
                a[i] = abs(a[i - 1] - rnd(0, 1000));
        }

        tests.push_back(a);
    }

    {
        int n = 10000;
        tests.push_back(vector<long long>(n, 0));
    }

    {
        int n = 10000;
        tests.push_back(vector<long long>(n, 1));
    }

    {
        int n = 10000;
        tests.push_back(vector<long long>(n, 1000000000LL));
    }

    {
        int n = 10000;
        vector<long long> a(n);

        for (int i = 0; i < n; i++)
            a[i] = (i % 2 == 0 ? 1000000000LL : 0);

        tests.push_back(a);
    }

    {
        int n = 10000;
        vector<long long> a(n);

        for (int i = 0; i < n; i++)
            a[i] = (i % 2 == 0 ? 0 : 1000000000LL);

        tests.push_back(a);
    }

    {
        int n = 20000;
        vector<long long> a(n);

        a[0] = 1000000000LL;

        for (int i = 1; i < n; i++)
            a[i] = a[i - 1] / 2;

        tests.push_back(a);
    }

    {
        int n = 20000;
        vector<long long> a(n);

        for (int i = 0; i < n; i++)
            a[i] = rnd(0, 1000000000LL);

        tests.push_back(a);
    }

    {
        int n = 20000;
        vector<long long> a(n);

        for (int i = 0; i < n; i++)
            a[i] = i % 100;

        tests.push_back(a);
    }

    {
        int n = 20000;
        vector<long long> a(n);

        for (int i = 0; i < n; i++)
            a[i] = 1000000000LL - (i % 100);

        tests.push_back(a);
    }

    {
        int n = 20000;
        vector<long long> a(n);

        for (int i = 0; i < n; i++)
            a[i] = rnd(0, 1000000000LL);

        tests.push_back(a);
    }

    int id = 1;

    for (auto &a : tests)
    {
        string file =
            "problems\\002\\tests\\test" +
            to_string(id) +
            ".in";

        ofstream out(file);

        out << 1 << '\n';
        out << a.size() << '\n';

        for (int i = 0; i < (int)a.size(); i++)
        {
            if (i)
                out << ' ';

            out << a[i];
        }

        out << '\n';

        out.close();

        id++;
    }

    cout << "Generated " << tests.size() << " test files.\n";

    return 0;
}