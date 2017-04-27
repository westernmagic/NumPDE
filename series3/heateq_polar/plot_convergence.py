from numpy import *
import matplotlib
import matplotlib.pyplot as plt

errors = loadtxt('errors.txt')
resolutions = loadtxt('resolutions.txt')

poly = polyfit(log(errors),log(resolutions),1)

plt.loglog(resolutions, errors, '-o', label='error')
plt.loglog(resolutions, exp(poly[1])*resolutions**poly[0], '--', label='$\\mathcal{O}(N^{%.2f})$' % poly[0])
plt.legend()
plt.xlabel('resolution $N$')
plt.ylabel('$||\\cdot||_\\infty$')
plt.grid(True)
plt.show()
