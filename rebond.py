import matplotlib.pyplot as plt
import sys 

file = open(sys.argv[1], "r")
abs =[]
ord = []

i = 0
line = file.readline()
while line:
    if (i%4==1):
        abs.append(float(line))
    else if (i%4 == 2):
        ord.append(float(line))
    i = i+1
    # utilisez readline() pour lire la ligne suivante
    line = file.readline()

plt.plot(abs,ord)
plt.show()
file.close()