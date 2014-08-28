def produce(x,n):
	if n==0:
		return 0
	else:
		return x+produce(x,n-1)
print produce(0,10)