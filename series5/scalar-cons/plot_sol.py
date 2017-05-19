import numpy, pylab, sys

basename = sys.argv[1]
u = numpy.loadtxt("%s.txt" % basename)
x = numpy.linspace(-2,2,len(u))
pylab.plot(x, u, '-o', label='$u(x)$', drawstyle='steps-mid')
pylab.xlabel("x")
pylab.legend()
pylab.show()
