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
soleil = False
terre = False
halley = False
jupiter = False

i = 0
line = file.readline()
while line:
    print(line)
    if (i%4==0):
        if (int(line) == 1):
            soleil = True
            terre = False
            halley = False
            jupiter = False
        elif (int(line) == 2):
            soleil = False
            terre = True
            halley = False
            jupiter = False
        elif (int(line) == 3):
            soleil = False
            terre = False
            halley = False
            jupiter = True
        else:
            soleil = False
            terre = False
            halley = True
            jupiter = False
    else:
        if (soleil):
            if (i%2 == 1 and i%4 !=3):
                abs1.append(float(line))
            elif (i%2 == 0 and i%4 !=3):
                ord1.append(float(line))
        elif (terre):
            if (i%2 == 1 and i%4 !=3):
                abs2.append(float(line))
            elif (i%2 == 0 and i%4 !=3):
                ord2.append(float(line))
        elif (halley):
            if (i%2 == 1 and i%4 !=3):
                abs4.append(float(line))
            elif (i%2 == 0 and i%4 !=3):
                ord4.append(float(line))
        else:
            if (i%2 == 1 and i%4 !=3):
                abs3.append(float(line))
            elif (i%2 == 0 and i%4 !=3):
                ord3.append(float(line))
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