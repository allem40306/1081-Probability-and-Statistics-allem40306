import sys
import math
import numpy as np
import cvxopt
import time

def readData():
    file = open('data.in', 'r', encoding="utf-8")
    lines = file.readlines()

    data_X = []
    data_Y = []

    for line in lines:
        line = line.replace('\n','').split(' ')
        for i in range(len(line)):
            line[i] = float(line[i])
        data_X.append(line[:-1])
        data_Y.append(line[-1])

    return np.array(data_X), np.array(data_Y)

def hard_limit(data_X, data_Y):
    num, dim = data_X.shape
    print(num, dim)
    K = np.multiply(data_Y[:, None], data_X)
    K = np.dot(K, K.T)
    P = cvxopt.matrix(K)
    q = cvxopt.matrix(-np.ones((num, 1)))
    G = cvxopt.matrix(-np.eye(num))
    h = cvxopt.matrix(np.zeros(num))
    A = cvxopt.matrix(data_Y.reshape(1, -1))
    b = cvxopt.matrix(np.zeros(1))
    cvxopt.solvers.options['show_progress'] = False
    sol = cvxopt.solvers.qp(P, q, G, h, A, b)
    alphas = np.array(sol['x'])
    # print(alphas)
    return alphas

def soft_limit(data_X, data_Y):
    num, dim = data_X.shape
    print(num, dim)
    K = np.multiply(data_Y[:, None], data_X)
    K = np.dot(K, K.T)
    P = cvxopt.matrix(K)
    q = cvxopt.matrix(-np.ones((num, 1)))
    G = cvxopt.matrix(np.vstack((np.eye(num)*-1,np.eye(num))))
    h = cvxopt.matrix(np.hstack((np.zeros(num), np.ones(num) * 500)))
    A = cvxopt.matrix(data_Y.reshape(1, -1))
    b = cvxopt.matrix(np.zeros(1))
    cvxopt.solvers.options['show_progress'] = False
    sol = cvxopt.solvers.qp(P, q, G, h, A, b)
    alphas = np.array(sol['x'])
    # print(alphas)
    return alphas

def getWeightandBias(data_X, data_Y, alpha):
    w = np.sum(alpha * data_Y[:, None] * data_X, axis=0)

    cond = (alpha > 1e-4).reshape(-1)
    b = data_Y[cond] - np.dot(data_X[cond], w)
    bias = b[0]

    norm = np.linalg.norm(w)
    w, bias = w / norm, bias / norm
    
    return w, bias

def test(data_X, data_Y, w, b):
    ok = 0
    fail = 0
    for i in range(len(data_X)):
        res = np.dot(w, data_X[i]) + b
        if res > 1e-4:
            res = 1.
        else:
            res = -1
        if math.fabs(res - data_Y[i]) < 1e-4:
            ok += 1
        else:
            fail += 1
        
    print(ok, fail) 
    print(ok/(ok + fail))

def main():
    data_X, data_Y = readData()
    Start = time.time()
    alpha = soft_limit(data_X, data_Y)
    w,b = getWeightandBias(data_X, data_Y, alpha)
    End = time.time()
    print(Start)
    print(End)
    print(End - Start)
    print(w)
    test(data_X, data_Y, w, b)

if __name__ == '__main__':
    np.set_printoptions(threshold=sys.maxsize)
    main()