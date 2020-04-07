import math
import numpy as np
import matplotlib.pyplot as plt

def f(w, p, b):
    res = np.dot(w, p) + b
    # log sigmoid
    a = []
    for row in res:
        for item in row:
            a.append(1. / (1 + np.exp(-item)))
    return a

def activation(p):
    a = []
    for row in p:
        for item in row:
            a.append(item * (1. - item))
    return a

def training(trainingData, alpha):
    numOfInput  = 2
    numOfOutput = 1
    numOfNeroun = 1
    epoch = 1
    w1 = np.reshape([0.1, 0.1], (numOfNeroun, numOfInput))
    b1 = np.reshape([0.1], (numOfNeroun, 1))
    w2 = np.reshape([0.1], (numOfOutput, numOfNeroun))
    b2 = np.reshape([0.1], (numOfOutput, 1))
    while 1:
        for data in trainingData:
            p = np.reshape(data[0], (numOfInput, 1))
            t = np.reshape(data[1], (numOfOutput, 1))
            ah1 = np.reshape(f(w1, p, b1), (numOfNeroun, 1))
            o = np.reshape(f(w2, ah1, b2), (numOfOutput, 1))
            d2 = (t - o) * np.reshape(activation(o), (numOfOutput, 1))
            d1 = np.dot(w2.T, d2) * np.reshape(activation(ah1), (numOfNeroun, 1))

            w2 += 2 * alpha * np.dot(d2, ah1)
            b2 += 2 * alpha * d2
            w1 += 2 * alpha * np.dot(d1, np.reshape(p, (1,numOfInput)))
            b1 += 2 * alpha * d1
        
        # mean absolute error
        totalError = 0.0
        for data in trainingData:
            p = np.reshape(data[0], (numOfInput, 1))
            t = np.reshape(data[1], (numOfOutput, 1))
            ah1 = np.reshape(f(w1, p, b1), (numOfNeroun, 1))
            o = np.reshape(f(w2, ah1, b2), (numOfOutput, 1))
            totalError += abs((t - o))

        if epoch == 1000 or max(totalError) / 120 < 0.28:
            break
        epoch += 1

    return w1, b1, epoch

def draw(trainingData, a, b, c, picName):
    px1 = []
    py1 = []
    px2 = []
    py2 = []
    for data in trainingData:
        x = data[0][0]
        y = data[0][1]
        t = data[1][0]
        if t == 1:
            px1.append(x)
            py1.append(y)
        else:
            px2.append(x)
            py2.append(y)
            
    zoom = max(max(px1,key=abs), max(px2,key=abs),max(py1,key=abs), max(py2,key=abs))
    zoom = zoom + 5
    plt.figure('Draw')
    plt.plot(px1, py1, 'ro')
    plt.plot(px2, py2, 'bo')
    #ax+by+c=0 y = -(ax+c)/b (-c/a,0) (0,-c/b) (c/a, -2c/b)
    linex = [-zoom,-c/a,0,zoom]
    liney = [-(-zoom*a+c)/b,0,-c/b,-(zoom*a+c)/b]
    plt.plot(linex, liney, 'y')
    plt.title(str(a)+'x+'+str(b)+'y+'+str(c)+'=0')
    plt.draw()
    plt.pause(1)
    plt.savefig('sdga_' + picName + '.png')
    plt.close()

def main():
    num = input("choose dataset [1~4]: ")
    dataName = 'dataset' + num
    file = open(dataName + '.txt', 'r', encoding='UTF-8')
    data = file.readlines()
    trainingData = []

    for line in data:
        p1, p2, t = line.replace('\n', '').split(',')
        trainingData.append([[int(p1), int(p2)], [int(t)]])

    for alpha in (0.1, 0.2, 0.3, 0.4, 0.5):
        w1, b1, epoch = training(trainingData, alpha)
        print('Number of hidden neurons = 1')
        print('Learning rates = ' + '%.1f'%(alpha))
        print('epochs = ' + str(epoch))
        print('The weight:' + str(w1))
        print('The bias:' + str(b1) + '\n')
        draw(trainingData, w1[0][0], w1[0][1], b1[0][0], dataName+'_'+str(alpha))

if __name__ == '__main__':
    main()