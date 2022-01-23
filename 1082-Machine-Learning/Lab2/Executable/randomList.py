import random

file = open('randomList.txt', 'w', encoding='UTF-8')

randomlist = random.sample(range(0, 50), 50)
for item in randomlist:
    file.write(str(item) + '\n')