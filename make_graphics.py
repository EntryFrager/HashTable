import matplotlib.pyplot as plt
import csv
import sys

X = []
Y = []

with open(sys.argv[1], 'r') as file:
    plotting = csv.reader(file, delimiter=';')

    for ROWS in plotting:
        X.append(float(ROWS[0]))
        Y.append(float(ROWS[1]))

plt.bar(X, Y)
plt.title(sys.argv[2])
plt.xlabel('Ячейки хэш-таблицы')
plt.ylabel('Количество коллизий')

file_name_png = sys.argv[1][:-3] + 'png'

plt.savefig(file_name_png)

