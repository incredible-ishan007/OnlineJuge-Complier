#include <bits/stdc++.h>
using namespace std;

struct TrieNode
{
    bool isWord = false;
    unordered_map<char, TrieNode*> child;
};

void addWord(TrieNode* root, string word)
{
    TrieNode* cur = root;

    for(char c : word)
    {
        if(!cur->child.count(c))
            cur->child[c] = new TrieNode();

        cur = cur->child[c];
    }

    cur->isWord = true;
}

int solve(string s, vector<string>& wordDict)
{
    TrieNode* root = new TrieNode();

    int maxL = 0;

    for(string word : wordDict)
    {
        addWord(root, word);
        maxL = max(maxL, (int)word.size());
    }

    int n = s.size();

    vector<int> dp(n + 1, 0);
    dp[n] = 1;

    for(int i = n - 1; i >= 0; i--)
    {
        TrieNode* cur = root;

        for(int j = i; j < min(i + maxL, n); j++)
        {
            char c = s[j];

            if(!cur->child.count(c))
                break;

            cur = cur->child[c];

            if(cur->isWord && dp[j + 1])
            {
                dp[i] = 1;
                break;
            }
        }
    }

    return dp[0];
}

int main(int argc, char* argv[])
{
    if(argc != 3)
        return 2;

    ifstream in(argv[1]);
    ifstream out(argv[2]);

    if(!in || !out)
        return 2;

    string s;
    int N;

    in >> s;
    in >> N;

    vector<string> wordDict(N);

    for(int i = 0; i < N; i++)
        in >> wordDict[i];

    int expected = solve(s, wordDict);

    int answer;

    if(!(out >> answer))
        return 1;

    if(answer != expected)
        return 1;

    string extra;

    if(out >> extra)
        return 1;

    return 0;
}