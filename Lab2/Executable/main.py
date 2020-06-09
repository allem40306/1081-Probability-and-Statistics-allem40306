import math
import numpy as np

def readRandomList():
    file = open('randomList.txt', 'r', encoding="utf-8")
    lines = file.readlines()

    randomList = []
    for line in lines:
        item = line.split(' ')
        item = item[0].replace('\n', '')
        randomList.append(int(item))
    
    return randomList   

def readData(filename, trainNum):
    file = open(filename, 'r', encoding="utf-8")
    lines = file.readlines()
    
    trainingData = []
    testingData = []
    randomList = readRandomList()
    cnt = 0

    for line in lines:
        sl, sh, pl, ph, label = line.split(' ')
        t = []
        label = label.replace('\n', '')
        if label == 'Iris-setosa':
            t = [1, 0, 0]
        elif label == 'Iris-versicolor':
            t = [0, 1, 0]
        else:
            t = [0, 0, 1]
        
        if randomList.index(cnt % 50) < int(trainNum):
            trainingData.append([[float(sl), float(sh), float(pl), float(ph)], t])
        else:
            testingData.append([[float(sl), float(sh), float(pl), float(ph)], t])
        cnt += 1

    return trainingData,testingData

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

def training(trainingData, alpha, numOfInput, numOfOutput, numOfNeroun):
    epoch = 1
    w1 = np.reshape([0.1 for i in range (0, numOfNeroun * numOfInput)], (numOfNeroun, numOfInput))
    b1 = np.reshape([0.1 for i in range (0, numOfNeroun)], (numOfNeroun, 1))
    w2 = np.reshape([0.1 for i in range (0, numOfOutput * numOfNeroun)], (numOfOutput, numOfNeroun))
    b2 = np.reshape([0.1 for i in range (0, numOfOutput)], (numOfOutput, 1))
    print(w1)
    print(b1)
    print(w2)
    print(b2)
    while 1:
        for data in trainingData:
            p = np.reshape(data[0], (numOfInput, 1))
            t = np.reshape(data[1], (numOfOutput, 1))
            ah1 = np.reshape(f(w1, p, b1), (numOfNeroun, 1))
            o = np.reshape(f(w2, ah1, b2), (numOfOutput, 1))
            d2 = (t - o) * np.reshape(activation(o), (numOfOutput, 1))
            d1 = np.dot(w2.T, d2) * np.reshape(activation(ah1), (numOfNeroun, 1))

            w2 += 2 * alpha * np.dot(d2, np.reshape(ah1, (1, numOfNeroun)))
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

    return w1, b1, w2, b2, epoch

def maxClass(p):
    ans = 0
    for i in range(0, len(p)):
        if p[i] > p[ans]:
            ans = i
    return ans

def testData(testingData, w1, b1, w2, b2, numOfInput, numOfOutput, numOfNeroun):
    accuracies = 0
    sz = 0
    for data in testingData:
        sz += 1
        p = np.reshape(data[0], (numOfInput, 1))
        t = np.reshape(data[1], (numOfOutput, 1))
        ah1 = np.reshape(f(w1, p, b1), (numOfNeroun, 1))
        o = np.reshape(f(w2, ah1, b2), (numOfOutput, 1))

        if maxClass(o) == maxClass(t):
            accuracies += 1
    return (accuracies / sz) * 100.0


def main():
    trainNum = int(input())
    numOfNeroun = int(input())
    print(trainNum, numOfNeroun)
    trainingData, testingData = readData('iris.txt', trainNum)
    file = open('result.txt', 'w', encoding='UTF-8')
    file.write('Number of hidden neurons = ' + str(numOfNeroun) + '\n')
    file.write('Training Data ' + str(trainNum * 2) + '%\n')
    for alpha in (0.1, 0.2, 0.3, 0.4, 0.5):
        w1, b1, w2, b2, epoch = training(trainingData, alpha, 4, 3, numOfNeroun)
        file.write('Learning rates = ' + '%.1f'%(alpha) + '\n')
        file.write('training accuracies = ' + '%.2f'%(testData(trainingData, w1, b1, w2, b2, 4, 3, numOfNeroun)) + '%\n')
        file.write('testing  accuracies = ' + '%.2f'%(testData(testingData,  w1, b1, w2, b2, 4, 3, numOfNeroun)) + '%\n')
        file.write('epochs = ' + str(epoch) + '\n\n')

if __name__ == '__main__':
    main()