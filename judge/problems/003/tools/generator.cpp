#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(123456789);

int rnd(int l, int r)
{
    return l + rng() % (r - l + 1);
}

vector<int> makeTest(int c0, int c1, int c2)
{
    vector<int> a;

    for (int i = 0; i < c0; i++)
        a.push_back(3);

    for (int i = 0; i < c1; i++)
        a.push_back(1);

    for (int i = 0; i < c2; i++)
        a.push_back(2);

    shuffle(a.begin(), a.end(), rng);

    return a;
}

int main()
{
    vector<vector<int>> tests;

    // Small and boundary cases

    tests.push_back({1});
    tests.push_back({2});
    tests.push_back({3});

    tests.push_back({1, 1});
    tests.push_back({1, 2});
    tests.push_back({2, 2});
    tests.push_back({1, 3});
    tests.push_back({2, 3});
    tests.push_back({3, 3});

    tests.push_back({1, 1, 1});
    tests.push_back({2, 2, 2});
    tests.push_back({1, 2, 3});
    tests.push_back({1, 1, 2});
    tests.push_back({1, 2, 2});

    // cnt0 even

    tests.push_back(makeTest(2, 0, 0));
    tests.push_back(makeTest(2, 1, 0));
    tests.push_back(makeTest(2, 0, 1));
    tests.push_back(makeTest(2, 1, 1));
    tests.push_back(makeTest(4, 1, 1));
    tests.push_back(makeTest(6, 5, 1));

    // cnt0 odd

    tests.push_back(makeTest(1, 0, 0));
    tests.push_back(makeTest(1, 1, 0));
    tests.push_back(makeTest(1, 0, 1));
    tests.push_back(makeTest(1, 2, 0));
    tests.push_back(makeTest(1, 0, 2));
    tests.push_back(makeTest(1, 3, 0));
    tests.push_back(makeTest(1, 0, 3));
    tests.push_back(makeTest(1, 3, 1));
    tests.push_back(makeTest(1, 1, 3));
    tests.push_back(makeTest(3, 4, 1));
    tests.push_back(makeTest(3, 1, 4));

    // Difference exactly around the critical boundary

    tests.push_back(makeTest(1, 5, 2));
    tests.push_back(makeTest(1, 2, 5));

    tests.push_back(makeTest(1, 6, 3));
    tests.push_back(makeTest(1, 3, 6));

    tests.push_back(makeTest(1, 7, 4));
    tests.push_back(makeTest(1, 4, 7));

    // Random small tests

    for (int tc = 0; tc < 10; tc++)
    {
        int n = rnd(1, 20);

        vector<int> a(n);

        for (int i = 0; i < n; i++)
            a[i] = rnd(1, 10000);

        tests.push_back(a);
    }

    // Random medium tests

    for (int tc = 0; tc < 5; tc++)
    {
        int n = rnd(100, 1000);

        vector<int> a(n);

        for (int i = 0; i < n; i++)
            a[i] = rnd(1, 10000);

        tests.push_back(a);
    }

    // Large all residue 0

    {
        int n = 20000;

        tests.push_back(vector<int>(n, 3));
    }

    // Large all residue 1

    {
        int n = 20000;

        tests.push_back(vector<int>(n, 1));
    }

    // Large all residue 2

    {
        int n = 20000;

        tests.push_back(vector<int>(n, 2));
    }

    // Large equal residue 1 and 2

    {
        int n = 20000;

        vector<int> a;

        for (int i = 0; i < n / 2; i++)
        {
            a.push_back(1);
            a.push_back(2);
        }

        tests.push_back(a);
    }

    // Large difference exactly 1

    {
        int n = 20000;

        vector<int> a;

        for (int i = 0; i < 9999; i++)
            a.push_back(1);

        for (int i = 0; i < 10001; i++)
            a.push_back(2);

        tests.push_back(a);
    }

    // Large difference exactly 3

    {
        int n = 20000;

        vector<int> a;

        for (int i = 0; i < 10003; i++)
            a.push_back(1);

        for (int i = 0; i < 9997; i++)
            a.push_back(2);

        tests.push_back(a);
    }

    // Large mixed random

    {
        int n = 20000;

        vector<int> a(n);

        for (int i = 0; i < n; i++)
            a[i] = rnd(1, 10000);

        tests.push_back(a);
    }

    // Maximum value stress

    {
        int n = 20000;

        vector<int> a(n);

        for (int i = 0; i < n; i++)
            a[i] = 10000;

        tests.push_back(a);
    }

    // Maximum N

    {
        int n = 20000;

        vector<int> a(n);

        for (int i = 0; i < n; i++)
            a[i] = rnd(1, 10000);

        tests.push_back(a);
    }

    // Write separate files

    int id = 1;

    for (auto &a : tests)
    {
        string file =
            "problems\\003\\tests\\test" +
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

    cout << "Generated " << tests.size()
         << " test files.\n";

    return 0;
}