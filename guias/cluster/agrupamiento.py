
def distancia(p1,p2):
	return ((p1[0] - p2[0]) ** 2) + ((p1[1] - p2[1]) ** 2)


def agrupar(lista):
	dist = float('inf')
	min = None	
	for x in xrange(len(lista)):
		for j in xrange(x + 1,len(lista)):
			d = distancia(lista[x], lista[j])
			if (d < dist):
				dist = d
				min = (lista[x], lista[j])
			"""elif (d == dist):
				print "DISTANCIAS IGUALES: " + str(min)
				print str(lista[x]) + "\t" +  str(lista[j])"""
	return min
	
	
def ejec():
	l = []
	l.append((0,0,'a'))
	l.append((10,10,'b'))
	l.append((21,21,'c'))
	l.append((33,33,'d'))
	l.append((5,27,'e'))
	l.append((28,6,'f'))
	while (len(l) != 1):
		min = agrupar(l)
		print min[0][2] + min[1][2]
		l.remove(min[0])
		l.remove(min[1])
		x = (min[0][0] + min[1][0]) / 2.0
		y = (min[0][1] + min[1][1]) / 2.0
		t = (x,y,min[0][2] + min[1][2])
		l.append(t)
		
		"""
		A,B,C}
b) 	{C,D}
c) 	{A,E}
d) 	{A,B,D,E}
"""
ejec()
