import matplotlib.pyplot as plt

# Ouvrir le fichier en lecture seule
file = open('res.txt', "r")
# utilisez readline() pour lire la première ligne
abs1 =[]
ord1 = []
abs2 =[]
ord2 = []
abs3 =[]
ord3 = []
abs4 =[]
ord4 = []
i = 0
line = file.readline()
while line:
    print(line)
    if (i%3==0):
        if(i%12==0):
            abs1.append(float(line))
        elif(i%12==3):
            abs2.append(float(line))
        elif(i%12==6):
            abs3.append(float(line))
        elif(i%12==9):
            abs4.append(float(line))
    elif (i%3==1):
        if(i%12==1):
            ord1.append(float(line))
        elif(i%12==4):
            ord2.append(float(line))
        elif(i%12==7):
            ord3.append(float(line))
        elif(i%12==10):
            ord4.append(float(line))
    i = i+1
    # utilisez readline() pour lire la ligne suivante
    line = file.readline()
print(abs1)
print(ord1)
plt.scatter(abs1,ord1)
plt.scatter(abs2,ord2)
plt.scatter(abs3,ord3)
plt.scatter(abs4,ord4)
plt.show()
file.close()