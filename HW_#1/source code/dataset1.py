import numpy as np

def calc(w, p, b):
    w = np.reshape(w, (2, 2))
    p = np.reshape(p, (2, 1))
    b = np.reshape(b, (2, 1))
    res = np.dot(w, p)
    a = []
    for row in res:
        for i in row:
            if i <= 0:
                a.append(0)
            else:
                a.append(1)
    return a


def training(trainingData):
    w = np.reshape([1, 0, 0, 1], (2, 2))
    b = np.reshape([1,1], (2, 1))
    time = 1
    while 1:
        ok = 1
        for data in trainingData:
            p = data[0]
            t = data[1]
            a = calc(w, p, b)
            if a == t:
                continue
            ok = 0
            e = np.reshape(t, (2, 1)) - np.reshape(a, (2, 1))
            w = w + e * np.reshape(p, (1, 2))
            b = b + e
        if ok == 1:
            break
        time += 1
    return w, b

def testData(w, b):
    file = open('testing_data1.txt', 'r', encoding='UTF-8')
    data = file.readlines()
    for line in data:
        p1, p2 = line.replace('\n', '').split()
        p = [int(p1), int(p2)]
        a = np.reshape(calc(w, p, b), (2, 1))
        print(a)

def main():
    file = open('training_data1.txt', 'r', encoding='UTF-8')
    data = file.readlines()
    trainingData = []

    for line in data:
        p1, p2, t1, t2 = line.replace('\n', '').split(' ')
        trainingData.append([[int(p1), int(p2)], [int(t1), int(t2)]])
    # print(trainingData)
    w, b = training(trainingData)
    print(w)
    print(b)
    testData(w, b)

if __name__ == "__main__":
    main()