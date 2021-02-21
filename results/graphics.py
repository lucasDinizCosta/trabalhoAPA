import matplotlib.pyplot as plt
import pandas as pd

plt.style.use('bmh')


recursive = pd.read_csv('C:/Git/Trabalho de APA/trabalhoAPA/results/recursive.csv', ';')

dynamic = pd.read_csv('C:/Git/Trabalho de APA/trabalhoAPA/results/dynamic.csv', ';')

x = recursive['instanceSize']
y = recursive['avgTime']

plt.title('Algoritmo Recursivo: Tamanho da Instância x Tempo Gasto')
plt.xlabel("Tamanho da Instância", fontsize=18)
plt.ylabel('Média de Tempo Gasto (segundos)', fontsize=16)

# Limits for the Y axis
# plt.ylim(0, 800)

plt.plot(x, y, color = (0.9,0.2,0.2,0.8))

plt.show()