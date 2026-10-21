#include <iostream>
using namespace std;

int main()
{
    const long long N = 300LL * 1024 * 1024;

    char* a = new char[N];

    for (long long i = 0; i < N; i++)
        a[i] = 1;

    cout << 100 << endl;

    delete[] a;

    return 0;
}