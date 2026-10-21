#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main()
{
    for(int tc = 1; tc <= 60; tc++)
    {
        ofstream out("problems/019/tests/test" + to_string(tc) + ".in");

        int k;
        vector<int> balls;

        // -------------------------
        // Basic / tiny cases
        // -------------------------

        if(tc == 1)
        {
            // One color, all balls go between boxes.
            k = 1;
            balls = {2};
        }
        else if(tc == 2)
        {
            k = 1;
            balls = {6};
        }
        else if(tc == 3)
        {
            k = 2;
            balls = {1, 1};
        }
        else if(tc == 4)
        {
            k = 2;
            balls = {2, 2};
        }
        else if(tc == 5)
        {
            k = 2;
            balls = {3, 1};
        }

        // -------------------------
        // Simple symmetric cases
        // -------------------------

        else if(tc == 6)
        {
            k = 3;
            balls = {2, 2, 2};
        }
        else if(tc == 7)
        {
            k = 4;
            balls = {1, 1, 1, 1};
        }
        else if(tc == 8)
        {
            k = 4;
            balls = {2, 2, 2, 2};
        }
        else if(tc == 9)
        {
            k = 5;
            balls = {2, 2, 2, 2, 2};
        }
        else if(tc == 10)
        {
            k = 6;
            balls = {1, 1, 1, 1, 1, 1};
        }

        // -------------------------
        // Example cases
        // -------------------------

        else if(tc == 11)
        {
            k = 3;
            balls = {2, 1, 1};
        }
        else if(tc == 12)
        {
            k = 4;
            balls = {1, 2, 1, 2};
        }

        // -------------------------
        // Unequal distributions
        // -------------------------

        else if(tc <= 20)
        {
            k = 3 + rng() % 4;   // 3..6

            balls.resize(k);

            int sum;

            do
            {
                sum = 0;

                for(int i = 0; i < k; i++)
                {
                    balls[i] = 1 + rng() % 6;
                    sum += balls[i];
                }
            }
            while(sum % 2 != 0);
        }

        // -------------------------
        // Heavy colors
        // -------------------------

        else if(tc <= 28)
        {
            k = 3 + rng() % 6;   // 3..8

            balls.resize(k);

            int sum;

            do
            {
                sum = 0;

                for(int i = 0; i < k; i++)
                {
                    balls[i] = 1 + rng() % 6;
                }

                // Force at least one heavy color.
                balls[rng() % k] = 6;

                sum = accumulate(balls.begin(), balls.end(), 0);
            }
            while(sum % 2 != 0);
        }

        // -------------------------
        // Many colors with one ball
        // -------------------------

        else if(tc <= 34)
        {
            k = 8;

            balls.assign(k, 1);

            // Sum must be even.
            // Start with 8 => already even.
        }

        // -------------------------
        // Many colors with two balls
        // -------------------------

        else if(tc <= 40)
        {
            k = 8;

            balls.assign(k, 2);
        }

        // -------------------------
        // Mixed 1 / 2
        // -------------------------

        else if(tc <= 46)
        {
            k = 8;

            balls.resize(k);

            int sum;

            do
            {
                sum = 0;

                for(int i = 0; i < k; i++)
                    balls[i] = 1 + rng() % 2;
            }
            while(accumulate(balls.begin(), balls.end(), 0) % 2 != 0);
        }

        // -------------------------
        // Mixed small / large
        // -------------------------

        else if(tc <= 52)
        {
            k = 8;

            balls.resize(k);

            int sum;

            do
            {
                sum = 0;

                for(int i = 0; i < k; i++)
                {
                    if(i % 2 == 0)
                        balls[i] = 1 + rng() % 2;
                    else
                        balls[i] = 5 + rng() % 2;

                    sum += balls[i];
                }
            }
            while(sum % 2 != 0);
        }

        // -------------------------
        // Maximum total balls
        // -------------------------

        else if(tc == 53)
        {
            k = 8;
            balls.assign(8, 6);
        }

        // -------------------------
        // Maximum with alternating
        // -------------------------

        else if(tc == 54)
        {
            k = 8;

            balls = {
                6, 1,
                6, 1,
                6, 1,
                6, 1
            };
        }

        // -------------------------
        // Maximum uneven
        // -------------------------

        else if(tc == 55)
        {
            k = 8;

            balls = {
                6, 6, 6, 6,
                1, 1, 1, 1
            };
        }

        // -------------------------
        // Random maximum cases
        // -------------------------

        else
        {
            k = 8;

            balls.resize(k);

            int sum;

            do
            {
                sum = 0;

                for(int i = 0; i < k; i++)
                {
                    balls[i] = 1 + rng() % 6;
                    sum += balls[i];
                }
            }
            while(sum % 2 != 0);
        }

        // -------------------------
        // Write test
        // -------------------------

        out << k << '\n';

        for(int i = 0; i < k; i++)
        {
            out << balls[i];

            if(i + 1 < k)
                out << ' ';
        }

        out << '\n';
    }

    return 0;
}