#include <bits/stdc++.h>
using namespace std;

using ll = long long;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ll rnd(ll l, ll r)
{
    return l + rng() % (r - l + 1);
}

vector<ll> getDivisors(ll s)
{
    vector<ll> d;

    for(ll i = 1; i * i <= s; i++)
    {
        if(s % i == 0)
        {
            d.push_back(i);

            if(i != s / i)
                d.push_back(s / i);
        }
    }

    sort(d.begin(), d.end());

    return d;
}

void addQuery(ofstream& out, ll x, ll y, ll s)
{
    x = max(1LL, min(x, s));
    y = max(1LL, min(y, s));

    out << x << ' ' << y << '\n';
}

int main()
{
    const int TESTS = 60;

    for(int tc = 1; tc <= TESTS; tc++)
    {
        string file =
            "problems/007/tests/test" +
            to_string(tc) + ".in";

        ofstream out(file);

        if(!out)
        {
            cout << "Could not create " << file << '\n';
            return 1;
        }

        ll s;
        int q;

        if(tc <= 10)
        {
            s = tc;
            q = 30;

            out << 1 << '\n';
            out << s << ' ' << q << '\n';

            for(int i = 0; i < q; i++)
                addQuery(out, rnd(1, s), rnd(1, s), s);
        }

        else if(tc <= 20)
        {
            s = rnd(10, 10000);
            q = 200;

            vector<ll> d = getDivisors(s);

            out << 1 << '\n';
            out << s << ' ' << q << '\n';

            for(int i = 0; i < q; i++)
            {
                ll x, y;
                ll v = d[rng() % d.size()];

                int type = rng() % 6;

                if(type == 0)
                {
                    x = v;
                    y = v;
                }
                else if(type == 1)
                {
                    x = v - 1;
                    y = v;
                }
                else if(type == 2)
                {
                    x = v + 1;
                    y = v;
                }
                else if(type == 3)
                {
                    x = v;
                    y = v - 1;
                }
                else if(type == 4)
                {
                    x = v;
                    y = v + 1;
                }
                else
                {
                    x = rnd(1, s);
                    y = rnd(1, s);
                }

                addQuery(out, x, y, s);
            }
        }

        else if(tc <= 30)
        {
            ll special[] =
            {
                12, 24, 36, 60, 120,
                180, 360, 720, 5040, 83160
            };

            s = special[tc - 21];
            q = 500;

            vector<ll> d = getDivisors(s);

            out << 1 << '\n';
            out << s << ' ' << q << '\n';

            for(int i = 0; i < q; i++)
            {
                ll v = d[rng() % d.size()];

                int type = rng() % 7;

                ll x, y;

                if(type == 0)
                    x = y = v;
                else if(type == 1)
                    x = v - 1, y = v;
                else if(type == 2)
                    x = v + 1, y = v;
                else if(type == 3)
                    x = v, y = v - 1;
                else if(type == 4)
                    x = v, y = v + 1;
                else
                    x = rnd(1, s), y = rnd(1, s);

                addQuery(out, x, y, s);
            }
        }

        else if(tc <= 40)
        {
            s = rnd(100000, 10000000);
            q = 1000;

            vector<ll> d = getDivisors(s);

            out << 1 << '\n';
            out << s << ' ' << q << '\n';

            for(int i = 0; i < q; i++)
            {
                if(i < 600)
                {
                    ll v = d[rng() % d.size()];

                    int type = rng() % 5;

                    ll x, y;

                    if(type == 0)
                        x = y = v;
                    else if(type == 1)
                        x = v - 1, y = v;
                    else if(type == 2)
                        x = v + 1, y = v;
                    else if(type == 3)
                        x = v, y = v + 1;
                    else
                        x = rnd(1, s), y = rnd(1, s);

                    addQuery(out, x, y, s);
                }
                else
                {
                    addQuery(out, rnd(1, s), rnd(1, s), s);
                }
            }
        }

        else if(tc <= 50)
        {
            ll special[] =
            {
                1000000007LL,
                9999999967LL,
                1000000000007LL,
                9999999999997LL,
                100000000000000LL
            };

            s = special[(tc - 41) % 5];
            q = 2000;

            out << 1 << '\n';
            out << s << ' ' << q << '\n';

            for(int i = 0; i < q; i++)
            {
                if(i < 50)
                    addQuery(out, 1, 1, s);
                else if(i < 100)
                    addQuery(out, s, s, s);
                else if(i < 150)
                    addQuery(out, 1, s, s);
                else if(i < 200)
                    addQuery(out, s, 1, s);
                else
                    addQuery(out, rnd(1, s), rnd(1, s), s);
            }
        }

        else if(tc <= 59)
        {
            ll special[] =
            {
                999999937LL,
                1000000007LL,
                9999999967LL,
                10000000019LL,
                100000000000LL,
                999999999999LL,
                1000000000007LL,
                9999999999999LL,
                100000000000000LL
            };

            s = special[tc - 51];
            q = 10000;

            out << 1 << '\n';
            out << s << ' ' << q << '\n';

            for(int i = 0; i < q; i++)
            {
                int type = rng() % 5;

                if(type == 0)
                    addQuery(out, 1, 1, s);
                else if(type == 1)
                    addQuery(out, s, s, s);
                else if(type == 2)
                    addQuery(out, 1, s, s);
                else if(type == 3)
                    addQuery(out, s, 1, s);
                else
                    addQuery(out, rnd(1, s), rnd(1, s), s);
            }
        }

        else
        {
            s = 100000000000000LL;
            q = 300000;

            out << 1 << '\n';
            out << s << ' ' << q << '\n';

            for(int i = 0; i < q; i++)
            {
                if(i < 100)
                    addQuery(out, 1, 1, s);
                else if(i < 200)
                    addQuery(out, s, s, s);
                else if(i < 300)
                    addQuery(out, 1, s, s);
                else if(i < 400)
                    addQuery(out, s, 1, s);
                else
                    addQuery(out, rnd(1, s), rnd(1, s), s);
            }
        }

        out.close();

        cout << "Generated test " << tc << '\n';
    }

    cout << "All 60 tests generated.\n";

    return 0;
}