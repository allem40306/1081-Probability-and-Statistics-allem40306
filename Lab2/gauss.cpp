#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
const int INF = 1e9;
const int MXN = 300;
const double EPS = 1e-8;
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

struct GaussElimination
{
    int n;
    vector<double> X;
    vector<vector<double>> A, originA;
    void init(int _n)
    {
        n = _n;
        A.resize(n);
        X.resize(n);
        FOR(i, 0, n) { A[i].resize(n + 1); }
        FOR(i, 0, n) FOR(j, 0, n + 1) { cin >> A[i][j]; }
        originA = A;
    }
    void Elimination()
    {
        FOR(i, 0, n)
        {
            bool ok = false;
            FOR(j, i, n)
            {
                if (fabs(A[j][i]) > EPS)
                {
                    swap(A[j], A[i]);
                    ok = true;
                    break;
                }
            }
            if (!ok)
            {
                continue;
            }
            double fs = A[i][i];
            FOR(j, i + 1, n)
            {
                double r = A[j][i] / fs;
                FOR(k, i, n + 1) { A[j][k] -= A[i][k] * r; }
            }
        }
    }
    void sol()
    {
        FORD(i, n - 1, 0 - 1)
        {
            X[i] = A[i][n];
            FOR(j, i + 1, n) { X[i] -= X[j] * A[i][j]; }
            X[i] /= A[i][i];
        }
    }
    void print()
    {
        FOR(i, 0, n) FOR(j, 0, n + 1) { cout << A[i][j] << " \n"[j == n]; }
        cout << '\n';
        FOR(i, 0, n) { cout << X[i] << " \n"[i == n - 1]; }
        cout << '\n';
    }
    bool isCorrect()
    {
        A = originA;
        FOR(i, 0, n)
        {
            double tmp = 0.0;
            FOR(j, 0, n) { tmp += A[i][j] * X[j]; }
            if (fabs(A[i][n] - tmp) > 1e-6)
            {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    IOS;
    GaussElimination ge;
    int n;
    clock_t t;
    cin >> n;
    ge.init(n);
    double tmp = 0.0;
    FOR(i, 0, 5)
    {
        t = clock();
        ge.Elimination();
        ge.sol();
        t = clock() - t;
        cout << "Input took " << t << " clicks (" << ((double)t) / CLOCKS_PER_SEC
             << " seconds).\n";
        tmp += t;
    }
    cout << tmp / 5.0 << '\n';
    // ge.print();
}
