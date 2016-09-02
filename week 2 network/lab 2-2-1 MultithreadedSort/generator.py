import random

f = open("input.txt", "w")
for i in range(100000000):
    f.write(str(random.randrange(2147483648)) + "\n")

f.close()
