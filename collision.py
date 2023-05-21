import matplotlib.pyplot as plt
import sys 


# Ouvrir le fichier en lecture seule
file = open(sys.argv[1], "r")
# utilisez readline() pour lire la première ligne
xcube =[]
ycube = []
xrec =[]
yrec = []
incube = False
i = 0
line = file.readline()
while line:
    if (i%4 == 0):
        if( (int(line) <1600)):
            incube = True
        else:
            incube = False
    elif (i%4 == 1):
        if(incube):
            xcube.append(float(line))
        else:
            xrec.append(float(line))
    elif (i%4 == 2):
        if (incube):
            ycube.append(float(line))
        else:
            yrec.append(float(line))
    i = i+1
    line = file.readline()

plt.scatter(xcube,ycube, c='r')
plt.scatter(xrec,yrec, c='b')

plt.show()
file.close()