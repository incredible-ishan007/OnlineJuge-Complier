#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main()
{
    for(int tc = 1; tc <= 60; tc++)
    {
        ofstream out("problems/016/tests/test" + to_string(tc) + ".in");

        int n, m;
        vector<vector<int>> a;

        // --------------------------------
        // Test 1: Single cell
        // --------------------------------

        if(tc == 1)
        {
            n = 1;
            m = 1;

            a = {{1}};
        }

        // --------------------------------
        // Test 2: Single tree
        // --------------------------------

        else if(tc == 2)
        {
            n = 1;
            m = 1;

            a = {{10}};
        }

        // --------------------------------
        // Test 3: Simple reachable trees
        // --------------------------------

        else if(tc == 3)
        {
            n = 2;
            m = 3;

            a = {
                {1, 2, 3},
                {1, 1, 4}
            };
        }

        // --------------------------------
        // Test 4: Unreachable tree
        // --------------------------------

        else if(tc == 4)
        {
            n = 3;
            m = 3;

            a = {
                {1, 2, 3},
                {0, 0, 0},
                {4, 5, 6}
            };
        }

        // --------------------------------
        // Test 5: LeetCode-style example
        // --------------------------------

        else if(tc == 5)
        {
            n = 3;
            m = 3;

            a = {
                {1, 2, 3},
                {0, 0, 4},
                {7, 6, 5}
            };
        }

        // --------------------------------
        // Test 6: Increasing straight path
        // --------------------------------

        else if(tc == 6)
        {
            n = 1;
            m = 10;

            a.resize(n, vector<int>(m));

            for(int j = 0; j < m; j++)
                a[0][j] = j + 2;

            a[0][0] = 1;
        }

        // --------------------------------
        // Small random grids
        // --------------------------------

        else if(tc <= 15)
        {
            n = 2 + rng() % 5;
            m = 2 + rng() % 5;

            a.assign(n, vector<int>(m, 1));

            int height = 2;

            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < m; j++)
                {
                    int type = rng() % 10;

                    if(type < 2)
                        a[i][j] = 0;
                    else if(type < 6)
                        a[i][j] = 1;
                    else
                        a[i][j] = height++;
                }
            }

            // Starting cell must be walkable.
            a[0][0] = 1;
        }

        // --------------------------------
        // Dense trees
        // --------------------------------

        else if(tc <= 22)
        {
            n = 5 + rng() % 6;
            m = 5 + rng() % 6;

            a.assign(n, vector<int>(m, 1));

            int height = 2;

            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < m; j++)
                {
                    if(i == 0 && j == 0)
                        continue;

                    a[i][j] = height++;
                }
            }
        }

        // --------------------------------
        // Many obstacles but reachable
        // --------------------------------

        else if(tc <= 30)
        {
            n = 8 + rng() % 8;
            m = 8 + rng() % 8;

            a.assign(n, vector<int>(m, 1));

            int height = 2;

            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < m; j++)
                {
                    if(i == 0 && j == 0)
                        continue;

                    if(rng() % 5 == 0)
                        a[i][j] = 0;
                    else if(rng() % 3 == 0)
                        a[i][j] = 1;
                    else
                        a[i][j] = height++;
                }
            }

            a[0][0] = 1;
        }

        // --------------------------------
        // Open medium grid
        // --------------------------------

        else if(tc <= 38)
        {
            n = 15 + rng() % 11;
            m = 15 + rng() % 11;

            a.assign(n, vector<int>(m));

            int height = 2;

            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < m; j++)
                    a[i][j] = height++;
            }

            a[0][0] = 1;
        }

        // --------------------------------
        // Medium random grid
        // --------------------------------

        else if(tc <= 46)
        {
            n = 20 + rng() % 11;
            m = 20 + rng() % 11;

            a.assign(n, vector<int>(m, 1));

            int height = 2;

            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < m; j++)
                {
                    if(i == 0 && j == 0)
                        continue;

                    int type = rng() % 10;

                    if(type < 1)
                        a[i][j] = 0;
                    else if(type < 4)
                        a[i][j] = 1;
                    else
                        a[i][j] = height++;
                }
            }

            a[0][0] = 1;
        }

        // --------------------------------
        // Large open grid
        // --------------------------------

        else if(tc <= 51)
        {
            n = 40 + rng() % 11;
            m = 40 + rng() % 11;

            a.assign(n, vector<int>(m));

            int height = 2;

            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < m; j++)
                    a[i][j] = height++;
            }

            a[0][0] = 1;
        }

        // --------------------------------
        // Maximum-size open grid
        // --------------------------------

        else if(tc == 52)
        {
            n = 50;
            m = 50;

            a.assign(n, vector<int>(m));

            int height = 2;

            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < m; j++)
                    a[i][j] = height++;
            }

            a[0][0] = 1;
        }

        // --------------------------------
        // Maximum grid, all trees
        // --------------------------------

        else if(tc == 53)
        {
            n = 50;
            m = 50;

            a.assign(n, vector<int>(m));

            int height = 1000000000;

            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < m; j++)
                {
                    if(i == 0 && j == 0)
                    {
                        a[i][j] = 1;
                    }
                    else
                    {
                        a[i][j] = height--;
                    }
                }
            }
        }

        // --------------------------------
        // Maximum grid with obstacles
        // --------------------------------

        else if(tc <= 56)
        {
            n = 50;
            m = 50;

            a.assign(n, vector<int>(m, 1));

            int height = 2;

            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < m; j++)
                {
                    if(i == 0 && j == 0)
                        continue;

                    if((i + j) % 7 == 0)
                        a[i][j] = 0;
                    else
                        a[i][j] = height++;
                }
            }

            a[0][0] = 1;
        }

        // --------------------------------
        // Completely blocked after start
        // --------------------------------

        else if(tc == 57)
        {
            n = 50;
            m = 50;

            a.assign(n, vector<int>(m, 0));

            a[0][0] = 1;

            a[0][1] = 2;
            a[1][0] = 3;
        }

        // --------------------------------
        // Long corridor
        // --------------------------------

        else if(tc == 58)
        {
            n = 1;
            m = 2500;

            a.resize(1, vector<int>(m));

            a[0][0] = 1;

            for(int j = 1; j < m; j++)
                a[0][j] = j + 1;
        }

        // --------------------------------
        // Tall corridor
        // --------------------------------

        else if(tc == 59)
        {
            n = 2500;
            m = 1;

            a.resize(n, vector<int>(1));

            a[0][0] = 1;

            for(int i = 1; i < n; i++)
                a[i][0] = i + 1;
        }

        // --------------------------------
        // Maximum random-ish grid
        // --------------------------------

        else
        {
            n = 50;
            m = 50;

            a.assign(n, vector<int>(m, 1));

            int height = 2;

            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < m; j++)
                {
                    if(i == 0 && j == 0)
                        continue;

                    int type = rng() % 10;

                    if(type < 2)
                        a[i][j] = 0;
                    else if(type < 5)
                        a[i][j] = 1;
                    else
                        a[i][j] = height++;
                }
            }

            a[0][0] = 1;
        }

        // --------------------------------
        // Write test
        // --------------------------------

        out << n << ' ' << m << '\n';

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                out << a[i][j];

                if(j + 1 < m)
                    out << ' ';
            }

            out << '\n';
        }
    }

    return 0;
}