from numpy import *
from pylab import *
import sys

basename = sys.argv[1]
method = sys.argv[2]
L1errors = loadtxt("%s_L1errors_%s.txt" %(basename, method))
Linferrors = loadtxt("%s_Linferrors_%s.txt" %(basename, method))
resolutions = loadtxt("%s_resolutions.txt" %basename)
print("Approximate order for L1: %1.2f" %
      round(polyfit(log(resolutions), log(L1errors), 1)[0], 2))
print("Approximate order for Linf: %1.2f" %
      round(polyfit(log(resolutions), log(Linferrors), 1)[0], 2))

loglog(resolutions, L1errors, '-o', label="$||u_h-u_{ex}||_{L1}$")
loglog(resolutions, Linferrors, '-*', label="$||u_h-u_{ex}||_\\inf$")
legend()
ylabel("errors")
xlabel("$N$")
grid("on")
title("Convergence for %s with %s scheme" %(basename, method))
show()

