import numpy as np
import pylab as pl
import pandas as pd

f = pd.read_csv("dynamic.csv", sep=';')
f2 = pd.read_csv("recursive.csv", sep=';')

x = f2['instanceSize']
y_ori = f2['avgTime']


#interpolation functions
coeficientes = np.polyfit (x, y_ori, 1)
pol1 = np.poly1d(coeficientes)
y_lin =   coeficientes[0]*x + coeficientes[1]
pl.plot(x, y_lin, ms=6, label='Linear')

coeficientes = np.polyfit (x, y_ori, 2)
pol1 = np.poly1d(coeficientes)
y_quad = coeficientes[0]*x**2  + coeficientes[1]*x + coeficientes[2]
pl.plot(x, y_quad, ms=6, label='Quad')

coeficientes = np.polyfit (x, y_ori, 3)
pol1 = np.poly1d(coeficientes)
y_cubic = coeficientes[0]*x**3 + coeficientes[1]*x**2  + coeficientes[2]*x + coeficientes[3]
pl.plot(x, y_cubic, ms=6, label='Cubica')
 
coeficientes = np.polyfit (x, np.log(y_ori), 1, w=np.sqrt(y_ori))
pol1 = np.poly1d(coeficientes)
y_exp = (np.exp(1)**coeficientes[1])*(np.exp(1)**(coeficientes[0]*x))
pl.plot(x, y_exp, ms=6, label='Exp', color='purple')

pl.xlim(x.min(), x.max())

pl.ylabel("Média de Tempo Gasto (segundos)")
pl.xlabel("Tamanho da instância")
pl.title("Algoritmo Recursivo: Tamanho da Instância x Tempo de Execução")
pl.plot(x, y_ori,'o',ms=6, label='Medições', color='red')
pl.legend()
pl.show()