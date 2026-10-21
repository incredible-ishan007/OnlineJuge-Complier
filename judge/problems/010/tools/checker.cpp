#include <bits/stdc++.h>
using namespace std;

vector<int> seg(4 * 20001, 0);

int query(int node, int l, int r, int current)
{
    if(current <= l)
        return 0;

    if(current > r)
        return seg[node];

    int mid = l + (r - l) / 2;

    return query(2 * node, l, mid, current) +
           query(2 * node + 1, mid + 1, r, current);
}

void update(int node, int l, int r, int current)
{
    if(l == r)
    {
        seg[node]++;
        return;
    }

    seg[node]++;

    int mid = l + (r - l) / 2;

    if(current <= mid)
        update(2 * node, l, mid, current);
    else
        update(2 * node + 1, mid + 1, r, current);
}

vector<int> solve(vector<int>& nums)
{
    int n = nums.size();

    vector<int> ans(n);

    const int padding = 10000;

    for(int i = n - 1; i >= 0; i--)
    {
        int curr = nums[i] + padding;

        ans[i] = query(1, 0, 20000, curr);

        update(1, 0, 20000, curr);
    }

    return ans;
}

int main(int argc, char* argv[])
{
    if(argc != 3)
        return 2;

    ifstream in(argv[1]);
    ifstream out(argv[2]);

    if(!in || !out)
        return 2;

    int n;

    if(!(in >> n))
        return 2;

    vector<int> nums(n);

    for(int i = 0; i < n; i++)
    {
        if(!(in >> nums[i]))
            return 2;
    }

    vector<int> expected = solve(nums);

    // Read contestant answer
    for(int i = 0; i < n; i++)
    {
        int actual;

        if(!(out >> actual))
            return 1;

        if(actual != expected[i])
            return 1;
    }

    // Reject extra output
    string extra;

    if(out >> extra)
        return 1;

    return 0;
}