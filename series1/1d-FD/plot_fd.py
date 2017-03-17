import numpy, pylab
u = numpy.loadtxt("u_fd.txt")
x = numpy.linspace(0,1,len(u))
pylab.plot(x, u, '-o', label='$u(x)$')
pylab.plot(x, (2*numpy.pi)**(-2) * numpy.sin(2*numpy.pi*x), label='$\\frac{1}{(2\\pi)^2}\sin(x)$')
pylab.xlabel("x")
pylab.legend()
pylab.show()
