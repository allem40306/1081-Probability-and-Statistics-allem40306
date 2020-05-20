import numpy as np
import matplotlib.pyplot as plt
import sys

def readPoints(filename):
    points = []
    file = open(filename, 'r')
    lines = file.readlines()
    for line in lines:
        a, b = line.replace('\n','').split(' ')
        points.append([float(a),float(b)])
    return points

def difftable1(points):
    sz = len(points)
    arr = [[0 for x in range(sz)] for y in range(sz)]
    for i in range(sz):
        arr[i][0] = points[i][1]
    for i in range(1, sz):
        for j in range(0, sz - i):
            # print(str(j + i) + ' ' + str(j))
            arr[j][i] = (arr[j + 1][i - 1] - arr[j][i - 1]) / (points[j + i][0] - points[j][0])
    return arr

def difftable2(points):
    sz = len(points)
    arr = [[0 for x in range(sz)] for y in range(sz)]
    for i in range(sz):
        arr[i][0] = points[i][1]
    for i in range(1, sz):
        for j in range(0, sz - i):
            # print(str(j + i) + ' ' + str(j))
            arr[j][i] = (arr[j + 1][i - 1] - arr[j][i - 1])
    return arr

def fact(n):
    ret = 1
    for i in range(1, n + 1):
        ret *= i
    return ret

def lagrange(points, x):
    ret = 0.0
    for i in range(len(points)):
        xi, yi = points[i]
        tmp = yi
        for j in range(len(points)):
            if i == j:
                continue
            xj = points[j][0]
            tmp *= (x-xj) / (xi-xj)
        ret += tmp
    return ret

def NewtonDividedDifference(points, table, x):
    ret = table[0][0]
    tmp = 1.0
    for i in range(1, len(points)):
        tmp *= (x - points[i - 1][0])
        ret += tmp * table[0][i]
        # print(str(tmp) + ' ' + str(table[0][i]))
    return ret

def GrogoryNewtonForward(points, table, x):
    sz = len(points)
    S = (x - points[0][0]) / (points[1][0] - points[0][0])
    ret = table[0][0]
    tmp = 1
    for i in range(1, sz):
        tmp *= (S - i + 1)
        tmp /= i
        ret += tmp * table[0][i]
    return ret

def GrogoryNewtonBackward(points, table, x):
    sz = len(points)
    S = (x - points[sz - 1][0] ) / (points[1][0] - points[0][0])
    # print(S)
    ret = table[sz - 1][0]
    tmp = 1
    for i in range(1, sz):
        tmp *= (S + i - 1)
        tmp /= i
        ret += tmp * table[sz - 1 - i][i]
        # print(tmp, table[sz - 1 - i][i])
    return ret

def GaussForward(points, table, x):
    sz = len(points)
    row = int(len(points) // 2)
    S = (x - points[row][0]) / (points[1][0] - points[0][0])
    ret = table[row][0]
    tmp = 1
    for i in range(1, sz):
        if i % 2 == 0:
            row -= 1
            tmp *= (S - i // 2)
        else:
            tmp *= (S + (i - 1) // 2)
        tmp /= i
        ret += tmp * table[row][i]
    return ret

def GaussForward(points, table, x):
    sz = len(points)
    row = int(len(points) // 2)
    S = (x - points[row][0]) / (points[1][0] - points[0][0])
    ret = table[row][0]
    tmp = 1
    # print(S)
    for i in range(1, sz):
        # print(str(i) + ':')
        if i % 2 == 0:
            row -= 1
            tmp *= (S - i // 2)
            # print(str(-i // 2))
        else:
            tmp *= (S + (i - 1) // 2)
            # print(str((i - 1) // 2))
        tmp /= i
        # print(tmp, table[row][i])
        ret += tmp * table[row][i]
    return ret

def GaussBackward(points, table, x):
    sz = len(points)
    row = int(len(points) // 2)
    S = (x - points[row][0]) / (points[1][0] - points[0][0])
    ret = table[row][0]
    tmp = 1
    # print(S)
    for i in range(1, sz):
        if i % 2 == 0:
            tmp *= (S + i // 2)
        else:
            tmp *= (S - (i - 1) // 2)
            row -= 1
        tmp /= i
        # print(tmp, table[row][i])
        ret += tmp * table[row][i]
    return ret

def main():
    num = input()
    points1 = readPoints('test' + num + '-1.txt')
    points2 = readPoints('test' + num + '-2.txt')
    table1 = difftable1(points1)
    table2 = difftable2(points2)
    # for item in points1:
    #     x, y = item
    #     print(lagrange(points1, x), y)
    #     print(NewtonDividedDifference(points1, table1, x), y)
    # for item in points2:
    #     x, y = item
    #     print(GrogoryNewtonForward(points2, table2, x), y)
    #     print(GrogoryNewtonBackward(points2, table2, x), y)
    #     print(GaussForward(points2, table2, x), y)
    #     print(GaussBackward(points2, table2, x), y)
    # print(GaussForward(points2, table2, 1.17))

if __name__ == "__main__":
	main()