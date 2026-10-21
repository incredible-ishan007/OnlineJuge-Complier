#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> solve(vector<int>& a)
{
    set<int> values;

    for(int i = 0; i < a.size(); i++)
        values.insert(a[i]);

    vector<vector<int>> ans;

    if(values.empty())
        return ans;

    auto it = values.begin();

    int start = *it;
    int prev = *it;

    ++it;

    while(it != values.end())
    {
        int x = *it;

        if(x == prev + 1)
        {
            prev = x;
        }
        else
        {
            ans.push_back({start, prev});

            start = x;
            prev = x;
        }

        ++it;
    }

    ans.push_back({start, prev});

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

    in >> n;

    vector<int> a(n);

    for(int i = 0; i < n; i++)
        in >> a[i];

    vector<vector<int>> expected = solve(a);

    int cnt;

    if(!(out >> cnt))
        return 1;

    if(cnt != expected.size())
        return 1;

    for(int i = 0; i < expected.size(); i++)
    {
        int l, r;

        if(!(out >> l >> r))
            return 1;

        if(l != expected[i][0] ||
           r != expected[i][1])
            return 1;
    }

    string extra;

    if(out >> extra)
        return 1;

    return 0;
}