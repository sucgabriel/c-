import matplotlib.pyplot as plt

# Ouvrir le fichier en lecture seule
file = open('fig.txt', "r")
# utilisez readline() pour lire la première ligne
abs =[]
ord = []

i = 0
line = file.readline()
while line:
    print(line);
    if (i%2==0):
        abs.append(float(line))
    else :
        ord.append(float(line))
    i = i+1
    # utilisez readline() pour lire la ligne suivante
    line = file.readline()

plt.plot(abs,ord)
plt.show()
file.close()