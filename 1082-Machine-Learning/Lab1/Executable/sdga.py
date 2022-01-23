import numpy as np
import matplotlib.pyplot as plt

# training the weight w and bias b based on training data
def training(w, trainingData, alpha):
    epoch = 1
    isFind = 0 # isFind = 1 mean find proper w and b that can classify testing_data
    old = 0
    while 1:
        for data in trainingData:
            p = data[0] # 3*1
            t = data[1] # 1
            a = np.dot(w,p)
            e = np.reshape(t, (1, 1)) - np.reshape(a, (1, 1))
            w = w + alpha * e * np.reshape(p, (1, 3))
        
        # mean absolute error
        totalError = 0.0
        sz = len(trainingData)
        for data in trainingData:
            p = data[0] # 3*1
            t = data[1] # 1
            a = np.dot(w, p)
            e = np.reshape(t, (1, 1)) - np.reshape(a, (1, 1))
            totalError += abs(e) ** 2

        if abs(old - totalError / sz) < 1e-8:
            isFind = 1
            break
        old = totalError / sz
        if epoch == 1000:
            break
        epoch += 1
    return w, epoch, isFind

def draw(trainingData, w, picName):
    c = w[0][0]
    a = w[0][1]
    b = w[0][2]
    px1 = []
    py1 = []
    px2 = []
    py2 = []
    for data in trainingData:
        x = data[0][1]
        y = data[0][2]
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



def main(num):
    dataName = 'dataset' + str(num)
    file = open(dataName + '.txt', 'r', encoding='UTF-8')
    data = file.readlines()
    trainingData = []

    for line in data:
        p1, p2, t = line.replace('\n', '').split(',')
        trainingData.append([[1, int(p1), int(p2)], [int(t)]])
    initial_w = np.reshape([0, 0, 0], (1, 3))
    w, epoch, isFind = training(initial_w, trainingData, 0.001)

    print('The initial weight: ' + str(initial_w))
    if isFind == 1:
        print('Find proper w and b. The num of epoch: ' + str(epoch))
    else:
        print('Not Find proper w and b. The maxiunm num of epoch: ' + str(epoch))
    print('The weight: ' + str(w))
    print()
    draw(trainingData, w, dataName)

if __name__ == "__main__":
    main(1)
    main(2)
    main(3)
    main(4)