#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct SegTree
{
    int n;
    vector<ll> tree;
    const ll NEG = -(1LL << 60);

    SegTree(int n)
    {
        this->n = n;
        tree.assign(4 * n, NEG);
    }

    void update(int node, int l, int r, int idx, ll val)
    {
        if(l == r)
        {
            tree[node] = val;
            return;
        }

        int mid = (l + r) / 2;

        if(idx <= mid)
            update(2 * node, l, mid, idx, val);
        else
            update(2 * node + 1, mid + 1, r, idx, val);

        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    ll query(int node, int l, int r, int ql, int qr)
    {
        if(qr < l || r < ql)
            return NEG;

        if(ql <= l && r <= qr)
            return tree[node];

        int mid = (l + r) / 2;

        return max(
            query(2 * node, l, mid, ql, qr),
            query(2 * node + 1, mid + 1, r, ql, qr)
        );
    }
};

int main(int argc, char* argv[])
{
    if(argc != 3)
        return 2;

    ifstream in(argv[1]);
    ifstream out(argv[2]);

    if(!in || !out)
        return 2;

    int n;
    in >> n;

    vector<ll> a(n), dp(n);

    for(int i = 0; i < n; i++)
        in >> a[i];

    vector<vector<int>> add(n);

    for(int i = 0; i < n; i++)
    {
        ll pos = i + a[i] + 1;

        if(pos < n)
            add[pos].push_back(i);
    }

    SegTree st(n);

    ll ans = 0;
    const ll NEG = -(1LL << 60);

    for(int i = 0; i < n; i++)
    {
        for(int idx : add[i])
            st.update(1, 0, n - 1, idx, dp[idx]);

        ll lim = i - a[i] - 1;

        ll best = NEG;

        if(lim >= 0)
            best = st.query(1, 0, n - 1, 0, (int)lim);

        if(best == NEG)
            dp[i] = a[i];
        else
            dp[i] = best + a[i];

        ans = max(ans, dp[i]);
    }

    ll userAns;

    if(!(out >> userAns))
        return 1;

    if(userAns != ans)
        return 1;

    string extra;

    if(out >> extra)
        return 1;

    return 0;
}