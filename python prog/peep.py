def peep(i):
	[(x,l) for x in i for l in i]
	return x,l
it = iter(range(5))
x,it1 = peep(it)
print x,list(it1)