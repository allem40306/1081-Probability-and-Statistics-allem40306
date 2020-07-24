import math

def f(x):
    # print(x)
    return 4 * x * x - 2 * x + 7

def Trapezoidal():
    ans = f(-10) + f(0)
    R = int(1e5)
    for i in range(1,R):
        ans += 2 * f(-10 + 1e-4 * i)
    ans *= 1e-4 / 2
    print(ans)

def Simpson31():
    ans = f(1) + f(1.6)
    R = int(6)
    for i in range(1,R):
        print(1 + 0.1 * i, f(1 + 0.1 * i))
        if i % 2 == 0:
            ans += 2 * f(1 + 0.1 * i)
            print(2 * f(1 + 0.1 * i))
        else:
            ans += 4 * f(1 + 0.1 * i)
            print(4 * f(1 + 0.1 * i))
    print(ans)
    ans *= 0.1 / 3
    print(ans)

def Simpson83():
    ans = f(1) + f(1.6)
    R = int(0.1)
    for i in range(1,R):
        if i % 3 == 0:
            ans += 2 * f(1 + 0.1 * i)
        else:
            ans += 3 * f(1 + 0.1 * i)
    ans *= 0.1 * 8 / 3
    print(ans)

def main():
    # Trapezoidal()
    Simpson31()
    Simpson83()

if __name__ == "__main__":
    main()