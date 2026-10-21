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

    int n, k;

    in >> n >> k;

    vector<int> a(n);

    for(int i = 0; i < n; i++)
        in >> a[i];

    // -------------------------
    // Calculate correct answer
    // -------------------------

    deque<int> dq;
    vector<int> answer;

    for(int i = 0; i < n; i++)
    {
        // Remove indices outside current window.
        while(!dq.empty() && dq.front() <= i - k)
            dq.pop_front();

        // Remove smaller elements from the back.
        while(!dq.empty() && a[dq.back()] <= a[i])
            dq.pop_back();

        dq.push_back(i);

        // Window is complete.
        if(i >= k - 1)
            answer.push_back(a[dq.front()]);
    }

    // -------------------------
    // Read contestant output
    // -------------------------

    vector<int> userAnswer;

    int x;

    while(out >> x)
        userAnswer.push_back(x);

    // -------------------------
    // Compare
    // -------------------------

    if(userAnswer.size() != answer.size())
        return 1;

    for(int i = 0; i < (int)answer.size(); i++)
    {
        if(userAnswer[i] != answer[i])
            return 1;
    }

    return 0;
}