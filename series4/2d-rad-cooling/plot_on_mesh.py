from numpy import *
from pylab import *

import matplotlib.tri
from math import atan2


vertices = loadtxt("vertices.txt")
indices = loadtxt("triangles.txt")
uImplicit = loadtxt("u_implicit.txt")
energyImplicit = loadtxt("energy_implicit.txt")

uExplicitNoCfl = loadtxt("u_explicit_no_cfl.txt")
energyExplicitNoCfl = loadtxt("energy_explicit_no_cfl.txt")

uExplicitCfl = loadtxt("u_explicit_cfl.txt")
energyExplicitCfl = loadtxt("energy_explicit_cfl.txt")

print("using %d vertices" % len(vertices))

grid = matplotlib.tri.Triangulation( vertices[:,0], vertices[:,1], indices)

tripcolor(grid, uImplicit);
title('Implicit')
colorbar()
show()


tripcolor(grid, uExplicitNoCfl);
title('Explicit (No CFL)')
colorbar()
show()


tripcolor(grid, uExplicitCfl);
title('Explicit CFL')
colorbar()
show()

tImplicit = linspace(0, 1, len(energyImplicit))
tExplicitNoCfl = linspace(0,1,len(energyExplicitNoCfl))
tExplicitCfl = linspace(0,1,len(energyExplicitCfl))

plot(tImplicit, energyImplicit, label='Implicit')
plot(tExplicitNoCfl, energyExplicitNoCfl, label='Explicit (No CFL)')
plot(tExplicitCfl, energyExplicitCfl, label='Explicit (CFL)')
ylim([-3,3])
xlabel('Time (t)')
ylabel('Energy(E)')
legend()
show()
