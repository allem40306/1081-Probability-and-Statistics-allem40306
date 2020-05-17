#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
const int INF = 1e9;
const int MXN = 0;
const int MXV = 0;
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define FOR(i, L, R) for (int i = L; i != (int)R; ++i)
#define FORD(i, L, R) for (int i = L; i != (int)R; --i)
#define IOS                                                                    \
    cin.tie(nullptr);                                                          \
    cout.tie(nullptr);                                                         \
    ios_base::sync_with_stdio(false);

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    freopen("test.in", "w", stdout);
    int n = 5000;
    cout << n << '\n';
    double lower_bound = -7;
    double upper_bound = 10;
    FOR(i, 0, n) FOR(j, 0, n + 1)
    {
        cout << fRand(lower_bound, upper_bound) << " \n"[j == n];
    }
    return 0;
}