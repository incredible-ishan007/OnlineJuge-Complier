#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r)
{
    return l + rng() % (r - l + 1);
}

void validate(const vector<int>& a)
{
    int n = a.size();

    assert(n >= 2);
    assert(n <= 400);

    long long sum = 0;

    for (int x : a)
    {
        assert(x >= 0);
        assert(x <= n);
        sum += x;
    }

    assert(sum == n);
}

vector<int> randomComposition(int n)
{
    vector<int> a(n, 0);

    int rem = n;

    for (int i = 0; i < n - 1; i++)
    {
        int x = rnd(0, rem);

        a[i] = x;
        rem -= x;
    }

    a[n - 1] = rem;

    shuffle(a.begin(), a.end(), rng);

    validate(a);

    return a;
}

vector<int> allOnes(int n)
{
    vector<int> a(n, 1);

    validate(a);

    return a;
}

vector<int> oneLarge(int n)
{
    vector<int> a(n, 0);

    a[0] = n;

    validate(a);

    return a;
}

vector<int> twoLarge(int n)
{
    vector<int> a(n, 0);

    int x = rnd(1, n - 1);

    a[0] = x;
    a[1] = n - x;

    shuffle(a.begin(), a.end(), rng);

    validate(a);

    return a;
}

vector<int> repeatedValue(int n, int mx)
{
    vector<int> a(n, 0);

    int rem = n;

    for (int i = 0; i < n && rem > 0; i++)
    {
        int x = rnd(1, min(mx, rem));

        a[i] = x;
        rem -= x;
    }

    shuffle(a.begin(), a.end(), rng);

    validate(a);

    return a;
}

vector<int> sparseCase(int n)
{
    vector<int> a(n, 0);

    int parts = rnd(2, min(n, 15));

    int rem = n;

    for (int i = 0; i < parts - 1; i++)
    {
        int x = rnd(1, rem - (parts - i - 1));

        a[i] = x;
        rem -= x;
    }

    a[parts - 1] = rem;

    shuffle(a.begin(), a.end(), rng);

    validate(a);

    return a;
}

vector<int> randomPartition(int n)
{
    vector<int> a(n, 0);

    int rem = n;
    int pos = 0;

    while (rem > 0)
    {
        int x = rnd(1, min(rem, 20));

        a[pos] = x;

        pos++;
        rem -= x;
    }

    shuffle(a.begin(), a.end(), rng);

    validate(a);

    return a;
}

int main()
{
    vector<vector<int>> tests;

    // --------------------------------------------------
    // Small edge cases
    // --------------------------------------------------

    tests.push_back({1, 1});
    tests.push_back({0, 2});
    tests.push_back({0, 0, 3});
    tests.push_back({1, 1, 1});
    tests.push_back({3, 0, 0});
    tests.push_back({2, 1, 0});
    tests.push_back({0, 1, 2});

    // --------------------------------------------------
    // All ones
    // --------------------------------------------------

    tests.push_back(allOnes(4));
    tests.push_back(allOnes(5));
    tests.push_back(allOnes(10));
    tests.push_back(allOnes(20));
    tests.push_back(allOnes(100));
    tests.push_back(allOnes(200));
    tests.push_back(allOnes(400));

    // --------------------------------------------------
    // One large value
    // --------------------------------------------------

    tests.push_back(oneLarge(10));
    tests.push_back(oneLarge(50));
    tests.push_back(oneLarge(100));
    tests.push_back(oneLarge(200));
    tests.push_back(oneLarge(400));

    // --------------------------------------------------
    // Two large values
    // --------------------------------------------------

    tests.push_back(twoLarge(10));
    tests.push_back(twoLarge(50));
    tests.push_back(twoLarge(100));
    tests.push_back(twoLarge(200));
    tests.push_back(twoLarge(400));

    // --------------------------------------------------
    // Repeated values
    // --------------------------------------------------

    tests.push_back(repeatedValue(20, 2));
    tests.push_back(repeatedValue(50, 3));
    tests.push_back(repeatedValue(100, 5));
    tests.push_back(repeatedValue(200, 10));
    tests.push_back(repeatedValue(400, 20));

    // --------------------------------------------------
    // Sparse distributions
    // --------------------------------------------------

    tests.push_back(sparseCase(20));
    tests.push_back(sparseCase(50));
    tests.push_back(sparseCase(100));
    tests.push_back(sparseCase(200));
    tests.push_back(sparseCase(400));

    // --------------------------------------------------
    // Random small
    // --------------------------------------------------

    for (int i = 0; i < 8; i++)
    {
        int n = rnd(2, 30);

        tests.push_back(randomComposition(n));
    }

    // --------------------------------------------------
    // Random medium
    // --------------------------------------------------

    for (int i = 0; i < 7; i++)
    {
        int n = rnd(50, 150);

        tests.push_back(randomComposition(n));
    }

    // --------------------------------------------------
    // Random large
    // --------------------------------------------------

    for (int i = 0; i < 6; i++)
    {
        int n = rnd(200, 400);

        tests.push_back(randomComposition(n));
    }

    // --------------------------------------------------
    // Random partitions
    // --------------------------------------------------

    for (int i = 0; i < 5; i++)
    {
        int n = rnd(100, 400);

        tests.push_back(randomPartition(n));
    }

    // --------------------------------------------------
    // Final validation
    // --------------------------------------------------

    assert(tests.size() == 60);

    for (auto& a : tests)
        validate(a);

    // --------------------------------------------------
    // Write test files
    // --------------------------------------------------

    int id = 1;

    for (auto& a : tests)
    {
        string filename =
            "problems\\004\\tests\\test" +
            to_string(id) +
            ".in";

        ofstream out(filename);

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

    cout << "Generated "
         << tests.size()
         << " valid test files.\n";

    return 0;
}