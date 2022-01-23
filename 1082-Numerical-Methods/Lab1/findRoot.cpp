#pragma GCC optimize(2)
#include "findRoot.h"
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

int main()
{
    IOS;

    cout << "Equation 1:\n\n";
    auto f1 = [=](double x) { return exp(x) - 3 * x * cos(2 * x) - 8.3; };
    auto df1 = [=](double x) {
        return exp(x) + 6 * x * sin(2 * x) - 3 * cos(2 * x);
    };
    auto g1 = [=](double x) { return (exp(x) - 8.3) / 3 * cos(2 * x); };
    bisection(f1, -2, 2);
    falsePosition(f1, -2, 2);
    modifyFalsePosition(f1, -2, 2);
    secant(f1, -100, 2);
    newton(f1, df1, -5);
    fixedPoint(f1, g1, 5);

    cout << "Equation 2:\n\n";
    auto f2 = [=](double x) { return exp(x * sin(x)) - x * cos(2 * x) - 2.8; };
    auto df2 = [=](double x) {
        return (sin(x) + x * cos(x)) * exp(x * sin(x)) + 2 * x * sin(2 * x) -
               cos(2 * x);
    };
    auto g2 = [=](double x) { return (exp(x * sin(x)) - 2.8) / (cos(2 * x)); };
    bisection(f2, -5, 5);
    falsePosition(f2, -5, 5);
    modifyFalsePosition(f2, -5, 5);
    secant(f2, -5, 2);
    newton(f2, df2, 5);
    fixedPoint(f2, g2, 0);

    cout << "Equation 3:\n\n";
    auto f3 = [=](double x) {
        return 7 * x * x * sin(4 * x) - 6 * x * cos(x) + 5.6;
    };
    auto df3 = [=](double x) {
        return 14 * x * sin(4 * x) + 28 * x * x * cos(4 * x) - 6 * cos(x) +
               6 * x * sin(x);
    };
    auto g3 = [=](double x) {
        return (7 * x * x * sin(4 * x) + 5.6) / (6 * cos(x));
    };
    bisection(f3, -5, 5);
    falsePosition(f3, -5, 5);
    modifyFalsePosition(f3, -5, 5);
    secant(f3, -5, 2);
    newton(f3, df3, 0);
    fixedPoint(f3, g3, -3.5);

    cout << "Equation 4:\n\n";
    auto f4 = [=](double x) {
        return 4 * x + exp(x) - 3 * cos(x) + 6.5;
    };
    auto df4 = [=](double x) { return 4 + exp(x) + 3 * sin(x); };
    auto g4 = [=](double x) { return (exp(x) + 3 * sin(x)) / 4; };
    bisection(f4, -5, 5);
    falsePosition(f4, -5, 5);
    modifyFalsePosition(f4, -5, 5);
    secant(f4, -5, 2);
    newton(f4, df4, 0);
    fixedPoint(f4, g4, 0);
}
