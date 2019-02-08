
import numpy
import scipy.integrate

data = numpy.loadtxt('dataThief.txt', delimiter=',')
inverted_ys = []
for y in data[:,1]:
    inverted_ys.append(1.0 / y)
simp = scipy.integrate.simps(x=data[:,0], y=inverted_ys)
simp /= 8.962
print(simp)

