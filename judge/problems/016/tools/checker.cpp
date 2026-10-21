#include <bits/stdc++.h>
using namespace std;

int bfs(const vector<vector<int>>& forest,
        int sr, int sc,
        int er, int ec)
{
    int n = forest.size();
    int m = forest[0].size();

    if(sr == er && sc == ec)
        return 0;

    queue<pair<int, int>> q;

    vector<vector<int>> dist(n, vector<int>(m, -1));

    q.push({sr, sc});
    dist[sr][sc] = 0;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while(!q.empty())
    {
        int r = q.front().first;
        int c = q.front().second;

        q.pop();

        for(int d = 0; d < 4; d++)
        {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if(nr < 0 || nr >= n ||
               nc < 0 || nc >= m)
                continue;

            if(dist[nr][nc] != -1)
                continue;

            if(forest[nr][nc] == 0)
                continue;

            dist[nr][nc] = dist[r][c] + 1;

            if(nr == er && nc == ec)
                return dist[nr][nc];

            q.push({nr, nc});
        }
    }

    return -1;
}

int solve(vector<vector<int>>& forest)
{
    int n = forest.size();
    int m = forest[0].size();

    vector<vector<int>> trees;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(forest[i][j] > 1)
            {
                trees.push_back({
                    forest[i][j],
                    i,
                    j
                });
            }
        }
    }

    sort(trees.begin(), trees.end());

    int ans = 0;

    int cr = 0;
    int cc = 0;

    for(int i = 0; i < trees.size(); i++)
    {
        int r = trees[i][1];
        int c = trees[i][2];

        int steps = bfs(
            forest,
            cr,
            cc,
            r,
            c
        );

        if(steps == -1)
            return -1;

        ans += steps;

        cr = r;
        cc = c;
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

    int n, m;

    in >> n >> m;

    vector<vector<int>> forest(
        n,
        vector<int>(m)
    );

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            in >> forest[i][j];
    }

    int expected = solve(forest);

    int userAns;

    if(!(out >> userAns))
        return 1;

    if(userAns != expected)
        return 1;

    // Reject extra output.
    string extra;

    if(out >> extra)
        return 1;

    return 0;
}