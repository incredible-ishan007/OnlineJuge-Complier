#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    long long target;

    cin >> n >> target;

    vector<long long> a(n);

    for (int i = 0; i < n; i++)
        cin >> a[i];

    unordered_map<long long, int> mp;

    for (int i = 0; i < n; i++)
    {
        long long need = target - a[i];

        if (mp.count(need))
        {
            cout << mp[need] << " " << i << '\n';
            return 0;
        }

        mp[a[i]] = i;
    }

    return 0;
}