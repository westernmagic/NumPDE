#!/usr/bin/env python2
import mpl_toolkits.mplot3d
from numpy import *
from pylab import *
from matplotlib import cm, colors

u = loadtxt("u_fd.txt")
N = int(sqrt(u.shape[0]))
print("N=%d" % N)
u.shape = (N,N)

fig = figure()
ax = fig.gca(projection="3d")
x,y = mgrid[0:1:N*1j, 0:1:N*1j]
norm = colors.Normalize()
ax.plot_surface(x,y,u, facecolors = cm.viridis(norm(u)))
m = cm.ScalarMappable(cmap = cm.viridis)
m.set_array(u)
fig.colorbar(m)
show()

#pcolormesh(x,y,u)
#colorbar()
#show()

plot(x[:, 50], u[:, 50], '-*', label='$U_{i,50}$')
plot(x[:,50], sin(2*pi*y[:,50])*sin(2*pi*x[:,50]), '--',label='exact')
legend()
show()
