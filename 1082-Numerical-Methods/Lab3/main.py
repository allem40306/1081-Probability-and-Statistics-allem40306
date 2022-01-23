import numpy as np
import matplotlib.pyplot as plt
import sys
import math

def readPoints(filename):
    points = []
    file = open(filename, 'r')
    lines = file.readlines()
    for line in lines:
        a, b = line.replace('\n','').split(' ')
        points.append([float(a),float(b)])
    return points

def draw(points, testPointsX, testPointsY, pictureName, num):
    plt.figure('Draw')
    if num == 1:
        plt.plot([points[i][0] for i in range(0,len(points))],
            [points[i][1] for i in range(0,len(points))], 'yo')
    elif num == 2:
        plt.plot([i / 1000 for i in range(2000, 9000 + 1)],
            [3*math.exp(i / 1000) * math.sin(i / 1000) + math.cos(i / 1000) + 6.9
             for i in range(2000, 9000 + 1)], 'yo')
    elif num == 3:
        plt.plot([i / 1000 for i in range(2000, 9000 + 1)],
            [4 * (i / 1000) * (i / 1000) * math.sin((i / 1000)) - 3 * math.cos((i / 1000)) + 7.5
             for i in range(2000, 9000 + 1)], 'yo')
    elif num == 4:
        plt.plot([i / 1000 for i in range(2000, 9000 + 1)],
            [2 * math.exp(2 * (i / 1000)) - 7 * math.sin((i / 1000)) + 8.8
             for i in range(2000, 9000 + 1)], 'yo')
    elif num == 5:
        plt.plot([i / 1000 for i in range(2000, 9000 + 1)],
            [4.4 * math.exp(math.sin(i / 1000)) - 9.6
             for i in range(2000, 9000 + 1)], 'yo')
    # testPointsY = [float(3*math.exp(testPointsX[i]) * math.sin(testPointsX[i]) + math.cos(testPointsX[i]) + 6.9) for i in range(0, len(testPointsX)) ]
    plt.plot(testPointsX, testPointsY, 'r')
    plt.draw()
    # plt.pause(5)
    plt.suptitle(pictureName)
    plt.savefig(pictureName + '.png')
    plt.close()

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

def generatePoints():
    testPointsX = [i / 1000 for i in range(2000, 9000 + 1)]
    testPointsY = [0 for i in range(0, len(testPointsX)) ]
    return testPointsX, testPointsY

def Lagrange(points, x):
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

    testPointsX, testPointsY = generatePoints()
    for i in range(0,len(testPointsX)):
        testPointsY[i] = round(Lagrange(points1, testPointsX[i]),3)
    draw(points1, testPointsX, testPointsY, 'Lagrange' + str(num), int(num))    

    testPointsX, testPointsY = generatePoints()
    for i in range(0,len(testPointsX)):
        testPointsY[i] = round(NewtonDividedDifference(points1, table1, testPointsX[i]),3)
    draw(points1, testPointsX, testPointsY, 'NewtonDividedDifference' + str(num), int(num))

    testPointsX, testPointsY = generatePoints()
    for i in range(0,len(testPointsX)):
        testPointsY[i] = round(GrogoryNewtonForward(points2, table2, testPointsX[i]),3)
    draw(points1, testPointsX, testPointsY, 'GrogoryNewtonForward' + str(num), int(num))

    testPointsX, testPointsY = generatePoints()
    for i in range(0,len(testPointsX)):
        testPointsY[i] = round(GrogoryNewtonBackward(points2, table2, testPointsX[i]),3)
    draw(points1, testPointsX, testPointsY, 'GrogoryNewtonBackward' + str(num), int(num))

    testPointsX, testPointsY = generatePoints()
    for i in range(0,len(testPointsX)):
        testPointsY[i] = round(GaussForward(points2, table2, testPointsX[i]),3)
    draw(points1, testPointsX, testPointsY, 'GaussForward' + str(num), int(num))

    testPointsX, testPointsY = generatePoints()
    for i in range(0,len(testPointsX)):
        testPointsY[i] = round(GaussBackward(points2, table2, testPointsX[i]),3)
    draw(points1, testPointsX, testPointsY, 'GaussBackward' + str(num), int(num))


    # for item in points1:
    #     x, y = item
    #     print(Lagrange(points1, x), y)
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