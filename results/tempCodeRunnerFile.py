coeficientes = np.polyfit (x, y_ori, 3)
# pol1 = np.poly1d(coeficientes)
# y_cubic = coeficientes[0]*x**3 + coeficientes[1]*x**2  + coeficientes[2]*x + coeficientes[3]
# pl.plot(x, y_cubic, ms=6, label='Cubica')