import cv2
import math
# from matplotlib import pyplot as plt
import numpy as np

class ImageThreshold():
    def __init__(self,img_name,threshold):
        self.img1 = cv2.imread(img_name)
        self.img2 = self.img1
        self.threshold = list(reversed(threshold))

    
    def Psnr(self):
        mse = np.mean((self.img1/1.0)-(self.img2/1.0))
        if mse < 1.0e-10:
            return 100
        return 10 * math.log10(255.0**2/mse)

    def Run(self):
        for i in range(1,len(self.threshold)):
            ret, self.img2 = cv2.threshold(self.img2, self.threshold[i - 1], 255, cv2.THRESH_TRUNC)
        # plt.imsave('res.png', self.img2, cmap='gray')
        return self.Psnr()
