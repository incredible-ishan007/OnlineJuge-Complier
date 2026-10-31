
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long target;
    cin >> n >> target;

    vector<long long> a(n);
    unordered_map<long long, int> mp;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        long long need = target - a[i];

        if (mp.find(need) != mp.end()) {
            cout << mp[need] << " " << i << '\n';
            return 0;
        }

        mp[a[i]] = i;
    }

    return 0;
}
