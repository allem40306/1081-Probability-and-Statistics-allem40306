import numpy as np

def training(trainingData):
    pass

def main():
    file = open('training_data.txt', 'r', encoding='UTF-8')
    data = file.readlines()
    trainingData = []

    for line in data:
        shape, texture, weight, kind = line.split(' ')
        tmp = []
        # print(kind[0:1])
        if kind[0:1] == "W":
            tmp = [0, 1]
        elif kind[0:1] == "P":
            tmp = [1, 0]
        elif kind[0:1] == "B":
            tmp = [0, 0]
        elif kind[0:1] == "O":
            tmp = [1, 1]
        trainingData.append([float(shape), float(texture), float(weight), tmp])
    res = training(trainingData)

if __name__ == "__main__":
    main()