import operator
c1 = "VPWBLWTSRCIXUS"
c2 = "ZTUWWIKZQNZZQS"
c3 = "QPPGDRKGIPZKFO"

def one_time_pad():
	uno_dos = []
	for i in xrange(len(c1)):
		#print str(ord(c1[i]) ^ ord(c2[i])) + "\t\t" + str(ord(c2[i]) ^ ord(c3[i])) + "\t\t" + str(ord(c1[i]) ^ ord(c3[i]))
		uno_dos.append(ord(c2[i]) ^ ord(c1[i]))
		
	for i in xrange(len(c1)):
		print chr(uno_dos[i] ^ ord(c1[i]))
		
	print "\n\n\n"
		
	for i in xrange(len(c2)):
		print chr(uno_dos[i] ^ ord(c2[i]))
		

def main():
	one_time_pad()

	
main()
