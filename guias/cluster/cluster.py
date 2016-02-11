


def distancia(p1,p2):
	return ((p1[0] - p2[0]) ** 2) + ((p1[1] - p2[1]) ** 2)



def clusteroide(lista):
	d = float('inf')
	min = None
	for x in xrange(len(lista)):
		suma = 0
		for y in xrange(len(lista)):
			suma += distancia(lista[x], lista[y])
		if (suma < d):
			d = suma
			min = lista[x]
	return min
	
def ejec():
	a = (1,6,'a')
	b = (3,7,'b')
	c = (4,3,'c')
	d = (7,7,'d')
	e = (8,2,'e')
	f = (9,5,'f')
	
	lista = [a,b,c,d]
	print "clusteroide de " + str([x[2] for x in lista]) + "\t\t" + str(clusteroide(lista)[2])
	
	lista = [a,b,c,d]
	print "clusteroide de " + str([x[2] for x in lista]) + "\t\t" + str(clusteroide(lista)[2])
	
	lista = [c,d,e,f]	
	print "clusteroide de " + str([x[2] for x in lista]) + "\t\t" + str(clusteroide(lista)[2])
	
	lista = [a,b,c,d]
	print "clusteroide de " + str([x[2] for x in lista]) + "\t\t" + str(clusteroide(lista)[2])
			

ejec()
