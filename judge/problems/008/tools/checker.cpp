#include <bits/stdc++.h>
using namespace std;

bool solve(int n)
{
    int x = n;
    int sum = 0;
    int product = 1;

    while(x > 0)
    {
        int d = x % 10;
        sum += d;
        product *= d;
        x /= 10;
    }

    return n % (sum + product) == 0;
}

int main(int argc, char* argv[])
{
    if(argc != 3)
        return 2;

    ifstream in(argv[1]);
    ifstream out(argv[2]);

    if(!in || !out)
        return 2;

    int t;
    in >> t;

    while(t--)
    {
        int n;
        in >> n;

        bool expected = solve(n);

        string answer;

        if(!(out >> answer))
            return 1;

        for(char& c : answer)
            c = tolower(c);

        string expectedAnswer = expected ? "true" : "false";

        if(answer != expectedAnswer)
            return 1;
    }

    string extra;

    if(out >> extra)
        return 1;

    return 0;
}