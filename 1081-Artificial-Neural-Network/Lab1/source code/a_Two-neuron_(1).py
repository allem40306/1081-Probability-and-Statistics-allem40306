import numpy as np

# return a = f(w, p, b) = wp + b
def f(w, p, b):
    w = np.reshape(w, (2, 2))
    p = np.reshape(p, (2, 1))
    b = np.reshape(b, (2, 1))
    res = np.dot(w, p) + b
    a = []
    # hardLimit
    for row in res:
        for i in row:
            if i <= 0:
                a.append(0)
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
            p = data[0]
            t = data[1]
            a = f(w, p, b)
            if a == t:
                continue
            ok = 0
            e = np.reshape(t, (2, 1)) - np.reshape(a, (2, 1))
            w = w + e * np.reshape(p, (1, 2))
            b = b + e
        if ok == 1:
            isFind = 1
            break
        if epoch == 1000:
            break
        epoch += 1
    return w, b, epoch, isFind

# test the data  with weight w and bias b based on training data
def testData(initial_w, initial_b, isFind, epoch, w, b):
    file = open('testing_data1.txt', 'r', encoding='UTF-8')
    data = file.readlines()
    file.close()
    
    file = open('a_Two-neuron_(1).txt', 'w', encoding='UTF-8')
    file.write('The initial weight' + '\n' + str(initial_w) + '\n')
    file.write('The initial bias' + '\n' + str(initial_b) + '\n')
    if isFind == 1:
        file.write('Find proper w and b. The num of epoch: ' + str(epoch) + '\n')
    else:
        file.write('Not Find proper w and b. The maxiunm num of epoch: ' + str(epoch) + '\n')
    file.write('The weight:\n' + str(w) + '\n')
    file.write('The bias:\n' + str(b) + '\n')
    file.write('Prediction of test examples\n')

    for line in data:
        p1, p2 = line.replace('\n', '').split()
        p = [int(p1), int(p2)]
        a = np.reshape(f(w, p, b), (2, 1))
        file.write(str(a) + '\n')

def main():
    file = open('training_data1.txt', 'r', encoding='UTF-8')
    data = file.readlines()
    trainingData = []

    for line in data:
        p1, p2, c = line.replace('\n', '').split(' ') # c(atorgy)
        t = []
        if c[0:1] == 'A':
            t = [0, 0]
        elif c[0:1] == 'B':
            t = [0, 1]
        elif c[0:1] == 'C':
            t = [1, 0]
        elif c[0:1] == 'D':
            t = [1, 1]
        trainingData.append([[int(p1), int(p2)], t])
    initial_w = np.reshape([1, 0, 0, 1], (2, 2))
    initial_b = np.reshape([1, 1], (2, 1))
    w, b, epoch, isFind = training(initial_w, initial_b, trainingData)
    testData(initial_w, initial_b, isFind, epoch, w, b)

if __name__ == "__main__":
    main()