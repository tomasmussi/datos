
def hash0(x):
	return (2*x) % 7
	
def hash1(x):
	return (3*x) % 7

def hash2(x):
	return (4*x) % 7
	
def eval(countmin, i):
	x0 = hash0(i)
	x1 = hash1(i)
	x2 = hash2(i)
	l = [countmin[0][x0], countmin[1][x1],countmin[2][x2] ]
	return max(l)

countmin = []
for i in range(3):
	l = [0,0,0,0,0,0,0]
	countmin.append(l)

stream = [ 2,3,1,8,6,4,9,7,10,6]
for i in stream:
	x0 = hash0(i)
	x1 = hash1(i)
	x2 = hash2(i)
	countmin[0][x0] += 1
	countmin[1][x1] += 1
	countmin[2][x2] += 1
	

