file = open('voicegender.txt', 'r', encoding="utf-8")
lines = file.readlines()

for line in lines:
    item = line.split(',')
    if item[20][1] == 'm':
        item[20] = -1.
    else:
        item[20] = 1.
    print(*item)
