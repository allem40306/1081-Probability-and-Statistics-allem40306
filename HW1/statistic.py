import matplotlib.pyplot as plt

def count(a):
    num = []
    total = []
    for i in range(140, 180 + 1):
        num.append(str(i))
        total.append(a.count(i))
    return num, total

fi = open("testdata.in", "r")
lines = fi.readlines()
a = []

for line in lines:
    x = line.replace('\n', '')
    x = int(x)
    a.append(x)

num, total = count(a)

plt.bar(num, total, label = 'count')
plt.savefig('tot_count.png')
