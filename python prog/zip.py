def zip_n(l1,l2):
	return [(x,y) for x in l1 for y in l2 if l1.index(x) == l2.index(y)]
print zip_n([1, 2, 3,4,5], ["a", "b", "c",'e'])

def map(f,l):
	return [f(x) for x in l]
def squire(x):return x*x

print map(squire,range(5))

def fliter(f,l):
	return [x for x in l if f(x) == True]
def env(x):return x%2 == 0
print fliter(env,range(10))
print 2**4
def triplets(n):
	r = range(n)
	return [(a,b,c) for a in r for b in range(a,n) for c in range(b,n) if a+ b == c if a*b*c != 0]
print triplets(5)

def enumerate(l):
	return [(a,b) for a in range(len(l)) for b in l if a==l.index(b)]
print enumerate(["a", "b", "c"])