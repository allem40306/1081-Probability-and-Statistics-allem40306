import random
import math
import cv2
import time

class FireflyAlgorithm():
    def __init__(self, D, NP, ML, alpha, beta0, gamma, img_name):
        self.D = D  # dimension of the problem
        self.NP = NP  # population size
        self.ML = ML # Maximum iteration number
        self.alpha = alpha
        self.beta0 = beta0
        self.gamma = gamma
        self.Fireflies = [[0 for i in range(self.D)]
                          for j in range(self.NP)]  # firefly agents
        self.Fireflies_tmp = [[0 for i in range(self.D)] for j in range(self.NP)]  # intermediate pop
        # self.I = [0.0] * self.NP  # light intensity
        self.Fitness = [0.0] * self.NP  # fitness values
        self.evaluations = 0
        self.img_name = img_name
        self.hist = None

    def read_image(self): # read image and get histogram
        img = cv2.imread(self.img_name)
        self.hist = cv2.calcHist([img], [0], None, [256], [0, 256])

    def cal_fitness(self,idx): # calculate fitness based on Maximum entropy thresholding algorithm
        a = [0]
        for i in range(len(self.Fireflies[idx])):
            a.append(math.floor(self.Fireflies[idx][i]))
        a.append(255)
        for i in range(1,len(a)):
            sum = 0.0
            h = 0.0
            for j in range(a[i-1],a[i]):
                sum = sum + self.hist[j] 
            if sum - 0.0 < 1e-6:
                continue 
            for j in range(a[i-1],a[i]):
                if self.hist[j]/sum - 0.0 < 1e-6:
                    continue 
                # print("here", self.hist[j]/sum)
                h = h + (self.hist[j]/sum) * math.log(self.hist[j]/sum)
        return -h

    def init_ffa(self): # initialize fireflies
        for i in range(self.NP):
            for j in range(self.D):
                self.Fireflies[i][j] = random.uniform(0, 1) * (256.0/float(self.D+1)) + (256.0/float(self.D+1)) * float(j)
            self.Fireflies[i] = sorted(self.Fireflies[i])
            self.Fitness[i] = self.cal_fitness(i)  # initialize attractiveness
    
    def replace_ffa(self):  # copy original population to a temporary area
        for i in range(self.NP):
            for j in range(self.D):
                self.Fireflies_tmp[i][j] = self.Fireflies[i][j]

    def get_distance(self,i,j):
        dis = 0
        for k in range(self.D):
            dis = dis + abs(self.Fireflies[i][k]-self.Fireflies[j][k])
        return dis

    def move_ffa(self): # move all fireflies to better locations
        for i in range(1,self.NP):
            for j in range(1,self.NP):
                if i != j and self.Fitness[i] < self.Fitness[j]:
                    dis = self.get_distance(i,j)
                    beta = self.beta0 * math.exp(-self.gamma * dis)
                    for k in range(self.D):
                        u = self.alpha * (random.uniform(0, 1) - 0.5)
                        self.Fireflies[i][k] = self.Fireflies[i][k] * (1.0 - beta) + self.Fireflies_tmp[j][k] * beta + u

    def handle_limit(self):
        for i in range(1,self.NP):
            for j in range(1,self.D):
                if self.Fireflies[i][j] < 0:
                    self.Fireflies[i][j] = 0
                if self.Fireflies[i][j] > 255:
                    self.Fireflies[i][j] = 255


    def Run(self):
        self.read_image()
        
        used_time = time.time()
        
        self.init_ffa()
        self.evaluations = 0

        while self.evaluations < self.ML:
            # update best firefly
            mxIndex = 0
            for i in range(1,self.NP):
                if self.Fitness[i] > self.Fitness[mxIndex]:
                    mxIndex = i
            
            self.replace_ffa()
            self.move_ffa()
            self.handle_limit()
            
            # update best firefly
            for i in range(1,self.D):
                u = self.alpha * (random.uniform(0, 1) - 0.5)
                self.Fireflies[mxIndex][i] = self.Fireflies[mxIndex][i] + u
            
            # calculate fitness
            for i in range(1,self.NP):
                self.Fireflies[i] = sorted(self.Fireflies[i])
                self.Fitness[i] = self.cal_fitness(i)
            
            self.evaluations = self.evaluations + 1
        
        used_time = time.time() - used_time

        return self.Fireflies[mxIndex], self.Fitness[mxIndex], used_time