#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 3)
        return 2;

    ifstream in(argv[1]);
    ifstream out(argv[2]);

    if(!in || !out)
        return 2;

    int n, m;
    in >> n >> m;

    vector<int> a(n), b(m);

    for(int i = 0; i < n; i++)
        in >> a[i];

    for(int i = 0; i < m; i++)
        in >> b[i];

    vector<int> ans;

    int i = 0;
    int j = 0;

    while(i < n && j < m)
    {
        if(a[i] <= b[j])
            ans.push_back(a[i++]);
        else
            ans.push_back(b[j++]);
    }

    while(i < n)
        ans.push_back(a[i++]);

    while(j < m)
        ans.push_back(b[j++]);

    if(ans.empty())
    {
        string answer;

        if(!(out >> answer))
            return 1;

        if(answer != "-1")
            return 1;

        string extra;

        if(out >> extra)
            return 1;

        return 0;
    }

    for(int x : ans)
    {
        int answer;

        if(!(out >> answer))
            return 1;

        if(answer != x)
            return 1;
    }

    string extra;

    if(out >> extra)
        return 1;

    return 0;
}