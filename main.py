from FireflyAlgorithm import *
from ImageThreshold import *

images = ['bird','bird2','cameraman','canoe','coins']#,'dog','goldhill','lena','office','onion','pepper']
num_of_run = 30

for image_name in images:
    for num_of_threshold in range(2,4):
        file = open(image_name + '_' + str(num_of_threshold) + '.txt', 'w')
        sum_fitness = 0.0
        sum_time = 0.0
        sum_psnr = 0.0
        best_fitness = 0.0
        best_threshold = None
        best_psnr = 0.0

        for run in range(num_of_run):
            print(image_name, num_of_threshold,run)
            Algorithm = FireflyAlgorithm(D=num_of_threshold, NP=50, ML=100, alpha=0.01, beta0=1, gamma=1.0, img_name=image_name+'.png')
            [threshold, fitness, used_time] = Algorithm.Run()
            Psnr = ImageThreshold(image_name+'.png',threshold)
            psnr = Psnr.Run()

            sum_fitness += fitness
            sum_time += used_time
            sum_psnr += psnr

            if fitness > best_fitness:
                best_fitness = fitness
                best_threshold = threshold
                best_psnr = psnr

        file.write('avg: ' + str(sum_fitness/float(num_of_run)) + ',' + str(sum_time/float(num_of_run)) + ',' + str(sum_psnr/float(num_of_run)) + '\n')
        file.write('best: ' + str(best_fitness) + ',' + str(best_threshold) + ',' + str(best_psnr) + '\n')
        


