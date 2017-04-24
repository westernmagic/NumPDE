from numpy import *
import matplotlib
import matplotlib.pyplot as plt
import sys

u = loadtxt(sys.argv[1])

Theta = radians(linspace(0, 360, 20))
R = linspace(0, 1, len(u))
r, theta = meshgrid(R, Theta)

plt.plot(R, u)
plt.show()

uPolar = array([u for k in range(len(Theta))])
fig, ax = plt.subplots(subplot_kw=dict(projection='polar'))
p = ax.pcolormesh(theta, r, uPolar)
fig.colorbar(p, ax=ax)
plt.show()

