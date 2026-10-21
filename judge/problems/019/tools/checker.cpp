#include <bits/stdc++.h>
using namespace std;

double fact[7] = {
    1,
    1,
    2,
    6,
    24,
    120,
    720
};

double totalWays = 0.0;
double matchingWays = 0.0;

void dfs(vector<int>& balls, int i, int diffBalls, int diffColors, double ways)
{
    if(i == (int)balls.size())
    {
        // Both boxes must contain the same number of balls.
        if(diffBalls == 0)
        {
            totalWays += ways;

            // Both boxes must also have the same number
            // of distinct colors.
            if(diffColors == 0)
                matchingWays += ways;
        }

        return;
    }

    /*
        Put b1 balls of this color into box 1
        and b2 balls into box 2.

        b1 + b2 = balls[i]
    */

    for(int b1 = 0; b1 <= balls[i]; b1++)
    {
        int b2 = balls[i] - b1;

        dfs(
            balls,
            i + 1,
            diffBalls + b1 - b2,
            diffColors + (b1 > 0) - (b2 > 0),
            ways / fact[b1] / fact[b2]
        );
    }
}

double solve(vector<int>& balls)
{
    totalWays = 0.0;
    matchingWays = 0.0;

    dfs(balls, 0, 0, 0, 1.0);

    return matchingWays / totalWays;
}

int main(int argc, char* argv[])
{
    if(argc != 3)
        return 2;

    ifstream in(argv[1]);
    ifstream out(argv[2]);

    if(!in || !out)
        return 2;

    int k;

    if(!(in >> k))
        return 2;

    vector<int> balls(k);

    for(int i = 0; i < k; i++)
    {
        if(!(in >> balls[i]))
            return 2;
    }

    // Calculate correct answer independently.
    double expected = solve(balls);

    // Read contestant answer.
    double actual;

    if(!(out >> actual))
        return 1;

    // Reject NaN / infinity.
    if(!isfinite(actual))
        return 1;

    /*
        Required accuracy:
        absolute error <= 1e-5
    */
    if(fabs(actual - expected) > 1e-5)
        return 1;

    /*
        Reject extra output.
    */
    string extra;

    if(out >> extra)
        return 1;

    return 0;
}