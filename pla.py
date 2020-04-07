import numpy as np
import matplotlib.pyplot as plt

# return a = f(w, p, b) = wp + b
def f(w, p, b):
    w = np.reshape(w, (1, 2))
    p = np.reshape(p, (2, 1))
    b = np.reshape(b, (1, 1))
    res = np.dot(w, p) + b
    a = []
    # hardLimit
    for row in res:
        for i in row:
            if i <= 0:
                a.append(-1)
            else:
                a.append(1)
    return a

# training the weight w and bias b based on training data
def training(w, b, trainingData):
    epoch = 1
    isFind = 0 # isFind = 1 mean find proper w and b that can classify testing_data
    while 1:
        ok = 1 # ok = 1 mean w and b don't change in one epoch
        for data in trainingData:
            p = data[0] # 2*1
            t = data[1] # 1
            a = f(w, p, b)
            if a == t:
                continue
            ok = 0
            e = np.reshape(t, (1, 1)) - np.reshape(a, (1, 1))
            w = w + e * np.reshape(p, (1, 2))
            b = b + e
        if ok == 1:
            isFind = 1
            break
        if epoch == 1000:
            break
        epoch += 1
    return w, b, epoch, isFind

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
    plt.draw()
    plt.pause(3)
    plt.savefig('plc_' + picName + '.png')
    plt.close()



def main():
    dataName = 'dataset1'
    file = open(dataName + '.txt', 'r', encoding='UTF-8')
    data = file.readlines()
    trainingData = []

    for line in data:
        p1, p2, t = line.replace('\n', '').split(',')
        trainingData.append([[int(p1), int(p2)], [int(t)]])
    initial_w = np.reshape([1, 0], (1, 2))
    initial_b = np.reshape([1], (1, 1))
    w, b, epoch, isFind = training(initial_w, initial_b, trainingData)

    print('The initial weight' + '\n' + str(initial_w) + '\n')
    print('The initial bias' + '\n' + str(initial_b) + '\n')
    if isFind == 1:
        print('Find proper w and b. The num of epoch: ' + str(epoch) + '\n')
    else:
        print('Not Find proper w and b. The maxiunm num of epoch: ' + str(epoch) + '\n')
    print('The weight:\n' + str(w) + '\n')
    print('The bias:\n' + str(b) + '\n')
    draw(trainingData, w[0][0], w[0][1], b[0], dataName)

if __name__ == "__main__":
    main()