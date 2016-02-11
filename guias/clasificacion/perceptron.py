


class Perceptron(object):
	
	def __init__(self):
		self.alfa = 1
		self.pesos = [0,0,0]

	def entrenar(self, x, y):
		total = 0
		for i in xrange(len(self.pesos)):
			total += self.pesos[i] * x[i]
		print str(x) + " * " + str(self.pesos) + " = " + str(total)
		print "\n"
		if ((total > 0 and y < 0) or (total <= 0 and y > 0)):
			signo = self.alfa * y
			for i in xrange(len(self.pesos)):
				self.pesos[i] += (signo * x[i])
			return False
		else:
			return True
		
	def __str__(self):
		return str(self.pesos)
	

def problema():
	x0 = [1,2,1]
	x1 = [1,3,-1]
	x2 = [1,-2,2]
	x3 = [1,2,-1]
	y0 = -1
	y1 = 1
	y2 = -1
	y3 = 1
	
	x = [x0,x1,x2,x3]
	y = [y0,y1,y2,y3]
	bien = False
	p = Perceptron()
	while (not bien):
		puedeSer = True
		for i in xrange(len(x)):
			puedeSer = puedeSer and p.entrenar(x[i],y[i])
		bien = puedeSer
		
	
	print p

problema()
