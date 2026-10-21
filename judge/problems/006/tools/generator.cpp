#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

string randomString(int len)
{
    string s;

    for(int i = 0; i < len; i++)
        s += char('a' + rng() % 4);

    return s;
}

int main()
{
    const int TESTS = 60;

    for(int tc = 1; tc <= TESTS; tc++)
    {
        string filename =
            "problems/006/tests/test" + to_string(tc) + ".in";

        ofstream out(filename);

        string s;
        vector<string> dict;

        if(tc <= 10)
        {
            vector<string> pool = {
                "a", "b", "ab", "ba", "aa",
                "bb", "aba", "bab", "abc", "cab"
            };

            int len = 1 + rng() % 15;

            s = randomString(len);

            shuffle(pool.begin(), pool.end(), rng);

            int n = 1 + rng() % 6;

            for(int i = 0; i < n; i++)
                dict.push_back(pool[i]);
        }
        else if(tc <= 20)
        {
            int parts = 5 + rng() % 15;

            for(int i = 0; i < parts; i++)
            {
                int len = 1 + rng() % 10;
                string word = randomString(len);

                s += word;
                dict.push_back(word);
            }

            int extra = 5 + rng() % 15;

            unordered_set<string> used(dict.begin(), dict.end());

            while(extra--)
            {
                int len = 1 + rng() % 10;
                string word = randomString(len);

                if(used.insert(word).second)
                    dict.push_back(word);
            }
        }
        else if(tc <= 30)
        {
            int len = 50 + rng() % 101;

            s = randomString(len);

            int n = 20 + rng() % 81;

            unordered_set<string> used;

            while((int)dict.size() < n)
            {
                int len2 = 1 + rng() % 20;
                string word = randomString(len2);

                if(used.insert(word).second)
                    dict.push_back(word);
            }
        }
        else if(tc <= 40)
        {
            int len = 150 + rng() % 151;

            s = string(len, 'a');

            vector<string> pool = {
                "a", "aa", "aaa", "aaaa", "aaaaa",
                "aaaaaa", "aaaaaaa", "aaaaaaaa",
                "aaaaaaaaa", "aaaaaaaaaa",
                "aaaaaaaaaaa", "aaaaaaaaaaaa",
                "aaaaaaaaaaaaa", "aaaaaaaaaaaaaa",
                "aaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaa",
                "aaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaa",
                "aaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaa"
            };

            shuffle(pool.begin(), pool.end(), rng);

            int n = 3 + rng() % 18;

            for(int i = 0; i < n; i++)
                dict.push_back(pool[i]);
        }
        else if(tc <= 50)
        {
            int len = 150 + rng() % 151;

            s = string(len, 'a');

            s.back() = 'b';

            dict = {
                "a", "aa", "aaa", "aaaa", "aaaaa",
                "aaaaaa", "aaaaaaa", "aaaaaaaa",
                "aaaaaaaaa", "aaaaaaaaaa"
            };
        }
        else
        {
            int len = 250 + rng() % 51;

            s = randomString(len);

            int n = 900 + rng() % 101;

            unordered_set<string> used;

            while((int)dict.size() < n)
            {
                int len2 = 1 + rng() % 20;

                string word = randomString(len2);

                if(used.insert(word).second)
                    dict.push_back(word);
            }
        }

        out << s << '\n';
        out << dict.size() << '\n';

        for(int i = 0; i < (int)dict.size(); i++)
        {
            if(i)
                out << ' ';

            out << dict[i];
        }

        out << '\n';

        out.close();
    }

    cout << "Generated " << TESTS << " test files.\n";

    return 0;
}