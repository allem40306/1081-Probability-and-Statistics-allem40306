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


def draw(points1, points2):
    plt.figure('Draw')
    plt.plot([points2[i][0] for i in range(0,len(points2))],
            [points2[i][1] for i in range(0,len(points2))], 'y')
    plt.plot([points1[i][0] for i in range(0,len(points1))],
            [points1[i][1] for i in range(0,len(points1))], 'ro')
    plt.draw()
    plt.savefig('ans.png')
    plt.close()

def main():
	point1 = readPoints('test.in')
	point2 = readPoints('test.out')
	draw(point1, point2)

if __name__ == "__main__":
    main()