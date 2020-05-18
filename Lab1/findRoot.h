#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-8;

void printResult(string method, double ans, int count)
{
    cout << "Method: " << method << '\n';
    cout << "The solution is: " << fixed << setprecision(10) << ans << '\n';
    cout << "Count(s) used in loop: " << count << '\n';
    cout << '\n';
}

template <typename Functor> void bisection(Functor &f, double L, double R)
{
    int cnt = 0;
    while (abs(L - R) > EPS)
    {
        ++cnt;
        double M = (L + R) / 2;
        if (f(L) * f(M) > 0)
        {
            L = M;
        }
        else
        {
            R = M;
        }
    }
    printResult("Bisection", (L + R) / 2, cnt);
}

template <typename Functor> void falsePosition(Functor &f, double L, double R)
{
    double old, M = R;
    int cnt = 0;
    do
    {
        ++cnt;
        old = M;
        M = (L * f(R) - R * f(L)) / (f(R) - f(L));
        if (f(L) * f(M) > 0)
        {
            L = M;
        }
        else
        {
            R = M;
        }
    } while (abs(old - M) > EPS);
    printResult("False Position", M, cnt);
}

template <typename Functor>
void modifyFalsePosition(Functor &f, double L, double R)
{
    double old, M = R;
    double fL = f(L), fR = f(R);
    int cnt = 0;
    do
    {
        ++cnt;
        old = M;
        M = (L * fR - R * fL) / (fR - fL);
        fL = f(L);
        fR = f(R);
        if (f(L) * f(M) > 0)
        {
            L = M;
            fL = f(L);
            fR = fR / 2;
        }
        else
        {
            R = M;
            fL = fL / 2;
            fR = f(R);
        }
    } while (abs(old - M) > EPS);
    printResult("Modify False Position", M, cnt);
}

template <typename Functor> void secant(Functor &f, double x1, double x2)
{
    double x3 = 0;
    int cnt = 0;
    do
    {
        ++cnt;
        x3 = (x1 * f(x2) - x2 * f(x1)) / (f(x2) - f(x1));
        x1 = x2;
        x2 = x3;
    } while (abs(x1 - x2) > EPS);
    printResult("Secant", x2, cnt);
}

template <typename Functor, typename Functor2>
void newton(Functor &f, Functor2 &df, double x1)
{
    double theta = 0.0;
    int cnt = 0;
    do
    {
        ++cnt;
        if (cnt >= 500)
        {
            cout << "Method: newton\n";
            cout << "not coverage\n\n";
            return;
        }
        theta = f(x1) / df(x1);
        x1 -= theta;
    } while (abs(theta) > EPS);
    printResult("Newton", x1, cnt);
}

template <typename Functor, typename Functor2>
void fixedPoint(Functor &f, Functor2 &g, double x1)
{
    double old = 1e9;
    int cnt = 0;
    do
    {
        ++cnt;
        if (cnt >= 500)
        {
            cout << "Method: fixed point\n";
            cout << "not coverage\n\n";
            return;
        }
        old = x1;
        x1 = g(x1);
    } while (abs(old - x1) > EPS);
    printResult("Fixed Point", x1, cnt);
}
