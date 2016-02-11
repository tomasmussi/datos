

def calculo(t):
	cuenta = 0
	for i in xrange(t,75,10):
		cuenta += 1
	print "Para t = %d tengo cuenta= %d" % (t, cuenta)
	return 75 * (2 * cuenta -1)
	
def computo(lista):
	suma = 0
	for i in lista:
		suma += calculo(i)
	return (float(suma) / len(lista)) - 565
	

