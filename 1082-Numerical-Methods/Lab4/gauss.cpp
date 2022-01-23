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

vector<double> xx, xy;

struct GaussElimination
{
    int n;
    vector<double> X;
    vector<vector<double>> A;
    void init(int _n)
    {
        n = _n + 1;
        A.resize(n);
        X.resize(n);
        FOR(i, 0, n) { A[i].resize(n + 1); }
        FOR(i, 0, n)
        {
            FOR(j, 0, i + 1)
            {
                A[i - j][j] = xx[i];
            }
        }
        FOR(i, 0, n - 1)
        {
            FOR(j, 0, n - i - 1)
            {
                A[(n - 1) - j][j + i + 1] = xx[n + i];
            }
        }
        FOR(i, 0, n){A[i][n] = xy[i];}
        // FOR(i, 0, n)
        // {
        //     FOR(j, 0, n + 1)
        //     {
        //         cout << A[i][j] << " \n"[j == n];
        //     }
        // }
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
    vector<double> sol()
    {
        FORD(i, n - 1, 0 - 1)
        {
            X[i] = A[i][n];
            FOR(j, i + 1, n) { X[i] -= X[j] * A[i][j]; }
            X[i] /= A[i][i];
        }
        return X;
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

pair<double, double> generate_XXandXY(vector<double> X, vector<double> Y)
{
    double sum_x = 0.0, sum_y = 0.0;
    FOR(i,0,X.size())
    {
        sum_x += X[i];
        sum_y += X[i] * Y[i];
    }
    return {sum_x, sum_y};
}

double calc_error(vector<double> X, vector<double> Y, vector<double> P)
{
    double total_error = 0;
    FOR(i,0,X.size())
    {
        double sum = 0;
        for(int j = X.size() - 1; j >= 0; --j)
        {
            sum *= X[i];
            sum += P[j];
        }
        total_error += abs(sum - Y[i]) * abs(sum - Y[i]);
    }
    return total_error;
}

double f(double x, vector<double> P)
{
    double sum = 0;
    for(int i = P.size() - 1; i >= 0; --i)
    {
        sum *= x;
        sum += P[i];
    }
    return sum;
}

int main()
{
    freopen("test.in", "r", stdin);
    GaussElimination ge;
    vector<double> X, Y;
    for(double x, y; cin >> x >> y;)
    {
        X.push_back(x);
        Y.push_back(y);
    }
    int n = X.size();
    vector<double> tmp(n, 1);
    for(int i = 0; i < (n << 1) - 1; ++i)
    {
        if(i)
        {
            FOR(j, 0, n){ tmp[j] *= X[j];}
        }
        pair<double, double> res = generate_XXandXY(tmp, Y);
        xx.push_back(res.first);
        xy.push_back(res.second);
    }
    vector<double> total_errors;
    FOR(i,1,n)
    {
        // when i = 6 or i == 8, it doesn't work
        if(i == 6 || i == 8)
        {
            cout << '\n';
            continue;
        }
        // cout << i << '\n';
        ge.init(i);
        ge.Elimination();
        // ge.print();
        vector<double> P = ge.sol();
        cout << calc_error(X, Y, P) / double(n - i) << '\n';
    }
    // i = 28 is best
    cout << "\ni = 28\n\n";
    ge.init(28);
    ge.Elimination();
    vector<double> P = ge.sol();
    for(int i = 0; i < 9200; ++i)
    {
        cout << double(i) * 0.001 << ' ' << f(double(i) * 0.001, P) << '\n';
    }
}
