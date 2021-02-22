import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

plt.style.use('bmh')


recursive = pd.read_csv('C:/Git/Trabalho de APA/trabalhoAPA/results/recursive.csv', ';')

dynamic = pd.read_csv('C:/Git/Trabalho de APA/trabalhoAPA/results/dynamic.csv', ';')

x = dynamic['instanceSize']
y = dynamic['avgTime']

# x2 = recursive['instanceSize']
# y2 = recursive['avgTime']

plt.title('Programação Dinâmica: Tamanho da Instância x Tempo Gasto')
plt.xlabel("Tamanho da Instância", fontsize=18)
plt.ylabel('Média de Tempo Gasto (segundos)', fontsize=16)

# Limits for the X axis
plt.xlim(500, 5000)
plt.ylim(0, 350)

plt.plot(x, y, color = (0.9,0.2,0.2,0.8))

def f(x): return 0.2*x**3/500**3

# x = np.linspace(500, 5000, 500)
plt.plot(x, f(x))

# plt.plot(x2, y2, color = (0.2,0.7,0.9,0.8))

plt.show()