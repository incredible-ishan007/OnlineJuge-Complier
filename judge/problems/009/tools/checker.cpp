#include <bits/stdc++.h>
using namespace std;

class ReferenceSolution
{
public:

    vector<int> freq;
    int distinct;
    int odd;

    void add(int x)
    {
        if(freq[x] % 2 == 0)
            odd++;
        else
            odd--;

        if(freq[x] == 0)
            distinct++;

        freq[x]++;
    }

    void remove(int x)
    {
        if(freq[x] % 2 == 0)
            odd++;
        else
            odd--;

        freq[x]--;

        if(freq[x] == 0)
            distinct--;
    }

    vector<bool> validSubarrays(
        vector<int>& nums,
        int k,
        vector<vector<int>>& queries)
    {
        int n = nums.size();
        int q = queries.size();

        vector<bool> ans(q, false);

        freq.assign(100001, 0);

        distinct = 0;
        odd = 0;

        vector<int> order(q);

        for(int i = 0; i < q; i++)
            order[i] = i;

        int block = max(1, (int)sqrt(n));

        sort(order.begin(), order.end(),
            [&](int a, int b)
            {
                int blockA = queries[a][0] / block;
                int blockB = queries[b][0] / block;

                if(blockA != blockB)
                    return blockA < blockB;

                return queries[a][1] > queries[b][1];
            });

        int left = 0;
        int right = -1;

        for(int id : order)
        {
            int l = queries[id][0];
            int r = queries[id][1];

            while(right < r)
            {
                right++;
                add(nums[right]);
            }

            while(right > r)
            {
                remove(nums[right]);
                right--;
            }

            while(left < l)
            {
                remove(nums[left]);
                left++;
            }

            while(left > l)
            {
                left--;
                add(nums[left]);
            }

            ans[id] = (distinct == k && odd == 0);
        }

        return ans;
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

    // -----------------------------
    // Read input
    // -----------------------------

    int n, k;

    if(!(in >> n >> k))
        return 2;

    vector<int> nums(n);

    for(int i = 0; i < n; i++)
    {
        if(!(in >> nums[i]))
            return 2;
    }

    int q;

    if(!(in >> q))
        return 2;

    vector<vector<int>> queries(q, vector<int>(2));

    for(int i = 0; i < q; i++)
    {
        if(!(in >> queries[i][0] >> queries[i][1]))
            return 2;
    }

    // -----------------------------
    // Calculate expected answer
    // -----------------------------

    ReferenceSolution solver;

    vector<bool> expected =
        solver.validSubarrays(nums, k, queries);

    // -----------------------------
    // Read contestant output
    // -----------------------------

    for(int i = 0; i < q; i++)
    {
        string actual;

        if(!(out >> actual))
            return 1;

        string correct =
            expected[i] ? "true" : "false";

        if(actual != correct)
            return 1;
    }

    // -----------------------------
    // Reject extra output
    // -----------------------------

    string extra;

    if(out >> extra)
        return 1;

    return 0;
}