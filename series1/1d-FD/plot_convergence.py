from numpy import *
from pylab import *
errors = loadtxt("errors_fd.txt")
resolutions = loadtxt("resolutions_fd.txt")
print("Approximate order: %1.2f" %
      round(polyfit(log(resolutions), log(errors), 1)[0], 2))

loglog(resolutions, errors, '-o', label="$||u_N-u||_\\infty$")
legend()
ylabel("errors")
xlabel("$N$")
grid("on")
show()

