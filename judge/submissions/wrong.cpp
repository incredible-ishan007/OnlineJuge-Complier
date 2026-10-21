#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    vector<int> seg;
    int padding = 10000;

    int query(int node, int l, int r, int current) {

        if(current <= l)
            return 0;

        if(current > r)
            return seg[node];

        int mid = l + (r - l) / 2;

        return query(2 * node, l, mid, current) +
               query(2 * node + 1, mid + 1, r, current);
    }

    void update(int node, int l, int r, int current) {

        if(l == r) {
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

    vector<int> countSmaller(vector<int>& nums) {

        int n = nums.size();

        vector<int> ans(n);

        seg.assign(4 * 20001 + 5, 0);

        for(int i = n - 1; i >= 0; i--) {

            int curr = nums[i] + padding;

            ans[i] = query(
                1,
                0,
                20000,
                curr
            );

            update(
                1,
                0,
                20000,
                curr
            );
        }

        return ans;
    }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> nums(n);

    for(int i = 0; i < n; i++)
        cin >> nums[i];

    Solution sol;

    vector<int> ans = sol.countSmaller(nums);

    for(int i = 0; i < n; i++) {

        if(i)
            cout << ' ';

        cout << ans[i]+1;
    }

    cout << '\n';

    return 0;
}