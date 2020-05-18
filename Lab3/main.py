import numpy as np
import matplotlib.pyplot as plt
import sys

def difftable(points):
    sz = len(points)
    arr = [[0 for x in range(sz)] for y in range(sz)]
    for i in range(sz):
        arr[i][0] = points[i][1]
    for i in range(1, sz):
        for j in range(0, sz - i):
            # print(str(j + i) + ' ' + str(j))
            arr[j][i] = (arr[j + 1][i - 1] - arr[j][i - 1]) / (points[j + i][0] - points[j][0])
    return arr

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

def readPoints(filename):
    points = []
    file = open(filename, 'r')
    lines = file.readlines()
    for line in lines:
        a, b = line.replace('\n','').split(' ')
        points.append([float(a),float(b)])
    return points

def main():
    num = input()
    points1 = readPoints('test' + num + '-1.txt')
    table = difftable(points1)
    # print(table)
    print(lagrange(points1, 2.4))
    print(NewtonDividedDifference(points1, table, 2.4))



if __name__ == "__main__":
	main()