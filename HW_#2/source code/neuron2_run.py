import math
import numpy as np

def readData(filename):
    file = open(filename, 'r')
    lines = file.readlines()
    
    trainingData = []

    for line in lines:
        sl, sh, pl, ph, label = line.split(' ')
        t = []
        label = label.replace('\n', '')
        if label == 'setosa':
            t = [0.9, 0.1, 0.1]
        elif label == 'versicolor':
            t = [0.1, 0.9, 0.1]
        else:
            t = [0.1, 0.1, 0.9]
        trainingData.append([[float(sl), float(sh), float(pl), float(ph)], t])

    return trainingData

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
    numOfInput  = 4
    numOfOutput = 3
    numOfNeroun = 2
    epoch = 1
    w1 = np.reshape([0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1], (numOfNeroun, numOfInput))
    b1 = np.reshape([0.1, 0.1], (numOfNeroun, 1))
    w2 = np.reshape([0.1, 0.1, 0.1, 0.1, 0.1, 0.1], (numOfOutput, numOfNeroun))
    b2 = np.reshape([0.1, 0.1, 0.1], (numOfOutput, 1))
    while 1:
        for data in trainingData:
            p = np.reshape(data[0], (numOfInput, 1))
            t = np.reshape(data[1], (numOfOutput, 1))
            ah1 = np.reshape(f(w1, p, b1), (numOfNeroun, 1))
            o = np.reshape(f(w2, ah1, b2), (numOfOutput, 1))
            d2 = (t - o) * np.reshape(activation(o), (numOfOutput, 1))
            d1 = np.dot(np.reshape(w2, (numOfNeroun, numOfOutput)), d2) * np.reshape(activation(ah1), (numOfNeroun, 1))

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

def testData(testingData, w1, b1, w2, b2):
    numOfInput = 4
    numOfOutput = 3
    numOfNeroun = 2
    accuracies = 0.0
    sz = 0
    for data in testingData:
        sz += 1
        p = np.reshape(data[0], (numOfInput, 1))
        t = np.reshape(data[1], (numOfOutput, 1))
        ah1 = np.reshape(f(w1, p, b1), (numOfNeroun, 1))
        o = np.reshape(f(w2, ah1, b2), (numOfOutput, 1))

        d = (1 - abs(o - t)) * 10 / 9
        accuracies += sum(d)

    return accuracies[0] / (sz * 3) * 100


def main():
    trainingData = readData('iris_training_data.txt')
    testingData = readData('iris_testing_data.txt')
    alpha = 0.1
    file = open('neuron2_run.txt', 'w', encoding='UTF-8')
    for i in range(0, 20):
        w1, b1, w2, b2, epoch = training(trainingData, alpha)
        file.write('Number of hidden neurons = 2\n')
        file.write('Learning rates = ' + '%.1f'%(alpha))
        file.write('training accuracies = ' + '%.2f'%(testData(trainingData, w1, b1, w2, b2)) + '%\n')
        file.write('testing  accuracies = ' + '%.2f'%(testData(testingData,  w1, b1, w2, b2)) + '%\n')
        file.write('epochs = ' + str(epoch) + '\n\n')
        alpha += 0.1

if __name__ == '__main__':
    main()